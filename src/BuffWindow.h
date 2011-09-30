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

#ifndef BUFFWINDOW_H
#define BUFFWINDOW_H

#include "CTexture.h"
#include "GLFT_Font.h"
#include "CSpell.h"
#include "FramesBase.h"
#include "tooltip.h"

class Player;

class BuffWindow : public FramesBase
{
public:
	BuffWindow( Player* player );
	~BuffWindow();

	void initFonts();
	void loadTextures();
	void draw( int mouseX, int mouseY );
	void clicked( int mouseX, int mouseY, uint8_t mouseState );
	CSpellActionBase* getSpellAtMouse( int mouseX, int mouseY );

private:
	Tooltip* tooltip;
	Player* player;
	GLFT_Font* spellFont;
	CTexture textures;
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells;
};

#endif
