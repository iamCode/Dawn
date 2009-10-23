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

#include "CharacterInfoScreen.h"

#include "CDrawingHelpers.h"
#include "CCharacter.h"
#include "Player.h"
#include "GLFT_Font.h"

CharacterInfoScreen::CharacterInfoScreen( Player *player_ )
	:	player( player_ ),
		posX(50),
		posY(100),
		width(331),
		height(445),
		visible(false)
{
	infoFont = NULL;
	currentTab = 0;
    tabs[0].tabimage.texture.reserve(1);
    tabs[0].tabimage.LoadIMG("data/interface/CharacterInfoScreen/meleeSelected.tga",0);
    tabs[0].height = 32;
    tabs[0].width = 64;
    tabs[0].posX = 33 + posX;
    tabs[0].posY = 190 + posY;

    tabs[1].tabimage.texture.reserve(1);
    tabs[1].tabimage.LoadIMG("data/interface/CharacterInfoScreen/defenseSelected.tga",0);
    tabs[1].height = 32;
    tabs[1].width = 64;
    tabs[1].posX = 106 + posX;
    tabs[1].posY = 190 + posY;

    tabs[2].tabimage.texture.reserve(1);
    tabs[2].tabimage.LoadIMG("data/interface/CharacterInfoScreen/spellsSelected.tga",0);
    tabs[2].height = 32;
    tabs[2].width = 64;
    tabs[2].posX = 179 + posX;
    tabs[2].posY = 190 + posY;

}

CharacterInfoScreen::~CharacterInfoScreen()
{
	if ( infoFont != NULL ) {
		delete infoFont;
	}
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
	infoFont = new GLFT_Font("data/verdana.ttf", 12);
}

void CharacterInfoScreen::drawScreen()
{
	DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
	                                  world_x + posX, width, world_y + posY, height );

	size_t descriptionTextStart = 20;
	size_t valueFieldStart = 200;
	size_t topBorderDistance = 20;
	size_t lineDistance = 15;

	int curLine = 0;
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Enylyn" /** name of the character **/ );
    infoFont->drawText( world_x + posX + valueFieldStart,
                        world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                        "Exp" );
    curLine++;
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Level %d %s", player->getLevel(), /** should be player->getClass()/getClassText()**/ "Wizard");
	curLine += 2;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Health" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentHealth(), player->getModifiedMaxHealth() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Mana" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentMana(), player->getModifiedMaxMana() );
	curLine += 2;

    infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Dexterity" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedDexterity() );
	curLine++;

    infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Intellect" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedIntellect() );
	curLine++;

    infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Strength" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedStrength() );
	curLine++;

    infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Vitality" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getModifiedVitality() );
	curLine++;

    infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Wisdom" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
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
	     || x > posX + textures.texture[0].width
	     || y > posY + textures.texture[0].height ) {
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
                                    world_x + posX + 200, 100, world_y + 492, 10 );
    glColor3f( 0.9f, 0.93f, 0.29f );
    DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                    world_x + posX + 200, expBarWidth, world_y + 492, 10 );
    glColor3f( 1.0f, 1.0f, 1.0f );
}

void CharacterInfoScreen::drawTabs()
{
    DrawingHelpers::mapTextureToRect( tabs[currentTab].tabimage.texture[0].texture,
                                      world_x + tabs[currentTab].posX, 64, world_y + tabs[currentTab].posY, 32 );

	size_t descriptionTextStart = 25;
	size_t valueFieldStart = 250;
	size_t topBorderDistance = 260;
	size_t lineDistance = 15;

	int curLine = 0;

    switch ( currentTab )
    {
        case 0: // draws melee tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Damage" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d-%d", player->getModifiedMinDamage(), player->getModifiedMaxDamage() );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to hit" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Critical strike" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
        break;
        case 1: // draws defense tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Armor" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Chance to block" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Dodge" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Parry" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
        break;
        case 2: // draws spells tab
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Spell damage bonus" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Critical strike" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.2f%%", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Life regen" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", 0 );
            curLine++;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Mana regen" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%d/sec", 0 );
            curLine += 2;

            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Resists" );
            curLine++;
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Air" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.0f%%", 0 );
            curLine++;
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Disease" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.0f%%", 0 );
            curLine++;
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Fire" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.0f%%", 0 );
            curLine++;
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Frost" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.0f%%", 0 );
            curLine++;
            infoFont->drawText( world_x + posX + descriptionTextStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "Holy" );
            infoFont->drawText( world_x + posX + valueFieldStart,
                                world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
                                "%.0f%%", 0 );
        break;
    }
}

