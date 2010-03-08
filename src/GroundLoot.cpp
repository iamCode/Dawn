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

#include "GroundLoot.h"
#include "fontcache.h"
#include "Player.h"
#include "item.h"

class Player;

extern size_t randomSizeT( size_t min, size_t max );
extern int mouseX, mouseY, world_x, world_y;

void sGroundItems::loadTooltip()
{
    tooltipXpos = xpos + (item->getSizeX() * 32) / 2 - tooltipWidth / 2;
    tooltipYpos = ypos + (item->getSizeY() * 32) / 2;

    GLfloat grey[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat orange[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    // setting the title of the tooltip based on item quality
    switch ( item->getItemQuality() )
    {
        case ItemQuality::POOR:
            for ( size_t x = 0; x < 4; x++ )
                color[x] = grey[x];
        break;
        case ItemQuality::NORMAL:
            for ( size_t x = 0; x < 4; x++ )
                color[x] = white[x];
        break;
        case ItemQuality::ENHANCED:
            for ( size_t x = 0; x < 4; x++ )
                color[x] = yellow[x];
        break;
        case ItemQuality::RARE:
            for ( size_t x = 0; x < 4; x++ )
                color[x] = orange[x];
        break;
        case ItemQuality::LORE:
            for ( size_t x = 0; x < 4; x++ )
                color[x] = red[x];
        break;
    }
}

GroundLoot::GroundLoot( Player *player_)
           : player( player_ ),
             drawTooltips( false )
{
    font = FontCache::getFontFromCache("data/verdana.ttf", 11);
    textures.texture.reserve(3);
    textures.LoadIMG("data/interface/tooltip/groundloot_background.tga",0);
    textures.LoadIMG("data/interface/tooltip/groundloot_left.tga",1);
    textures.LoadIMG("data/interface/tooltip/groundloot_right.tga",2);
}

GroundLoot::~GroundLoot()
{
}

void GroundLoot::enableTooltips()
{
    drawTooltips = true;
}

void GroundLoot::disableTooltips()
{
    drawTooltips = false;
}

void GroundLoot::searchForItems( int x, int y )
{
    for ( size_t curItem = 0; curItem < groundItems.size(); curItem++ )
    {
        // if we're holding left ALT down, we first check to see if player is looting by tooltips.
        if ( drawTooltips )
        {
            if ( x >= groundItems[curItem].tooltipXpos
            && x <= static_cast<int>( groundItems[curItem].tooltipXpos + groundItems[curItem].tooltipWidth + 16)
            && y >= groundItems[curItem].tooltipYpos
            && y <= static_cast<int>( groundItems[curItem].tooltipYpos + 16 ) )
            {
                lootItem( groundItems[curItem].item, curItem );
                return;
            }
        } else {

            if ( x >= groundItems[curItem].xpos
            && x <= static_cast<int>( groundItems[curItem].xpos + groundItems[curItem].item->getSizeX() * 32)
            && y >= groundItems[curItem].ypos
            && y <= static_cast<int>( groundItems[curItem].ypos + groundItems[curItem].item->getSizeY() * 32) )
            {
                lootItem( groundItems[curItem].item, curItem );
                return;
            }
        }
    }
}

void GroundLoot::lootItem( Item *item, size_t itemIndex )
{
    if ( dynamic_cast<GoldHeap*>( item ) != NULL ) {
        // some gold heap
        GoldHeap *goldHeap = dynamic_cast<GoldHeap*>( item );
        player->giveCoins( goldHeap->numCoins() );
        delete goldHeap;
        removeItem( itemIndex );
    } else {
        bool inserted = player->getInventory()->insertItem( item );
        if ( inserted ) {
            removeItem( itemIndex );
        }
    }
}

InventoryItem *GroundLoot::getFloatingSelection( int x, int y )
{
    // search for items on the ground and return them to use as floating selection in the inventoryscreen.
    for ( size_t curItem = 0; curItem < groundItems.size(); curItem++ )
    {
        if ( x >= groundItems[curItem].xpos
        && x <= static_cast<int>( groundItems[curItem].xpos + groundItems[curItem].item->getSizeX() * 32)
        && y >= groundItems[curItem].ypos
        && y <= static_cast<int>( groundItems[curItem].ypos + groundItems[curItem].item->getSizeY() * 32) )
        {
            InventoryItem *returnItem = new InventoryItem( groundItems[curItem].item, 0, 0, player );
            removeItem( curItem );
            return returnItem;
		}
    }
    return NULL;
}

void GroundLoot::addItem( int x, int y, Item *newItem )
{
    /// we dont want items to be dropped at the exact the same position, therefor we do a little random here aswell.
    groundItems.push_back( sGroundItems( x + randomSizeT(-20,20), y + randomSizeT(-20,20), newItem, font->calcStringWidth( newItem->getName() ) ) );
    sortItems();
}

void GroundLoot::removeItem( size_t pos )
{
    groundItems.erase( groundItems.begin() + pos );
    sortItems();
}

bool groundItemYPosCompareFunction( const sGroundItems &item1, const sGroundItems &item2 )
{
	return item1.tooltipYpos <= item2.tooltipYpos;
}

extern bool hasIntersection( int r1_l, int r1_r, int r1_b, int r1_t, int r2_l, int r2_r, int r2_b, int r2_t );

void GroundLoot::sortItems()
{
    // first restore original item position so tooltips always stay close to the items
    for ( size_t curItem=0; curItem<groundItems.size(); ++curItem ) {
        groundItems[curItem].tooltipYpos = groundItems[curItem].ypos;
    }

    // sort by Y-Position. This gives an inital sorting
    std::sort(groundItems.begin(), groundItems.end(), groundItemYPosCompareFunction);

    // Check each item for collision against already placed items and move up until it no longer collides
    for ( size_t curItem = 1; curItem < groundItems.size(); ++curItem ) {
    	sGroundItems &curGroundItem = groundItems[ curItem ];
    	bool fitsSpace;
    	do
    	{
    		fitsSpace = true;
    		for ( size_t previousItem = 0; previousItem < curItem; ++previousItem ) {
    			// check for overlap

    			if ( hasIntersection( curGroundItem.tooltipXpos, curGroundItem.tooltipXpos + curGroundItem.tooltipWidth,
    			                      curGroundItem.tooltipYpos, curGroundItem.tooltipYpos + 16,
    			                      groundItems[previousItem].tooltipXpos,
    			                      groundItems[previousItem].tooltipXpos + groundItems[previousItem].tooltipWidth,
    			                      groundItems[previousItem].tooltipYpos,
    			                      groundItems[previousItem].tooltipYpos + 16 ) ) {
    				fitsSpace = false;
    			}
    			groundItems[ curItem ].tooltipYpos++;
    		}
    	} while ( ! fitsSpace );
    }
}

void GroundLoot::draw()
{
	for ( size_t curItem = 0; curItem < groundItems.size(); curItem++ )
	{
		DrawingHelpers::mapTextureToRect( groundItems[ curItem ].item->getSymbolTexture()->texture[0].texture,
		                                  groundItems[ curItem ].xpos,
		                                  groundItems[ curItem ].item->getSizeX() * 32,
		                                  groundItems[ curItem ].ypos,
		                                  groundItems[ curItem ].item->getSizeY() * 32 );
	}
}

void GroundLoot::drawTooltip()
{
    if ( drawTooltips )
	{
	    for ( size_t curItem = 0; curItem < groundItems.size(); curItem++ )
        {
            if ( groundItems[curItem].tooltipXpos < mouseX + world_x
              && groundItems[curItem].tooltipXpos + groundItems[curItem].tooltipWidth+16 > mouseX + world_x
              && groundItems[curItem].tooltipYpos < mouseY + world_y
              && groundItems[curItem].tooltipYpos + 16 > mouseY + world_y )
            {
                glColor4f( 0.1f, 0.1f, 0.1f, 1.0f );
            } else {
                glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
            }

            // left border
            DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                              groundItems[curItem].tooltipXpos,
                                              textures.texture[1].width,
                                              groundItems[curItem].tooltipYpos,
                                              textures.texture[1].height );
            // background
            DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                              groundItems[curItem].tooltipXpos+16,
                                              groundItems[curItem].tooltipWidth-16,
                                              groundItems[curItem].tooltipYpos,
                                              textures.texture[0].height );
            // right border
            DrawingHelpers::mapTextureToRect( textures.texture[2].texture,
                                              groundItems[curItem].tooltipXpos+groundItems[curItem].tooltipWidth,
                                              textures.texture[2].width,
                                              groundItems[curItem].tooltipYpos,
                                              textures.texture[2].height );

            glColor4fv( groundItems[curItem].color );
            font->drawText( groundItems[curItem].tooltipXpos+10,
                            groundItems[curItem].tooltipYpos+2,
                            groundItems[curItem].item->getName() );
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        }
	}
}
