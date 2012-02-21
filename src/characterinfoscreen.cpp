/**
    Copyright (C) 2009,2010,2011,2012  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#include "characterinfoscreen.h"

#include "drawinghelpers.h"
#include "character.h"
#include "player.h"
#include "statssystem.h"
#include "GLFT_Font.h"

CharacterInfoScreen::CharacterInfoScreen( Player *player )
	:   FramesBase( 25, 100, 434, 492, 13, 15 )
{
	// add moveability to the frame, allwoing to drag the frame by the title
	addMoveableFrame( 434, 21, 13, 486 );

	// add a close button to the frame (not a graphical one, that's still handled by the base graphic file).
	addCloseButton( 22, 22, 422, 483);

	this->player = player;
	infoFont = NULL;
	currentTab = 0;
	tabs[0].tabimage.LoadIMG("data/interface/CharacterInfoScreen/meleeSelected.tga",0);
	tabs[0].height = 32;
	tabs[0].width = 58;
	tabs[0].posX = 61;
	tabs[0].posY = 242;

	tabs[1].tabimage.LoadIMG("data/interface/CharacterInfoScreen/defenseSelected.tga",0);
	tabs[1].height = 32;
	tabs[1].width = 72;
	tabs[1].posX = 196;
	tabs[1].posY = 242;

	tabs[2].tabimage.LoadIMG("data/interface/CharacterInfoScreen/spellsSelected.tga",0);
	tabs[2].height = 32;
	tabs[2].width = 59;
	tabs[2].posX = 340;
	tabs[2].posY = 242;
}

CharacterInfoScreen::~CharacterInfoScreen()
{
}

void CharacterInfoScreen::LoadTextures()
{
	textures.LoadIMG("data/interface/CharacterInfoScreen/background.tga",0);
	textures.LoadIMG("data/white2x2pixel.tga",1);
}

void CharacterInfoScreen::initFonts()
{
	infoFont = FontCache::getFontFromCache("data/verdana.ttf", 12);
}

void CharacterInfoScreen::draw( int mouseX, int mouseY )
{
	DrawingHelpers::mapTextureToRect( textures.getTexture(0),
	                                  world_x + posX, textures.getTexture(0).width, world_y + posY, textures.getTexture(0).height );

	size_t descriptionTextStart = 60;
	size_t valueFieldStart = 280;
	size_t topBorderDistance = 30;
	size_t lineDistance = 15;

	int curLine = 0;
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    player->getName() );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Exp" );
	curLine++;
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Level %d %s", player->getLevel(), player->getClassName().c_str() );
	curLine += 2;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Health" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentHealth(), player->getModifiedMaxHealth() );
	curLine++;

	if ( player->getArchType() == CharacterArchType::Caster ) {
	    infoFont->drawText( world_x + posX + descriptionTextStart,
                            world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                            "Mana" );
        infoFont->drawText( world_x + posX + valueFieldStart,
                            world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                            "%d / %d", player->getCurrentMana(), player->getModifiedMaxMana() );
	} else if ( player->getArchType() == CharacterArchType::Fighter ) {
        infoFont->drawText( world_x + posX + descriptionTextStart,
                            world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                            "Max fatigue" );
        infoFont->drawText( world_x + posX + valueFieldStart,
                            world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                            "%d", player->getModifiedMaxFatigue() );
	}
	curLine += 2;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Dexterity" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedDexterity() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Intellect" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedIntellect() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Strength" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedStrength() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Vitality" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedVitality() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Wisdom" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedWisdom() );
	curLine++;

	drawExpBar();

	drawTabs();
}

void CharacterInfoScreen::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
    // loop through our tabs, see if any got clicked.
    for (size_t tabIndex = 0; tabIndex <= 2; tabIndex++) {
        if ( mouseX > tabs[tabIndex].posX + posX
            && mouseY > tabs[tabIndex].posY + posY
            && mouseX < tabs[tabIndex].posX + posX + tabs[tabIndex].width
            && mouseY < tabs[tabIndex].posY + posY + tabs[tabIndex].height ) {
            currentTab = tabIndex;
        }
    }
}

void CharacterInfoScreen::drawExpBar()
{
    uint64_t neededXP = (player->getExpNeededForLevel(player->getLevel()+1)) - player->getExpNeededForLevel(player->getLevel());
    uint64_t currentXP = player->getExperience() - player->getExpNeededForLevel(player->getLevel());

    int expBarWidth = static_cast<float>(currentXP) / neededXP * 100;

    glColor3f( 0.7f, 0.73f, 0.29f );
    DrawingHelpers::mapTextureToRect( textures.getTexture(1),
                                    world_x + posX + 280, 100, world_y + posY + 433, 10 );
    glColor3f( 0.9f, 0.93f, 0.29f );
    DrawingHelpers::mapTextureToRect( textures.getTexture(1),
                                    world_x + posX + 280, expBarWidth, world_y + posY + 433, 10 );
    glColor3f( 1.0f, 1.0f, 1.0f );
}

void CharacterInfoScreen::drawTabs()
{
    DrawingHelpers::mapTextureToRect( tabs[currentTab].tabimage.getTexture(0),
                                      world_x + tabs[currentTab].posX + posX, tabs[currentTab].tabimage.getTexture(0).width, world_y + tabs[currentTab].posY + posY, tabs[currentTab].tabimage.getTexture(0).height );

	const StatsSystem *statsSystem = StatsSystem::getStatsSystem();

	size_t descriptionTextStart = 80;
	size_t valueFieldStart = 300;
	size_t topBorderDistance = 265;
	size_t lineDistance = 15;

	int curLine = 0;

    switch ( currentTab )
    {
        case 0: // draws melee tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Damage" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "%d-%d",
			                    static_cast<size_t>(player->getModifiedMinDamage() * statsSystem->complexGetDamageModifier(player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel())),
			                    static_cast<size_t>(player->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier(player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel())) );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to hit" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetHitChance( player->getLevel(), player->getModifiedHitModifierPoints(), player->getLevel() ) * 100.0 ) );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Critical strike" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetMeleeCriticalStrikeChance( player->getLevel(), player->getModifiedMeleeCriticalModifierPoints(), player->getLevel() ) * 100.0 ) );
        break;
        case 1: // draws defense tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Armor" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d", player->getModifiedArmor() );
            curLine++;

			infoFont->drawText( world_x + posX + descriptionTextStart,
			                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "Damage Reduction" );
			infoFont->drawText( world_x + posX + valueFieldStart,
			                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "%.2f%%", (statsSystem->complexGetDamageReductionModifier( player->getLevel(), player->getModifiedArmor(), player->getLevel() ) * 100.0) );
			curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to block" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", (statsSystem->complexGetBlockChance( player->getLevel(), player->getModifiedBlockModifierPoints(), player->getLevel() ) * 100.0 ) );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Dodge" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", (statsSystem->complexGetEvadeChance( player->getLevel(), player->getModifiedEvadeModifierPoints(), player->getLevel() ) * 100.0) );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Parry" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", (statsSystem->complexGetParryChance( player->getLevel(), player->getModifiedParryModifierPoints(), player->getLevel() ) * 100.0) );
			curLine++;

			for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
				ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
				infoFont->drawText( world_x + posX + descriptionTextStart,
				                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    std::string("Resist ").append( ElementType::getElementName( curElementType )) );
				infoFont->drawText( world_x + posX + valueFieldStart,
				                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    "%.2f%%", (statsSystem->complexGetResistElementChance( player->getLevel(), player->getModifiedResistElementModifierPoints( curElementType ), player->getLevel() ) * 100.0) );
            	curLine++;
            }

        break;
        case 2: // draws spells tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Spell critical strike" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetSpellCriticalStrikeChance( player->getLevel(), player->getModifiedSpellCriticalModifierPoints(), player->getLevel() ) * 100.0) );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Health regen" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", player->getModifiedHealthRegen() );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Mana regen" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", player->getModifiedManaRegen() );
            curLine += 2;

			for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
				ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
				infoFont->drawText( world_x + posX + descriptionTextStart,
				                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    std::string(ElementType::getElementName( curElementType ).append(" spell effect") ) );
				infoFont->drawText( world_x + posX + valueFieldStart,
				                    world_y + posY + frameHeight - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    "%.2f%%", (statsSystem->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curElementType ), player->getLevel() ) * 100.0) );
            	curLine++;
            }

        break;
    }
}

