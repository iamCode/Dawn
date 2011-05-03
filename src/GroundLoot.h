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

#ifndef __GROUNDLOOT_H__
#define __GROUNDLOOT_H__

#include "item.h"
#include "GLFT_Font.h"
#include "inventory.h"

class Player;

struct sGroundItems
{
    int xpos, ypos, tooltipXpos, tooltipYpos, tooltipWidth;
    std::string itemValue[3];
    int coinsOffset[3];
    int coinsTextOffset[3];
    GLfloat color[4];
    Item *item;
    void loadTooltip();

    sGroundItems( int xpos_, int ypos_, Item *item_, int fontLength )
    {
        xpos = xpos_;
        ypos = ypos_;
        item = item_;
        tooltipWidth = fontLength;
        loadTooltip();
    }

    bool operator<(const sGroundItems& item1) const { // instead of using a predicate in our sort call.
		return tooltipYpos < item1.tooltipYpos;
	};
};

class GroundLoot
{
	friend class CZone;

    public:
        GroundLoot( Player *player_ );
        ~GroundLoot();

        InventoryItem *getFloatingSelection( int x, int y );
        bool PickUpLoot( Player *player_, sGroundItems groundItem, size_t curItem );
        void searchForItems( int x, int y );
        void lootItem( Item *item, size_t itemIndex );
        void addItem( int x, int y, Item *newItem );
        void removeItem( size_t pos );
        void removeItem( Item *item );
        void sortItems();
        void draw();
        void drawTooltip();
        void enableTooltips();
        void disableTooltips();

    private:
        std::vector<sGroundItems> groundItems;
        GLFT_Font *font;
        CTexture textures;
        Player *player;
        bool drawTooltips;
};


#endif
