#include "loadingscreen.h"

#include "CTexture.h"
#include "CDrawingHelpers.h"
#include "GLFT_Font.h"

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

	font = new GLFT_Font("data/verdana.ttf", 20);
	backgroundTexture = new CTexture();
	backgroundTexture->texture.reserve(1);
	backgroundTexture->LoadIMG( "data/interface/LoadingScreen/loadingScreen.tga", 0 );
	progressTexture = new CTexture();
	progressTexture->texture.reserve(1);
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
	if ( font != NULL ) {
		delete font;
	}
}

void LoadingScreen::draw()
{
	// show screen
	DrawingHelpers::mapTextureToRect( backgroundTexture->texture[0].texture,
	                                  posX, width,
	                                  posY, height );
	DrawingHelpers::mapTextureToRect( progressTexture->texture[0].texture,
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




