/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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
#include "player.h"
#include <cassert>
#include <memory>
#include "CDrawingHelpers.h"
#include "FramesBase.h"
#include "InventoryScreen.h"
#include "configuration.h"
#include "soundengine.h"

extern std::auto_ptr<InventoryScreen> inventoryScreen;
extern std::auto_ptr<Shop> shopWindow;

namespace DawnInterface
{
	void addTextToLogWindow( GLfloat color[], const char *text, ... );
	Shop *addShop()
	{
		return shopWindow.get();
	}
}

Shop::Shop( Player *player_, CNPC *shopkeeper_) : FramesBase( 30, 80, 454, 404, 13, 15 )
{
    addMoveableFrame( 454, 21, 13, 398 );
    addCloseButton( 22, 22, 444, 398 );
    currentTab = 0;
    backpackFieldWidth = 32;
    backpackFieldHeight = 32;
    backpackSeparatorWidth = 3;
    backpackSeparatorHeight = 3;
    backpackOffsetX = 67;
    backpackOffsetY = 56;
    numSlotsX = 10;
    numSlotsY = 6;
    floatingSelection = NULL;
    player = player_;
    shopkeeper = shopkeeper_;

    tabs[0].tabimage.LoadIMG("data/interface/Shop/weapontab.tga",0);
    tabs[0].height = 128;
    tabs[0].width = 128;

    tabs[0].posX = 61;
    tabs[0].posY = 264;

    tabs[1].tabimage.LoadIMG("data/interface/Shop/armortab.tga",0);
    tabs[1].height = 128;
    tabs[1].width = 128;
    tabs[1].posX = 202;
    tabs[1].posY = 264;

    tabs[2].tabimage.LoadIMG("data/interface/Shop/misctab.tga",0);
    tabs[2].height = 128;
    tabs[2].width = 128;
    tabs[2].posX = 343;
    tabs[2].posY = 264;

    // load the font for itemstack text.
    itemStackFont = FontCache::getFontFromCache("data/verdana.ttf", 12);

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

void Shop::toggle()
{
    if ( isVisible() == false )
    {
        // this seeds a new ticket so that item tooltips will be reloaded.
        player->startShopping();
        player->setTicketForItemTooltip();
    } else {
        player->stopShopping();
    }
    FramesBase::toggle();
}

void Shop::loadTextures()
{
    textures.LoadIMG("data/interface/Shop/base.tga",0);
    textures.LoadIMG("data/white2x2pixel.tga",1);
}

void Shop::loadShopkeeperInventory()
{

}

void Shop::draw( int mouseX, int mouseY )
{
    DrawingHelpers::mapTextureToRect( textures.getTexture(0),
                                      world_x + posX, textures.getTexture(0).width, world_y + posY, textures.getTexture(0).height);
    drawTabs();
    drawItems();
    drawItemTooltip( mouseX, mouseY );
    drawFloatingSelection( mouseX, mouseY );
}

void Shop::drawTabs()
{
    DrawingHelpers::mapTextureToRect( tabs[currentTab].tabimage.getTexture(0),
                                      world_x + tabs[currentTab].posX + posX, tabs[currentTab].width , world_y + tabs[currentTab].posY + posY, tabs[currentTab].height );
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
		if ( curInvItem->canPlayerUseItem() == true && ( player->getCoins() >= curItem->getValue() ) )
		{
		    shade[1] = 1.0f; // green color
        } else {
            shade[0] = 1.0f; // red color
        }

        glColor4fv(shade);
        DrawingHelpers::mapTextureToRect( textures.getTexture(1),
                                          world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);

        glColor4f(1.0f,1.0f,1.0f,1.0f);

		DrawingHelpers::mapTextureToRect( symbolTexture->getTexture(0),
		                                  world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);

        // if we have an item that is stackable, and the stacksize is more than 1, we draw that number.
		if ( curInvItem->getCurrentStackSize() > 1 ) {
            itemStackFont->drawText( world_x + posX + backpackOffsetX + backpackFieldWidth - itemStackFont->calcStringWidth( "%d", curInvItem->getCurrentStackSize() ) + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
                                 world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
                                 "%d", curInvItem->getCurrentStackSize() );
		}
    }
}

