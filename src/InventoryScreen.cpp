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

InventoryScreenSlot::InventoryScreenSlot( ItemSlot::ItemSlot itemSlot_, size_t offsetX_, size_t offsetY_, size_t sizeX_, size_t sizeY_ )
	: itemSlot( itemSlot_ ),
	  offsetX( offsetX_ ),
	  offsetY( offsetY_ ),
	  sizeX( sizeX_ ),
	  sizeY( sizeY_ )
{
}

size_t InventoryScreenSlot::getOffsetX() const
{
	return offsetX;
}

size_t InventoryScreenSlot::getOffsetY() const
{
	return offsetY;
}

size_t InventoryScreenSlot::getSizeX() const
{
	return sizeX;
}

size_t InventoryScreenSlot::getSizeY() const
{
	return sizeY;
}

ItemSlot::ItemSlot InventoryScreenSlot::getItemSlot() const
{
	return itemSlot;
}

void addInventoryScreenSlot( InventoryScreenSlot **mySlots, ItemSlot::ItemSlot slotToUse, size_t offsetX, size_t offsetY, size_t sizeX, size_t sizeY )
{
	mySlots[ static_cast<size_t>(slotToUse) ] = new InventoryScreenSlot( slotToUse, offsetX, offsetY, sizeX, sizeY );
}

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
		backpackOffsetY( 12 ),
		numSlotsX( 10 ),
		numSlotsY( 4 ) {
	mySlots = new InventoryScreenSlot*[ static_cast<size_t>( ItemSlot::COUNT )];
	for ( size_t curSlotNr=0; curSlotNr < static_cast<size_t>( ItemSlot::COUNT ); ++curSlotNr ) {
		mySlots[curSlotNr] = NULL;
	}
	
	addInventoryScreenSlot( mySlots, ItemSlot::HEAD, 96, 539, 67, 67 );
	addInventoryScreenSlot( mySlots, ItemSlot::AMULET, 131, 489, 32, 32 );
	addInventoryScreenSlot( mySlots, ItemSlot::MAIN_HAND, 11, 369, 67, 102 );
	addInventoryScreenSlot( mySlots, ItemSlot::OFF_HAND, 96, 369, 67, 102 );
	addInventoryScreenSlot( mySlots, ItemSlot::BELT, 96, 319, 67, 32 );
	addInventoryScreenSlot( mySlots, ItemSlot::LEGS, 96, 199, 67, 102 );
	addInventoryScreenSlot( mySlots, ItemSlot::SHOULDER, 376, 504, 67, 67 );
	addInventoryScreenSlot( mySlots, ItemSlot::CHEST, 376, 419, 67, 67 );
	addInventoryScreenSlot( mySlots, ItemSlot::GLOVES, 376, 334, 67, 67 );
	addInventoryScreenSlot( mySlots, ItemSlot::CLOAK, 461, 369, 67, 102 );
	addInventoryScreenSlot( mySlots, ItemSlot::RING_ONE, 376, 284, 32, 32 );
	addInventoryScreenSlot( mySlots, ItemSlot::RING_TWO, 411, 284, 32, 32 );
	addInventoryScreenSlot( mySlots, ItemSlot::BOOTS, 376, 199, 67, 67 );
	
	// check that all slots were set
	bool allSlotsFilled = true;
	for ( size_t curSlotNr=0; curSlotNr < static_cast<size_t>( ItemSlot::COUNT ); ++curSlotNr ) {
		if ( mySlots[curSlotNr] == NULL ) {
			allSlotsFilled = false;
			dawn_debug_warn( "InventoryScreenSlot for position %d missing. You have to look up the %dth ItemSlot in ItemSlot::ItemSlot to find out which it is", curSlotNr, curSlotNr + 1 );
		}
	}
	if ( ! allSlotsFilled ) {
		dawn_debug_warn( "I don't have InventoryScreenSlots for all items... aborting" );
		abort();
	}
};

