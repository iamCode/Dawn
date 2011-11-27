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

#include "textwindow.h"

#include "SDL/SDL.h"
#include "frames.h" // for Frames

#include <cstring> // for strtok_r
#include <memory>
#include "GLFT_Font.h"
#include "fontcache.h"
#include "luafunctions.h"
#include "configuration.h"

GLFT_Font *textWindowFont = NULL;

char *strtok_r(char *str, const char *delim, char **nextp)
{
    char *ret;

    if ( str == NULL )
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;
    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}

void formatMultilineText( std::string textIn, std::vector< std::string > &textLines, int lineWidth, GLFT_Font *font )
{
	// for strtok_r
	std::string text = std::string("").append(textIn);
	char *some_ptr = NULL;
	char **save_ptr = &some_ptr;
	std::string delim = " ";
	char *nextString = strtok_r( const_cast<char*>(text.c_str()), delim.c_str(), save_ptr );
	std::string curLine = "";
	std::string testCurLine = "";
	while ( nextString != NULL ) {
		if ( testCurLine != "" ) {
			testCurLine.append(" ");
		}
		testCurLine.append( nextString );
		// check render length of curLine
		int estimatedWidth = font->calcStringWidth(testCurLine);
		if ( estimatedWidth <= lineWidth ) {
			curLine = testCurLine;
		} else {
			textLines.push_back( curLine );
			curLine = std::string("").append( nextString );
			testCurLine = curLine;
		}
		nextString = strtok_r( NULL, delim.c_str(), save_ptr );
	}

	if ( curLine != "" ) {
		textLines.push_back( curLine );
	}
}

void initTextWindowFont()
{
	if ( textWindowFont != NULL ) {
		return;
	}

	textWindowFont = FontCache::getFontFromCache("data/verdana.ttf", 14);
}

TextWindow::TextWindow()
	:	FramesBase( 0, 0, 0, 0, 0, 0 ),
		positionType( PositionType::CENTER ),
		x( 0 ),
		y( 0 ),
		autocloseTime( 1 ),
		creationTime( 0 ),
		executeTextOnClose( "" ),
		explicitClose( false )
{
	updateFramesPosition();
}

void TextWindow::setText( std::string text )
{
	initTextWindowFont();

	textLines.clear();

	// format the text.
	const int lineWidth = 416;

	formatMultilineText( text, textLines, lineWidth, textWindowFont );

	updateFramesPosition();
}

void TextWindow::setAutocloseTime( int autocloseTime )
{
	this->autocloseTime = autocloseTime;
	creationTime = SDL_GetTicks();
}

void TextWindow::setPosition( PositionType::PositionType positionType, int x, int y )
{
	this->positionType = positionType;
	this->x = x;
	this->y = y;

	updateFramesPosition();
}

void TextWindow::center()
{
	this->positionType = PositionType::CENTER;
	this->x = Configuration::screenWidth/2;
	this->y = 280;

	updateFramesPosition();
}

void TextWindow::setOnCloseText( std::string onCloseText )
{
	this->executeTextOnClose = onCloseText;
}

void TextWindow::updateFramesPosition()
{
	const int blockSizeX = 32;
	const int blockSizeY = 32;
	const int lineWidth = 416;

	int neededWidth = lineWidth;
	int neededHeight = 0;
	if ( textLines.size() > 0 ) {
		const int lineSpace = textWindowFont->getHeight() * 0.5;
		neededHeight = textWindowFont->getHeight() * textLines.size()
		               + lineSpace * (textLines.size() - 1);
	}
	int neededInnerBlocksX = neededWidth / blockSizeX;
	if ( neededWidth % blockSizeX != 0 ) {
		++neededInnerBlocksX;
	}
	int neededInnerBlocksY = neededHeight / blockSizeY;
	if ( neededHeight % blockSizeY != 0 ) {
		++neededInnerBlocksY;
	}

	int leftX = 0;
	int bottomY = 0;

	switch ( positionType )
	{
		case PositionType::CENTER:
			leftX = x - (neededInnerBlocksX * blockSizeX / 2);
			bottomY = y - (neededInnerBlocksY * blockSizeY / 2);
		break;
		case PositionType::BOTTOMLEFT:
			leftX = x;
			bottomY = y;
		break;
		case PositionType::LEFTCENTER:
			leftX = x;
			bottomY = y - (neededInnerBlocksY * blockSizeY / 2);
		break;
		case PositionType::BOTTOMCENTER:
			leftX = x + (neededInnerBlocksX * blockSizeX / 2);
			bottomY = y;
		break;
	}

	FramesBase::posX = leftX;
	FramesBase::posY = bottomY;
	FramesBase::frameWidth  = (neededInnerBlocksX + 2) * blockSizeX;
	FramesBase::frameHeight = (neededInnerBlocksY + 2) * blockSizeY;
}

