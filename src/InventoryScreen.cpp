/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

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

#include "InventoryScreen.h"
#include "CDrawingHelpers.h"

#include "inventory.h"
#include "CCharacter.h"
#include "item.h"

#include <cassert>

namespace dawn_configuration
{
	extern int screenWidth;
}

extern std::vector<Item*> groundItems;
extern std::vector<std::pair<int,int> > groundPositions;

InventoryScreen::InventoryScreen( Player *player_ )
	:	player( player_ ),
		posX(0),
		posY(100),
		width(350),
		height(400),
		visible(false),
		floatingSelection( NULL ),
		backpackFieldWidth( 32 ),
		backpackFieldHeight( 32 ),
		backpackSeparatorWidth( 3 ),
		backpackSeparatorHeight( 3 ),
		backpackOffsetX( 96 ),
		backpackOffsetY( 112 ),
		numSlotsX( 10 ),
		numSlotsY( 4 )
{};

InventoryScreen::~InventoryScreen()
{

}

void InventoryScreen::LoadTextures()
{
	textures.texture.reserve(2);
	textures.LoadIMG("data/interface/inventory_base.tga",0);
	textures.LoadIMG("data/white2x2pixel.tga",1);
	posX = dawn_configuration::screenWidth - textures.texture[0].width - 50;
}

void InventoryScreen::dropItemOnGround( InventoryItem *inventoryItem )
{
	groundItems.push_back( inventoryItem->getItem() );
	groundPositions.push_back( std::pair<int,int>( player->getXPos(), player->getYPos() ) );
}

void InventoryScreen::clicked( int clickX, int clickY )
{
	// Put Floating selection out of inventory.
	// Check several positions here for equipping, for now weapon hand and shield hand

	Inventory *inventory = player->getInventory();

	if ( ! isOnThisScreen(clickX,clickY) || ! isVisible() ) {
		// clicked outside inventory window
		if ( floatingSelection != NULL ) {
			// drop item...
			dropItemOnGround( floatingSelection );
			if ( inventory->containsItem( floatingSelection ) ) {
				inventory->removeItem( floatingSelection );
			}
			delete floatingSelection;
			floatingSelection = NULL;

			return;
		}
	}

	// calculate field index under mouse
	if ( ! isOnBackpackScreen( clickX, clickY ) ) {
		return;
	}

	int fieldIndexX = ( clickX - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
	int fieldIndexY = ( clickY - backpackOffsetY ) / (backpackFieldHeight+backpackSeparatorHeight);

	if ( floatingSelection != NULL ) {
		if ( inventory->hasSufficientSpaceAt( fieldIndexX, fieldIndexY, floatingSelection->getSizeX(), floatingSelection->getSizeY() ) ) {
			inventory->insertItemAt( floatingSelection, fieldIndexX, fieldIndexY );
			floatingSelection = NULL;
		}
	}
	else if ( ! inventory->isPositionFree( fieldIndexX, fieldIndexY ) ) {
		floatingSelection = inventory->getItemAt( fieldIndexX, fieldIndexY );
		inventory->removeItem( floatingSelection );
	}
}

bool InventoryScreen::isVisible() const
{
    return visible;
}

void InventoryScreen::setVisible(bool newVisible)
{
    visible = newVisible;
}

void InventoryScreen::drawBackpack()
{
	Inventory *inventory = player->getInventory();
	std::vector<InventoryItem*> items = inventory->getBackpackItems();

	size_t numItems = items.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		InventoryItem *curInvItem = items[ curItemNr ];
		Item *curItem = curInvItem->getItem();
		CTexture *symbolTexture = curItem->getSymbolTexture();

		size_t invPosX = curInvItem->getInventoryPosX();
		size_t invPosY = curInvItem->getInventoryPosY();
		size_t sizeX = curItem->getSizeX();
		size_t sizeY = curItem->getSizeY();

		DrawingHelpers::mapTextureToRect( symbolTexture->texture[0].texture,
		                                  world_x + posX + backpackOffsetX + invPosX * backpackFieldWidth + invPosX * backpackSeparatorWidth,
		                                  backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth,
		                                  world_y + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
		                                  backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight);
	}
}

