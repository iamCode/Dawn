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

#ifndef _CharacterInfoScreen_h_
#define _CharacterInfoScreen_h_

#include "CTexture.h"

class Player;
class GLFT_Font;

struct sTabs
{
    int posX, posY, width, height;
    CTexture tabimage;
};

class CharacterInfoScreen
{
	private:
		Player *player;
		bool visible;
		int posX, posY, width, height;
		uint8_t currentTab;
		CTexture textures;
		GLFT_Font *infoFont;
		sTabs tabs[3];


	public:
		CharacterInfoScreen( Player *player_ );
		~CharacterInfoScreen();

		void setVisible( bool newVisible );
		bool isVisible() const;
		bool isOnThisScreen( int x, int y );

		void clicked( int clickX, int clickY );

		void LoadTextures();
		void initFonts();

		void drawScreen();
		void drawExpBar();
		void drawTabs();
};

#endif // _CharacterInfoScreen_h_
