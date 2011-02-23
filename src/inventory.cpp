/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "inventory.h"

#include "item.h"
#include "CCharacter.h"
#include "Player.h"
#include "globals.h"

#include <cassert>


InventoryItem::InventoryItem( Item *item, size_t inventoryPosX, size_t inventoryPosY, Player *player, InventoryItem *copyFrom )
    :   item( item ),
		player( player ),
        currentStackSize( 1 ),
		inventoryPosX( inventoryPosX ),
		inventoryPosY( inventoryPosY )
{
    // copy properties from the original inventoryItem (if we've suggested so)
    if ( copyFrom != NULL ) {
        copyAttributes( copyFrom );
    }
    tooltip = new itemTooltip(item, this, player);
}

InventoryItem::~InventoryItem()
{
    delete tooltip;
}

size_t InventoryItem::getInventoryPosX() const
{
	return inventoryPosX;
}

size_t InventoryItem::getInventoryPosY() const
{
	return inventoryPosY;
}

void InventoryItem::setInventoryPos( size_t inventoryPosX_, size_t inventoryPosY_ )
{
	inventoryPosX = inventoryPosX_;
	inventoryPosY = inventoryPosY_;
}

size_t InventoryItem::getSizeX() const
{
	return item->getSizeX();
}

size_t InventoryItem::getSizeY() const
{
	return item->getSizeY();
}

Item* InventoryItem::getItem() const
{
	return item;
}

itemTooltip* InventoryItem::getTooltip() const
{
    return tooltip;
}

/// Class Inventory

Inventory::Inventory( size_t sizeX_, size_t sizeY_, Player *player_ )
        :   player( player_ )
{
	size_t numEquippable = static_cast<size_t>( ItemSlot::COUNT );
	equippedItems = new InventoryItem* [ numEquippable ];
	for ( size_t curEquippable=0; curEquippable<numEquippable; ++curEquippable ) {
		equippedItems[ curEquippable ] = NULL;
	}

	sizeX = sizeX_;
	sizeY = sizeY_;

	slotUsed = new bool*[sizeX];
	for ( size_t curX=0; curX<sizeX; ++curX ) {
		slotUsed[ curX ] = new bool[sizeY];
		for ( size_t curY=0; curY<sizeY; ++curY ) {
			slotUsed[ curX ][ curY ] = false;
		}
	}
}

Inventory::~Inventory()
{
	delete[] equippedItems;

	for ( size_t curX=0; curX<sizeX; ++curX ) {
		delete[] slotUsed[ curX ];
	}
	delete[] slotUsed;
}

bool Inventory::stackItemIfPossible( Item *item, InventoryItem *itemToStack ) const
{
    if ( item->isItemStackable() == true ) {
        std::vector<InventoryItem*> fittingItemsToStack = getIdenticalItemsFromBackpack( item );
        for ( size_t curItem = 0; curItem < fittingItemsToStack.size(); curItem++ ) {
            if ( itemToStack != NULL ) { /// checking for suitable item to stack when we have an InventoryItem to account for
                if ( itemToStack->getCurrentStackSize() + fittingItemsToStack[ curItem ]->getCurrentStackSize() <= item->getMaxStackSize() ) {
                    fittingItemsToStack[ curItem ]->setCurrentStackSize( itemToStack->getCurrentStackSize() + fittingItemsToStack[ curItem ]->getCurrentStackSize() );
                    return true;
                }
            } else { /// else we just check for an item that fits that isn't already full.
                if ( fittingItemsToStack[ curItem ]->isItemStackFull() == false ) {
                    fittingItemsToStack[ curItem ]->increaseCurrentStack();
                    return true;
                }
            }
        }
    }
    return false;
}

bool Inventory::insertItem( Item *item, InventoryItem *oldInventoryItem )
{
    /// if the item is stackable, we will try and add it to an existing item's stack, if such an item exists in the inventory.
    bool ableToStackTheItem = stackItemIfPossible( item, oldInventoryItem );
    if ( ableToStackTheItem == true ) {
        return true;
    }

	size_t itemSizeX = item->getSizeX();
	size_t itemSizeY = item->getSizeY();

	bool foundPosition = false;
	size_t foundX = 0;
	size_t foundY = 0;

	// look for next free position
	for ( size_t freeX=0; freeX<sizeX-itemSizeX+1 && !foundPosition; ++freeX ) {
		for ( size_t freeY=0; freeY<sizeY-itemSizeY+1 && !foundPosition; ++freeY ) {
			if ( hasSufficientSpaceAt( freeX, freeY, itemSizeX, itemSizeY ) ) {
				foundPosition = true;
				foundX = freeX;
				foundY = freeY;
			}
		}
	}

	if ( ! foundPosition ) {
		return false;
	}

    InventoryItem *newInvItem = new InventoryItem( item, foundX, foundY, player, oldInventoryItem );
    insertItemAt( newInvItem, foundX, foundY );
    return true;
}