bool TextWindow::canBeDeleted() const
{
    return ( explicitClose || ( autocloseTime > 0 && (SDL_GetTicks() - creationTime) > autocloseTime ) );
}

void TextWindow::close()
{
	if ( executeTextOnClose != "" ) {
		LuaFunctions::executeLuaScript( executeTextOnClose );
	}
}

void TextWindow::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	if ( (mouseState == SDL_BUTTON_LEFT) && isMouseOnFrame( mouseX, mouseY ) ) {
		explicitClose = true;
	}
}

extern int world_x;
extern int world_y;

void TextWindow::draw( int mouseX, int mouseY )
{
	if ( explicitClose || ( autocloseTime > 0 && (SDL_GetTicks() - creationTime) > autocloseTime ) ) {
		return;
	}
	const int blockSizeX = 32;
	const int blockSizeY = 32;
	const int lineWidth = 416;
	const int lineSpace = textWindowFont->getHeight() * 0.5;

	int neededWidth = lineWidth;
	int neededHeight = 0;
	if ( textLines.size() > 0 ) {
		neededHeight = textWindowFont->getHeight() * textLines.size()
		               + lineSpace * (textLines.size() - 1);
	}
	int neededInnerBlocksX = neededWidth / blockSizeX;
	if ( neededWidth % blockSizeX != 0 ) {
		++neededInnerBlocksX;
	}
	int neededInnerBlocksY = neededHeight / blockSizeY;
	if ( neededHeight % blockSizeY != 0 ) {
		++neededInnerBlocksY;
	}

	int leftX = 0;
	int bottomY = 0;

	switch ( positionType )
	{
		case PositionType::CENTER:
			leftX = x - (neededInnerBlocksX * blockSizeX / 2);
			bottomY = y - (neededInnerBlocksY * blockSizeY / 2);
		break;
		case PositionType::BOTTOMLEFT:
			leftX = x;
			bottomY = y;
		break;
		case PositionType::LEFTCENTER:
			leftX = x;
			bottomY = y - (neededInnerBlocksY * blockSizeY / 2);
		break;
		case PositionType::BOTTOMCENTER:
			leftX = x + (neededInnerBlocksX * blockSizeX / 2);
			bottomY = y;
		break;
	}

	leftX += world_x;
	bottomY += world_y;

	// draw the frame
	Frames::drawFrame( leftX, bottomY, neededInnerBlocksX, neededInnerBlocksY, blockSizeX, blockSizeY );

	// draw the text
	int curX = leftX + blockSizeX;
	int curY = bottomY + neededInnerBlocksY * blockSizeY + textWindowFont->getHeight();
	for ( size_t curLineNr = 0; curLineNr < textLines.size(); ++curLineNr ) {
		std::string curLine = textLines[ curLineNr ];
		textWindowFont->drawText( curX, curY, curLine );
		curY -= textWindowFont->getHeight();
		curY -= lineSpace;
	}
}

std::vector<TextWindow*> allTextWindows;

namespace DawnInterface
{
	TextWindow *createTextWindow()
	{
		TextWindow *newTextWindow = new TextWindow();
		allTextWindows.push_back( newTextWindow );
		newTextWindow->toggle();
		return newTextWindow;
	}
}

