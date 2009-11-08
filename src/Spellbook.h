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

#ifndef __SPELLBOOK_H__
#define __SPELLBOOK_H__

#include "CTexture.h"
#include "CSpell.h"
#include "GLFT_Font.h"
#include "tooltip.h"

class Player;

struct sSpellSlot
{
    CActionFactory *action;
    GLFT_Font *font;
    Tooltip *tooltip;
    int posX;
    int posY;
    int width;
    int height;

    void sSpellSlot::initFont();

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

class Spellbook
{
    public:
        Spellbook( Player *player );
        ~Spellbook();
        void loadTextures();
        void draw();
        void setVisible( bool newVisible );
        void drawSpellTooltip( int x, int y );
        void clicked( int clickX, int clickY );

        bool isVisible() const;
        bool isMouseOver( int x, int y ) const;

        int8_t getMouseOverSpellSlotId( int x, int y ) const;

    private:
        CTexture textures;
        std::vector<sSpellSlot> spellSlot;
        Player *player;
        bool visible;
        int posX;
        int posY;
};

#endif
