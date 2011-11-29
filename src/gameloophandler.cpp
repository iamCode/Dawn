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

#include "gameloophandler.h"
#include "dawnstate.h"

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
#include <GL/gl.h>
#include "framesbase.h"
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

	for( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
	{
		activeFrames[curFrame]->draw( lastEvent->motion.x, Configuration::screenHeight - lastEvent->motion.y - 1 );
	}

	SDL_GL_SwapBuffers();
}

void MainMenuHandler::handleEvents()
{
	while( SDL_PollEvent( lastEvent ) )
	{
		if(lastEvent->type == SDL_MOUSEBUTTONDOWN)
		{
			if( !mouseButtonDown )
			{
				mouseButtonDown = true;
				// iterate through all our active frames and click on them if mouse is over.
				for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
				{
					activeFrames[ curFrame ]->clicked( lastEvent->motion.x, Configuration::screenHeight - lastEvent->motion.y - 1, lastEvent->button.button );
				}
			}
		}
		else
		{
			mouseButtonDown = false;
		}
	}
}

void MainMenuHandler::updateScene()
{
}

void MainMenuHandler::finish()
{
	activeFrames.clear();
}

// LoadingScreenHandler

#include "loadingmanager.h"
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

void setNextGameLoopHandler( GameLoopHandler *nextHandler );

LoadingScreenHandler::LoadingScreenHandler( LoadingScreen *loadingScreen, LoadingManager *loadingManager )
{
	this->loadingScreen = loadingScreen;
	this->loadingManager = loadingManager;

}

void LoadingScreenHandler::activate( SDL_Event *lastEvent )
{
	this->lastEvent = lastEvent;

	finishMe = false;

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

	SDL_ShowCursor(false);

	loadingManager->startBackgroundThread();
//	DawnState::setDawnState( DawnState::LoadingScreen );
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
	// just ignore the lastEvents
	while(SDL_PollEvent(lastEvent) )
	{
		// do nothing
	}
}