InventoryScreen::~InventoryScreen()
{
	size_t count = static_cast<size_t>( ItemSlot::COUNT );
	for ( size_t curSlot=0; curSlot<count; ++curSlot )
	{
		delete mySlots[ curSlot ];
	}
	delete[] mySlots;
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

	for ( size_t curSlotNr=0; curSlotNr < static_cast<size_t>( ItemSlot::COUNT ); ++curSlotNr ) {
		ItemSlot::ItemSlot curSlotEnum = static_cast<ItemSlot::ItemSlot>( curSlotNr );
		if ( isOverSlot( curSlotEnum, clickX, clickY ) ) {
			if ( floatingSelection != NULL ) {
				if ( floatingSelection->getItem()->getEquipPosition() == Inventory::getEquipType( curSlotEnum ) )
				{
					if ( inventory->getItemAtSlot( curSlotEnum ) == NULL ) {
						inventory->wieldItemAtSlot( curSlotEnum, floatingSelection );
						floatingSelection = NULL;
					} else {
						InventoryItem *tmp = floatingSelection;
						floatingSelection = inventory->getItemAtSlot( curSlotEnum );
						inventory->wieldItemAtSlot( curSlotEnum, tmp);
					}
				}
			}
			else if ( inventory->getItemAtSlot( curSlotEnum ) != NULL ) {
				floatingSelection = inventory->getItemAtSlot( curSlotEnum );
				inventory->wieldItemAtSlot( curSlotEnum, NULL );
			}
			return;
		}
	}

	// calculate field index under mouse
	if ( ! isOnBackpackScreen( clickX, clickY ) ) {
		return;
	}

	int fieldIndexX = ( clickX - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
	int fieldIndexY = ( clickY - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

	if ( floatingSelection != NULL ) {
		if ( inventory->hasSufficientSpaceWithExchangeAt( fieldIndexX, fieldIndexY, floatingSelection->getSizeX(), floatingSelection->getSizeY() ) ) {
			floatingSelection = inventory->insertItemWithExchangeAt( floatingSelection, fieldIndexX, fieldIndexY );
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
		                                  world_y + posY + backpackOffsetY + invPosY * backpackFieldHeight + invPosY * backpackSeparatorHeight,
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
	if ( ! isVisible() || floatingSelection == NULL ) {
		return;
	}
	if ( isOnBackpackScreen(x,y) )
	{
	    Item *floatingItem = floatingSelection->getItem();
	    Inventory *inventory = player->getInventory();
	    GLfloat shade[4] = { 0.0f, 0.0f, 0.0f, 0.3f };
	    size_t sizeX = floatingItem->getSizeX();
		size_t sizeY = floatingItem->getSizeY();

        // calculate which backpack-slot we are looking at.
		int fieldIndexX = ( x - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( y - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        // set the shade-color depending on if the item fits or not.
        if ( inventory->hasSufficientSpaceWithExchangeAt( fieldIndexX, fieldIndexY, sizeX, sizeY ) )
        {
            shade[1] = 1.0f; // green color
        } else {
            shade[0] = 1.0f; // red color
        }

        // calculate the size of the shade, if too big, we resize it.
        int shadePosX = world_x + posX + backpackOffsetX
		                + fieldIndexX * backpackFieldWidth
		                + fieldIndexX * backpackSeparatorWidth;
        int shadePosY = world_y + posY + backpackOffsetY-1
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
		return;
	}

	for ( size_t curSlotNr=0; curSlotNr<static_cast<size_t>(ItemSlot::COUNT); ++curSlotNr )
	{
		ItemSlot::ItemSlot curSlotEnum = static_cast<ItemSlot::ItemSlot>( curSlotNr );
		if ( isOverSlot( curSlotEnum, x,y) ) {
			Inventory *inventory = player->getInventory();
			GLfloat shade[4] = { 0.0f, 0.0f, 0.0f, 0.3f };

			// set the shade-color depending on if the item fits or not.
			if ( floatingSelection->getItem()->getEquipPosition() == Inventory::getEquipType( curSlotEnum ) )
			{
				shade[1] = 1.0f; // green color
			} else {
				shade[0] = 1.0f; // red color
			}

			InventoryScreenSlot *curScreenSlot = mySlots[ curSlotNr ];
			glColor4fv(shade);
			DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
											  world_x + posX + curScreenSlot->getOffsetX(),
											  curScreenSlot->getSizeX(),
											  world_y + posY + curScreenSlot->getOffsetY(),
											  curScreenSlot->getSizeY());
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			return;
		}
	}
}


void InventoryScreen::draw()
{
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                      world_x + posX, textures.texture[0].width, world_y + posY, textures.texture[0].height);

	drawBackpack();
	for ( size_t curSlotNr=0; curSlotNr < static_cast<size_t>( ItemSlot::COUNT ); ++curSlotNr ) {
		drawSlot( static_cast<ItemSlot::ItemSlot>(curSlotNr) );
	}
}

void InventoryScreen::drawSlot( ItemSlot::ItemSlot curSlot )
{
	Inventory *inventory = player->getInventory();
	InventoryItem *invItem = inventory->getItemAtSlot( curSlot );
	if ( invItem != NULL ) {
		Item *item = invItem->getItem();
		CTexture *symbolTexture = item->getSymbolTexture();

		InventoryScreenSlot *curScreenSlot = mySlots[ static_cast<size_t>( curSlot ) ];

		double stretchX = ((double)curScreenSlot->getSizeX()) / ((double)symbolTexture->texture[0].width);
		double stretchY = ((double)curScreenSlot->getSizeY()) / ((double)symbolTexture->texture[0].height);

		size_t drawSizeX;
		size_t drawSizeY;

		if ( stretchX < stretchY ) {
			drawSizeX = curScreenSlot->getSizeX();
			drawSizeY = symbolTexture->texture[0].height * stretchX;
			if ( drawSizeY > curScreenSlot->getSizeY() ) {
				drawSizeY = curScreenSlot->getSizeY();
			}
		} else {
			drawSizeX = symbolTexture->texture[0].width * stretchY;
			if ( drawSizeX > curScreenSlot->getSizeX() ) {
				drawSizeX = curScreenSlot->getSizeX();
			}
			drawSizeY = curScreenSlot->getSizeY();
		}
		size_t centerOffsetX = (curScreenSlot->getSizeX() - drawSizeX) / 2;
		size_t centerOffsetY = (curScreenSlot->getSizeY() - drawSizeY) / 2;

		DrawingHelpers::mapTextureToRect( symbolTexture->texture[0].texture,
										  world_x + posX + curScreenSlot->getOffsetX() + centerOffsetX,
										  drawSizeX,
										  world_y + posY + curScreenSlot->getOffsetY() + centerOffsetY,
										  drawSizeY );
	}
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
	     || y < posY + backpackOffsetY
	     || x > posX + backpackOffsetX + backpackFieldWidth * numSlotsX + (numSlotsX-1)*backpackSeparatorWidth
	     || y > posY + backpackOffsetY + backpackFieldHeight * numSlotsY + (numSlotsY-1)*backpackSeparatorHeight ) {
		return false;
	}
	return true;
}

bool InventoryScreen::isOverSlot( ItemSlot::ItemSlot itemSlot, int x, int y ) const
{
	InventoryScreenSlot *curSlot = mySlots[ static_cast<size_t>( itemSlot ) ];
	if ( x < posX + curSlot->getOffsetX()
		 || y < posY + curSlot->getOffsetY()
		 || x > posX + curSlot->getOffsetX() + curSlot->getSizeX()
		 || y > posY + curSlot->getOffsetY() + curSlot->getSizeY() ) {
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

void InventoryScreen::drawItemTooltip( int x, int y )
{
    // draws tooltip over item in the backpack
    if ( isOnBackpackScreen(x,y) && isVisible() && floatingSelection == NULL ) {
        Inventory *inventory = player->getInventory();
        InventoryItem *tooltipItem;
        int fieldIndexX = ( x - (posX + backpackOffsetX) ) / (backpackFieldWidth+backpackSeparatorWidth);
        int fieldIndexY = ( y - (posY + backpackOffsetY) ) / (backpackFieldHeight+backpackSeparatorHeight);

        if ( ! inventory->isPositionFree( fieldIndexX, fieldIndexY ) ) {
            tooltipItem = inventory->getItemAt( fieldIndexX, fieldIndexY );
            tooltipItem->tt->draw( x, y );
        }
    }

    // draws tooltip over equipped item
    if ( isVisible() && floatingSelection == NULL && !isOnBackpackScreen( x, y ) )
    {
        ItemSlot::ItemSlot tooltipslot = getMouseOverSlot( x, y );

        if ( tooltipslot != ItemSlot::COUNT )
        {
            Inventory *inventory = player->getInventory();
            InventoryItem *tooltipItem;

            tooltipItem = inventory->getItemAtSlot( tooltipslot );
            if ( tooltipItem )
            {
                tooltipItem->tt->draw( x, y );
            }
        }
    }
}

ItemSlot::ItemSlot InventoryScreen::getMouseOverSlot( int x, int y ) const
{
    if ( isOverSlot( ItemSlot::AMULET, x, y ) )
        return ItemSlot::AMULET;
    if ( isOverSlot( ItemSlot::BELT, x, y ) )
        return ItemSlot::BELT;
    if ( isOverSlot( ItemSlot::BOOTS, x, y ) )
        return ItemSlot::BOOTS;
    if ( isOverSlot( ItemSlot::CHEST, x, y ) )
        return ItemSlot::CHEST;
    if ( isOverSlot( ItemSlot::CLOAK, x, y ) )
        return ItemSlot::CLOAK;
    if ( isOverSlot( ItemSlot::GLOVES, x, y ) )
        return ItemSlot::GLOVES;
    if ( isOverSlot( ItemSlot::HEAD, x, y ) )
        return ItemSlot::HEAD;
    if ( isOverSlot( ItemSlot::LEGS, x, y ) )
        return ItemSlot::LEGS;
    if ( isOverSlot( ItemSlot::MAIN_HAND, x, y ) )
        return ItemSlot::MAIN_HAND;
    if ( isOverSlot( ItemSlot::OFF_HAND, x, y ) )
        return ItemSlot::OFF_HAND;
    if ( isOverSlot( ItemSlot::RING_ONE, x, y ) )
        return ItemSlot::RING_ONE;
    if ( isOverSlot( ItemSlot::RING_TWO, x, y ) )
        return ItemSlot::RING_TWO;
    if ( isOverSlot( ItemSlot::SHOULDER, x, y ) )
        return ItemSlot::SHOULDER;
	return ItemSlot::COUNT;
}
