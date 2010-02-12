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

#include "CInterface.h"
#include "CSpell.h"

#include "CDrawingHelpers.h"

void CInterface::LoadTextures()
{
	interfacetextures.texture.reserve(5);
	interfacetextures.LoadIMG("data/lifebar.tga",0);
	interfacetextures.LoadIMG("data/interface/lifemana_bottom.tga",1);
	interfacetextures.LoadIMG("data/interface/lifemana_top.tga",2);
	interfacetextures.LoadIMG("data/interface/lifebar.tga",3);
	interfacetextures.LoadIMG("data/interface/manabar.tga",4);

    damageDisplayTexturesSmall.texture.reserve(10);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/0small.tga",0);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/1small.tga",1);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/2small.tga",2);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/3small.tga",3);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/4small.tga",4);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/5small.tga",5);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/6small.tga",6);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/7small.tga",7);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/8small.tga",8);
	damageDisplayTexturesSmall.LoadIMG("data/interface/combattext/9small.tga",9);

	damageDisplayTexturesBig.texture.reserve(10);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/0big.tga",0);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/1big.tga",1);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/2big.tga",2);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/3big.tga",3);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/4big.tga",4);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/5big.tga",5);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/6big.tga",6);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/7big.tga",7);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/8big.tga",8);
	damageDisplayTexturesBig.LoadIMG("data/interface/combattext/9big.tga",9);
}

void CInterface::DrawInterface()
{
	// drawing the base of the life and mana bar.
	DrawingHelpers::mapTextureToRect( interfacetextures.texture[1].texture,
	                                  world_x, interfacetextures.texture[1].width,
	                                  world_y+RES_Y-interfacetextures.texture[1].height, interfacetextures.texture[1].height );

    /** drawing the procentual display of characters life and mana.
    starts of at an Y-offset of 31, this is where the transparent part of the lifebar starts.
    The "bar" is 91 pixels wide, that means 100% life/mana = 91 pixels of bar. **/
    int lifeBarWidth = static_cast<float>(player->getCurrentHealth()) / player->getModifiedMaxHealth() * 91;
    int manaBarWidth = static_cast<float>(player->getCurrentMana()) / player->getModifiedMaxMana() * 91;

    DrawingHelpers::mapTextureToRect( interfacetextures.texture[3].texture,
	                                  world_x+31, lifeBarWidth,
	                                  world_y+RES_Y-interfacetextures.texture[3].height, interfacetextures.texture[3].height );
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[4].texture,
	                                  world_x+31, manaBarWidth,
	                                  world_y+RES_Y-32-interfacetextures.texture[4].height, interfacetextures.texture[4].height );

    // drawing the top part of the life and mana bar
    DrawingHelpers::mapTextureToRect( interfacetextures.texture[2].texture,
	                                  world_x, interfacetextures.texture[2].width,
	                                  world_y+RES_Y-interfacetextures.texture[2].height, interfacetextures.texture[2].height );


	if (player->continuePreparing()) {
		glColor4f(0.8f,0.8f,0.0f,1.0f);
		DrawingHelpers::mapTextureToRect(interfacetextures.texture[0].texture,world_x+150,100*player->getPreparationPercentage(),world_y+20,20);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
	}

    // drawing damage / healing text floating upwards fading away.
	drawCombatText();
}

void CInterface::SetPlayer(CCharacter *player_)
{
	player = player_;
}

void CInterface::addCombatText( int amount, bool critical, uint8_t damageType, int x_pos, int y_pos )
{
    std::stringstream converterStream, damageStream;
    converterStream << amount;
    std::string tempString = converterStream.str();
    int damageNumber;
    int rand_x = 0;

    rand_x = (rand() % + 64) - 32;

    int characterSpace = 16;

    if ( critical == true )
    {
        characterSpace = 24; // more space between digits if critical (need more space since bigger font)
    }

    // adding every digit in the amount of damage / heal to our struct.
    // adding a random value (rand_x) to x_pos, to spread the damage out a bit so it wont look too clogged.
    for (size_t streamCounter = 0; streamCounter < tempString.length(); streamCounter++) {
        damageStream.clear();
        damageStream << tempString.at(streamCounter);
        damageStream >> damageNumber;
        damageDisplay.push_back(sDamageDisplay( damageNumber, critical, damageType, x_pos+(streamCounter*characterSpace)+rand_x, y_pos ));
    }
}

void CInterface::drawCombatText()
{
    // different color for heal and damage. damage = red, heal = green
    GLfloat damageType[2][3] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };

    CTexture *fontTextures;
    float reduce_amount;

    for (size_t currentDamageDisplay = 0; currentDamageDisplay < damageDisplay.size(); currentDamageDisplay++) {

        // cleaning up text that is already faded out.
        if (damageDisplay[currentDamageDisplay].transparency < 0.0f) {
            damageDisplay.erase(damageDisplay.begin() + currentDamageDisplay);
            if ( currentDamageDisplay >= damageDisplay.size() )
                break;
        }

        if ( damageDisplay[currentDamageDisplay].critical == true )
        {
            fontTextures = &damageDisplayTexturesBig;
            reduce_amount = 0.04;
        } else {
            fontTextures = &damageDisplayTexturesSmall;
            reduce_amount = 0.06;
        }

        // fading and moving text upwards every 50ms
        damageDisplay[currentDamageDisplay].thisFrame = SDL_GetTicks();
        if ((damageDisplay[currentDamageDisplay].thisFrame - damageDisplay[currentDamageDisplay].lastFrame) > 50) {
            damageDisplay[currentDamageDisplay].transparency -= reduce_amount;
            damageDisplay[currentDamageDisplay].y_pos++;
            damageDisplay[currentDamageDisplay].lastFrame = damageDisplay[currentDamageDisplay].thisFrame;
        }

        //sets the color of the text we're drawing based on what type of damage type we're displaying.
        glColor4f(damageType[damageDisplay[currentDamageDisplay].damageType][0],damageType[damageDisplay[currentDamageDisplay].damageType][1],damageType[damageDisplay[currentDamageDisplay].damageType][2],damageDisplay[currentDamageDisplay].transparency);
        DrawingHelpers::mapTextureToRect( fontTextures->texture[damageDisplay[currentDamageDisplay].digitToDisplay].texture,
                                        damageDisplay[currentDamageDisplay].x_pos, fontTextures->texture[damageDisplay[currentDamageDisplay].digitToDisplay].width,
                                        damageDisplay[currentDamageDisplay].y_pos, fontTextures->texture[damageDisplay[currentDamageDisplay].digitToDisplay].height );

        //reset color back to default.
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
}
