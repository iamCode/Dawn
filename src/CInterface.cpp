/**                    Dawn - 2D roleplaying game
    Copyright (C) 2009  Tobias Eliasson (arnestig@users.sourceforge.net)

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

void CInterface::LoadTextures() {
    interfacetextures.texture.reserve(10);
    interfacetextures.LoadIMG("data/interface/blended_bg.tga",0);
    interfacetextures.LoadIMG("data/interface/lifemana.tga",1);
};

void CInterface::DrawInterface() {
    // background, black and nicely blended.
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, interfacetextures.texture[0].texture);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x, world_y+RES_Y-interfacetextures.texture[0].height, 0.0f);
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+RES_X, world_y+RES_Y-interfacetextures.texture[0].height, 0.0f);
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+RES_X, world_y+RES_Y, 0.0f);
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x, world_y+RES_Y, 0.0f);
    glEnd();

    // life and mana bars
    glBindTexture( GL_TEXTURE_2D, interfacetextures.texture[1].texture);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x, world_y+RES_Y-interfacetextures.texture[1].height, 0.0f);
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+interfacetextures.texture[1].width, world_y+RES_Y-interfacetextures.texture[1].height, 0.0f);
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+interfacetextures.texture[1].width, world_y+RES_Y, 0.0f);
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x, world_y+RES_Y, 0.0f);
    glEnd();
    glDisable(GL_BLEND);
}
