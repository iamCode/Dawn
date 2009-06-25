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

#include "CInterface.h"

#include "CDrawingHelpers.h"

void CInterface::LoadTextures() {
    interfacetextures.texture.reserve(10);
    interfacetextures.LoadIMG("data/interface/blended_bg.tga",0);
    interfacetextures.LoadIMG("data/interface/lifemana.tga",1);
};

void CInterface::DrawInterface() {
    glEnable(GL_BLEND);

    // background at bottom of screen, black and nicely blended.
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[0].texture,
                                      world_x, RES_X,
                                      world_y, interfacetextures.texture[0].height );

    // life and mana bars (bottom left)
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[1].texture,
                                      world_x, interfacetextures.texture[1].width,
                                      world_y, interfacetextures.texture[1].height );

    glDisable(GL_BLEND);
}