void Shop::drawItemTooltip( int mouseX, int mouseY )
{
    // draws tooltip over item in the shop
    if ( isOnSlotsScreen(mouseX,mouseY) && isVisible() && floatingSelection == NULL ) {
        InventoryItem *tooltipItem;
        int fieldIndexX = ( mouseX - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( mouseY - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        if ( !isPositionFree( fieldIndexX, fieldIndexY, currentTab ) ) {
            // draw tooltip of the current item in the shop.
            tooltipItem = getItemAt( fieldIndexX, fieldIndexY, currentTab );
            tooltipItem->getTooltip()->setShopItem( true );
            tooltipItem->getTooltip()->draw( mouseX, mouseY );

            //if player is holding down right shift and has an
            // item with same slot equipped, we draw that too.
            Uint8 *keys;
            keys = SDL_GetKeyState(NULL);
            int thisTooltipPosX;
            int previousFrameHeight;
            bool firstItemCompared = false;
            if ( keys[SDLK_LSHIFT] )
            {
                std::vector<InventoryItem*> equippedItems = player->getInventory()->getEquippedItems();
                for ( size_t curItem = 0; curItem < equippedItems.size(); curItem++ )
                {
                    if ( equippedItems[ curItem ]->getItem()->getEquipPosition() == tooltipItem->getItem()->getEquipPosition() )
                    {
                        int thisTooltipPosY = mouseY;
                        // if this is our second item we're adding to the compare, then we need to position it next to the previous tooltip.
                        if ( firstItemCompared == true )
                        {
                            thisTooltipPosY += previousFrameHeight + 30;
                        }

                        // if this is the first (or only) item we're going to draw in the compare we check where it will fit.
                        if ( firstItemCompared == false ) {
							if ( Configuration::screenWidth - (mouseX + tooltipItem->getTooltip()->getTooltipWidth() + 60) > equippedItems[ curItem ]->getTooltip()->getTooltipWidth() ) {
                                thisTooltipPosX = mouseX + tooltipItem->getTooltip()->getTooltipWidth() + 30;
                            } else {
                                thisTooltipPosX = mouseX - 30 - equippedItems[ curItem ]->getTooltip()->getTooltipWidth();
                            }
                        }

                        previousFrameHeight = equippedItems[ curItem ]->getTooltip()->getTooltipHeight();
                        equippedItems[ curItem ]->getTooltip()->draw( thisTooltipPosX, thisTooltipPosY );
                        firstItemCompared = true;
                    }
                }
            }
        }
    }
}

void Shop::drawFloatingSelection( int mouseX, int mouseY )
{
	// draw floating selection
	if ( hasFloatingSelection() ) {
		Item *floatingItem = floatingSelection->getItem();
		size_t sizeX = floatingItem->getSizeX();
		size_t sizeY = floatingItem->getSizeY();

		DrawingHelpers::mapTextureToRect( floatingItem->getSymbolTexture()->getTexture(0),
		                                  mouseX, backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  mouseY-20, backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);
	}
}

void Shop::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
    if ( isOnSlotsScreen( mouseX, mouseY ) )
    {
        if ( inventoryScreen->hasFloatingSelection() )
        {
            sellToShop( inventoryScreen->getFloatingSelection(), true );
            inventoryScreen->unsetFloatingSelection();
        }

        if ( hasFloatingSelection() )
        {
            sellToShop( getFloatingSelection(), false );
            unsetFloatingSelection();
            return;
        }

        int fieldIndexX = ( mouseX - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( mouseY - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        if ( !isPositionFree( fieldIndexX, fieldIndexY, currentTab ) )
        {
            InventoryItem *curItem = getItemAt( fieldIndexX, fieldIndexY, currentTab );
            if ( player->getCoins() >= curItem->getItem()->getValue() )
            {
                if ( mouseState == SDL_BUTTON_RIGHT ) {
                    // direct buy on right button
                    bool inserted = player->getInventory()->insertItem( curItem->getItem(), curItem );
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
        if ( mouseX > tabs[tabIndex].posX + posX
            && mouseY > tabs[tabIndex].posY + posY
            && mouseX < tabs[tabIndex].posX + posX + tabs[tabIndex].width
            && mouseY < tabs[tabIndex].posY + posY + tabs[tabIndex].height ) {
            currentTab = tabIndex;
            return;
        }
    }

    if ( !isOnSlotsScreen( mouseX, mouseY ) )
    {
        if ( hasFloatingSelection() )
        {
            sellToShop( getFloatingSelection(), false );
            unsetFloatingSelection();
            return;
        }
    }
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
		InventoryItem *newItem = new InventoryItem( item, foundX, foundY, player, sellItem );
        insertItemAt( newItem, foundX, foundY, itemTab );
    }

	if ( givePlayerMoney ) {
        SoundEngine::playSound( "data/sound/sell_buy_item.ogg" );
	    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
	    player->giveCoins( floor( sellItem->getItem()->getValue() * 0.75 ) * sellItem->getCurrentStackSize() );
	    if ( sellItem->getCurrentStackSize() > 1 ) {
            DawnInterface::addTextToLogWindow( yellow, "Sold %d %s.", sellItem->getCurrentStackSize(), item->getName().c_str() );
	    } else {
            DawnInterface::addTextToLogWindow( yellow, "Sold %s.", item->getName().c_str() );
	    }
        // player only gets 75% of the itemvalue when he sells an item
	}
}

void Shop::buyFromShop()
{
    player->reduceCoins( floatingSelection->getItem()->getValue() * floatingSelection->getCurrentStackSize() );

    SoundEngine::playSound( "data/sound/sell_buy_item.ogg" );

    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
    if ( floatingSelection->getCurrentStackSize() > 1 ) {
        DawnInterface::addTextToLogWindow( yellow, "Purchased %d %s.", floatingSelection->getCurrentStackSize(), floatingSelection->getItem()->getName().c_str() );
    } else {
        DawnInterface::addTextToLogWindow( yellow, "Purchased %s.", floatingSelection->getItem()->getName().c_str() );
    }

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

std::string currency::getLongTextString( uint32_t coins )
{
    std::stringstream ss;
    ss.clear();

    uint32_t copper = 0, silver = 0, gold = 0;
    bool addComma = false;

    exchangeCoins( copper, silver, gold, coins );
    if ( gold > 0 ) {
        ss << gold << " gold";
        addComma = true;
    }
    if ( silver > 0 ) {
        if ( addComma == true ) {
            ss << ", ";
        }
        ss << silver << " silver";
        addComma = true;
    }
    if ( copper > 0 ) {
        if ( addComma == true ) {
            ss << ", ";
        }
        ss << copper << " copper";
    }
    return ss.str();;
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

    return ss.str();
}
