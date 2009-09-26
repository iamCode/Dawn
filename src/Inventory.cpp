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

#include "Inventory.h"
#include "CDrawingHelpers.h"

Inventory::Inventory( Player *player_, int posX_ )
	:	player( player_ ),
		posX(posX_),
		posY(100),
		width(350),
		height(400),
		visible(false) {};

Inventory::~Inventory()
{

}

void Inventory::LoadTextures()
{
	textures.texture.reserve(1);
	textures.LoadIMG("data/interface/inventory_base.tga",0);
}

bool Inventory::isVisible() const
{
    return visible;
}

void Inventory::setVisible(bool newVisible)
{
    visible = newVisible;
}

void Inventory::draw()
{
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                      world_x + posX - textures.texture[0].width - 50, textures.texture[0].width, world_y + posY, textures.texture[0].height);
}
