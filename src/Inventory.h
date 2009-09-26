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

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "CTexture.h"

class Player;

class Inventory
{
	private:
		Player *player;
		bool visible;
		int posX, posY, width, height;
		CTexture textures;

	public:
		Inventory( Player *player_, int posX_ );
		~Inventory();

		void setVisible( bool newVisible );
		bool isVisible() const;

		void LoadTextures();

		void draw();
};

#endif
