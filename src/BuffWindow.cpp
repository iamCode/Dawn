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

#include "BuffWindow.h"
#include "Player.h"
#include "CDrawingHelpers.h"
#include "TimeConverterHelper.h"
#include "debug.h"

BuffWindow::BuffWindow( Player *player_)
        :   player( player_ ),
            posX( 300 ),
            spellFont( NULL )
{
    initFonts();
    loadTextures();
    posY = dawn_configuration::screenHeight - 50;
    posX = dawn_configuration::screenWidth - 204;
}

BuffWindow::~BuffWindow()
{
    if ( spellFont != NULL )
    {
        delete spellFont;
    }
}

void BuffWindow::initFonts()
{
	spellFont = new GLFT_Font();
	spellFont->open("data/verdana.ttf", 9);
}

void BuffWindow::loadTextures()
{
    textures.texture.reserve(2);
	textures.LoadIMG("data/interface/BuffWindow/frame.tga",0);
	textures.LoadIMG("data/interface/BuffWindow/background.tga",1);
}

void BuffWindow::draw()
{
    // load the active spells from the player
    activeSpells = player->getActiveSpells();

    for ( size_t curSpell = 0; curSpell < activeSpells.size(); curSpell++ )
    {
            // here we draw the border and background for the spells we have affecting us.
            // buffs will be drawn with a green border and debuffs with a red border.. for now we draw everyone green.
            // spell border
            glColor4f( 0.0f, 0.7f, 0.0f, 1.0f );
            DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                            world_x+posX, 36,
                                            world_y+posY-40*curSpell, 36 );

            // background
            DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                            world_x+posX+36, 168,
                                            world_y+posY-40*curSpell, 36 );


            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            activeSpells[curSpell].first->drawSymbol( world_x + posX + 2, 32, world_y + posY - 40 * curSpell + 2, 32 );
            spellFont->drawText(world_x+posX+40,world_y+posY+16-34*curSpell,activeSpells[curSpell].first->getName());
            spellFont->drawText(world_x+posX+40,world_y+posY+6-34*curSpell,TimeConverter::convertTime( activeSpells[curSpell].second, activeSpells[curSpell].first->getDuration()  ) );
    }

}
