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

#include "threadObject/Thread.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <csignal>
#include <deque>

#include "GLee/GLee.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_getenv.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "GLFT_Font.h"
#include "pnglite/pnglite.h"

#include "zone.h"
#include "interface.h"
#include "editor.h"
#include "inventoryscreen.h"
#include "utils.h"
#include "actionbar.h"
#include "buffwindow.h"
#include "shop.h"
#include "debug.h"
#include "interactionpoint.h"
#include "textwindow.h"
#include "questwindow.h"
#include "optionswindow.h"
#include "loadingscreen.h"
#include "globals.h"
#include "logwindow.h"
#include "soundengine.h"
#include "configuration.h"
#include "frames.h"
#include "gameloophandler.h"
#include "configuredframes.h"
#include "resolution.h"
#include "testinterface.h"
#include "loadingmanager.h"

#ifdef _WIN32
#define SDLK_PRINT 316 // this is because Windows printscreen doesn't match the SDL predefined keycode.
#endif

/* Global settings now reside in the
   Configuration namespace, variables
   are added to this across multiple files.
   current headers adding to it:
   debug.h
 */

// FIXME: This is a temp hack until the
// 	objects dont need those variables.
//	david: I'll have this sorted pretty
//	quick.
int world_x = 0, world_y = 0;
int mouseX, mouseY;
int done = 0;
CMessage message;


SDL_Surface *screen;
cameraFocusHandler focus;

CEditor Editor;

CInterface GUI;

std::vector<FramesBase*> activeFrames;

float lastframe,thisframe;	// FPS Stuff
int ff, fps;	            // FPS Stuff

GLFT_Font *fpsFont;
std::auto_ptr<CharacterInfoScreen> characterInfoScreen;
std::auto_ptr<InventoryScreen> inventoryScreen;
std::auto_ptr<ActionBar> actionBar;
std::auto_ptr<Spellbook> spellbook;
std::auto_ptr<BuffWindow> buffWindow;
std::auto_ptr<QuestWindow> questWindow;
std::auto_ptr<OptionsWindow> optionsWindow;
std::auto_ptr<Shop> shopWindow;
std::auto_ptr<LogWindow> logWindow;
std::auto_ptr<ConfigurableFrame> optionsFrame( new ConfigurableFrame( 100, 100, 100, 100, DawnState::OptionsMenu ) );
std::auto_ptr<ConfigurableFrame> mainMenuFrame( new ConfigurableFrame( 100, 100, 0, 0, DawnState::MainMenu ) );
std::auto_ptr<ConfigurableFrame> chooseClassFrame( new ConfigurableFrame( 100, 100, 0, 0, DawnState::ChooseClass ) );
std::auto_ptr<LoadingScreen> loadingScreen;

std::auto_ptr<GameLoopHandler> mainMenuHandler( new MainMenuHandler() );

GameLoopHandler *currentGameLoopHandler = NULL;
GameLoopHandler *nextGameLoopHandler = NULL;

void setNextGameLoopHandler( GameLoopHandler *nextHandler )
{
	nextGameLoopHandler = nextHandler;
}

namespace Globals
{
	std::map< std::string, CZone* > allZones;
	std::vector< std::pair<CSpellActionBase*, uint32_t> > activeAoESpells;
}

static bool HandleCommandLineAurguments(int argc, char** argv)
{
	bool run_game = true;
	std::string executable(argv[0]);
#ifdef _WIN32
	freopen( "CON", "wt", stdout ); // Redirect stdout to the command line
#endif
	for( int i=1; i < argc; ++i )
	{
		std::string currentarg(argv[i]);
		if( currentarg == "-f" || currentarg == "--fullscreen" )
		{
			Configuration::fullscreenenabled = true;
		}
		else if( currentarg == "-w" || currentarg == "--window" )
		{
			Configuration::fullscreenenabled = false;
		}
		else if( currentarg == "--nosound" )
		{
			Configuration::soundenabled = false;
		#ifdef TESTINTERFACE
		}
		else if( currentarg == "-T" || currentarg == "--test" )
		{
			TestInterface::executeTest( argv[i+1] );
			i++;
		#endif
		}
		else if( currentarg == "-h" || currentarg == "--help" )
		{
			std::cout << "Dawn-RPG Startup Parameters" <<
			          std::endl << std::endl <<
			          " -f, --fullscreen         Run Dawn in fullscreen mode" <<
			          std::endl <<
			          " -w, --window             Run Dawn inside a window" <<
			          std::endl <<
			          " --nosound                Run Dawn without sound" <<
			          std::endl <<
			          " -h, --help               Show this help screen" <<
			          #ifdef TESTINTERFACE
                          " -T, --test FILE          Run Dawn testcase" <<
			              std::endl <<
			          #endif
			          std::endl;
			run_game = false;
		}
		else
		{
			std::cout << std::endl <<"\"" << currentarg <<
			          "\" is not a recognised option" << std::endl << std::endl <<
			          "Please type \"" << executable <<
			          " -h\" for all available options" << std::endl <<
			          std::endl;
			run_game = false;
			break;
		}
	}
#ifdef _WIN32
	freopen( "stdout.txt", "wt", stdout ); // Redirect stdout back to the file
#endif
	return run_game;
}

