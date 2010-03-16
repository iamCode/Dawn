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

#include "CharacterInfoScreen.h"

#include "CDrawingHelpers.h"
#include "CCharacter.h"
#include "Player.h"
#include "StatsSystem.h"
#include "GLFT_Font.h"

CharacterInfoScreen::CharacterInfoScreen( Player *player_ )
	:	player( player_ ),
		visible(false),
		posX(25),
		posY(100),
		width(462),
		height(512)
{
	infoFont = NULL;
	currentTab = 0;
	tabs[0].tabimage.texture.reserve(1);
	tabs[0].tabimage.LoadIMG("data/interface/CharacterInfoScreen/meleeSelected.tga",0);
	tabs[0].height = 32;
	tabs[0].width = 58;
	tabs[0].posX = 61 + posX;
	tabs[0].posY = 242 + posY;

	tabs[1].tabimage.texture.reserve(1);
	tabs[1].tabimage.LoadIMG("data/interface/CharacterInfoScreen/defenseSelected.tga",0);
	tabs[1].height = 32;
	tabs[1].width = 72;
	tabs[1].posX = 196 + posX;
	tabs[1].posY = 242 + posY;

	tabs[2].tabimage.texture.reserve(1);
	tabs[2].tabimage.LoadIMG("data/interface/CharacterInfoScreen/spellsSelected.tga",0);
	tabs[2].height = 32;
	tabs[2].width = 59;
	tabs[2].posX = 340 + posX;
	tabs[2].posY = 242 + posY;

}

CharacterInfoScreen::~CharacterInfoScreen()
{
}

void CharacterInfoScreen::setVisible( bool newVisible )
{
	visible = newVisible;
}

bool CharacterInfoScreen::isVisible() const
{
	return visible;
}

void CharacterInfoScreen::LoadTextures()
{
	textures.texture.reserve(2);
	textures.LoadIMG("data/interface/CharacterInfoScreen/background.tga",0);
	textures.LoadIMG("data/white2x2pixel.tga",1);
}

void CharacterInfoScreen::initFonts()
{
	infoFont = FontCache::getFontFromCache("data/verdana.ttf", 12);
}

void CharacterInfoScreen::drawScreen()
{
	DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
	                                  world_x + posX, textures.texture[0].width, world_y + posY, textures.texture[0].height );

	size_t descriptionTextStart = 60;
	size_t valueFieldStart = 280;
	size_t topBorderDistance = 50;
	size_t lineDistance = 15;

	int curLine = 0;
	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    player->getName() );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Exp" );
	curLine++;
	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Level %d %s", player->getLevel(), /** should be player->getClass()/getClassText()**/ "Wizard");
	curLine += 2;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Health" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentHealth(), player->getModifiedMaxHealth() );
	curLine++;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Mana" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentMana(), player->getModifiedMaxMana() );
	curLine += 2;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Dexterity" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedDexterity() );
	curLine++;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Intellect" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedIntellect() );
	curLine++;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Strength" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedStrength() );
	curLine++;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Vitality" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedVitality() );
	curLine++;

	infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Wisdom" );
	infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
	                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedWisdom() );
	curLine++;

	drawExpBar();

	drawTabs();
}

void CharacterInfoScreen::clicked( int clickX, int clickY )
{
    // loop through our tabs, see if any got clicked.
    for (size_t tabIndex = 0; tabIndex <= 2; tabIndex++) {
        if ( clickX > tabs[tabIndex].posX
            && clickY > tabs[tabIndex].posY
            && clickX < tabs[tabIndex].posX + tabs[tabIndex].width
            && clickY < tabs[tabIndex].posY + tabs[tabIndex].height ) {
            currentTab = tabIndex;
        }
    }
}

bool CharacterInfoScreen::isOnThisScreen( int x, int y )
{
    if ( x < posX
	     || y < posY
	     || x > posX + width
	     || y > posY + height ) {
		return false;
	}
	return true;

}

