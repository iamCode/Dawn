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

#include "MenuBase.h"
#include "configuration.h"
#include "fontcache.h"

MenuItem::MenuItem( std::string caption_, MenuItemType::MenuItemType menuItemType_ )
    :   caption( caption_ ),
        menuItemType( menuItemType_ )
{
    font = FontCache::getFontFromCache( "data/verdana.ttf", 22 );
}

MenuItem::~MenuItem()
{
}

MenuItemType::MenuItemType MenuItem::getMenuItemType() const
{
    return menuItemType;
}

std::string MenuItem::getCaption() const
{
    return caption;
}

void MenuItem::drawText( int x, int y ) const
{
    font->drawText( x, y, caption );
}

MenuBase::MenuBase()
{
    baseTextures = new CTexture();
    baseTextures->LoadIMG( "data/interface/tooltip/lower_left2.tga", 0 );
    baseTextures->LoadIMG( "data/interface/tooltip/lower_right2.tga", 1 );
    baseTextures->LoadIMG( "data/interface/tooltip/upper_left2.tga", 2 );
    baseTextures->LoadIMG( "data/interface/tooltip/upper_right2.tga", 3 );
    baseTextures->LoadIMG( "data/interface/tooltip/background2.tga", 4 );
    baseTextures->LoadIMG( "data/interface/tooltip/upper2.tga", 5 );
    baseTextures->LoadIMG( "data/interface/tooltip/lower2.tga", 6 );
    baseTextures->LoadIMG( "data/interface/tooltip/left2.tga", 7 );
    baseTextures->LoadIMG( "data/interface/tooltip/right2.tga", 8 );
}

MenuBase::~MenuBase()
{
    delete baseTextures;
}

void MenuBase::resizeMenu()
{

}

MenuItem* MenuBase::getMenuItem( size_t index )
{
    return menuItems[ index ];
}

void MenuBase::addMenuItem( std::string caption, MenuItemType::MenuItemType menuItemType )
{
    menuItems.push_back( new MenuItem( caption, menuItemType ) );
    resizeMenu();
}

bool MenuBase::isMouseOnFrame( int mouseX, int mouseY ) const
{

}

void MenuBase::clicked( int mouseX, int mouseY, uint8_t mouseState )
{

}

void MenuBase::draw( int mouseX, int mouseY )
{
    for ( size_t curMenuItem = 0; curMenuItem < menuItems.size(); curMenuItem++ ) {
        getMenuItem( curMenuItem )->drawText( Configuration::screenWidth / 2, Configuration::screenHeight / 2 - curMenuItem * 40 );
    }
}