namespace DawnInterface
{
	CNPC* addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn )
	{
		CNPC* newMob = new CNPC( 0, 0, 0, 0, 0 );
		newMob->baseOnType( mobID );
		newMob->setSpawnInfo( x_pos, y_pos, respawn_rate, do_respawn );
		newMob->setActiveGUI( &GUI );
		Globals::getCurrentZone()->addNPC( newMob );
		return newMob;
	}

	void removeMobSpawnPoint( CNPC* mobSpawnPoint )
	{
		Globals::getCurrentZone()->removeNPC( mobSpawnPoint );
	}

	void setCurrentZone( std::string zoneName )
	{
		if ( Globals::allZones[ zoneName ] == NULL ) {
			Globals::allZones[ zoneName ] = new CZone();
		}
		CZone* newCurZone = Globals::allZones[ zoneName ];
		Globals::setCurrentZone( newCurZone );
	}
}

void deactivateCurrentGameLoopHandler()
{
	currentGameLoopHandler->setDone();
}

void DrawScene()
{
	//glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslated(-focus.getX(), -focus.getY(),0);

	/* FIXME, TEMPORARY HACK: this is a quick fix, world_* should be
	 * removed once Editor and GUI don't need them */
	world_x = focus.getX();
	world_y = focus.getY();

	glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 50% Alpha ( NEW )

	CZone* curZone = Globals::getCurrentZone();

	curZone->DrawZone();

	// draw items on the ground
	curZone->getGroundLoot()->draw();

	// draw AoE spells
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeAoESpells = Globals::getActiveAoESpells();
	for( size_t curActiveAoESpellNr = 0; curActiveAoESpellNr < activeAoESpells.size(); ++curActiveAoESpellNr )
	{
		if( !activeAoESpells[curActiveAoESpellNr].first->isEffectComplete() )
		{
			activeAoESpells[curActiveAoESpellNr].first->drawEffect();
		}
	}

	// draw the interactions on screen
	std::vector<InteractionPoint*> zoneInteractionPoints = curZone->getInteractionPoints();
	for( size_t curInteractionNr=0; curInteractionNr<zoneInteractionPoints.size(); ++curInteractionNr )
	{
		InteractionPoint *curInteraction = zoneInteractionPoints[curInteractionNr];
		curInteraction->draw();
	}

	// draw the NPC
	std::vector<CNPC*> zoneNPCs = curZone->getNPCs();
	for( unsigned int x=0; x<zoneNPCs.size(); x++ )
	{
		CNPC *curNPC = zoneNPCs[x];
		curNPC->Draw();
	}

	Player* player = Globals::getPlayer();
	player->Draw();

	for( unsigned int x=0; x<zoneNPCs.size(); x++ )
	{
		CNPC *curNPC = zoneNPCs[x];
		if( player->getTarget() == curNPC )
		{
			GUI.drawTargetedNPCText();
		}

		// draw the spell effects for our NPCs
		std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = curNPC->getActiveSpells();
		for( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr )
		{
			if( !activeSpellActions[curActiveSpellNr].first->isEffectComplete() )
			{
				activeSpellActions[curActiveSpellNr].first->drawEffect();
			}
		}
	}

	// draw the spell effects for our player.
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = player->getActiveSpells();
	for( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr )
	{
		if( !activeSpellActions[ curActiveSpellNr ].first->isEffectComplete() )
		{
			activeSpellActions[ curActiveSpellNr ].first->drawEffect();
		}
	}

	// check our FPS and output it
	thisframe = SDL_GetTicks(); // Count the FPS
	ff++;
	if( ( thisframe-lastframe ) > 1000 )
	{
		fps = ff;
		ff = 0;
		lastframe = thisframe;
	}

	if( Editor.isEnabled() )
	{
		Editor.DrawEditor();
	}
	else
	{
		// draw tooltips if we're holding left ALT key.
		curZone->getGroundLoot()->drawTooltip();

		for( size_t curInteractionNr=0; curInteractionNr<zoneInteractionPoints.size(); ++curInteractionNr )
		{
			InteractionPoint *curInteraction = zoneInteractionPoints[ curInteractionNr ];
			if( curInteraction->isMouseOver( mouseX, mouseY ) )
			{
				curInteraction->drawInteractionSymbol( mouseX, mouseY, player->getXPos(), player->getYPos() );
			}
		}

		actionBar->draw();
		logWindow->draw();
		GUI.DrawInterface();
	}

	// loop through our vector of active frames and draw them. If they are in the vector they are visible...
	for( size_t curFrame = 0; curFrame < activeFrames.size(); curFrame++ )
	{
		activeFrames[ curFrame ]->draw( mouseX, mouseY );
	}

	if( actionBar->isMouseOver( mouseX, mouseY ) && !spellbook->hasFloatingSpell() && Editor.isEnabled() == false)
	{
		actionBar->drawSpellTooltip( mouseX, mouseY );
	}

	shopWindow->drawItemTooltip( mouseX, mouseY );
	shopWindow->drawFloatingSelection( world_x + mouseX, world_y + mouseY );
	inventoryScreen->drawItemTooltip( mouseX, mouseY );
	inventoryScreen->drawFloatingSelection( world_x + mouseX, world_y + mouseY );
	spellbook->drawFloatingSpell( mouseX, mouseY );

	// note: we need to cast fpsFont.getHeight to int since otherwise the whole expression would be an unsigned int
	//       causing overflow and not drawing the font if it gets negative

	// I've removed this text for now, just for a cleaner look. Enable it if you need some info while coding. /Arnestig
	//fpsFont->drawText(focus.getX(), focus.getY()+Configuration::screenHeight - static_cast<int>(fpsFont->getHeight()), "FPS: %d     world_x: %2.2f, world_y: %2.2f      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps,focus.getX(),focus.getY(), character.x_pos, character.y_pos, mouseX, mouseY);
	// Only FPS
	fpsFont->drawText( focus.getX()+Configuration::screenWidth-100, focus.getY()+Configuration::screenHeight - static_cast<int>(fpsFont->getHeight()), "FPS: %d",fps );

	message.DrawAll();
	message.DeleteDecayed();

	GUI.DrawCursor();

	SDL_GL_SwapBuffers();
}


