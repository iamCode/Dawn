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

#include "controlelement.h"

#include "drawinghelpers.h"
#include "GLFT_Font.h"

#include <vector>
#include <iostream>
#include <cassert>

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

void Label::execute()
{
	if( onClickedFunc != NULL )
	{
		(*onClickedFunc)();
	}
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
    if ( mouseX > getPosX() && mouseX < getPosX() + font->calcStringWidth( text )
            && mouseY > getPosY() && mouseY < getPosY() + font->getHeight() )
    {
        execute();
        return; // true;
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

/// class SelectionBox

SelectionBox::SelectionBox( GLFT_Font *font, GLFT_Font *selectFont )
{
	setFont( font );
	setSelectFont( selectFont );
	entries.clear();
	setBaseColor( 0.0f, 0.0f, 0.0f, 0.0f );
	setSelectColor( 0.0f, 0.0f, 0.0f, 0.0f );
	onSelectedFunc = NULL;
	maxWidth = 0;
	maxSelectedWidth = 0;
	selected = -1;
	//state = CLOSED;
	state = OPEN;
}

SelectionBox::~SelectionBox()
{
	if ( onSelectedFunc != NULL )
		delete onSelectedFunc;
}

void SelectionBox::setFont( GLFT_Font *font )
{
	this->font = font;
}

void SelectionBox::setSelectFont( GLFT_Font *selectFont )
{
	this->selectFont = selectFont;
}

void SelectionBox::setEntries( std::vector<std::string> entries, int initialSelected )
{
	this->entries = entries;
	this->selected = initialSelected;
	maxWidth = 0;
	maxSelectedWidth=0;
	for ( size_t curEntryNr=0; curEntryNr<entries.size(); ++curEntryNr ) {
		int curWidth = font->calcStringWidth( entries[ curEntryNr ] );
		maxWidth = std::max( maxWidth, curWidth );
		int curSelectedWidth = selectFont->calcStringWidth( entries[ curEntryNr ] );
		maxSelectedWidth = std::max( maxSelectedWidth, curSelectedWidth );
	}
	maxWidth += 20; // border and stuff like that
	this->state = CLOSED;
}

int SelectionBox::getSelected() const
{
	return selected;
}

void SelectionBox::setSelected( int selected )
{
	state = CLOSED;

	if ( this->selected == selected )
		return;

	this->selected = selected;
	if ( onSelectedFunc != NULL ) {
		(*onSelectedFunc)( selected );
	}
}

namespace Frames
{
	extern std::auto_ptr<CTexture> frameTextures;
}

void SelectionBox::draw( int mouseX, int mouseY )
{
	if ( selected >= 0 ) {
		assert( selected < entries.size() );
		bool mouseInsideBox = ( mouseX >= getPosX() && mouseX < getPosX() + getWidth() && mouseY >= getPosY() && mouseY < getPosY() + getHeight() );
		if ( mouseInsideBox ) {
			glColor4f( selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha );
		} else {
			glColor4f( baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha );
		}
		font->drawText( getPosX(), getPosY(), entries[selected] );
	}

	glColor4f( baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha );

	// TODO: Draw background and open/closed-Symbol depending on state

	if ( state == OPEN ) {
		DrawingHelpers::mapTextureToRect(Frames::frameTextures->getTexture(4), getPosX() + 15, std::max( maxSelectedWidth+10, getWidth()-15), getPosY()-selectFont->getHeight()*1.2*(entries.size()-1)-5, selectFont->getHeight()*1.2*(entries.size()-1)+5 );
		// draw the entries and highlight the one the mouse is over (if any)
		int curX=getPosX()+20;
		int curY=getPosY()-selectFont->getHeight()*1.2;
		for ( size_t curEntryNr=0; curEntryNr<entries.size(); ++curEntryNr ) {
			bool mouseOverEntry = ( mouseX > curX && mouseX <= curX+maxSelectedWidth && mouseY > curY && mouseY < curY+(selectFont->getHeight()*1.2) );
			if ( mouseOverEntry ) {
				glColor4f( selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha );
			}
			selectFont->drawText( curX, curY, entries[ curEntryNr ] );
			if ( mouseOverEntry ) {
				glColor4f( baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha );
			}
			curY -= (selectFont->getHeight()*1.2);
		}
	}
}

void SelectionBox::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	if ( mouseX >= getPosX() && mouseX < getPosX() + getWidth() && mouseY >= getPosY() && mouseY < getPosY() + getHeight() ) {
		// clicked inside the box. Just open / close other options
		if ( state == OPEN ) {
			state = CLOSED;
		} else {
			state = OPEN;
		}
		return;
	}
	if ( state == OPEN ) {
		int curX=getPosX()+20;
		int curY=getPosY()-selectFont->getHeight()*1.2;
		for ( size_t curEntryNr=0; curEntryNr<entries.size(); ++curEntryNr ) {
			bool mouseOverEntry = ( mouseX > curX && mouseX <= curX+maxSelectedWidth && mouseY > curY && mouseY < curY+(selectFont->getHeight()*1.2) );
			if ( mouseOverEntry ) {
				setSelected( curEntryNr );
				break;
			}
			curY -= (selectFont->getHeight()*1.2);
		}
	}
}

void SelectionBox::setOnSelected( CallbackType *onSelectedFunc )
{
	if ( this->onSelectedFunc )
		delete this->onSelectedFunc;

	this->onSelectedFunc = onSelectedFunc;
}

int SelectionBox::getWidth() const
{
	return maxWidth;
}

int SelectionBox::getHeight() const
{
	return font->getHeight();
}

void SelectionBox::setBaseColor( float red, float green, float blue, float alpha )
{
	this->baseColorRed = red;
	this->baseColorGreen = green;
	this->baseColorBlue = blue;
	this->baseColorAlpha = alpha;
}

void SelectionBox::setSelectColor( float red, float green, float blue, float alpha )
{
	this->selectColorRed = red;
	this->selectColorGreen = green;
	this->selectColorBlue = blue;
	this->selectColorAlpha = alpha;
}

