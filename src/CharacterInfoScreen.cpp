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
#include "GLFT_Font.h"

CharacterInfoScreen::CharacterInfoScreen( Player *player_ )
	:	player( player_ ),
		posX(50),
		posY(100),
		width(350),
		height(400),
		visible(false)
{
	infoFont = NULL;
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
	textures.texture.reserve(1);
	textures.LoadIMG("data/interface/characterinfo_background.tga",0);
}

void CharacterInfoScreen::initFonts()
{
	infoFont = new GLFT_Font("data/DejaVuSerif-Italic.ttf", 20);
}

void CharacterInfoScreen::drawScreen()
{
	DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
	                                  world_x + posX, width, world_y + posY, height );
	
	size_t descriptionTextStart = 20;
	size_t valueFieldStart = 160;
	size_t topBorderDistance = 20;
	size_t lineDistance = 30;
	
	int curLine = 0;
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Level" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d", player->getLevel() );
	curLine++;

	uint64_t nextXP = (player->getExpNeededForLevel(player->getLevel()+1));
	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "EXP" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%jd / %jd", player->getExperience(), nextXP );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Health" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentHealth(), player->getMaxHealth() );
	curLine++;

	infoFont->drawText( world_x + posX + descriptionTextStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "Mana" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d / %d", player->getCurrentMana(), player->getMaxMana() );
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
	                    "Damage" );
	infoFont->drawText( world_x + posX + valueFieldStart,
	                    world_y + posY + height - (topBorderDistance + curLine*lineDistance + infoFont->getHeight()),
	                    "%d-%d", player->getModifiedMinDamage(), player->getModifiedMaxDamage() );
	curLine++;
}