void dawn_init_signal_handlers()
{
	#ifndef WIN32
	dawn_debug_info("Initializing signal handlers...");
	signal( SIGFPE,  generalSignalHandler );
	signal( SIGSEGV, generalSignalHandler );
	signal( SIGBUS,  generalSignalHandler );
	signal( SIGABRT, generalSignalHandler );
	#endif
}

class DawnInitObject;
bool threadedMode = false;

//extern int64_t numCharactersDrawn;
int64_t numTexturesDrawn = 0;

bool dawn_init( int argc, char* argv[] )
{
	if( !HandleCommandLineAurguments( argc, argv ) )
	{
		return false;
	}

	std::string sdlVideoCenteredParam( "SDL_VIDEO_CENTERED=1" );
	putenv( const_cast<char*>(sdlVideoCenteredParam.c_str()) );

	dawn_debug_info( "Initializing..." );
	dawn_init_signal_handlers();
	dawn_debug_info("Checking if the game data exists");

	if( !utils::file_exists( "data/spells.lua" ) )
	{
		dawn_debug_fatal( "The LUA script \"spells.lua\"", "Could not be found" );
	}

	if( !utils::file_exists("data/mobdata.all" ) )
	{
		dawn_debug_fatal( "The LUA script \"mobdata.all\"", "Could not be found" );
	}

	if( !utils::file_exists( "data/itemdatabase.lua" ) )
	{
		dawn_debug_fatal( "The LUA script \"itemdatabase.lua\"", "Could not be found" );
	}

	if( !utils::file_exists( "data/gameinit.lua" ) )
	{
		dawn_debug_fatal( "The LUA script \"gameinit.lua\"", "Could not be found" );
	}

	if( !utils::file_exists( "data/verdana.ttf" ) )
	{
		dawn_debug_fatal( "Font  \"verdana.ttf\"", "Could not be found" );
	}

	if( SDL_Init( SDL_INIT_AUDIO|SDL_INIT_VIDEO ) < 0 )
	{
		dawn_debug_fatal( "Unable to init SDL: %s", SDL_GetError() );
	}

	atexit( SDL_Quit );

	dawn_debug_info( "checking configured and possible resolutions" );
	Resolution configResolution( Configuration::screenWidth,
	                             Configuration::screenHeight,
	                             Configuration::bpp,
	                             Configuration::fullscreenenabled );

	bool configResolutionWorks = Resolution::checkResolution( configResolution );

	if( configResolutionWorks )
	{
		Configuration::addPossibleResolution( configResolution.width, configResolution.height, configResolution.bpp, configResolution.fullscreen );
	}

	Resolution::scanPossibleResolutions();

	if( !configResolutionWorks )
	{
		dawn_debug_warn( "configured resolution does not work. Trying to use another resolution." );

		if ( Resolution::getPossibleResolutions().size() == 0 )
		{
			dawn_debug_fatal("no working resolution found!");
		}

		configResolution	                = Resolution::getBestResolution( Configuration::fullscreenenabled );
		Configuration::screenWidth	        = configResolution.width;
		Configuration::screenHeight	        = configResolution.height;
		Configuration::bpp	                = configResolution.bpp;
		Configuration::fullscreenenabled	= configResolution.fullscreen;
	}

	Resolution::setResolution( screen, configResolution );

	if ( !screen )
	{
		dawn_debug_fatal( "Unable to set resolution" );
	}

	SoundEngine::initSound();
	SoundEngine::playMusic( "data/music/loading.ogg", true );

	glEnable( GL_TEXTURE_2D );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glViewport( 0, 0, Configuration::screenWidth, Configuration::screenHeight );

	glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity(); // reset view to 0,0

	glOrtho( 0.0f, Configuration::screenWidth, 0.0f, Configuration::screenHeight, -1.0f, 1.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity(); // reset view to 0,0

	glEnable( GL_BLEND ); // enable blending
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_DEPTH_TEST ); // Turn Depth Testing Off

	currentGameLoopHandler = mainMenuHandler.get();

	/// choose class here. Will be moved later when we have a real character creation page, start page etc.. works for now.
	Frames::initFrameTextures();
	DrawFunctions::initDrawTextures();

	ConfiguredFrames::fillOptionsFrame( optionsFrame.get() );
	ConfiguredFrames::fillMainMenuFrame( mainMenuFrame.get() );
	ConfiguredFrames::fillChooseClassFrame( chooseClassFrame.get() );

	activeFrames.push_back( mainMenuFrame.get() );
	mainMenuFrame->setVisible( true );

	loadingScreen = std::auto_ptr<LoadingScreen>(new LoadingScreen());
	return true;
}

