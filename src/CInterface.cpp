/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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
#include "globals.h"
#include "CNPC.h"
#include "CZone.h"
#include "Player.h"
#include "CDrawingHelpers.h"
#include "random.h"
#include <vector>

int mx, my;

namespace DawnInterface
{
	void addTextToLogWindow( GLfloat color[], const char* text, ... );
}

CInterface::CInterface()
{
	NPCTextFont = NULL;
}

void CInterface::initFonts()
{
	NPCTextFont = FontCache::getFontFromCache( "data/verdana.ttf", 12 );
	levelFont = FontCache::getFontFromCache( "data/verdana.ttf", 12 );
}

void CInterface::LoadTextures()
{
	interfacetextures.LoadIMG( "data/lifebar.tga", 0);
	interfacetextures.LoadIMG( "data/interface/tooltip/NPCTarget_background.tga", 1);
	interfacetextures.LoadIMG( "data/interface/tooltip/NPCTarget_left.tga", 2);
	interfacetextures.LoadIMG( "data/interface/tooltip/NPCTarget_right.tga", 3);
	interfacetextures.LoadIMG( "data/white2x2pixel.tga", 4);
	interfacetextures.LoadIMG( "data/interface/BuffWindow/frame.tga", 5);
	interfacetextures.LoadIMG( "data/interface/BuffWindow/background.tga", 6);
	interfacetextures.LoadIMG( "data/fear.tga", 7);
	interfacetextures.LoadIMG( "data/stun.tga", 8);
	interfacetextures.LoadIMG( "data/confused.tga", 9);
	interfacetextures.LoadIMG( "data/mesmerized.tga", 10);
	interfacetextures.LoadIMG( "data/interface/Portrait/base.tga", 11);
	interfacetextures.LoadIMG( "data/interface/Portrait/bar.tga", 12);
	interfacetextures.LoadIMG( "data/interface/Portrait/bar_small.tga", 13);
	interfacetextures.LoadIMG( "data/interface/Portrait/Warrior.tga", 14);
	interfacetextures.LoadIMG( "data/cursors/pointer.png", 15);

	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/0small.tga", 0 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/1small.tga", 1 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/2small.tga", 2 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/3small.tga", 3 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/4small.tga", 4 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/5small.tga", 5 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/6small.tga", 6 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/7small.tga", 7 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/8small.tga", 8 );
	damageDisplayTexturesSmall.LoadIMG( "data/interface/combattext/9small.tga", 9 );

	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/0big.tga", 0 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/1big.tga", 1 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/2big.tga", 2 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/3big.tga", 3 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/4big.tga", 4 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/5big.tga", 5 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/6big.tga", 6 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/7big.tga", 7 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/8big.tga", 8 );
	damageDisplayTexturesBig.LoadIMG( "data/interface/combattext/9big.tga", 9 );
}

