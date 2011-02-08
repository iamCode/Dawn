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

#include "loadingscreen.h"

#include "CTexture.h"
#include "CDrawingHelpers.h"
#include "GLFT_Font.h"
#include "fontcache.h"
#include "configuration.h"

extern size_t randomSizeT( size_t min, size_t max );

LoadingScreen::LoadingScreen()
{
	font = NULL;
	backgroundTexture = NULL;
	progressTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 20);
	backgroundTexture = new CTexture();
	backgroundTexture->LoadIMG( "data/interface/LoadingScreen/SilverForest.tga", 0 );
	progressTexture = new CTexture();
	progressTexture->LoadIMG( "data/lifebar.tga", 0 );

    // randomly choose background and calculate positions for the background
    srand( time( 0 ) );
    backgroundToDraw = rand() % backgroundTexture->getTexture().size() + 0;
    width = backgroundTexture->getTexture( backgroundToDraw ).width;
    height = backgroundTexture->getTexture( backgroundToDraw ).height;
    posX = (Configuration::screenWidth - width) / 2;
    posY = (Configuration::screenHeight - height) / 2;

	curText = "";
	progress = 0.0;
}

LoadingScreen::~LoadingScreen()
{
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
	if ( progressTexture != NULL ) {
		delete progressTexture;
	}
}

void LoadingScreen::draw()
{
    int progressBarXPos = Configuration::screenWidth / 2 - 256;
	int progressBarYPos = 20;
	int progressBarWidth = Configuration::screenWidth / 2;

	// show screen
	DrawingHelpers::mapTextureToRect( backgroundTexture->getTexture( backgroundToDraw ),
	                                  posX, width,
	                                  posY, height );

	// draw the first part of the progress bar with a bright red color
	glColor3f( 0.75f, 0.2f, 0.2f );
	DrawingHelpers::mapTextureToRect( progressTexture->getTexture(0),
	                                  progressBarXPos, progress * progressBarWidth,
	                                  progressBarYPos, 16 );

    // draw the second part of the progress bar with a dark red color
	glColor3f( 0.5f, 0.1f, 0.1f );
    DrawingHelpers::mapTextureToRect( progressTexture->getTexture(0),
	                                  progressBarXPos+progress * progressBarWidth, progressBarWidth - progress * progressBarWidth,
	                                  progressBarYPos, 16 );
    glColor3f( 1.0f, 1.0f, 1.0f );

	int textX = posX + width / 2 - font->calcStringWidth( curText ) / 2;
	int textY = 30 + font->getHeight();
	font->drawText( textX, textY, curText );
}

void LoadingScreen::setCurrentText( std::string text )
{
	this->curText = text;
}

void LoadingScreen::setProgress( double progress )
{
	this->progress = progress;
}




