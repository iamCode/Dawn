#include "GameLoopHandler.h"

void GameLoopHandler::setDone()
{
	this->finishMe = true;
}

bool GameLoopHandler::isDone()
{
	return this->finishMe;
}

// MainMenuHandler

#include "threadObject/Thread.h"
#include "GLee/GLee.h"
#include "GL/gl.h"
#include "FramesBase.h"
extern std::vector <FramesBase*> activeFrames;
#include "configuration.h"

void MainMenuHandler::activate( SDL_Event *lastEvent )
{
	this->lastEvent = lastEvent;
	mouseButtonDown = false;
	finishMe = false;
}

void MainMenuHandler::drawScene()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity(); // reset view to 0,0

	SDL_Event &event = *lastEvent;
	for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame ) {
		activeFrames[curFrame]->draw( event.motion.x, Configuration::screenHeight - event.motion.y - 1 );
	}
	
	SDL_GL_SwapBuffers();
}

void MainMenuHandler::handleEvents()
{
	while (SDL_PollEvent(lastEvent) ) {
		if (lastEvent->type == SDL_MOUSEBUTTONDOWN) {
			if ( ! mouseButtonDown ) {
				mouseButtonDown = true;
				// iterate through all our active frames and click on them if mouse is over.
				for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame ) {
					if ( activeFrames[ curFrame ]->isMouseOnFrame( lastEvent->motion.x, Configuration::screenHeight - lastEvent->motion.y - 1 ) ) {
						activeFrames[ curFrame ]->clicked( lastEvent->motion.x, Configuration::screenHeight - lastEvent->motion.y - 1, lastEvent->button.button );
					}
				}
			}
		} else {
			mouseButtonDown = false;
		}
	}
}

void MainMenuHandler::updateScene()
{
}

void MainMenuHandler::finish()
{
}

// LoadingScreenHandler

#include "LoadingManager.h"
#include "loadingscreen.h"
#include "textureframe.h"

TextureFrame *textureFrame = NULL;
DawnInitObject *curTextureProcessor = NULL;
bool initPhase = false;

extern uint32_t imgLoadTime;
extern uint32_t sdlLoadTime;
extern uint32_t imgInversionTime;
extern uint32_t mipmapBuildTime;
extern uint32_t debugOutputTime;

extern GLFT_Font *fpsFont;
extern CMessage message;

LoadingScreenHandler::LoadingScreenHandler( LoadingScreen *loadingScreen, LoadingManager *loadingManager )
{
	this->loadingScreen = loadingScreen;
	this->loadingManager = loadingManager;
}

void LoadingScreenHandler::activate( SDL_Event *lastEvent )
{
	this->lastEvent = lastEvent;
	lastTicks = SDL_GetTicks();
	curTicks = lastTicks;
	
	initStartTicks = SDL_GetTicks();
	drawingTime = 0;

	imgLoadTime = 0;
	sdlLoadTime = 0;
	imgInversionTime = 0;
	debugOutputTime = 0;
	
	initPhase = true;
	textureFrame = new TextureFrame();
	
	loadingManager->startBackgroundThread();
}

void LoadingScreenHandler::drawScene()
{
	curTicks = SDL_GetTicks();
	if ( curTicks-lastTicks >= 200 )
	{
		lastTicks = curTicks;
		
		loadingScreen->setCurrentText( loadingManager->getActivityText() );
		loadingScreen->setProgress( loadingManager->getProgress() );
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		loadingScreen->draw();
		SDL_GL_SwapBuffers();
		drawingTime += SDL_GetTicks()-curTicks;
	}
}

void LoadingScreenHandler::handleEvents()
{
	// just ignore the events
	while (SDL_PollEvent(lastEvent) ) {
		// do nothing
	}
}

void LoadingScreenHandler::updateScene()
{
	if ( ! loadingManager->isFinished() ) {
		loadingManager->executeMainThreadActions();
	} else {
		setDone();
	}
}

void LoadingScreenHandler::finish()
{
	textureFrame->finishFrame();
	delete textureFrame;
	
	loadingManager->finish();

	initPhase = false;
	
	optionsWindow->setTextureDependentPositions();
	inventoryScreen->setTextureDependentPositions();
	
	fpsFont = FontCache::getFontFromCache("data/verdana.ttf", 12);
	message.initFonts();
	Editor.initFonts();
	characterInfoScreen->initFonts();
    actionBar->initFonts();
    GUI.initFonts();
    logWindow->clear(); 

	uint32_t initTime = SDL_GetTicks()-initStartTicks;
	std::cout << "initialization took " << initTime << " ms" << std::endl;
	std::cout << "included are " << imgLoadTime << " ms for image loading (" << sdlLoadTime << " ms for IMG_Load, " << imgInversionTime << " for image Y-inversion, " << mipmapBuildTime << " ms for mipmap-building, total >= " << (100*(sdlLoadTime+imgInversionTime+mipmapBuildTime))/imgLoadTime << "% of LoadIMG submeasured)" << std::endl;
	std::cout << "included are " << debugOutputTime << " ms for debug output" << std::endl;
	std::cout << "included are " << drawingTime << " ms for menu drawing" << std::endl;
	std::cout << "total submeasures cover >= " << (100*(imgLoadTime+debugOutputTime+drawingTime)/initTime) << "% of init time" << std::endl;
}

void processTextureInOpenGLThread( CTexture *texture, std::string textureFile, int textureIndex, int textureOffsetX, int textureOffsetY )
{
	curTextureProcessor->setCurrentTextureToProcess( texture, textureFile, textureIndex, textureOffsetX, textureOffsetY );
}

void processFontInOpenGLThread( GLFT_Font *font, const std::string &filename, unsigned int size )
{
	curTextureProcessor->setCurrentFontToProcess( font, filename, size );
}