void CInterface::DrawInterface()
{
	/// start drawing our portrait, with lifebar, mana, fatigue, exp

	// draw the portrait of the character (ie, a humanlike guy or girl)
	DrawingHelpers::mapTextureToRect( player->getPortraitTexture()->getTexture(0),
                                      world_x+4, player->getPortraitTexture()->getTexture(0).width,
									  world_y+Configuration::screenHeight-68, player->getPortraitTexture()->getTexture(0).height );


	// drawing the base of the portrait
	DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(11),
	                                  world_x, interfacetextures.getTexture(11).width,
									  world_y+50+Configuration::screenHeight-interfacetextures.getTexture(11).height, interfacetextures.getTexture(11).height );

	/** drawing the procentual display of characters life and mana.
	starts of at an X-offset of 76, this is where the hollow parts of the life, mana, fatigue and experience bars starts.
	The bar is 123 pixels wide, that means 100% life/mana/fatigue/experience = 123 pixels of bar. **/
	float lifeBarPercentage = static_cast<float>(player->getCurrentHealth() ) / player->getModifiedMaxHealth();
	float manaBarPercentage = static_cast<float>(player->getCurrentMana()) / player->getModifiedMaxMana();
	float fatigueBarPercentage = static_cast<float>( 1 - ( static_cast<float>(player->getCurrentFatigue()) / player->getModifiedMaxFatigue() ) );
	uint64_t neededXP = (player->getExpNeededForLevel(player->getLevel()+1)) - player->getExpNeededForLevel(player->getLevel());
	uint64_t currentXP = player->getExperience() - player->getExpNeededForLevel(player->getLevel());
	float experienceBarPercentage = static_cast<float>( currentXP ) / neededXP;

	// draw the barwidth with no transparency.
	/// health bar
	glColor4f( 0.815f, 0.16f, 0.16f, 1.0f );
	DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(12),
	                                  world_x+76, lifeBarPercentage * 123,
	                                  world_y+Configuration::screenHeight-35, interfacetextures.getTexture(12).height );
	/// mana bar
	if( player->getArchType() == CharacterArchType::Caster )
	{
		glColor4f( 0.16f, 0.576f, 0.815f, 1.0f );
		DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(12),
		                                  world_x+76, manaBarPercentage * 123,
		                                  world_y+Configuration::screenHeight-53,
		                                  interfacetextures.getTexture(12).height );
	}

	/// fatigue bar
	if( player->getArchType() == CharacterArchType::Fighter )
	{
		if( fatigueBarPercentage <= 0.33 )
		{
			glColor4f( 0.109f, 0.917f, 0.047f, 1.0f );
		}
		else if( fatigueBarPercentage >= 0.34 && fatigueBarPercentage <= 0.66 )
		{
			glColor4f( 0.917f, 0.847f, 0.047f, 1.0f );
		}
		else
		{
			glColor4f( 0.917f, 0.047f, 0.047f, 1.0f );
		}

		DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(12),
		                                  world_x+76, fatigueBarPercentage * 123,
		                                  world_y+Configuration::screenHeight-53,
		                                  interfacetextures.getTexture(12).height );
	}

	/// exp bar
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(13),
	                                  world_x+76, experienceBarPercentage * 123,
	                                  world_y+Configuration::screenHeight-67,
	                                  interfacetextures.getTexture(13).height );

	/// draw our level beside the experience bar
	levelFont->drawText( world_x+60-levelFont->calcStringWidth("%d", player->getLevel())/2,
	                                                           world_y+Configuration::screenHeight-70,
	                                                           "%d",player->getLevel() );

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

	/// done with the portrait

	if (player->continuePreparing())
	{
		// draw backdrop first.
		glColor4f(0.5f,0.5f,0.0f,1.0f);
		DrawingHelpers::mapTextureToRect(interfacetextures.getTexture(0),
		                                 world_x+Configuration::screenWidth/2-50,100,
		                                 world_y+100,20);

		// then the actual castbar
		glColor4f(0.8f,0.8f,0.0f,1.0f);
		DrawingHelpers::mapTextureToRect(interfacetextures.getTexture(0),
		                                 world_x+Configuration::screenWidth/2-50,
		                                 100*player->getPreparationPercentage(),
		                                 world_y+100,20);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
	}

	// drawing damage / healing text floating upwards fading away.
	drawCombatText();

	// draw symboms displaying different states of characters / NPCs (fear is one as an example).
	drawCharacterStates();
}

void CInterface::DrawCursor()
{
	SDL_GetMouseState(&mx, &my);
	my = Configuration::screenHeight - my - 1;

	DrawingHelpers::mapTextureToRect(interfacetextures.getTexture(15),
	                                 mx+world_x,
	                                 19,
	                                 my+world_y-19,
	                                 19);
}

void CInterface::SetPlayer(CCharacter *player_)
{
	player = player_;
}

