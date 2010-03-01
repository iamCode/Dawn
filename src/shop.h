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

#ifndef __SHOP_H__
#define __SHOP_H__

#include <stdint.h>
#include <string>
#include "CNPC.h"
#include "CharacterInfoScreen.h"

namespace currency
{
    enum currency
    {
        COPPER, // 100 COPPER == 1 SILVER
        SILVER, // 100 SILVER == 1 GOLD
        GOLD
    };
    void exchangeCoins( uint32_t &copper, uint32_t &silver, uint32_t &gold, uint32_t &coins );
    std::string convertCoinsToString( currency::currency currency, uint32_t coins );
}

class Shop
{
    public:
        Shop( Player *player_, CNPC *shopkeeper_);
        void loadShopkeeperInventory();
        void loadTextures();

        bool isVisible() const;
        void setVisible( bool newVisible );

        void draw();
        void drawItems();
        void drawTabs();
        void drawItemTooltip( int x, int y );
        void drawFloatingSelection( int x, int y );

        void clicked( int clickX, int clickY );

        size_t getItemTab( Item *item );

        bool isOnThisScreen ( int x, int y ) const;
        bool isOnSlotsScreen( int x, int y );
        bool isPositionFree( size_t invPosX, size_t invPosY, size_t curTab ) const;

        bool hasFloatingSelection() const;
        bool hasSufficientSpaceAt( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY, size_t itemTab ) const;

        void sellToShop( InventoryItem *sellItem, bool givePlayerMoney );
        void buyFromShop();

        void insertItemAt( InventoryItem *newItem, size_t foundX, size_t foundY, size_t itemTab );
        InventoryItem* getItemAt( size_t invPosX, size_t invPosY, size_t itemTab );
        void removeItem( InventoryItem *inventoryItem );

        void unsetFloatingSelection();
        InventoryItem *getFloatingSelection() const;

    private:
        uint8_t currentTab;

        int posX, posY, width, height;

		size_t backpackFieldWidth;
		size_t backpackFieldHeight;
		size_t backpackSeparatorWidth;
		size_t backpackSeparatorHeight;
		size_t backpackOffsetX;
		size_t backpackOffsetY;
		size_t numSlotsX;
		size_t numSlotsY;

		CTexture textures;

		sTabs tabs[3];

		bool visible;
		bool ***slotUsed;

		InventoryItem *floatingSelection;

		Player *player;
		CNPC *shopkeeper;

		std::vector<InventoryItem*> shopkeeperInventory[3];
};



#endif