void setQuitGame()
{
	deactivateCurrentGameLoopHandler();
	setNextGameLoopHandler( NULL );
}

void game_loop()
{
	SDL_Event lastEvent;

	// activate first game loop handler
	if( currentGameLoopHandler != NULL )
	{
		currentGameLoopHandler->activate( &lastEvent );
	}

	while( currentGameLoopHandler != NULL )
	{
		currentGameLoopHandler->handleEvents();

		if( !Globals::isPaused() )
			currentGameLoopHandler->updateScene();

		// reset drawing context
		currentGameLoopHandler->drawScene();

		if( currentGameLoopHandler->isDone() )
		{
			currentGameLoopHandler->finish();
			currentGameLoopHandler = nextGameLoopHandler;
			nextGameLoopHandler = NULL;
			if ( currentGameLoopHandler != NULL )
			{
				currentGameLoopHandler->activate( &lastEvent );
			}
		}
	}
}

int main(int argc, char* argv[])
{
	// init random number generator
	RNG::initRNG( time( 0 ) );

	// load settings
	LuaFunctions::executeLuaFile( "settings.lua" );

	if( dawn_init( argc, argv ) )
	{
		std::auto_ptr<GameScreenHandler> gameLoopHandler( new GameScreenHandler() );
		std::auto_ptr<LoadingScreenHandler> loadingScreenHandler( new LoadingScreenHandler( loadingScreen.get(), new DawnInitObject() ) );
		loadingScreenHandler->setFollowHandler( gameLoopHandler.get() );
		nextGameLoopHandler = loadingScreenHandler.get();
		game_loop();
	}

	return 0;
}