void InventoryScreen::drawFloatingSelection( int x, int y )
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

void InventoryScreen::drawItemPlacement( int x, int y )
{
	if ( isOnBackpackScreen(x,y) && isVisible() && floatingSelection != NULL )
	{
	    Item *floatingItem = floatingSelection->getItem();
	    Inventory *inventory = player->getInventory();
	    GLfloat shade[4] = { 0.0f, 0.0f, 0.0f, 0.3f };
	    size_t sizeX = floatingItem->getSizeX();
		size_t sizeY = floatingItem->getSizeY();

        // calculate which backpack-slot we are looking at.
		int fieldIndexX = ( x - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( y - backpackOffsetY ) / (backpackFieldHeight+backpackSeparatorHeight);

        // set the shade-color depending on if the item fits or not.
        if ( inventory->hasSufficientSpaceAt( fieldIndexX, fieldIndexY, sizeX, sizeY ) )
        {
            shade[1] = 1.0f; // green color
        } else {
            shade[0] = 1.0f; // red color
        }

        // calculate the size of the shade, if too big, we resize it.
        int shadePosX = world_x + posX + backpackOffsetX 
		                + fieldIndexX * backpackFieldWidth
		                + fieldIndexX * backpackSeparatorWidth;
        int shadePosY = world_y + backpackOffsetY-1 
		                + fieldIndexY * backpackFieldHeight
		                + fieldIndexY * backpackSeparatorHeight;
        int shadeWidth = backpackFieldWidth * sizeX + (sizeX-1)*backpackSeparatorWidth;
        int shadeHeight = backpackFieldHeight * sizeY + (sizeY-1)*backpackSeparatorHeight;

        if ( sizeY + fieldIndexY > numSlotsY )
        {
            shadeHeight = backpackFieldWidth * ( sizeY - (( sizeY + fieldIndexY ) - numSlotsY ))
			              + ( sizeY - (( sizeY + fieldIndexY ) - (numSlotsY-1) ))*backpackSeparatorWidth;
        }

        if ( sizeX + fieldIndexX > numSlotsX )
        {
            shadeWidth = backpackFieldHeight * ( sizeX - (( sizeX + fieldIndexX ) - numSlotsX ))
			             + ( sizeX - (( sizeX + fieldIndexX ) - (numSlotsX-1) ))*backpackSeparatorHeight;
        }

        glColor4fv(shade);
        DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                          shadePosX,
                                          shadeWidth,
                                          shadePosY,
                                          shadeHeight);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
	}
}


void InventoryScreen::draw()
{
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                      world_x + posX, textures.texture[0].width, world_y + posY, textures.texture[0].height);

	drawBackpack();
}

bool InventoryScreen::isOnThisScreen( int x, int y ) const
{
	if ( x < posX
	     || y < posY
	     || x > posX + textures.texture[0].width
	     || y > posY + textures.texture[0].height ) {
		return false;
	}
	return true;
}

bool InventoryScreen::isOnBackpackScreen( int x, int y ) const
{
	if ( x < posX + backpackOffsetX
	     || y < backpackOffsetY
	     || x > posX + backpackOffsetX + backpackFieldWidth * numSlotsX + (numSlotsX-1)*backpackSeparatorWidth
	     || y > backpackOffsetY + backpackFieldHeight * numSlotsY + (numSlotsY-1)*backpackSeparatorHeight ) {
		return false;
	}
	return true;
}

bool InventoryScreen::hasFloatingSelection() const
{
	return floatingSelection != NULL;
}

void InventoryScreen::selectFloating( InventoryItem *item )
{
	assert( floatingSelection == NULL );
	floatingSelection = item;
}


