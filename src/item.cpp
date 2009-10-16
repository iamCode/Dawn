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

#include "item.h"

Item::Item( std::string name_, size_t sizeX_, size_t sizeY_, std::string symbolFile, EquipPosition::EquipPosition equipPosition_ )
	:	name( name_ ),
		sizeX( sizeX_ ),
		sizeY( sizeY_ ),
		equipPosition( equipPosition_ )
{
	symbolTexture.texture.reserve(1);
	symbolTexture.LoadIMG( symbolFile, 0 );
}

std::string Item::getName() const
{
	return name;
}

size_t Item::getSizeX() const
{
	return sizeX;
}

size_t Item::getSizeY() const
{
	return sizeY;
}

CTexture* Item::getSymbolTexture()
{
	return &symbolTexture;
}

EquipPosition::EquipPosition Item::getEquipPosition() const
{
	return equipPosition;
}


