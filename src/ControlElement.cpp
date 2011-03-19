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

#include "ControlElement.h"

#include "CDrawingHelpers.h"
#include "GLFT_Font.h"

#include <iostream>

/// class Label

Label::Label( GLFT_Font *font_, std::string text_ )
{
	setFont( font_ );
	setText( text_ );
	setBaseColor( 0.0f, 0.0f, 0.0f, 0.0f );
	setSelectColor( 0.0f, 0.0f, 0.0f, 0.0f );
	onClickedFunc = NULL;
}

Label::~Label()
{
	if ( onClickedFunc != NULL )
		delete onClickedFunc;
}

void Label::setText( std::string newText )
{
	text = newText;
}

void Label::setFont( GLFT_Font *newFont )
{
	font = newFont;
}

void Label::setOnClicked( SimpleFunctionObject* onClickedFunc )
{
	if ( this->onClickedFunc ) {
		delete this->onClickedFunc;
	}
	this->onClickedFunc = onClickedFunc;
}

void Label::draw( int mouseX, int mouseY )
{
	if ( font == NULL || text == "" )
		return;

	if (  onClickedFunc != NULL
			&& mouseX > getPosX() && mouseX < getPosX() + font->calcStringWidth( text )
			&& mouseY > getPosY() && mouseY < getPosY() + font->getHeight() )
		glColor4f( selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha );
	else
		glColor4f( baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha );
	font->drawText( getPosX(), getPosY(), text );

	// draw child controls if any
	FramesBase::draw( mouseX, mouseY );
}

void Label::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	if ( onClickedFunc != NULL )
	{
		if ( mouseX > getPosX() && mouseX < getPosX() + font->calcStringWidth( text )
				&& mouseY > getPosY() && mouseY < getPosY() + font->getHeight() )
		{
			std::cout << "clicked on label " << text << std::endl;
			(*onClickedFunc)();
			return; // true;
		}
	}
	//return false;
}

int Label::getWidth() const
{
	return font->calcStringWidth( text );
}

int Label::getHeight() const
{
	return font->getHeight();
}

void Label::setBaseColor( float red, float green, float blue, float alpha )
{
	baseColorRed = red;
	baseColorGreen = green;
	baseColorBlue = blue;
	baseColorAlpha = alpha;
}

void Label::setSelectColor( float red, float green, float blue, float alpha )
{
	selectColorRed = red;
	selectColorGreen = green;
	selectColorBlue = blue;
	selectColorAlpha = alpha;
}

