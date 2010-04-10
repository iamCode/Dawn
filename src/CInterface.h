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

#ifndef __C_INTERFACE__
#define __C_INTERFACE__

#include "CTexture.h"
#include "CCharacter.h"
#include "GLFT_Font.h"

extern int RES_X,RES_Y,world_x,world_y;

struct sDamageDisplay {
    int digitToDisplay;
    bool critical;
    uint8_t damageType;
    int x_pos;
    int y_pos;
    float transparency;
    uint32_t thisFrame;
    uint32_t lastFrame;

    sDamageDisplay(int digitToDisplay_, bool critical_, uint8_t damageType_, int x_pos_, int y_pos_) {
        digitToDisplay = digitToDisplay_;
        critical = critical_;
        damageType = damageType_;
        x_pos = x_pos_;
        y_pos = y_pos_;
        transparency = 1.0f;

    }
};

class CInterface
{
	public:
		CInterface();
		void LoadTextures();
		void initFonts();
		bool enabled;
		void DrawInterface();
        void drawTargetedNPCText();
		void drawCombatText();
		void SetPlayer(CCharacter *player_);

		void addCombatText( int amount, bool critical, uint8_t damageType, int x_pos, int y_pos);

	private:
		CTexture interfacetextures;
		CTexture damageDisplayTexturesBig;
		CTexture damageDisplayTexturesSmall;


		std::vector<sDamageDisplay> damageDisplay;

		CCharacter *player;

		GLFT_Font *NPCTextFont;
};


#endif