void CharacterInfoScreen::drawExpBar()
{
    uint64_t neededXP = (player->getExpNeededForLevel(player->getLevel()+1)) - player->getExpNeededForLevel(player->getLevel());
    uint64_t currentXP = player->getExperience() - player->getExpNeededForLevel(player->getLevel());

    int expBarWidth = static_cast<float>(currentXP) / neededXP * 100;

    glColor3f( 0.7f, 0.73f, 0.29f );
    DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                    world_x + posX + 280, 100, world_y + 533, 10 );
    glColor3f( 0.9f, 0.93f, 0.29f );
    DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                    world_x + posX + 280, expBarWidth, world_y + 540, 10 );
    glColor3f( 1.0f, 1.0f, 1.0f );
}

void CharacterInfoScreen::drawTabs()
{
    DrawingHelpers::mapTextureToRect( tabs[currentTab].tabimage.texture[0].texture,
                                      world_x + tabs[currentTab].posX, tabs[currentTab].tabimage.texture[0].width, world_y + tabs[currentTab].posY, tabs[currentTab].tabimage.texture[0].height );

	const StatsSystem *statsSystem = StatsSystem::getStatsSystem();

	size_t descriptionTextStart = 80;
	size_t valueFieldStart = 300;
	size_t topBorderDistance = 285;
	size_t lineDistance = 15;

	int curLine = 0;

    switch ( currentTab )
    {
        case 0: // draws melee tab
            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Damage" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "%d-%d",
			                    static_cast<size_t>(player->getModifiedMinDamage() * statsSystem->complexGetDamageModifier(player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel())),
			                    static_cast<size_t>(player->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier(player->getLevel(), player->getModifiedDamageModifierPoints(), player->getLevel())) );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to hit" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetHitChance( player->getLevel(), player->getModifiedHitModifierPoints(), player->getLevel() ) * 100.0 ) );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Critical strike" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetMeleeCriticalStrikeChance( player->getLevel(), player->getModifiedMeleeCriticalModifierPoints(), player->getLevel() ) * 100.0 ) );
        break;
        case 1: // draws defense tab
            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Armor" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d", player->getModifiedArmor() );
            curLine++;

			infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
			                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "Damage Reduction" );
			infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
			                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
			                    "%.2f%%", (statsSystem->complexGetDamageReductionModifier( player->getLevel(), player->getModifiedArmor(), player->getLevel() ) * 100.0) );
			curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to block" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", (statsSystem->complexGetBlockChance( player->getLevel(), player->getModifiedBlockModifierPoints(), player->getLevel() ) * 100.0 ) );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Dodge" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", (statsSystem->complexGetEvadeChance( player->getLevel(), player->getModifiedEvadeModifierPoints(), player->getLevel() ) * 100.0) );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Parry" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0.0 );
			curLine++;

			for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
				ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
				infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
				                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    std::string("Resist ").append( ElementType::getElementName( curElementType )) );
				infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
				                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    "%.2f%%", (statsSystem->complexGetResistElementChance( player->getLevel(), player->getModifiedResistElementModifierPoints( curElementType ), player->getLevel() ) * 100.0) );
            	curLine++;
            }

        break;
        case 2: // draws spells tab
            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Spell critical strike" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", ( statsSystem->complexGetSpellCriticalStrikeChance( player->getLevel(), player->getModifiedSpellCriticalModifierPoints(), player->getLevel() ) * 100.0) );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Life regen" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", 0.0 );
            curLine++;

            infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Mana regen" );
            infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
                                static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", 0.0 );
            curLine += 2;

			for ( size_t curElement=0; curElement< static_cast<size_t>(ElementType::Count); ++curElement ) {
				ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
				infoFont->drawText( static_cast<float>(world_x) + posX + descriptionTextStart,
				                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    std::string(ElementType::getElementName( curElementType ).append(" spell effect") ) );
				infoFont->drawText( static_cast<float>(world_x) + posX + valueFieldStart,
				                    static_cast<float>(world_y) + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
				                    "%.2f%%", (statsSystem->complexGetSpellEffectElementModifier( player->getLevel(), player->getModifiedSpellEffectElementModifierPoints( curElementType ), player->getLevel() ) * 100.0) );
            	curLine++;
            }

        break;
    }
}

