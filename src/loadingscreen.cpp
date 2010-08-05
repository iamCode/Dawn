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

namespace dawn_configuration
{
	extern int screenWidth;
	extern int screenHeight;
}

LoadingScreen::LoadingScreen()
{
	font = NULL;
	backgroundTexture = NULL;
	progressTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 20);
	backgroundTexture = new CTexture();
	backgroundTexture->texture.resize(1);
	backgroundTexture->LoadIMG( "data/interface/LoadingScreen/loadingScreen.tga", 0 );
	progressTexture = new CTexture();
	progressTexture->texture.resize(1);
	progressTexture->LoadIMG( "data/interface/lifebar.tga", 0 );

	width = backgroundTexture->texture[0].width;
	height = backgroundTexture->texture[0].height;
	// center on screen
	posX = (dawn_configuration::screenWidth - width) / 2;
	posY = (dawn_configuration::screenHeight - height) / 2;
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
	// show screen
	DrawingHelpers::mapTextureToRect( backgroundTexture->texture[0],
	                                  posX, width,
	                                  posY, height );
	DrawingHelpers::mapTextureToRect( progressTexture->texture[0],
	                                  posX+92, progress * (width-184),
	                                  posY+92, 32 );

	// show option names (continue, quit, load, save, settings)
	int textX = posX + width / 2 - font->calcStringWidth( curText ) / 2;
	int textY = posY + height - 92 - font->getHeight();
	font->drawText( textX, textY, curText );
	//std::cout << "drawing loading screen" << std::endl;
}

void LoadingScreen::setCurrentText( std::string text )
{
	this->curText = text;
}

void LoadingScreen::setProgress( double progress )
{
	this->progress = progress;
}




