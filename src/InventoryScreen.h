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

#ifndef __INVENTORYSCREEN_H__
#define __INVENTORYSCREEN_H__

#include "CTexture.h"

class Player;
class InventoryItem;

class InventoryScreen
{
	private:
		Player *player;
		bool visible;
		int posX, posY, width, height;
		CTexture textures;

		InventoryItem *floatingSelection;

		void drawBackpack();
		void dropItemOnGround( InventoryItem *item );

	public:
		InventoryScreen( Player *player_ );
		~InventoryScreen();

		void setVisible( bool newVisible );
		bool isVisible() const;

		void clicked( int clickX, int clickY );

		void LoadTextures();

		void draw();
		void drawFloatingSelection( int x, int y );
		void drawItemPlacement( int x, int y );

		bool isOnThisScreen( int x, int y ) const;
		bool isOnBackpackScreen( int x, int y ) const;
		bool hasFloatingSelection() const;

		void selectFloating( InventoryItem *item );
};

#endif
