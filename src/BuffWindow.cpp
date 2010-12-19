/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

#include "BuffWindow.h"
#include "Player.h"
#include "CDrawingHelpers.h"
#include "TimeConverterHelper.h"
#include "debug.h"
#include "fontcache.h"
#include "configuration.h"

BuffWindow::BuffWindow( Player *player ) : FramesBase ( 0, 0, 0, 0, 0, 0 )
{
    initFonts();
    loadTextures();
    toggle();
    this->player = player;
    tooltip = NULL;
    posY = Configuration::screenHeight - 50;
    posX = Configuration::screenWidth - 204;
}

BuffWindow::~BuffWindow()
{
}

void BuffWindow::initFonts()
{
	spellFont = FontCache::getFontFromCache( "data/verdana.ttf", 9 );
}

void BuffWindow::loadTextures()
{
	textures.LoadIMG("data/interface/BuffWindow/frame.tga",0);
	textures.LoadIMG("data/interface/BuffWindow/background.tga",1);
}

void BuffWindow::draw( int mouseX, int mouseY )
{
    // load the active spells from the player
    activeSpells = player->getActiveSpells();

    for ( size_t curSpell = 0; curSpell < activeSpells.size(); curSpell++ )
    {
        // only draw spells that has a duration.
        if ( activeSpells[ curSpell ].first->getDuration() > 0 ) {
            // here we draw the border and background for the spells we have affecting us.
            // healing and buffs will be drawn with a green border and debuffs or hostile spells with a red border..
            if ( activeSpells[ curSpell ].first->isSpellHostile() == true ) {
                glColor4f( 0.7f, 0.0f, 0.0f, 1.0f );
            } else {
                glColor4f( 0.0f, 0.7f, 0.0f, 1.0f );
            }

            DrawingHelpers::mapTextureToRect( textures.getTexture(0),
                                            world_x+posX, 36,
                                            world_y+posY-40*curSpell, 36 );

            // background
            DrawingHelpers::mapTextureToRect( textures.getTexture(1),
                                            world_x+posX+36, 168,
                                            world_y+posY-40*curSpell, 36 );


            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            activeSpells[curSpell].first->drawSymbol( world_x + posX + 2, 32, world_y + posY - 40 * curSpell + 2, 32 );
            spellFont->drawText(world_x+posX+40,world_y+posY+18-40*curSpell,activeSpells[curSpell].first->getName());
            spellFont->drawText(world_x+posX+40,world_y+posY+8-40*curSpell,TimeConverter::convertTime( activeSpells[curSpell].second, activeSpells[curSpell].first->getDuration()  ) );
        }
    }

    CSpellActionBase *spellUnderMouse = getSpellAtMouse( mouseX, mouseY );
    if ( spellUnderMouse != NULL ) {
        if ( tooltip != NULL ) {
            if ( dynamic_cast<spellTooltip*>( tooltip )->getParent() != spellUnderMouse ) {
                delete tooltip;
                tooltip = new spellTooltip( spellUnderMouse, player );
            }
        } else {
            tooltip = new spellTooltip( spellUnderMouse, player );
        }
        tooltip->draw( mouseX, mouseY );
    }
}

CSpellActionBase* BuffWindow::getSpellAtMouse( int mouseX, int mouseY )
{
    for ( size_t curSpell = 0; curSpell < activeSpells.size(); curSpell++ )
    {
        // only draw spells that has a duration.
        if ( activeSpells[ curSpell ].first->getDuration() > 0 ) {
            int spellPosYStart = posY-40*curSpell;
            int spellPosXStart = posX;
            if ( mouseY > spellPosYStart
              && mouseY < spellPosYStart + 36
              && mouseX > spellPosXStart
              && mouseX < spellPosXStart + 204 ) {
                return activeSpells[ curSpell ].first;
            }
        }
    }
    return NULL;
}

void BuffWindow::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
    // if the right mouse button is used, we try to remove the spell.
    if ( mouseState == SDL_BUTTON_RIGHT ) {
        CSpellActionBase *spellUnderMouse = getSpellAtMouse( mouseX, mouseY );
        if ( spellUnderMouse != NULL ) {
            if ( spellUnderMouse->isSpellHostile() == false ) {
                player->removeActiveSpell( spellUnderMouse );
            }
        }
    }
}