bool Inventory::hasSufficientSpaceAt( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY ) const
{
	size_t inventoryMaxX = inventoryPosX + itemSizeX - 1;
	size_t inventoryMaxY = inventoryPosY + itemSizeY - 1;
	if ( (inventoryMaxX >= sizeX) || (inventoryMaxY >= sizeY) ) {
		return false;
	}

	for ( size_t curX=inventoryPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=inventoryPosY; curY<=inventoryMaxY; ++curY ) {
			if ( slotUsed[ curX ][ curY ] ) {
				return false;
			}
		}
	}

	return true;
}

bool Inventory::hasSufficientSpaceWithExchangeAt( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY )
{
	size_t inventoryMaxX = inventoryPosX + itemSizeX - 1;
	size_t inventoryMaxY = inventoryPosY + itemSizeY - 1;
	InventoryItem* firstBlockingItemFound = NULL;
	if ( (inventoryMaxX >= sizeX) || (inventoryMaxY >= sizeY) ) {
		return false;
	}

	for ( size_t curX=inventoryPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=inventoryPosY; curY<=inventoryMaxY; ++curY ) {
			if ( slotUsed[ curX ][ curY ] ) {
				InventoryItem* curBlockinItemFound = getItemAt( curX, curY );
				if ( firstBlockingItemFound == NULL ) {
					firstBlockingItemFound = curBlockinItemFound;
				}
				else if ( firstBlockingItemFound != curBlockinItemFound ) {
					return false;
				}
			}
		}
	}

	return true;
}

InventoryItem* Inventory::findFirstBlockingItem( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY )
{
	size_t inventoryMaxX = inventoryPosX + itemSizeX - 1;
	size_t inventoryMaxY = inventoryPosY + itemSizeY - 1;
	assert ( (inventoryMaxX < sizeX) && (inventoryMaxY < sizeY) );

	for ( size_t curX=inventoryPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=inventoryPosY; curY<=inventoryMaxY; ++curY ) {
			if ( slotUsed[ curX ][ curY ] ) {
				InventoryItem *curBlockinItemFound = getItemAt( curX, curY );
				return curBlockinItemFound;
			}
		}
	}

	return NULL;
}

std::vector<InventoryItem*> Inventory::getEquippedItems() const
{
	std::vector<InventoryItem*> allEquippedItems;
	for ( size_t curSlotNr=0; curSlotNr < static_cast<size_t>( ItemSlot::COUNT ); ++curSlotNr ) {
		if ( equippedItems[ curSlotNr ] != NULL ) {
			allEquippedItems.push_back( equippedItems[ curSlotNr ] );
		}
	}
	return allEquippedItems;
}

std::vector<InventoryItem*> Inventory::getBackpackItems() const
{
	return backpackItems;
}

void Inventory::wieldItemAtSlot( ItemSlot::ItemSlot slotToUse, InventoryItem *item )
{
    assert( (item == NULL) || (item->getItem()->getEquipPosition() == Inventory::getEquipType( slotToUse )) );

    if ( item != NULL ) {
        // if we have equipped a two-handed weapon and replacing it with an item in mainhand or offhand, we need to set the off-hand slot to NULL
        if ( slotToUse == ItemSlot::MAIN_HAND || slotToUse == ItemSlot::OFF_HAND ) {
            if ( isWieldingTwoHandedWeapon() == true ) {
                equippedItems[ static_cast<size_t>( ItemSlot::MAIN_HAND ) ] = NULL;
                equippedItems[ static_cast<size_t>( ItemSlot::OFF_HAND ) ] = NULL;
            }
        }

        // if the item we're about to equip is a two-handed weapon, we also put that item in the off-hand slot.
        if ( item->getItem()->isTwoHandedWeapon() == true ) {
            equippedItems[ static_cast<size_t>( ItemSlot::OFF_HAND ) ] = item;
        }
    } else {
        // if we're removing a two-handed weapon, we also need to set the off-hand slot to NULL.
        if ( ( slotToUse == ItemSlot::MAIN_HAND || slotToUse == ItemSlot::OFF_HAND ) && isWieldingTwoHandedWeapon() == true ) {
            equippedItems[ static_cast<size_t>( ItemSlot::MAIN_HAND ) ] = NULL;
            equippedItems[ static_cast<size_t>( ItemSlot::OFF_HAND ) ] = NULL;
        }
    }

    equippedItems[ static_cast<size_t>( slotToUse ) ] = item;

    // this will seed a new ticket to the item and spell tooltips, telling them to reload their data.
    player->setTicketForItemTooltip();
    player->setTicketForSpellTooltip();
}

