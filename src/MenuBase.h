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

#ifndef __MENU_BASE__
#define __MENU_BASE__

#include "CTexture.h"
#include "GLFT_Font.h"
#include <iostream>
#include <vector>

namespace MenuItemType {
    enum MenuItemType {
        MENU,
        FUNCTION
    };
}

class MenuItem {
    public:
        MenuItem( std::string caption_, MenuItemType::MenuItemType menuItemType_ );
        ~MenuItem();

        MenuItemType::MenuItemType getMenuItemType() const;
        std::string getCaption() const;
        void drawText( int x, int y ) const;
		size_t getTextWidth() const;

    private:
        GLFT_Font *font;
        std::string caption;
        MenuItemType::MenuItemType menuItemType;
};

class MenuBase {
    public:
        MenuBase();
        ~MenuBase();

        MenuItem* getMenuItem( size_t index );
        void addMenuItem( std::string caption, MenuItemType::MenuItemType menuItemType );
        bool isMouseOnFrame( int mouseX, int mouseY ) const;
        void clicked( int mouseX, int mouseY, uint8_t mouseState );
        void draw( int mouseX, int mouseY );

    private:
        void resizeMenu();
        std::vector<MenuItem*> menuItems;

		size_t neededBlocksWidth;
		size_t neededBlocksHeight;
};

#endif
