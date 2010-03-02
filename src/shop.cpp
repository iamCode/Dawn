/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

#include "shop.h"
#include <sstream>
#include "Player.h"
#include <cassert>
#include <memory>

Shop::Shop( Player *player_, CNPC *shopkeeper_)
	:	player( player_ ),
        shopkeeper( shopkeeper_ ),
		visible(false),
		currentTab( 0 ),
		posX( 30 ),
		posY( 80 ),
		floatingSelection( NULL ),
		backpackFieldWidth( 32 ),
		backpackFieldHeight( 32 ),
		backpackSeparatorWidth( 3 ),
		backpackSeparatorHeight( 3 ),
		backpackOffsetX( 67 ),
		backpackOffsetY( 56 ),
		numSlotsX( 10 ),
		numSlotsY( 6 )
		{
		    tabs[0].tabimage.texture.reserve(1);
            tabs[0].tabimage.LoadIMG("data/interface/Shop/weapontab.tga",0);
            tabs[0].height = 128;
            tabs[0].width = 128;

            tabs[0].posX = 61 + posX;
            tabs[0].posY = 264 + posY;

            tabs[1].tabimage.texture.reserve(1);
            tabs[1].tabimage.LoadIMG("data/interface/Shop/armortab.tga",0);
            tabs[1].height = 128;
            tabs[1].width = 128;
            tabs[1].posX = 202 + posX;
            tabs[1].posY = 264 + posY;

            tabs[2].tabimage.texture.reserve(1);
            tabs[2].tabimage.LoadIMG("data/interface/Shop/misctab.tga",0);
            tabs[2].height = 128;
            tabs[2].width = 128;
            tabs[2].posX = 343 + posX;
            tabs[2].posY = 264 + posY;

		    loadShopkeeperInventory();
            loadTextures();

            slotUsed = new bool**[3];
            for ( size_t curItemTab=0; curItemTab<3; ++curItemTab ) {
                slotUsed[ curItemTab ] = new bool*[numSlotsX];
                for ( size_t curX=0; curX<numSlotsX; ++curX ) {
                    slotUsed[ curItemTab ][ curX ] = new bool[numSlotsY];
                    for ( size_t curY=0; curY<numSlotsY; ++curY ) {
                        slotUsed[ curItemTab ][ curX ][ curY ] = false;
                    }
                }
            }
        };

bool Shop::isVisible() const
{
    return visible;
}

void Shop::setVisible( bool newVisible )
{
    visible = newVisible;
}

void Shop::loadTextures()
{
    textures.texture.reserve(2);
    textures.LoadIMG("data/interface/Shop/base.tga",0);
    textures.LoadIMG("data/white2x2pixel.tga",1);
}

void Shop::loadShopkeeperInventory()
{

}

void Shop::draw()
{
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                      world_x + posX, textures.texture[0].width, world_y + posY, textures.texture[0].height);
    drawTabs();
    drawItems();
}

void Shop::drawTabs()
{
    DrawingHelpers::mapTextureToRect( tabs[currentTab].tabimage.texture[0].texture,
                                      world_x + tabs[currentTab].posX, tabs[currentTab].width , world_y + tabs[currentTab].posY, tabs[currentTab].height );
}

void Shop::drawItems()
{
    size_t numItems = shopkeeperInventory[currentTab].size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		InventoryItem *curInvItem = shopkeeperInventory[ currentTab ][ curItemNr ];
		Item *curItem = curInvItem->getItem();
		CTexture *symbolTexture = curItem->getSymbolTexture();

		size_t invPosX = curInvItem->getInventoryPosX();
		size_t invPosY = curInvItem->getInventoryPosY();
		size_t sizeX = curItem->getSizeX();
		size_t sizeY = curItem->getSizeY();

		GLfloat shade[4] = { 0.0f, 0.0f, 0.0f, 0.1f };

		// if the item is equippable for the player and if we can afford it,
		// we draw a green backdrop. If not, a red backdrop.
		if ( curInvItem->isLevelReqMet() && ( player->getCoins() >= curItem->getValue() ) )
		{
		    shade[1] = 1.0f; // green color
        } else {
            shade[0] = 1.0f; // red color
        }

        glColor4fv(shade);
        DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                          world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);

        glColor4f(1.0f,1.0f,1.0f,1.0f);

		DrawingHelpers::mapTextureToRect( symbolTexture->texture[0].texture,
		                                  world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);
        }
}