InventoryItem* Inventory::getItemAtSlot( ItemSlot::ItemSlot slotToUse )
{
	return equippedItems[ static_cast<size_t>( slotToUse ) ];
}

bool Inventory::isPositionFree( size_t invPosX, size_t invPosY ) const
{
	if ( invPosX >= sizeX || invPosY >= sizeY ) {
		return false;
	}

	return ( !slotUsed[invPosX][invPosY] );
}

InventoryItem* Inventory::getItemAt( size_t invPosX, size_t invPosY )
{
	assert( ! isPositionFree( invPosX, invPosY ) );

	size_t numBackItems = backpackItems.size();
	for ( size_t curBackItemNr=0; curBackItemNr<numBackItems; ++curBackItemNr ) {
		InventoryItem *curItem = backpackItems[ curBackItemNr ];
		size_t itemPosX = curItem->getInventoryPosX();
		size_t itemPosY = curItem->getInventoryPosY();
		size_t itemSizeX = curItem->getItem()->getSizeX();
		size_t itemSizeY = curItem->getItem()->getSizeY();

		if ( itemPosX <= invPosX && itemPosX + itemSizeX > invPosX
		     && itemPosY <= invPosY && itemPosY + itemSizeY > invPosY ) {
			return curItem;
		}
	}

	// should have found an item so should never reach here
	abort();
}

void InventoryItem::copyAttributes( InventoryItem *copyFrom )
{
    currentStackSize = copyFrom->getCurrentStackSize();
}

bool Inventory::isWieldingTwoHandedWeapon() const
{
    if ( equippedItems[ static_cast<size_t>( ItemSlot::MAIN_HAND ) ] != NULL ) {
        return equippedItems[ static_cast<size_t>( ItemSlot::MAIN_HAND ) ]->getItem()->isTwoHandedWeapon();
    }

    return false;
}

WeaponType::WeaponType Inventory::getWeaponTypeBySlot( ItemSlot::ItemSlot itemSlot ) const
{
    if ( equippedItems[ static_cast<size_t>( itemSlot ) ] == NULL ) {
        return WeaponType::NO_WEAPON;
    }
    return equippedItems[ static_cast<size_t>( itemSlot ) ]->getItem()->getWeaponType();
}

std::vector<InventoryItem*> Inventory::getIdenticalItemsFromBackpack( Item *item ) const
{
    std::vector<InventoryItem*> ourItems;
    for ( size_t curBackpackItemNr=0; curBackpackItemNr<backpackItems.size(); ++curBackpackItemNr ) {
		if ( backpackItems[ curBackpackItemNr ]->getItem() == item ) {
			ourItems.push_back( backpackItems[ curBackpackItemNr ] );
		}
	}
	return ourItems;
}

bool Inventory::containsItem( InventoryItem *inventoryItem ) const
{
	for ( size_t curBackpackItemNr=0; curBackpackItemNr<backpackItems.size(); ++curBackpackItemNr ) {
		if ( backpackItems[ curBackpackItemNr ] == inventoryItem ) {
			return true;
		}
	}
	return false;
}

void Inventory::removeItem( InventoryItem *inventoryItem )
{
	for ( size_t curBackpackItemNr=0; curBackpackItemNr<backpackItems.size(); ++curBackpackItemNr ) {
		if ( backpackItems[ curBackpackItemNr ] == inventoryItem ) {
			for ( size_t curX=inventoryItem->getInventoryPosX(); curX<inventoryItem->getInventoryPosX() + inventoryItem->getSizeX(); ++curX ) {
				for ( size_t curY=inventoryItem->getInventoryPosY(); curY<inventoryItem->getInventoryPosY() + inventoryItem->getSizeY(); ++curY ) {
					slotUsed[curX][curY] = false;
				}
			}
			backpackItems[ curBackpackItemNr ] = backpackItems[ backpackItems.size() - 1 ];
			backpackItems.resize( backpackItems.size() - 1 );
		}
	}
}

