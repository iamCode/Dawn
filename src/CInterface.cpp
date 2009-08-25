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

void CInterface::LoadTextures()
{
	interfacetextures.texture.reserve(4);
	interfacetextures.LoadIMG("data/interface/blended_bg.tga",0);
	interfacetextures.LoadIMG("data/interface/lifemana.tga",1);
	interfacetextures.LoadIMG("data/lifebar.tga",2);
	interfacetextures.LoadIMG("data/border.tga",3);

    damageDisplayTextures.texture.reserve(10);
	damageDisplayTextures.LoadIMG("data/interface/combattext/0.tga",0);
	damageDisplayTextures.LoadIMG("data/interface/combattext/1.tga",1);
	damageDisplayTextures.LoadIMG("data/interface/combattext/2.tga",2);
	damageDisplayTextures.LoadIMG("data/interface/combattext/3.tga",3);
	damageDisplayTextures.LoadIMG("data/interface/combattext/4.tga",4);
	damageDisplayTextures.LoadIMG("data/interface/combattext/5.tga",5);
	damageDisplayTextures.LoadIMG("data/interface/combattext/6.tga",6);
	damageDisplayTextures.LoadIMG("data/interface/combattext/7.tga",7);
	damageDisplayTextures.LoadIMG("data/interface/combattext/8.tga",8);
	damageDisplayTextures.LoadIMG("data/interface/combattext/9.tga",9);
};

extern std::vector<CActionFactory*> quickSlots;

void CInterface::DrawInterface()
{
	// background at bottom of screen, black and nicely blended.
	DrawingHelpers::mapTextureToRect( interfacetextures.texture[0].texture,
	                                  world_x, RES_X,
	                                  world_y, interfacetextures.texture[0].height );

	// spell key shortcut fields
	size_t numShortcutFields = 10;
	for ( size_t curShortcutField=0; curShortcutField < numShortcutFields; ++curShortcutField ) {
		// we draw in order 1 2 3 4 5 6 7 8 9 0, so calculate the correct index for the field we are drawing
		size_t curIndex = ( (curShortcutField + 1) % 10 );
		std::string charToDraw( 1, char('0' + curIndex ) );
		shortcutFont.drawText( world_x+ 300 + curShortcutField * 70 - 10, world_y + 50, charToDraw.c_str() );

		if ( quickSlots[ curIndex ] != NULL ) {
			quickSlots[ curIndex ]->draw( world_x+ 300 + curShortcutField * 70 + 2, 46,
			                                        world_y+ 10, 46 );
		}

		DrawingHelpers::mapTextureToRect( interfacetextures.texture[3].texture,
		                                  world_x+ 300 + curShortcutField * 70, 50,
		                                  world_y+ 8, 50 );
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

    // drawing damage / healing text floating upwards fading away.
	drawCombatText();
};

void CInterface::SetPlayer(CCharacter *player_)
{
	player = player_;
};

void CInterface::addCombatText( int amount, bool critical, uint8_t damageType, int x_pos, int y_pos )
{
    std::stringstream converterStream, damageStream;
    converterStream << amount;
    std::string tempString = converterStream.str();
    int damageNumber;

    int rand_x = (rand() % + 64) - 32;

    // adding every digit in the amount of damage / heal to our struct.
    // adding a random value (rand_x) to x_pos, to spread the damage out a bit so it wont look too clogged.
    for (size_t streamCounter = 0; streamCounter < tempString.length(); streamCounter++) {
        damageStream.clear();
        damageStream << tempString.at(streamCounter);
        damageStream >> damageNumber;
        damageDisplay.push_back(sDamageDisplay( damageNumber, critical, damageType, x_pos+(streamCounter*16)+rand_x, y_pos ));
    }
};

void CInterface::drawCombatText()
{
    // different color for heal and damage. damage = red, heal = green
    GLfloat damageType[2][3] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };

    for (size_t currentDamageDisplay = 0; currentDamageDisplay < damageDisplay.size(); currentDamageDisplay++) {

        // cleaning up text that is already faded out.
        if (damageDisplay[currentDamageDisplay].transparency < 0.0f) {
            damageDisplay.erase(damageDisplay.begin() + currentDamageDisplay);
            break;
        }

        // fading and moving text upwards every 50ms
        damageDisplay[currentDamageDisplay].thisFrame = SDL_GetTicks();
        if ((damageDisplay[currentDamageDisplay].thisFrame - damageDisplay[currentDamageDisplay].lastFrame) > 50) {
            damageDisplay[currentDamageDisplay].transparency -= 0.06;
            damageDisplay[currentDamageDisplay].y_pos++;
            damageDisplay[currentDamageDisplay].lastFrame = damageDisplay[currentDamageDisplay].thisFrame;
        }

        //sets the color of the text we're drawing based on what type of damage type we're displaying.
        glColor4f(damageType[damageDisplay[currentDamageDisplay].damageType][0],damageType[damageDisplay[currentDamageDisplay].damageType][1],damageType[damageDisplay[currentDamageDisplay].damageType][2],damageDisplay[currentDamageDisplay].transparency);
        DrawingHelpers::mapTextureToRect( damageDisplayTextures.texture[damageDisplay[currentDamageDisplay].digitToDisplay].texture,
                                        damageDisplay[currentDamageDisplay].x_pos, damageDisplayTextures.texture[damageDisplay[currentDamageDisplay].digitToDisplay].width,
                                        damageDisplay[currentDamageDisplay].y_pos, damageDisplayTextures.texture[damageDisplay[currentDamageDisplay].digitToDisplay].height );

        //reset color back to default.
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
};
