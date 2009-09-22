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
	int curLine = 0;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Level" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getLevel() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Health" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d / %d", player->getCurrentHealth(), player->getMaxHealth() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Mana" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d / %d", player->getCurrentMana(), player->getMaxMana() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Strength" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getStrength() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Damage" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getStrength() );
	curLine++;
}
