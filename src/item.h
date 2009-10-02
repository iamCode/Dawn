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

#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include "CTexture.h"

class Item
{
	public:
		Item( std::string name, size_t sizeX, size_t sizeY, std::string symbolFile );
		// probably like CCharacter: baseOnType
		
		std::string getName() const;
		
		size_t getSizeX() const;
		size_t getSizeY() const;
		
		CTexture* getSymbolTexture();
		
	private:
		std::string name;
		size_t sizeX;
		size_t sizeY;
		
		CTexture symbolTexture;
};

#endif // __ITEM_H__
