/**    Copyright (C) 2009,2010  Dawn - 2D roleplaying game    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.    This program is free software: you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation, either version 3 of the License, or    (at your option) any later version.    This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.    You should have received a copy of the GNU General Public License    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/
#include "shop.h"#include <sstream>
#include "Player.h"


Shop::Shop( Player *player_, CNPC *shopkeeper_)
	:	player( player_ ),
        shopkeeper( shopkeeper_ ),
		visible(false),
		currentTab( 0 ),
		posX( 50 ),
		posY( 80 ),
		floatingSelection( NULL ),
		backpackFieldWidth( 32 ),
		backpackFieldHeight( 32 ),
		backpackSeparatorWidth( 3 ),
		backpackSeparatorHeight( 3 ),
		backpackOffsetX( 69 ),
		backpackOffsetY( 59 ),
		numSlotsX( 10 ),
		numSlotsY( 6 )
		{
		    tabs[0].tabimage.texture.reserve(1);
            tabs[0].tabimage.LoadIMG("data/interface/shop/weapontab.tga",0);
            tabs[0].height = 128;
            tabs[0].width = 128;

            tabs[0].posX = 61 + posX;
            tabs[0].posY = 264 + posY;

            tabs[1].tabimage.texture.reserve(1);
            tabs[1].tabimage.LoadIMG("data/interface/shop/armortab.tga",0);
            tabs[1].height = 128;
            tabs[1].width = 128;
            tabs[1].posX = 202 + posX;
            tabs[1].posY = 264 + posY;

            tabs[2].tabimage.texture.reserve(1);
            tabs[2].tabimage.LoadIMG("data/interface/shop/misctab.tga",0);
            tabs[2].height = 128;
            tabs[2].width = 128;
            tabs[2].posX = 343 + posX;
            tabs[2].posY = 264 + posY;

		    loadShopkeeperInventory();
            loadTextures();
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
    textures.texture.reserve(1);
    textures.LoadIMG("data/interface/Shop/base.tga",0);
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
    size_t numItems = shopkeeperInventory.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		InventoryItem *curInvItem = shopkeeperInventory[ curItemNr ];
		Item *curItem = curInvItem->getItem();
		CTexture *symbolTexture = curItem->getSymbolTexture();

		size_t invPosX = curInvItem->getInventoryPosX();
		size_t invPosY = curInvItem->getInventoryPosY();
		size_t sizeX = curItem->getSizeX();
		size_t sizeY = curItem->getSizeY();

		DrawingHelpers::mapTextureToRect( symbolTexture->texture[0].texture,
		                                  world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);
	}
}

void Shop::clicked( int clickX, int clickY )
{
    // loop through our tabs, see if any got clicked.
    for (size_t tabIndex = 0; tabIndex <= 2; tabIndex++) {
        if ( clickX > tabs[tabIndex].posX
            && clickY > tabs[tabIndex].posY
            && clickX < tabs[tabIndex].posX + tabs[tabIndex].width
            && clickY < tabs[tabIndex].posY + tabs[tabIndex].height ) {
            currentTab = tabIndex;
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

void Shop::sellItem( InventoryItem *sellItem )
{

}

bool Shop::hasFloatingSelection() const
{
    return floatingSelection != NULL;
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
