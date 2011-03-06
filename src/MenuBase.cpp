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
#include "Frames.h"

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

size_t MenuItem::getTextWidth() const
{
	return font->calcStringWidth(caption);
}

MenuBase::MenuBase()
	: neededBlocksWidth(0),
	  neededBlocksHeight(0)
{
}

MenuBase::~MenuBase()
{
}

void MenuBase::resizeMenu()
{
	const size_t blockWidth = 32;
	const size_t blockHeight = 32;
	neededBlocksHeight = (menuItems.size() * 40) / blockHeight;
	if ( neededBlocksHeight * blockHeight < (menuItems.size() * 40) )
		neededBlocksHeight++;

	size_t maxWidth = 0;
	for ( size_t curMenuItemNr=0; curMenuItemNr<menuItems.size(); ++curMenuItemNr )
	{
		maxWidth = std::max( maxWidth, menuItems[curMenuItemNr]->getTextWidth() );
	}
	neededBlocksWidth = maxWidth / blockWidth;
	if ( neededBlocksWidth * blockWidth < maxWidth )
		neededBlocksWidth++;
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
	const size_t blockWidth = 32;
	const size_t blockHeight = 32;
	Frames::drawFrame( (Configuration::screenWidth - (neededBlocksWidth+2) * blockWidth)/2,
					   (Configuration::screenHeight - (neededBlocksHeight+2) * blockHeight)/2,
					   neededBlocksWidth,
					   neededBlocksHeight,
					   blockWidth,
					   blockHeight );
	int startX = (Configuration::screenWidth - neededBlocksWidth * blockWidth)/2;
	int startY = (Configuration::screenHeight + neededBlocksHeight * blockHeight)/2 - 40;
    for ( size_t curMenuItem = 0; curMenuItem < menuItems.size(); curMenuItem++ ) {
		getMenuItem( curMenuItem )->drawText( startX, startY );
		startY -= 40;
    }
}