void LoadingScreenHandler::updateScene()
{
	if( !loadingManager->isFinished() )
	{
		loadingManager->executeMainThreadActions();
	}
	else
	{
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

	fpsFont = FontCache::getFontFromCache( "data/verdana.ttf", 12 );
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

	if( nextHandler != NULL )
	{
		setNextGameLoopHandler( nextHandler );
	}
}

void LoadingScreenHandler::setFollowHandler( GameLoopHandler *nextHandler )
{
	this->nextHandler = nextHandler;
}

void processTextureInOpenGLThread( CTexture *texture, std::string textureFile, int textureIndex, int textureOffsetX, int textureOffsetY )
{
	curTextureProcessor->setCurrentTextureToProcess( texture, textureFile, textureIndex, textureOffsetX, textureOffsetY );
}

void processFontInOpenGLThread( GLFT_Font *font, const std::string &filename, unsigned int size )
{
	curTextureProcessor->setCurrentFontToProcess( font, filename, size );
}

// GameScreenHandler

#include "interactionpoint.h"
#include "interactionregion.h"
#include "textwindow.h"
#include "utils.h"

extern std::vector<TextWindow*> allTextWindows;
extern cameraFocusHandler focus;

bool KP_interrupt = false;
bool KP_select_next = false;
bool KP_screenshot = false;
bool KP_toggle_showCharacterInfo = false;
bool KP_toggle_showInventory = false;
bool KP_toggle_showSpellbook = false;
bool KP_toggle_showQuestWindow = false;
bool KP_toggle_showOptionsWindow = false;

#ifdef _WIN32
	#define TOOLTIP_KEY SDLK_LALT
#else
	// there ALT + mouseclick seems to be moving windows under X or at least KDE
	#define TOOLTIP_KEY SDLK_LCTRL
#endif

void GameScreenHandler::activate( SDL_Event* lastEvent )
{
	this->lastEvent = lastEvent;

	finishMe = false;

	lastTicks = SDL_GetTicks();
	curTicks = lastTicks;
	ticksDiff = 0;

	Player* player = Globals::getPlayer();
	focus.setFocus(player);

	GLfloat color[] = { 1.0f, 1.0f, 0.0f };
	DawnInterface::addTextToLogWindow( color, "Welcome to the world of Dawn, %s.", player->getName().c_str() );
	DawnState::setDawnState( DawnState::InGame );
}

void GameScreenHandler::handleEvents()
{
	if( Editor.isEnabled() )
	{
		Editor.HandleKeys();
		lastTicks = SDL_GetTicks();
		curTicks  = lastTicks;
		ticksDiff = 0;
		return;
	}

	Player* player = Globals::getPlayer();

	while( SDL_PollEvent( lastEvent ) )
	{
		if( lastEvent->type == SDL_QUIT )
		{
			done = 1;
		}

		std::pair<int,int> mouseDownXY;

		if( lastEvent->type == SDL_MOUSEBUTTONDOWN )
		{
			mouseDownXY = std::pair<int,int>( mouseX, mouseY );

			bool clickedInFrame = false;

			// iterate through all our active frames and click on them if mouse is over.
			for( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
			{
				if( activeFrames[ curFrame ]->isMouseOnFrame( mouseX, mouseY ) )
				{
					// check if mouse is over closebutton (if any) and then we try and close the frame
					if( activeFrames[ curFrame ]->isMouseOnCloseButton( mouseX, mouseY ) == true )
					{
						activeFrames[ curFrame ]->toggle();
						clickedInFrame = true;
						break;
					}

					// check to see if mouse is over titlebar, then we try to move the frame.
					if( activeFrames[ curFrame ]->isMouseOnTitlebar( mouseX, mouseY ) == true )
					{
						activeFrames[ curFrame ]->moveFrame( mouseX, mouseY );
						activeFrames[ curFrame ]->setOnTop();
						clickedInFrame = true;
						break;
					}

					activeFrames[ curFrame ]->clicked( mouseX, mouseY, lastEvent->button.button );
					activeFrames[ curFrame ]->setOnTop();
					clickedInFrame = true;
					break;
				}
			}

			// looks like we clicked without finding any frame to click on. this could mean that we want to interact with the background in some way. let's try that.
			if( clickedInFrame == false )
			{
				actionBar->clicked( mouseX, mouseY );
				buffWindow->clicked( mouseX, mouseY, lastEvent->button.button );
				if( shopWindow->hasFloatingSelection() )
				{
					shopWindow->clicked( mouseX, mouseY, lastEvent->button.button );
				}

				if( inventoryScreen->hasFloatingSelection() )
				{
					inventoryScreen->clicked( mouseX, mouseY, lastEvent->button.button );
				}

				if( spellbook->hasFloatingSpell() )
				{
					spellbook->clicked( mouseX, mouseY, lastEvent->button.button );
				}

				switch( lastEvent->button.button )
				{
					case SDL_BUTTON_LEFT:
					{
						CZone* curZone = Globals::getCurrentZone();
						curZone->getGroundLoot()->searchForItems( world_x + mouseX, world_y + mouseY );

						if( inventoryScreen->isVisible() )
						{
							InventoryItem* floatingSelection = curZone->getGroundLoot()->getFloatingSelection( world_x + mouseX, world_y + mouseY );
							if ( floatingSelection != NULL ) {
								inventoryScreen->setFloatingSelection( floatingSelection );
							}
						}

						// get and iterate through the NPCs
						std::vector<CNPC*> zoneNPCs = curZone->getNPCs();
						for( unsigned int x = 0; x < zoneNPCs.size(); x++ )
						{
							CNPC* curNPC = zoneNPCs[x];

							// is the mouse over a NPC and no AoE spell is being prepared?
							if( curNPC->CheckMouseOver( mouseX+world_x, mouseY+world_y ) && !actionBar->isPreparingAoESpell() )
							{
								// is the NPC friendly?
								if( !curNPC->getAttitude() == Attitude::FRIENDLY )
								{
									// set a target if the player has none
									if( !player->hasTarget( curNPC ) )
									{
										player->setTarget( curNPC, curNPC->getAttitude() );
									}
									else
									{
										player->setTarget( NULL );
									}
									break;
								}
							}
						}
					}
					break;

					case SDL_BUTTON_RIGHT:
					{
						// look for interactionpoints when right-clicking.
						std::vector<InteractionPoint*> zoneInteractionPoints = Globals::getCurrentZone()->getInteractionPoints();
						for( size_t curInteractionNr=0; curInteractionNr < zoneInteractionPoints.size(); ++curInteractionNr )
						{
							InteractionPoint *curInteraction = zoneInteractionPoints[ curInteractionNr ];
							if ( curInteraction->isMouseOver( mouseX, mouseY ) )
							{
								curInteraction->startInteraction( player->getXPos(), player->getYPos() );
								break;
							}
						}
					}
					break;
				}
			}
		}

		if( lastEvent->type == SDL_MOUSEMOTION )
		{
			mouseX = lastEvent->motion.x;
			mouseY = Configuration::screenHeight - lastEvent->motion.y - 1;

			// we have clicked a spell and want to drag it. we need to make sure we've dragged it far enough and are still holding in our left mouse button
			if( ( sqrt(pow(mouseDownXY.first-mouseX,2) + pow(mouseDownXY.second-mouseY,2)) > 25 ) && lastEvent->button.button == SDL_BUTTON_LEFT && !actionBar->isPreparingAoESpell() )
			{
				actionBar->dragSpell();
			}

			for( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
			{
				if( activeFrames[ curFrame ]->isMovingFrame() == true )
				{
					activeFrames[ curFrame ]->moveFrame( mouseX, mouseY );
					break;
				}
			}
		}

		if( lastEvent->type == SDL_MOUSEBUTTONUP )
		{
			if( actionBar->isPreparingAoESpell() )
			{
				actionBar->makeReadyToCast( mouseX+world_x, mouseY+world_y );
			}

			actionBar->executeSpellQueue();
			for( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
			{
				if( activeFrames[ curFrame ]->isMovingFrame() == true )
				{
					activeFrames[ curFrame ]->stopMovingFrame( mouseX, mouseY );
					break;
				}
			}
		}
	}
}

void GameScreenHandler::updateScene()
{
	Player* player = Globals::getPlayer();

	// update our quests, or remove any quest that was finished
	questWindow->tryToPurgeQuests();

	// close and possibly delete closed windows
	for( size_t curTextWindowNr=0; curTextWindowNr<allTextWindows.size(); ++curTextWindowNr )
	{
		TextWindow *curTextWindow = allTextWindows[ curTextWindowNr ];
		if( curTextWindow->canBeDeleted() == true )
		{
			curTextWindow->close();
			curTextWindow->toggle();

			delete curTextWindow;
			allTextWindows.erase( allTextWindows.begin() + curTextWindowNr );
		}
	}

	Uint8* keys = SDL_GetKeyState(NULL);

	curTicks  = SDL_GetTicks();
	ticksDiff = curTicks - lastTicks;
	lastTicks = curTicks;

	player->giveMovePoints( ticksDiff );
	player->Move();
	player->regenerateLifeManaFatigue( ticksDiff );

	std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
	for( unsigned int x = 0; x < zoneNPCs.size(); x++ )
	{
		CNPC* curNPC = zoneNPCs[x];
		if( curNPC->isAlive() )
		{
			curNPC->giveMovePoints( ticksDiff );
			curNPC->Move();
			curNPC->regenerateLifeManaFatigue( ticksDiff );
		}
		curNPC->Respawn();
		curNPC->Wander();

		// check all active spells for inEffects on our NPCs.
		curNPC->cleanupActiveSpells();
		std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = curNPC->getActiveSpells();
		for( size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr )
		{
			activeSpellActions[ curActiveSpellNr ].first->inEffect();
		}
	}

	// check all active AoE spells and see they're finished and look for inEffects and process 'em
	for( unsigned int i = 0; i < Globals::getCurrentZone()->MagicMap.size(); ++i )
	{
		Globals::getCurrentZone()->MagicMap[i]->process();
		Globals::getCurrentZone()->MagicMap[i]->getSpell()->inEffect();
		Globals::cleanupActiveAoESpells();

		if( Globals::getCurrentZone()->MagicMap[i]->isDone() )
		{
			Globals::getCurrentZone()->MagicMap.erase(Globals::getCurrentZone()->MagicMap.begin()+i);
		}
	}

	// making sure our target is still alive, not invisible and still in range while stealthed. if not well set our target to NULL.
	if( player->getTarget() )
	{
		double distance = sqrt( pow((player->getTarget()->getXPos()+player->getTarget()->getWidth()/2) - (player->getXPos()+player->getWidth()/2),2)
		                       +pow((player->getTarget()->getYPos()+player->getTarget()->getHeight()/2) - (player->getYPos()+player->getHeight()/2),2) );
		if( player->getTarget()->isAlive() == false ||
		  ( player->getTarget()->isInvisible() == true && player->canSeeInvisible() == false ) ||
		  ( player->getTarget()->isSneaking() == true && distance > 260 && player->canSeeSneaking() == false ) )
		{
			player->setTarget(NULL);
		}
	}

	// check all active spells for inEffects on our player.
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = player->getActiveSpells();
	for( size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr )
	{
		activeSpellActions[ curActiveSpellNr ].first->inEffect();
	}
	player->cleanupActiveSpells();

	std::vector<InteractionRegion*> interactionRegions = Globals::getCurrentZone()->getInteractionRegions();
	for( size_t curInteractionRegionNr=0; curInteractionRegionNr<interactionRegions.size(); ++curInteractionRegionNr )
	{
		InteractionRegion* curInteractionRegion = interactionRegions[ curInteractionRegionNr ];
		curInteractionRegion->interactWithPlayer( player );
	}

	Globals::getCurrentZone()->cleanupNPCList();
	Globals::getCurrentZone()->cleanupInteractionList();
	Globals::getCurrentZone()->cleanupInteractionRegionList();

	// something more like key handling (should it go to the handleEvents?)
	if(keys[SDLK_k]) // kill all NPCs in the zone. testing purposes.
	{
		std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
		for( unsigned int x=0; x<zoneNPCs.size(); x++ )
		{
			if( zoneNPCs[x]->isAlive() )
			{
				zoneNPCs[x]->Die();
			}
		}
	}

	if(lastEvent->key.keysym.sym == SDLK_PRINT && !KP_screenshot)
	{
		KP_screenshot = true;
		utils::takeScreenshot();
	}

	if(lastEvent->key.keysym.sym != SDLK_PRINT)
	{
		KP_screenshot = false;
	}

	if(keys[SDLK_l] && !Editor.KP_toggle_editor)
	{
		Editor.setEditZone( Globals::getCurrentZone() );
		LuaFunctions::executeLuaFile( "data/tileAdjacency.lua" );
		Editor.setEnabled( true );
		Editor.initFocus( &focus );
		Editor.KP_toggle_editor = true;
	}

	if(!keys[SDLK_l])
	{
		Editor.KP_toggle_editor = false;
	}

	if(keys[SDLK_TAB] && !KP_select_next)
	{
		KP_select_next = true;
		bool FoundNewTarget = false;
		std::vector<CNPC*> NPClist;

		// select next npc on screen
		std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
		for( size_t curNPCNr = 0; curNPCNr < zoneNPCs.size(); ++curNPCNr )
		{
			// if NPC is in on screen (might be changed to line of sight or something)
			// this makes a list of all visible NPCs, easier to select next target this way.
			// also makes sure the NPC isn't invisible or sneaking outside of our vision range.
			CNPC* curNPC = zoneNPCs[curNPCNr];
			double distance = sqrt( pow((curNPC->getXPos()+curNPC->getWidth()/2) - (player->getXPos()+player->getWidth()/2),2)
			                       +pow((curNPC->getYPos()+curNPC->getHeight()/2) - (player->getYPos()+player->getHeight()/2),2) );

			if( DrawingHelpers::isRectOnScreen( curNPC->x_pos, 1, curNPC->y_pos, 1 ) &&
			                                    curNPC->isAlive() &&
			                                    ( curNPC->isInvisible() == false || ( curNPC->isInvisible() == true && player->canSeeInvisible() == true ) ) &&
			                                    ( curNPC->isSneaking() == false || ( curNPC->isSneaking() == true && ( distance < 260 || player->canSeeSneaking() == true ) ) ) ) {
			NPClist.push_back(curNPC);
			}
		}
		// selects next target in the list, if target = NULL, set target to first NPC on the visible list.
		for( size_t curNPC = 0; curNPC < NPClist.size(); ++curNPC )
		{
			if( !player->getTarget() )
			{
				player->setTarget(NPClist[0], NPClist[0]->getAttitude());
			}

			if( player->getTarget() == NPClist[curNPC] )
			{
				if( curNPC+1 == NPClist.size() )
				{
					player->setTarget(NPClist[0], NPClist[0]->getAttitude());
				}
				else
				{
					player->setTarget( NPClist[curNPC+1], NPClist[curNPC+1]->getAttitude() );
				}
				FoundNewTarget = true;
				break;
			}
		}

		if( !FoundNewTarget && NPClist.size() > 0)
		{
			player->setTarget( NPClist[0], NPClist[0]->getAttitude() );
		}
	}

	if( keys[TOOLTIP_KEY] )
	{
		Globals::getCurrentZone()->getGroundLoot()->enableTooltips();
	}

	if( !keys[TOOLTIP_KEY] )
	{
		Globals::getCurrentZone()->getGroundLoot()->disableTooltips();
	}

	if( !keys[SDLK_TAB] )
	{
		KP_select_next = false;
	}

	/*if( keys[SDLK_ESCAPE] && !KP_toggle_showOptionsWindow ) {
		KP_toggle_showOptionsWindow = true;
		optionsWindow->toggle();
	}

	if( !keys[SDLK_ESCAPE] ) {
		KP_toggle_showOptionsWindow = false;
	}*/

	if( keys[SDLK_ESCAPE] )
	{
		if( actionBar->isPreparingAoESpell() )
		{
			actionBar->stopCastingAoE();
		}

		if( !KP_toggle_showOptionsWindow )
		{
			KP_toggle_showOptionsWindow = true;
			optionsWindow->toggle();
		}
	}

	if( !keys[SDLK_ESCAPE] )
	{
		if( KP_toggle_showOptionsWindow )
		{
			KP_toggle_showOptionsWindow = false;
		}
	}

	if( keys[SDLK_c] && !KP_toggle_showCharacterInfo )
	{
		KP_toggle_showCharacterInfo = true;
		characterInfoScreen->toggle();
	}

	if( !keys[SDLK_c] )
	{
		KP_toggle_showCharacterInfo = false;
	}

	if( keys[SDLK_b] && !KP_toggle_showSpellbook )
	{
		KP_toggle_showSpellbook = true;
		spellbook->toggle();
	}

	if( !keys[SDLK_b] )
	{
		KP_toggle_showSpellbook = false;
	}

	if( keys[SDLK_i] && !KP_toggle_showInventory )
	{
		KP_toggle_showInventory = true;
		inventoryScreen->toggle();
	}

	if( !keys[SDLK_i] )
	{
		KP_toggle_showInventory = false;
	}

	if( keys[SDLK_q] && !KP_toggle_showQuestWindow )
	{
		KP_toggle_showQuestWindow = true;
		questWindow->toggle();
	}

	if( !keys[SDLK_q] )
	{
		KP_toggle_showQuestWindow = false;
	}

	if( !optionsWindow->isVisible() )
	{
		actionBar->handleKeys();
	}

	if( keys[SDLK_5] && !KP_interrupt )
	{
		KP_interrupt = true;
		player->CastingInterrupted();
	}

	if(!keys[SDLK_5])
	{
		KP_interrupt = false;
	}

	if( keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT] )
	{
		player->setMovementSpeed( 2 );
	}
	else if( !keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT] )
	{
		player->setMovementSpeed( 1 );
	}

	//	if (keys[SDLK_BACKSPACE] && player->getTarget() != NULL) {
	//		GLfloat color[] = {255, 255, 255, 255};
	//		DawnInterface::addTextToLogWindow(color, "TarX:%d TarY:%d", player->getTarget()->getXPos(), player->getTarget()->getYPos());
	//	}

	if( keys[SDLK_p] )
	{
		GLfloat color[] = { 255, 0, 255, 255 };
		DawnInterface::addTextToLogWindow( color, "Player X: %d", player->getXPos() );
		DawnInterface::addTextToLogWindow( color, "Player Y: %d", player->getYPos() );
	}

	focus.updateFocus();
}

void DrawScene();

void GameScreenHandler::drawScene()
{
	DrawScene();
}

void GameScreenHandler::finish()
{
}
