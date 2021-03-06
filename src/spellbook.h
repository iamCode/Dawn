/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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

#ifndef SPELLBOOK_H
#define SPELLBOOK_H

#include "texture.h"
#include "spell.h"
#include "GLFT_Font.h"
#include "tooltip.h"
#include "framesbase.h"

class Player;

struct sSpellSlot
{
	CSpellActionBase* action;
	GLFT_Font* font;
	Tooltip* tooltip;
	int posX;
	int posY;
	int width;
	int height;

	void initFont();

	sSpellSlot(int posX_, int posY_, int width_, int height_)
	{
		posX = posX_;
		posY = posY_;
		width = width_;
		height = height_;
		action = NULL;
		font = NULL;
		tooltip = NULL;
		initFont();
	}
};

class Spellbook : public FramesBase
{
public:
	Spellbook( Player* player );
	~Spellbook();
	void loadTextures();
	void draw( int mouseX, int mouseY );
	void drawSpellTooltip( int mouseX, int mouseY );
	void drawFloatingSpell( int mouseY, int mouseX );
	void clicked( int mouseX, int mouseY, uint8_t mouseState );

	bool hasFloatingSpell() const;

	int8_t getMouseOverSpellSlotId( int mouseX, int mouseY ) const;
	sSpellSlot* getFloatingSpell() const;
	void setFloatingSpell( CSpellActionBase* newFloatingSpell );
	void unsetFloatingSpell();
	void reloadSpellsFromPlayer();
	void clear();
	std::string getLuaSaveText() const;

private:
	bool isMouseOverNextPageArea( int mouseX, int mouseY );
	bool isMouseOverPreviousPageArea( int mouseX, int mouseY );
	void nextPage();
	void previousPage();
	void refreshPage();

	int nextPageButtonOffsetX;
	int nextPageButtonOffsetY;

	int previousPageButtonOffsetX;
	int previousPageButtonOffsetY;

	int pageButtonWidth;
	int pageButtonHeight;

	CTexture textures;
	std::vector<sSpellSlot> spellSlot;
	sSpellSlot floatingSpellSlot;
	std::vector<CSpellActionBase*> inscribedSpells;
	Player* player;
	int curPage;
	sSpellSlot* floatingSpell;
};

#endif