void Shop::drawItemTooltip( int x, int y )
{
    // draws tooltip over item in the shop
    if ( isOnSlotsScreen(x,y) && isVisible() && floatingSelection == NULL ) {
        InventoryItem *tooltipItem;
        int fieldIndexX = ( x - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( y - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        if ( !isPositionFree( fieldIndexX, fieldIndexY, currentTab ) ) {
            // draw tooltip of the current item in the shop.
            tooltipItem = getItemAt( fieldIndexX, fieldIndexY, currentTab );
            tooltipItem->getTooltip()->setShopItem( true );
            tooltipItem->getTooltip()->draw( x, y );

            //if player is holding down right shift and has an
            // item with same slot equipped, we draw that too.
            Uint8 *keys;
            keys = SDL_GetKeyState(NULL);
            int equippedItemOffset = 0;
            if ( keys[SDLK_LSHIFT] )
            {
                std::vector<InventoryItem*> playersInventory = player->getInventory()->getEquippedItems();
                for ( size_t curItem = 0; curItem < playersInventory.size(); curItem++ )
                {
                    if ( playersInventory[ curItem ]->getItem()->getEquipPosition() == tooltipItem->getItem()->getEquipPosition() )
                    {
                        equippedItemOffset += tooltipItem->getTooltip()->getTooltipWidth() + 30;
                        playersInventory[ curItem ]->getTooltip()->draw( x + equippedItemOffset, y );
                    }
                }
            }
        }
    }
}

void Shop::drawFloatingSelection( int x, int y )
{
	// draw floating selection
	if ( floatingSelection != NULL ) {
		Item *floatingItem = floatingSelection->getItem();
		size_t sizeX = floatingItem->getSizeX();
		size_t sizeY = floatingItem->getSizeY();

		DrawingHelpers::mapTextureToRect( floatingItem->getSymbolTexture()->texture[0].texture,
		                                  x, backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  y-20, backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);
	}
}

void Shop::clicked( int clickX, int clickY, uint8_t mouseButton )
{
    if ( isOnSlotsScreen( clickX, clickY ) )
    {
        if ( hasFloatingSelection() )
        {
            sellToShop( getFloatingSelection(), false );
            unsetFloatingSelection();
            return;
        }

        int fieldIndexX = ( clickX - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( clickY - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        if ( !isPositionFree( fieldIndexX, fieldIndexY, currentTab ) )
        {
            InventoryItem *curItem = getItemAt( fieldIndexX, fieldIndexY, currentTab );
            if ( player->getCoins() >= curItem->getItem()->getValue() )
            {
                if ( mouseButton == SDL_BUTTON_RIGHT ) {
                    // direct buy on right button
                    bool inserted = player->getInventory()->insertItem( curItem->getItem() );
                    if ( inserted ) {
                        floatingSelection = curItem;
                        removeItem( floatingSelection );
                        buyFromShop();
                    }
                } else {
                    // add pick up item on left click
                    floatingSelection = curItem;
                    removeItem( floatingSelection );
                }
            }
        }
        return;
    }

    // loop through our tabs, see if any got clicked.
    for (size_t tabIndex = 0; tabIndex <= 2; tabIndex++) {
        if ( clickX > tabs[tabIndex].posX
            && clickY > tabs[tabIndex].posY
            && clickX < tabs[tabIndex].posX + tabs[tabIndex].width
            && clickY < tabs[tabIndex].posY + tabs[tabIndex].height ) {
            currentTab = tabIndex;
            return;
        }
    }

    if ( !isOnSlotsScreen( clickX, clickY ) )
    {
        if ( hasFloatingSelection() )
        {
            sellToShop( getFloatingSelection(), false );
            unsetFloatingSelection();
            return;
        }
    }
}

bool Shop::isOnThisScreen( int x, int y ) const
{
    if ( x < posX
	     || y < posY
	     || x > posX + textures.texture[0].width
	     || y > posY + textures.texture[0].height ) {
		return false;
	}
	return true;

}

bool Shop::isOnSlotsScreen( int x, int y )
{
	if ( x < static_cast<int>(posX + backpackOffsetX)
	     || y < static_cast<int>(posY + backpackOffsetY)
	     || x > static_cast<int>(posX + backpackOffsetX + backpackFieldWidth * numSlotsX + (numSlotsX-1)*backpackSeparatorWidth)
	     || y > static_cast<int>(posY + backpackOffsetY + backpackFieldHeight * numSlotsY + (numSlotsY-1)*backpackSeparatorHeight) ) {
		return false;
	}
	return true;
}

bool Shop::isPositionFree( size_t invPosX, size_t invPosY, size_t curTab ) const
{
	if ( invPosX >= numSlotsX || invPosY >= numSlotsY ) {
		return false;
	}

	return ( !slotUsed[ curTab ][ invPosX ][ invPosY ] );
}

void Shop::addItem( Item *item )
{
	InventoryItem invItem( item, 0, 0, player );
	sellToShop( &invItem, false );
}

void Shop::sellToShop( InventoryItem *sellItem, bool givePlayerMoney )
{
	Item *item = sellItem->getItem();

	size_t itemSizeX = item->getSizeX();
	size_t itemSizeY = item->getSizeY();

	size_t itemTab = getItemTab( item );

	bool foundPosition = false;
	size_t foundX = 0;
	size_t foundY = 0;

	// look for next free position
	for ( size_t freeX=0; freeX<numSlotsX-itemSizeX+1 && !foundPosition; ++freeX ) {
		for ( size_t freeY=0; freeY<numSlotsY-itemSizeY+1 && !foundPosition; ++freeY ) {
			if ( hasSufficientSpaceAt( freeX, freeY, itemSizeX, itemSizeY, itemTab ) ) {
				foundPosition = true;
				foundX = freeX;
				foundY = freeY;
			}
		}
	}

	if ( foundPosition ) {
		InventoryItem *newItem = new InventoryItem( item, foundX, foundY, player );
        insertItemAt( newItem, foundX, foundY, itemTab );
	}

	if ( givePlayerMoney ) {
	    player->giveCoins( sellItem->getItem()->getValue() * 0.75 );
	    // player only gets 75% of the itemvalue when he sells an item
	}
}

void Shop::buyFromShop()
{
    player->reduceCoins( floatingSelection->getItem()->getValue() );

    delete floatingSelection;
    floatingSelection = NULL;
}

void Shop::insertItemAt( InventoryItem *inventoryItem, size_t invPosX, size_t invPosY, size_t itemTab )
{
	assert( hasSufficientSpaceAt( invPosX, invPosY, inventoryItem->getSizeX(), inventoryItem->getSizeY(), itemTab ) );
	inventoryItem->setInventoryPos( invPosX, invPosY );
	shopkeeperInventory[itemTab].push_back( inventoryItem );

	size_t inventoryMaxX = invPosX + inventoryItem->getSizeX() - 1;
	size_t inventoryMaxY = invPosY + inventoryItem->getSizeY() - 1;

	for ( size_t curX=invPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=invPosY; curY<=inventoryMaxY; ++curY ) {
			slotUsed[itemTab][ curX ][ curY ] = true;
		}
	}
}

InventoryItem* Shop::getItemAt( size_t invPosX, size_t invPosY, size_t itemTab )
{
	assert( ! isPositionFree( invPosX, invPosY, itemTab ) );

	size_t numBackItems = shopkeeperInventory[ itemTab ].size();
	for ( size_t curBackItemNr=0; curBackItemNr<numBackItems; ++curBackItemNr ) {
		InventoryItem *curItem = shopkeeperInventory[ itemTab ][ curBackItemNr ];
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

size_t Shop::getItemTab( Item *item )
{
    switch ( item->getItemType() )
    {
        case ItemType::MISCELLANEOUS:
            return 2;
        break;
        case ItemType::ARMOR:
            return 1;
        break;
        case ItemType::WEAPON:
            if ( item->getWeaponType() == WeaponType::SHIELD ) // this is to get all shields into the secondary tab.
            {
                return 1;
            }
            return 0;
        break;
        case ItemType::JEWELRY:
            return 2;
        break;
        case ItemType::SCROLL:
            return 2;
        break;
        case ItemType::POTION:
            return 2;
        break;
        case ItemType::FOOD:
            return 2;
        break;
        case ItemType::DRINK:
            return 2;
        break;
        case ItemType::NEWSPELL:
            return 2;
        break;
        default:
            return 0;
        break;
    }
}

bool Shop::hasFloatingSelection() const
{
    return floatingSelection != NULL;
}

void Shop::unsetFloatingSelection()
{
    assert( floatingSelection != NULL );

    delete floatingSelection;
    floatingSelection = NULL;
}

InventoryItem *Shop::getFloatingSelection() const
{
    return floatingSelection;
}

bool Shop::hasSufficientSpaceAt( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY, size_t itemTab ) const
{
	size_t inventoryMaxX = inventoryPosX + itemSizeX - 1;
	size_t inventoryMaxY = inventoryPosY + itemSizeY - 1;
	if ( (inventoryMaxX >= numSlotsX) || (inventoryMaxY >= numSlotsY) ) {
		return false;
	}


    for ( size_t curX=inventoryPosX; curX<=inventoryMaxX; ++curX ) {
		for ( size_t curY=inventoryPosY; curY<=inventoryMaxY; ++curY ) {
			if ( slotUsed[ itemTab][ curX ][ curY ] ) {
				return false;
			}
		}
	}

	return true;
}

void Shop::removeItem( InventoryItem *inventoryItem )
{
	for ( size_t curTab = 0; curTab < 3; ++curTab ) {
	    for ( size_t curBackpackItemNr=0; curBackpackItemNr<shopkeeperInventory[curTab].size(); ++curBackpackItemNr ) {
            if ( shopkeeperInventory[ curTab ][ curBackpackItemNr ] == inventoryItem ) {
                for ( size_t curX=inventoryItem->getInventoryPosX(); curX<inventoryItem->getInventoryPosX() + inventoryItem->getSizeX(); ++curX ) {
                    for ( size_t curY=inventoryItem->getInventoryPosY(); curY<inventoryItem->getInventoryPosY() + inventoryItem->getSizeY(); ++curY ) {
                        slotUsed[curTab][curX][curY] = false;
                    }
                }
                shopkeeperInventory[ curTab ][ curBackpackItemNr ] = shopkeeperInventory[ curTab ][ shopkeeperInventory[curTab].size() - 1 ];
                shopkeeperInventory[ curTab ].resize( shopkeeperInventory[ curTab ].size() - 1 );
            }
	    }
	}
}

void currency::exchangeCoins( uint32_t &copper, uint32_t &silver, uint32_t &gold, uint32_t &coins )
{
    // exchanging coins to copper coins.
    copper = coins%100;
    coins -= copper;
    if ( coins == 0 )
        return;

    coins /= 100;
    silver =  coins%100;
    coins -= silver;
    if ( coins == 0 )
        return;

    gold = coins/100;
}

std::string currency::convertCoinsToString( currency::currency currency, uint32_t coins )
{
    std::stringstream ss;
    std::string output;

    uint32_t copper = 0, silver = 0, gold = 0;

    exchangeCoins( copper, silver, gold, coins );

    switch ( currency )
    {
        case currency::COPPER:
            ss << copper;
        break;
        case currency::SILVER:
            ss << silver;
        break;
        case currency::GOLD:
            ss << gold;
        break;
    };

    output = ss.str();

    return output;
}

extern std::auto_ptr<Shop> shopWindow;

namespace DawnInterface
{
	Shop *addShop()
	{
		return shopWindow.get();
	}
}