void Inventory::insertItemAt( InventoryItem *inventoryItem, size_t invPosX, size_t invPosY )
{
	assert( hasSufficientSpaceAt( invPosX, invPosY, inventoryItem->getSizeX(), inventoryItem->getSizeY() ) );
	inventoryItem->setInventoryPos( invPosX, invPosY );
	backpackItems.push_back( inventoryItem );

	size_t inventoryMaxX = invPosX + inventoryItem->getSizeX() - 1;
	size_t inventoryMaxY = invPosY + inventoryItem->getSizeY() - 1;

	for ( size_t curX=invPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=invPosY; curY<=inventoryMaxY; ++curY ) {
			slotUsed[ curX ][ curY ] = true;
		}
	}
}

InventoryItem* Inventory::insertItemWithExchangeAt( InventoryItem *inventoryItem, size_t invPosX, size_t invPosY )
{
	assert( hasSufficientSpaceWithExchangeAt( invPosX, invPosY, inventoryItem->getSizeX(), inventoryItem->getSizeY() ) );
	InventoryItem *blockingItem = findFirstBlockingItem( invPosX, invPosY, inventoryItem->getSizeX(), inventoryItem->getSizeY() );

	if ( blockingItem != NULL ) {
		removeItem( blockingItem );
	}

	inventoryItem->setInventoryPos( invPosX, invPosY );
	backpackItems.push_back( inventoryItem );

	size_t inventoryMaxX = invPosX + inventoryItem->getSizeX() - 1;
	size_t inventoryMaxY = invPosY + inventoryItem->getSizeY() - 1;

	for ( size_t curX=invPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=invPosY; curY<=inventoryMaxY; ++curY ) {
			slotUsed[ curX ][ curY ] = true;
		}
	}

	return blockingItem;
}

size_t InventoryItem::getCurrentStackSize() const
{
    return currentStackSize;
}

void InventoryItem::setCurrentStackSize( size_t currentStackSize )
{
    this->currentStackSize = currentStackSize;
}

void InventoryItem::increaseCurrentStack()
{
    if ( currentStackSize < getItem()->getMaxStackSize() ) {
        currentStackSize++;
        getTooltip()->reloadTooltip();
    }
}

void InventoryItem::decreaseCurrentStack()
{
    if ( currentStackSize > 0 ) {
        currentStackSize--;
        getTooltip()->reloadTooltip();
    }
}

bool InventoryItem::isItemStackFull() const
{
    if ( currentStackSize == getItem()->getMaxStackSize() ) {
        return true;
    }
    return false;
}

std::string Inventory::getReloadText()
{
	std::ostringstream oss;
	oss << "-- Player's inventory" << std::endl;
	oss << "-- Items in Backpack" << std::endl;

	for ( size_t curBackpackNr=0; curBackpackNr<backpackItems.size(); ++curBackpackNr ) {
		InventoryItem *curBackpackItem = backpackItems[ curBackpackNr ];
		Item *curItem = curBackpackItem->getItem();
		oss << "DawnInterface.restoreItemInBackpack( itemDatabase[\"" << curItem->getID() << "\"], "
		    << curBackpackItem->getInventoryPosX() << ", " << curBackpackItem->getInventoryPosY() << ", " << curBackpackItem->getCurrentStackSize() << " );"
		    << std::endl;
	}

	oss << "-- equipped Items" << std::endl;
	size_t numEquippable = static_cast<size_t>( ItemSlot::COUNT );
	for ( size_t curEquippable=0; curEquippable<numEquippable; ++curEquippable ) {
		if ( equippedItems[ curEquippable ] != NULL ) {
			Item *curItem = equippedItems[ curEquippable ]->getItem();
			// if the item is two-handed and we're inspecting the off-hand slot, don't output it.
			if ( !( curItem->isTwoHandedWeapon() == true && curEquippable == static_cast<size_t>( ItemSlot::OFF_HAND ) ) ) {
                oss << "DawnInterface.restoreWieldItem( " << curEquippable << ", "
                    << "itemDatabase[\"" << curItem->getID() << "\"] " << ");"
                    << std::endl;
			}
		}
	}

	return oss.str();
}