void CInterface::addCombatText( int amount, bool critical, uint8_t damageType, int x_pos, int y_pos, bool update )
{
    std::stringstream converterStream, damageStream;
    converterStream << amount;
    std::string tempString = converterStream.str();
    int damageNumber;
    int rand_x = 0;

    rand_x = RNG::randomInt(-32,32);

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
        damageDisplay.push_back(sDamageDisplay( damageNumber, critical, damageType, x_pos+(streamCounter*characterSpace)+rand_x, y_pos, update ));
    }
}

void CInterface::drawCombatText()
{
	int k = 0;
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
        if ((damageDisplay[currentDamageDisplay].thisFrame - damageDisplay[currentDamageDisplay].lastFrame) > 50 ) {
            damageDisplay[currentDamageDisplay].transparency -= reduce_amount;
            damageDisplay[currentDamageDisplay].y_pos++;
            damageDisplay[currentDamageDisplay].lastFrame = damageDisplay[currentDamageDisplay].thisFrame;
        }

        if( damageDisplay[currentDamageDisplay].update ) k = 1;
        damageDisplay[currentDamageDisplay].x_pos += (player->getDeltaX()*k);
        damageDisplay[currentDamageDisplay].y_pos += (player->getDeltaY()*k);

        //sets the color of the text we're drawing based on what type of damage type we're displaying.
        glColor4f(damageType[damageDisplay[currentDamageDisplay].damageType][0],damageType[damageDisplay[currentDamageDisplay].damageType][1],damageType[damageDisplay[currentDamageDisplay].damageType][2],damageDisplay[currentDamageDisplay].transparency);
        DrawingHelpers::mapTextureToRect( fontTextures->getTexture(damageDisplay[currentDamageDisplay].digitToDisplay),
                                        damageDisplay[currentDamageDisplay].x_pos, fontTextures->getTexture(damageDisplay[currentDamageDisplay].digitToDisplay).width,
                                        damageDisplay[currentDamageDisplay].y_pos, fontTextures->getTexture(damageDisplay[currentDamageDisplay].digitToDisplay).height );

        //reset color back to default.
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
}

void CInterface::drawTargetedNPCText()
{
    CNPC *npc = dynamic_cast<CNPC*>( player->getTarget() );

    glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );

    uint8_t width = 40;
    uint8_t stringWidth = NPCTextFont->calcStringWidth(npc->getName().c_str() );

    if ( stringWidth > width+64 )
    {
        width = stringWidth - 56;
    }

    int fontStart = npc->x_pos+npc->getWidth()/2-stringWidth/2;
    int tooltipStart = npc->x_pos+npc->getWidth()/2-(width+64)/2;

    DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(2),
                                      tooltipStart, 32,
                                      npc->y_pos+npc->getHeight()-3, 32 );
    DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(1),
                                      tooltipStart+32, width,
                                      npc->y_pos+npc->getHeight()-3, 32 );
    DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(3),
                                      tooltipStart+32+width, 32,
                                      npc->y_pos+npc->getHeight()-3, 32 );

    float life_percentage = static_cast<float>(npc->getCurrentHealth()) / static_cast<float>(npc->getModifiedMaxHealth());
    glColor4f(1.0f-life_percentage,life_percentage,0.0f,1.0f);
	DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(0),
	                                  npc->getXPos(), npc->getWidth()*life_percentage,
	                                  npc->getYPos()+npc->getHeight(), 8 );
	glColor4f(1.0f,1.0f,1.0f,1.0f);


    switch ( npc->getAttitude() )
    {
        case Attitude::FRIENDLY:
            glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
        break;
        case Attitude::NEUTRAL:
            glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
        break;
        case Attitude::HOSTILE:
            glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
        break;
    }

    NPCTextFont->drawText( fontStart, npc->y_pos+npc->getHeight() + 12, "%s",npc->getName().c_str() );

    // load the active spells from the NPC
    std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells = npc->getActiveSpells();

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
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(5),
                                            npc->getXPos()+(19*curSpell)+2, 18,
                                            npc->getYPos()+npc->getHeight() + 30, 18 );

            // background
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(6),
                                            npc->getXPos()+(19*curSpell)+2, 18,
                                            npc->getYPos()+npc->getHeight() + 30, 18 );

            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            activeSpells[curSpell].first->drawSymbol( npc->getXPos() + (19*curSpell) + 3, 16, npc->getYPos()+npc->getHeight() + 31, 16 );
        }
    }

    if (npc->continuePreparing()) {
        // draw backdrop first.
        glColor4f(0.5f,0.5f,0.0f,1.0f);
		DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(0),
	                                  npc->getXPos(), npc->getWidth(),
	                                  npc->getYPos()+npc->getHeight()-12, 8 );
        // then the actual castbar
		glColor4f(0.8f,0.8f,0.0f,1.0f);
		DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(0),
	                                  npc->getXPos(), npc->getWidth()*npc->getPreparationPercentage(),
	                                  npc->getYPos()+npc->getHeight()-12, 8 );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        NPCTextFont->drawText( npc->getXPos(), npc->getYPos()+npc->getHeight()-24, "%s",npc->getCurrentSpellActionName().c_str() );
	}
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
}

