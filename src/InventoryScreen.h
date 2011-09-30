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

#ifndef __INVENTORYSCREEN_H__
#define __INVENTORYSCREEN_H__

#include "CTexture.h"
#include "GLFT_Font.h"
#include "item.h" // for EquipPosition
#include "FramesBase.h"

class Player;
class InventoryItem;

class InventoryScreenSlot
{
private:
	ItemSlot::ItemSlot itemSlot;
	size_t offsetX;
	size_t offsetY;
	size_t sizeX;
	size_t sizeY;
	CTexture textures;

public:
	InventoryScreenSlot( ItemSlot::ItemSlot itemSlot, size_t offsetX, size_t offsetY, size_t sizeX, size_t sizeY, std::string plain_file );
	size_t getOffsetX() const;
	size_t getOffsetY() const;
	size_t getSizeX() const;
	size_t getSizeY() const;
	CTexture *getTexture();

	ItemSlot::ItemSlot getItemSlot() const;
};

class InventoryScreen : public FramesBase
{
private:
	Player* player;
	CTexture textures;

	InventoryItem* floatingSelection;

	InventoryScreenSlot** mySlots;

	GLFT_Font* coinsFont;

	void drawBackpack();
	void dropItemOnGround( InventoryItem* item );

	size_t backpackFieldWidth;
	size_t backpackFieldHeight;
	size_t backpackSeparatorWidth;
	size_t backpackSeparatorHeight;
	size_t backpackOffsetX;
	size_t backpackOffsetY;
	size_t numSlotsX;
	size_t numSlotsY;

	void equipOnSlotOriginDependingAndPlaySound( ItemSlot::ItemSlot slotToUse, InventoryItem* wieldItem, bool fromShop , InventoryItem* newFloatingSelection );

public:
	InventoryScreen( Player* player_ );
	~InventoryScreen();

	void clicked( int clickX, int clickY, uint8_t mouseState );

	void loadTextures();
	void setTextureDependentPositions();

	void draw( int mouseX, int mouseY );
	void drawCoins();
	void drawSlot( ItemSlot::ItemSlot curSlot );
	void drawFloatingSelection( int mouseX, int mouseY );
	void drawItemPlacement( int mouseX, int mouseY );
	void drawItemTooltip( int mouseX, int mouseY );

	bool isMouseOnThisFrame( int mouseX, int mouseY ) const;
	bool isOnBackpackScreen( int mouseX, int mouseY ) const;
	bool isOverSlot( ItemSlot::ItemSlot itemSlot, int mouseX, int mouseY ) const;
	bool hasFloatingSelection() const;

	InventoryItem* getFloatingSelection() const;

	ItemSlot::ItemSlot getMouseOverSlot( int mouseX, int mouseY ) const;

	void setFloatingSelection( InventoryItem* item );
	void unsetFloatingSelection();
};

#endif
