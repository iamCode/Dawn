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
	SDL_Event &event = *lastEvent;
	for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame ) {
		activeFrames[curFrame]->draw( event.motion.x, Configuration::screenHeight - event.motion.y - 1 );
	}
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
