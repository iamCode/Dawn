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
#include "CSpell.h"

#include "CDrawingHelpers.h"

void CInterface::initFonts()
{
    shortcutFont.open("data/verdana.ttf", 9);
}

void CInterface::LoadTextures() {
    interfacetextures.texture.reserve(10);
    interfacetextures.LoadIMG("data/interface/blended_bg.tga",0);
    interfacetextures.LoadIMG("data/interface/lifemana.tga",1);
    interfacetextures.LoadIMG("data/lifebar.tga",2);
    interfacetextures.LoadIMG("data/border.tga",3);
};

void CInterface::DrawInterface() {
    // background at bottom of screen, black and nicely blended.
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[0].texture,
                                      world_x, RES_X,
                                      world_y, interfacetextures.texture[0].height );

    // spell key shortcut fields
    size_t numShortcutFields = 10;
    for ( size_t curShortcutField=0; curShortcutField < numShortcutFields; ++curShortcutField )
    {
        DrawingHelpers::mapTextureToRect( interfacetextures.texture[3].texture,
                                      world_x+ 300 + curShortcutField * 70, 50,
                                      world_y+ 8, 50 );

        std::string charToDraw( 1, char('0' + ( (curShortcutField + 1) % 10 ) ) );
        shortcutFont.drawText( world_x+ 300 + curShortcutField * 70 - 10, world_y + 50, charToDraw.c_str() );

        CTexture *spellSymbol = NULL;

        // determine spell symbol
        if ( curShortcutField == 0 )
        {
            spellSymbol = SpellCreation::getSpellSymbolByName("Lightning");
        }
        else if ( curShortcutField == 2 )
        {
            spellSymbol = SpellCreation::getSpellSymbolByName("Magic Missile");
        }

        if ( spellSymbol != NULL )
        {
            DrawingHelpers::mapTextureToRect( spellSymbol->texture[0].texture,
                                      world_x+ 300 + curShortcutField * 70 + 2, 46,
                                      world_y+ 10, 46 );
        } 
    }

    // life and mana bars (bottom left)
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[1].texture,
                                      world_x, interfacetextures.texture[1].width,
                                      world_y, interfacetextures.texture[1].height );

    if (player->continuePreparing()) {
        glColor4f(0.8f,0.8f,0.0f,1.0f);
        DrawingHelpers::mapTextureToRect(interfacetextures.texture[2].texture,world_x+150,100*player->getPreparationPercentage(),world_y+20,20);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
};

void CInterface::SetPlayer(CCharacter *player_) {
    player = player_;
};