void CInterface::drawCharacterStates()
{
    /// draws states for the characters
    /// Todo: charmed
    std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
    std::vector<CCharacter*> allCharacters;
    allCharacters.push_back( player );
    for ( size_t curNPC = 0; curNPC < zoneNPCs.size(); curNPC++ ) {
        allCharacters.push_back( zoneNPCs[ curNPC ] );
    }

    for ( size_t curCharacter = 0; curCharacter < allCharacters.size(); curCharacter++ ) {
        /// draws fear symbol
        if ( allCharacters[ curCharacter  ]->isFeared() == true ) {
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(7),
                                              allCharacters[ curCharacter ]->getXPos() + allCharacters[ curCharacter ]->getWidth() / 2 - interfacetextures.getTexture(7).width / 2, interfacetextures.getTexture(7).width,
                                              allCharacters[ curCharacter ]->getYPos() + allCharacters[ curCharacter ]->getHeight() / 2, interfacetextures.getTexture(7).height );
        }
        /// draws stun symbol
        if ( allCharacters[ curCharacter ]->isStunned() == true ) {
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(8),
                                              allCharacters[ curCharacter ]->getXPos() + allCharacters[ curCharacter ]->getWidth() / 2 - interfacetextures.getTexture(8).width / 2, interfacetextures.getTexture(8).width,
                                              allCharacters[ curCharacter ]->getYPos() + allCharacters[ curCharacter ]->getHeight() / 2, interfacetextures.getTexture(8).height );
        }
        /// draws confused symbol
        if ( allCharacters[ curCharacter ]->isConfused() == true ) {
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(9),
                                              allCharacters[ curCharacter ]->getXPos() + allCharacters[ curCharacter ]->getWidth() / 2 - interfacetextures.getTexture(9).width / 2, interfacetextures.getTexture(9).width,
                                              allCharacters[ curCharacter ]->getYPos() + allCharacters[ curCharacter ]->getHeight() / 2, interfacetextures.getTexture(9).height );
        }
        /// draws mesmerized symbol
        if ( allCharacters[ curCharacter ]->isMesmerized() == true ) {
            DrawingHelpers::mapTextureToRect( interfacetextures.getTexture(10),
                                              allCharacters[ curCharacter ]->getXPos() + allCharacters[ curCharacter ]->getWidth() / 2 - interfacetextures.getTexture(10).width / 2, interfacetextures.getTexture(10).width,
                                              allCharacters[ curCharacter ]->getYPos() + allCharacters[ curCharacter ]->getHeight() / 2, interfacetextures.getTexture(10).height );
        }
    }
}