void Inventory::clear()
{
	// remove backpack items
	for ( size_t curBackpackNr=0; curBackpackNr<backpackItems.size(); ++curBackpackNr ) {
		InventoryItem *curBackpackItem = backpackItems[ curBackpackNr ];
		delete curBackpackItem;
	}
	backpackItems.resize( 0 );

	// free space in inventory so we can place new items
	for ( size_t curX=0; curX<sizeX; ++ curX ) {
		for ( size_t curY=0; curY<sizeY; ++curY ) {
			slotUsed[curX][curY] = false;
		}
	}

	// remove equipped items
	size_t numEquippable = static_cast<size_t>( ItemSlot::COUNT );
	for ( size_t curEquippable=0; curEquippable<numEquippable; ++curEquippable ) {
		if ( equippedItems[ curEquippable ] != NULL ) {
            /// check if our weapon is of a two-handed type, then we need to set the other side (offhand or mainhand) to NULL aswell.
            if ( equippedItems[ curEquippable]->getItem()->isTwoHandedWeapon() == true ) {
                delete equippedItems[ curEquippable ];
                equippedItems[ ItemSlot::MAIN_HAND ] = NULL;
                equippedItems[ ItemSlot::OFF_HAND ] = NULL;
            } else {
                delete equippedItems[ curEquippable ];
            }
		}
		equippedItems[ curEquippable ] = NULL;
	}
}

namespace DawnInterface
{
	std::string getInventorySaveText()
	{
		return Globals::getPlayer()->getInventory()->getReloadText();
	}

	void restoreItemInBackpack( Item *item, int inventoryPosX, int inventoryPosY, size_t stackSize )
	{
		InventoryItem *invItem = new InventoryItem( item, inventoryPosX, inventoryPosY, Globals::getPlayer() );
		invItem->setCurrentStackSize( stackSize );
		Globals::getPlayer()->getInventory()->insertItemWithExchangeAt( invItem, inventoryPosX, inventoryPosY );
	}

	void restoreWieldItem( int slot, Item *item )
	{
		ItemSlot::ItemSlot slotToUse = static_cast<ItemSlot::ItemSlot>( slot );
		InventoryItem *invItem = new InventoryItem( item, 0, 0, Globals::getPlayer() );
		Globals::getPlayer()->getInventory()->wieldItemAtSlot( slotToUse, invItem );
	}
}

EquipPosition::EquipPosition Inventory::getEquipType( ItemSlot::ItemSlot itemSlot )
{
	switch ( itemSlot ) {
		case ItemSlot::HEAD:
			return EquipPosition::HEAD;
		case ItemSlot::AMULET:
			return EquipPosition::AMULET;
		case ItemSlot::MAIN_HAND:
			return EquipPosition::MAIN_HAND;
		case ItemSlot::OFF_HAND:
			return EquipPosition::OFF_HAND;
		case ItemSlot::BELT:
			return EquipPosition::BELT;
		case ItemSlot::LEGS:
			return EquipPosition::LEGS;
		case ItemSlot::SHOULDER:
			return EquipPosition::SHOULDER;
		case ItemSlot::CHEST:
			return EquipPosition::CHEST;
		case ItemSlot::GLOVES:
			return EquipPosition::GLOVES;
		case ItemSlot::CLOAK:
			return EquipPosition::CLOAK;
		case ItemSlot::BOOTS:
			return EquipPosition::BOOTS;
		case ItemSlot::RING_ONE:
			return EquipPosition::RING;
		case ItemSlot::RING_TWO:
			return EquipPosition::RING;
		case ItemSlot::COUNT:
			return EquipPosition::NONE;
	}
	dawn_debug_fatal("Reached end of Inventory::getEquipType without finding the given ItemSlot. This should not be.");
	abort();
}

bool InventoryItem::canPlayerUseItem() const
{
    bool useableItem = true;

    if ( player->getLevel() < item->getRequiredLevel() ) {
        useableItem = false;
    }

    if ( item->getArmorType() != ArmorType::NO_ARMOR ) {
        useableItem = player->canWearArmorType( item );
    }

    if ( item->isUseable() ) {
        if ( player->getLevel() < item->getSpell()->getRequiredLevel() ) {
            useableItem = false;
        }
        if ( player->getClass() != item->getSpell()->getRequiredClass() && item->getSpell()->getRequiredClass() != CharacterClass::ANYCLASS ) {
            useableItem = false;
        }
        if ( item->getItemType() == ItemType::NEWSPELL ) {
            if ( player->isSpellInscribedInSpellbook( item->getSpell() ) == true ) {
                useableItem = false;
            }
        }
    }

    return useableItem;
}
