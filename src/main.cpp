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

#include "threadObject/Thread.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <csignal>
#include <deque>

#ifdef _WIN32
	#include <windows.h> // Nothing uses this, perhaps it could be removed?
#endif

#ifdef _WIN32
	#define TOOLTIP_KEY SDLK_LALT
#else
	// there ALT + mouseclick seems to be moving windows under X or at least KDE
	#define TOOLTIP_KEY SDLK_LCTRL
#endif

#include "GLee/GLee.h" // OpenGL Easy Extention Library

#include <SDL/SDL.h> // SDL
#include <SDL/SDL_opengl.h> // SDL OpenGL
#include <SDL/SDL_image.h> // SDL Image library (image formats: BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV)
#include <SDL/SDL_getenv.h>

#include <GL/gl.h> // OpenGL
#include <GL/glu.h> // OpenGL Utility Library. This will have to be changed in updated versions, as it changes for different OS's

#include "GLFT_Font.h"
#include "pnglite/pnglite.h"

#include "MenuBase.h"
#include "CTexture.h"
#include "CZone.h"
#include "CInterface.h"
#include "CCharacter.h"
#include "CEditor.h"
#include "CMessage.h"
#include "InventoryScreen.h"
#include "cameraFocusHandler.h"
#include "utils.h"
#include "tooltip.h"
#include "ActionBar.h"
#include "Spellbook.h"
#include "BuffWindow.h"
#include "shop.h"
#include "GroundLoot.h"
#include "CLuaFunctions.h"
#include "CSpell.h"
#include "debug.h"
#include "CharacterInfoScreen.h"
#include "item.h"
#include "interactionpoint.h"
#include "interactionregion.h"
#include "textwindow.h"
#include "questwindow.h"
#include "optionswindow.h"
#include "loadingscreen.h"
#include "globals.h"
#include "FramesBase.h"
#include "LogWindow.h"
#include "textureframe.h"
#include "soundengine.h"
#include "configuration.h"
#include "ConfigurableFrame.h"
#include "Frames.h"
#include "GameLoopHandler.h"

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

extern std::vector<TextWindow*> allTextWindows;

std::vector<FramesBase*> activeFrames;

bool KP_interrupt = false;
bool KP_select_next = false;
bool KP_screenshot = false;
bool KP_toggle_showCharacterInfo = false;
bool KP_toggle_showInventory = false;
bool KP_toggle_showSpellbook = false;
bool KP_toggle_showQuestWindow = false;
bool KP_toggle_showOptionsWindow = false;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

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
std::auto_ptr<ConfigurableFrame> optionsFrame( new ConfigurableFrame( 100, 100, 100, 100 ) );
std::auto_ptr<ConfigurableFrame> mainMenuFrame( new ConfigurableFrame( 100, 100, 0, 0 ) );
std::auto_ptr<ConfigurableFrame> chooseClassFrame( new ConfigurableFrame( 100, 100, 0, 0 ) );
std::auto_ptr<LoadingScreen> loadingScreen;

std::auto_ptr<GameLoopHandler> mainMenuHandler( new MainMenuHandler() );

GameLoopHandler *currentGameLoopHandler = NULL;
GameLoopHandler *nextGameLoopHandler = NULL;

namespace Globals
{
	std::map< std::string, CZone* > allZones;
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeAoESpells;
}

static bool HandleCommandLineAurguments(int argc, char** argv)
{
	bool run_game = true;
	std::string executable(argv[0]);
#ifdef _WIN32
	freopen( "CON", "wt", stdout ); // Redirect stdout to the command line
#endif
	for (int i=1 ; i < argc ; ++i) {
		std::string currentarg(argv[i]);
		if (currentarg == "-f" || currentarg == "--fullscreen") {
			Configuration::fullscreenenabled = true;
		} else if (currentarg == "-w" || currentarg == "--window") {
			Configuration::fullscreenenabled = false;
		} else if (currentarg == "--nosound" ) {
			Configuration::soundenabled = false;
		} else if (currentarg == "-h" || currentarg == "--help") {
			std::cout << "Dawn-RPG Startup Parameters" <<
			          std::endl << std::endl <<
			          " -f, --fullscreen         Run Dawn in fullscreen mode" <<
			          std::endl <<
			          " -w, --window             Run Dawn inside a window" <<
			          std::endl <<
			          " --nosound                Run Dawn without sound" <<
			          std::endl <<
			          " -h, --help               Show this help screen" <<
			          std::endl;
			run_game = false;
		} else {
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
	CNPC *addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn )
	{
		CNPC *newMob = new CNPC(0, 0, 0, 0, 0);
		newMob->baseOnType( mobID );
		newMob->setSpawnInfo( x_pos, y_pos, respawn_rate, do_respawn );
		newMob->setActiveGUI( &GUI );
		Globals::getCurrentZone()->addNPC( newMob );
		return newMob;
	}

	void removeMobSpawnPoint( CNPC *mobSpawnPoint )
	{
		Globals::getCurrentZone()->removeNPC( mobSpawnPoint );
	}

	void setCurrentZone( std::string zoneName )
	{
		if ( Globals::allZones[ zoneName ] == NULL ) {
			Globals::allZones[ zoneName ] = new CZone();
		}
		CZone *newCurZone = Globals::allZones[ zoneName ];
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

	CZone *curZone = Globals::getCurrentZone();

	curZone->DrawZone();

	// draw items on the ground
	curZone->getGroundLoot()->draw();

	//draw AoE spells
	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeAoESpells = Globals::getActiveAoESpells();
	for ( size_t curActiveAoESpellNr = 0; curActiveAoESpellNr < activeAoESpells.size(); ++curActiveAoESpellNr ) {
		if ( ! activeAoESpells[ curActiveAoESpellNr ].first->isEffectComplete() ) {
				activeAoESpells[ curActiveAoESpellNr ].first->drawEffect();
		}
	}

	// draw the interactions on screen
	std::vector<InteractionPoint*> zoneInteractionPoints = curZone->getInteractionPoints();
	for ( size_t curInteractionNr=0; curInteractionNr<zoneInteractionPoints.size(); ++curInteractionNr ) {
		InteractionPoint *curInteraction = zoneInteractionPoints[ curInteractionNr ];
		curInteraction->draw();
	}

	// draw the NPC
	std::vector<CNPC*> zoneNPCs = curZone->getNPCs();
	for (unsigned int x=0; x<zoneNPCs.size(); x++)
	{
		CNPC *curNPC = zoneNPCs[x];
		curNPC->Draw();
	}

	Player *player = Globals::getPlayer();
	player->Draw();

	for (unsigned int x=0; x<zoneNPCs.size(); x++)
	{
		CNPC *curNPC = zoneNPCs[x];
		if ( player->getTarget() == curNPC )
		{
			GUI.drawTargetedNPCText();
		}

		// draw the spell effects for our NPCs
		std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = curNPC->getActiveSpells();
		for ( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
						if ( ! activeSpellActions[ curActiveSpellNr ].first->isEffectComplete() ) {
								activeSpellActions[ curActiveSpellNr ].first->drawEffect();
						}
				}
		}
	// draw the spell effects for our player.
		std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = player->getActiveSpells();
		for ( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
				if ( ! activeSpellActions[ curActiveSpellNr ].first->isEffectComplete() ) {
						activeSpellActions[ curActiveSpellNr ].first->drawEffect();
				}
		}

	// check our FPS and output it
	thisframe=SDL_GetTicks();     // Count the FPS
	ff++;
	if ((thisframe-lastframe) > 1000) {
		fps=ff;
		ff=0;
		lastframe=thisframe;
	}

	if (Editor.isEnabled() ) {
		Editor.DrawEditor();
	} else {

	  // draw tooltips if we're holding left ALT key.
    curZone->getGroundLoot()->drawTooltip();

    for ( size_t curInteractionNr=0; curInteractionNr<zoneInteractionPoints.size(); ++curInteractionNr ) {
      InteractionPoint *curInteraction = zoneInteractionPoints[ curInteractionNr ];
      if ( curInteraction->isMouseOver(mouseX, mouseY) ) {
        curInteraction->drawInteractionSymbol( mouseX, mouseY, player->getXPos(), player->getYPos() );
      }
    }

    actionBar->draw();
    logWindow->draw();
    GUI.DrawInterface();
	}

	// loop through our vector of active frames and draw them. If they are in the vector they are visible...
	for ( size_t curFrame = 0; curFrame < activeFrames.size(); curFrame++ )
	{
	    activeFrames[ curFrame ]->draw( mouseX, mouseY );
	}

	if ( actionBar->isMouseOver( mouseX, mouseY ) && !spellbook->hasFloatingSpell() && Editor.isEnabled() == false)
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
	fpsFont->drawText(focus.getX()+Configuration::screenWidth-100, focus.getY()+Configuration::screenHeight - static_cast<int>(fpsFont->getHeight()), "FPS: %d",fps);

	message.DrawAll();
	message.DeleteDecayed();

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

extern int64_t numCharactersDrawn;
int64_t numTexturesDrawn = 0;


bool dawn_init(int argc, char** argv)
{
		if(!HandleCommandLineAurguments(argc, argv))
			return false;

		std::string sdlVideoCenteredParam( "SDL_VIDEO_CENTERED=1" );
		putenv( const_cast<char*>(sdlVideoCenteredParam.c_str()) );

		dawn_debug_info("Initializing...");
		dawn_init_signal_handlers();
		dawn_debug_info("Checking if the game data exists");

		if(!utils::file_exists("data/spells.lua"))
			dawn_debug_fatal("The LUA script \"spells.lua\", "
				"Could not be found");
		if(!utils::file_exists("data/mobdata.all"))
			dawn_debug_fatal("The LUA script \"mobdata.all\", "
				"Could not be found");
		if(!utils::file_exists("data/itemdatabase.lua"))
			dawn_debug_fatal("The LUA script \"itemdatabase.lua\", "
				"Could not be found");
		if(!utils::file_exists("data/gameinit.lua"))
			dawn_debug_fatal("The LUA script \"gameinit.lua\", "
					"Could not be found");
		if(!utils::file_exists("data/verdana.ttf"))
			dawn_debug_fatal("Font  \"verdana.ttf\", "
				"Could not be found");

		if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
			dawn_debug_fatal("Unable to init SDL: %s", SDL_GetError());

		atexit(SDL_Quit);

		if (Configuration::fullscreenenabled)
			screen = SDL_SetVideoMode(Configuration::screenWidth,
			                          Configuration::screenHeight, Configuration::bpp,
			                          SDL_OPENGL | SDL_FULLSCREEN);
		else
			screen = SDL_SetVideoMode(Configuration::screenWidth,
			                          Configuration::screenHeight, Configuration::bpp,
			                          SDL_OPENGL);

		if ( !screen )
			dawn_debug_fatal("Unable to set resolution");

		SoundEngine::initSound();
		SoundEngine::playMusic("data/music/loading.ogg", true);

        glEnable( GL_TEXTURE_2D );

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glViewport( 0, 0, Configuration::screenWidth, Configuration::screenHeight );

		glClear( GL_COLOR_BUFFER_BIT );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity(); // reset view to 0,0

		glOrtho(0.0f, Configuration::screenWidth, 0.0f, Configuration::screenHeight, -1.0f, 1.0f);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  // reset view to 0,0

		glEnable( GL_BLEND ); // enable blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

		currentGameLoopHandler = mainMenuHandler.get();
		
        /// choose class here. Will be moved later when we have a real character creation page, start page etc.. works for now.
		Frames::initFrameTextures();
		DrawFunctions::initDrawTextures();

		// setup options menu frame
		optionsFrame->setAutoresize();
		optionsFrame->setCenteringLayout();
		optionsFrame->setCenterOnScreen();
		std::auto_ptr<Label> optionsFrameLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Select Options" ));
		optionsFrameLabel->setBaseColor( 1.0f, 0.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> optionsFrameBackLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Back" ));
		optionsFrameBackLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		optionsFrameBackLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> optionsFrameFullscreenLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Fullscreen" ));
		optionsFrameFullscreenLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		optionsFrameFullscreenLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		optionsFrame->setVisible( false );

		if ( ! Configuration::fullscreenenabled )
			optionsFrameFullscreenLabel->setText( "Windowed" );

		class ToggleFrameFunction : public SimpleFunctionObject
		{
			private:
				FramesBase *currentFrame;
				FramesBase *nextFrame;

			public:
				ToggleFrameFunction( FramesBase *current, FramesBase *next )
					: currentFrame( current ),
					  nextFrame( next )
				{
				}
				void operator() ()
				{
					currentFrame->toggle();
					nextFrame->toggle();
				}
		};

		optionsFrameBackLabel->setOnClicked( new ToggleFrameFunction(optionsFrame.get(), mainMenuFrame.get()) );

		class ToggleFullscreenFunction : public SimpleFunctionObject
		{
			private:
				Label *fullscreenLabel;
				bool fullscreen;
			public:
				ToggleFullscreenFunction( Label *fullscreenLabel_, bool initialValue )
					: fullscreenLabel( fullscreenLabel_ ),
					  fullscreen( initialValue )
				{
				}
				void operator() ()
				{
					Configuration::fullscreenenabled = !Configuration::fullscreenenabled;
					if (Configuration::fullscreenenabled)
					{
						screen = SDL_SetVideoMode(Configuration::screenWidth,
												  Configuration::screenHeight, Configuration::bpp,
												  SDL_OPENGL | SDL_FULLSCREEN);
						if ( screen == NULL )
						{
							Configuration::fullscreenenabled = false;
							screen = SDL_SetVideoMode(Configuration::screenWidth,
													  Configuration::screenHeight, Configuration::bpp,
													  SDL_OPENGL);
						}
					}
					else
					{
						screen = SDL_SetVideoMode(Configuration::screenWidth,
												  Configuration::screenHeight, Configuration::bpp,
												  SDL_OPENGL);
						if ( screen == NULL )
						{
							Configuration::fullscreenenabled = true;
							screen = SDL_SetVideoMode(Configuration::screenWidth,
													  Configuration::screenHeight, Configuration::bpp,
													  SDL_OPENGL | SDL_FULLSCREEN);
						}
					}
					if ( Configuration::fullscreenenabled )
						fullscreenLabel->setText("Fullscreen");
					else
						fullscreenLabel->setText("Windowed");
				}
		};

		optionsFrameFullscreenLabel->setOnClicked( new ToggleFullscreenFunction( optionsFrameFullscreenLabel.get(), Configuration::fullscreenenabled ) );

		optionsFrame->addChildFrame( 10, 0, std::auto_ptr<FramesBase>(optionsFrameBackLabel.release()) );
		optionsFrame->addChildFrame( 10, 22, std::auto_ptr<FramesBase>(optionsFrameFullscreenLabel.release()) );
		optionsFrame->addChildFrame( 0, 70, std::auto_ptr<FramesBase>(optionsFrameLabel.release()) );
		
		// setup main menu frame
		mainMenuFrame->setAutoresize();
		mainMenuFrame->setCenteringLayout();
		mainMenuFrame->setCenterOnScreen();
		std::auto_ptr<Label> quitLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Quit Game" ) );
		quitLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		quitLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> optionsLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Options" ) );
		optionsLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		optionsLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> newGameLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "New Game" ) );
		newGameLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		newGameLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );

		class QuitGameFunction : public SimpleFunctionObject
		{
			void operator() ()
			{
				exit(0);
			}
		};
		
		optionsLabel->setOnClicked( new ToggleFrameFunction( mainMenuFrame.get(), optionsFrame.get() ) );
		newGameLabel->setOnClicked( new ToggleFrameFunction( mainMenuFrame.get(), chooseClassFrame.get() ) );
		quitLabel->setOnClicked( new QuitGameFunction() );

		mainMenuFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(quitLabel.release()) );
		mainMenuFrame->addChildFrame( 0, 10, std::auto_ptr<FramesBase>(optionsLabel.release()) );
		mainMenuFrame->addChildFrame( 0, 30, std::auto_ptr<FramesBase>(newGameLabel.release()) );

		activeFrames.push_back( mainMenuFrame.get() );
		mainMenuFrame->setVisible( true );
		/*
		std::auto_ptr<MenuBase> mainMenu( new MenuBase() );
        mainMenu->addMenuItem( "New game", MenuItemType::MENU );
        mainMenu->addMenuItem( "Load game", MenuItemType::MENU );
        mainMenu->addMenuItem( "Options", MenuItemType::MENU );
        mainMenu->addMenuItem( "About", MenuItemType::MENU );
        mainMenu->addMenuItem( "Quit", MenuItemType::FUNCTION );
*/
		chooseClassFrame->setAutoresize();
		chooseClassFrame->setCenteringLayout();
		chooseClassFrame->setCenterOnScreen();
		std::auto_ptr<Label> captionLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Choose class" ) );
		captionLabel->setBaseColor( 1.0f, 0.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> licheLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Liche" ) );
		licheLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		licheLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> rangerLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Ranger" ) );
		rangerLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		rangerLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> warriorLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Warrior" ) );
		warriorLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		warriorLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
		std::auto_ptr<Label> backLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Back" ) );
		backLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
		backLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );

		class ChooseClassFunction : public SimpleFunctionObject
		{
			private:
				CharacterClass::CharacterClass characterClass;
			public:
				ChooseClassFunction( CharacterClass::CharacterClass characterClass_ )
					: characterClass( characterClass_ )
				{
				}

				void operator() ()
				{
					// activate next handler
					Globals::getPlayer()->setClass( characterClass );
					deactivateCurrentGameLoopHandler();
				}
		};

		licheLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Liche ) );
		rangerLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Ranger ) );
		warriorLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Warrior ) );
		backLabel->setOnClicked( new ToggleFrameFunction( chooseClassFrame.get(), mainMenuFrame.get() ) );

		chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(backLabel.release()) );
		chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(warriorLabel.release()) );
		chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(rangerLabel.release()) );
		chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(licheLabel.release()) );
		chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(captionLabel.release()) );

		loadingScreen = std::auto_ptr<LoadingScreen>(new LoadingScreen());
		return true;
}

void setQuitGame()
{
	done = 1;
}

void game_loop_old()
{
	// TODO: Break this down into subroutines

	Uint32 lastTicks = SDL_GetTicks();
	Uint32 curTicks  = lastTicks;
	Uint32 ticksDiff = 0;
	Uint8 *keys;
	std::pair<int,int> mouseDownXY;
	done = 0;

	Player *player = Globals::getPlayer();

	focus.setFocus(player);

	GLfloat white[] = { 1.0f, 1.0f, 1.0f };

	DawnInterface::addTextToLogWindow( white, "Welcome %s to the world of Dawn!", player->getName().c_str() );

	while (!done) {
		if (Editor.isEnabled()) {
			Editor.HandleKeys();
			lastTicks = SDL_GetTicks();
			curTicks  = lastTicks;
			ticksDiff = 0;
		} else {
			SDL_Event event;


			while (SDL_PollEvent(&event)) {
						if (event.type == SDL_QUIT)  {
							done = 1;
						}

						if (event.type == SDL_MOUSEBUTTONDOWN) {
							mouseDownXY = std::pair<int,int>( mouseX, mouseY );

						bool clickedInFrame = false;

						// iterate through all our active frames and click on them if mouse is over.
						for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
						{
								if ( activeFrames[ curFrame ]->isMouseOnFrame( mouseX, mouseY ) )
								{
										// check if mouse is over closebutton (if any) and then we try and close the frame
										if ( activeFrames[ curFrame ]->isMouseOnCloseButton( mouseX, mouseY ) == true )
										{
												activeFrames[ curFrame ]->toggle();
												clickedInFrame = true;
												break;
										}

										// check to see if mouse is over titlebar, then we try to move the frame.
										if ( activeFrames[ curFrame ]->isMouseOnTitlebar( mouseX, mouseY ) == true )
										{
												activeFrames[ curFrame ]->moveFrame( mouseX, mouseY );
												activeFrames[ curFrame ]->setOnTop();
												clickedInFrame = true;
												break;
										}

										activeFrames[ curFrame ]->clicked( mouseX, mouseY, event.button.button );
										activeFrames[ curFrame ]->setOnTop();
										clickedInFrame = true;
										break;
								}
						}

						// looks like we clicked without finding any frame to click on. this could mean that we want to interact with the background in some way. let's try that.
						if ( clickedInFrame == false )
						{
								actionBar->clicked( mouseX, mouseY );
								buffWindow->clicked( mouseX, mouseY, event.button.button );
								if ( shopWindow->hasFloatingSelection() )
								{
										shopWindow->clicked( mouseX, mouseY, event.button.button );
								}

								if ( inventoryScreen->hasFloatingSelection() )
								{
										inventoryScreen->clicked( mouseX, mouseY, event.button.button );
								}

								if ( spellbook->hasFloatingSpell() )
								{
										spellbook->clicked( mouseX, mouseY, event.button.button );
								}

								switch (event.button.button) {
										case SDL_BUTTON_LEFT:
										{
												CZone *curZone = Globals::getCurrentZone();
												curZone->getGroundLoot()->searchForItems( world_x + mouseX, world_y + mouseY );

												if ( inventoryScreen->isVisible() )
												{
														InventoryItem *floatingSelection = curZone->getGroundLoot()->getFloatingSelection( world_x + mouseX, world_y + mouseY );
														if ( floatingSelection != NULL )
														{
																inventoryScreen->setFloatingSelection( floatingSelection );
														}
												}

                                                std::vector<CNPC*> zoneNPCs = curZone->getNPCs();
                                                for (unsigned int x=0; x<zoneNPCs.size(); x++) {
                                                        CNPC *curNPC = zoneNPCs[x];
                                                        if ( curNPC->CheckMouseOver(mouseX+world_x,mouseY+world_y) ) {
                                                                if ( ! curNPC->getAttitude() == Attitude::FRIENDLY ) {
                                                                        if( !player->hasTarget( curNPC ) )
                                                                            player->setTarget( curNPC, curNPC->getAttitude() );
                                                                        else
                                                                            player->setTarget( NULL );
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
												for ( size_t curInteractionNr=0; curInteractionNr < zoneInteractionPoints.size(); ++curInteractionNr ) {
														InteractionPoint *curInteraction = zoneInteractionPoints[ curInteractionNr ];
														if ( curInteraction->isMouseOver( mouseX, mouseY ) ) {
																curInteraction->startInteraction( player->getXPos(), player->getYPos() );
																break;
														}
												}
										}
										break;
								}
						}
				}

				if (event.type == SDL_MOUSEMOTION)
				{
						mouseX = event.motion.x;
						mouseY = Configuration::screenHeight - event.motion.y - 1;

                        // we have clicked a spell and want to drag it. we need to make sure we've dragged it far enough and are still holding in our left mouse button
						if ( ( sqrt(pow(mouseDownXY.first-mouseX,2) + pow(mouseDownXY.second-mouseY,2)) > 25 ) && event.button.button == SDL_BUTTON_LEFT && !actionBar->isPreparingAoESpell() )
						{
								actionBar->dragSpell();
						}

						for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
						{
								if ( activeFrames[ curFrame ]->isMovingFrame() == true )
								{
										activeFrames[ curFrame ]->moveFrame( mouseX, mouseY );
										break;
								}
						}
				}

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					if( actionBar->isPreparingAoESpell() )
						actionBar->makeReadyToCast( mouseX+world_x, mouseY+world_y );

					actionBar->executeSpellQueue();
					for ( int curFrame = activeFrames.size()-1; curFrame >= 0; --curFrame )
					{
							if ( activeFrames[ curFrame ]->isMovingFrame() == true )
							{
									activeFrames[ curFrame ]->stopMovingFrame( mouseX, mouseY );
									break;
							}
					}
				}
	}

			// close and possibly delete closed windows
			for ( size_t curTextWindowNr=0; curTextWindowNr<allTextWindows.size(); ++curTextWindowNr ) {
				TextWindow *curTextWindow = allTextWindows[ curTextWindowNr ];
				if ( curTextWindow->canBeClosed() ) {
						curTextWindow->close();
						curTextWindow->toggle();
						if ( curTextWindow->destroyAfterClose() )
						{
								delete curTextWindow;
								allTextWindows.erase( allTextWindows.begin() + curTextWindowNr );
						}
				}
			}

			keys = SDL_GetKeyState(NULL);

			curTicks  = SDL_GetTicks();
			ticksDiff = curTicks - lastTicks;
			lastTicks = curTicks;

			player->giveMovePoints( ticksDiff );
			player->Move();
			player->regenerateLifeManaFatigue( ticksDiff );

			std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
			for (unsigned int x=0; x<zoneNPCs.size(); x++) {
				CNPC *curNPC = zoneNPCs[x];
				if ( curNPC->isAlive() ) {
						curNPC->giveMovePoints( ticksDiff );
						curNPC->Move();
						curNPC->regenerateLifeManaFatigue( ticksDiff );
				}
				curNPC->Respawn();
				curNPC->Wander();

				// check all active spells for inEffects on our NPCs.
				curNPC->cleanupActiveSpells();
				std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = curNPC->getActiveSpells();
				for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
						activeSpellActions[ curActiveSpellNr ].first->inEffect();
				}
			}

			// check all active AoE spells and see they're finished and look for inEffects and process 'em
			for ( unsigned int i=0; i<Globals::getCurrentZone()->MagicMap.size(); ++i)
			{
				Globals::getCurrentZone()->MagicMap[i]->process();
				Globals::getCurrentZone()->MagicMap[i]->getSpell()->inEffect();
				Globals::cleanupActiveAoESpells();

				if ( Globals::getCurrentZone()->MagicMap[i]->isDone() )
					Globals::getCurrentZone()->MagicMap.erase(Globals::getCurrentZone()->MagicMap.begin()+i);
			}

// making sure our target is still alive, not invisible and still in range while stealthed. if not well set our target to NULL.
if (player->getTarget()) {
	double distance = sqrt( pow((player->getTarget()->getXPos()+player->getTarget()->getWidth()/2) - (player->getXPos()+player->getWidth()/2),2)
													+pow((player->getTarget()->getYPos()+player->getTarget()->getHeight()/2) - (player->getYPos()+player->getHeight()/2),2) );
	if ( player->getTarget()->isAlive() == false
	|| ( player->getTarget()->isInvisible() == true && player->canSeeInvisible() == false )
	|| ( player->getTarget()->isSneaking() == true && distance > 260 && player->canSeeSneaking() == false ) ) {
			player->setTarget(NULL);
	}
}

// check all active spells for inEffects on our player.
std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = player->getActiveSpells();
for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
	activeSpellActions[ curActiveSpellNr ].first->inEffect();
}
player->cleanupActiveSpells();

			std::vector<InteractionRegion*> interactionRegions = Globals::getCurrentZone()->getInteractionRegions();
			for ( size_t curInteractionRegionNr=0; curInteractionRegionNr<interactionRegions.size(); ++curInteractionRegionNr ) {
				InteractionRegion *curInteractionRegion = interactionRegions[ curInteractionRegionNr ];
				curInteractionRegion->interactWithPlayer( player );
			}

			Globals::getCurrentZone()->cleanupNPCList();
			Globals::getCurrentZone()->cleanupInteractionList();
			Globals::getCurrentZone()->cleanupInteractionRegionList();

			if (keys[SDLK_k]) { // kill all NPCs in the zone. testing purposes.
					std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
					for (unsigned int x=0; x<zoneNPCs.size(); x++) {
							if ( zoneNPCs[x]->isAlive() ) {
									zoneNPCs[x]->Die();
							}
					}
			}

			if (event.key.keysym.sym == SDLK_PRINT && !KP_screenshot)
			{
					KP_screenshot = true;
					utils::takeScreenshot();
			}

			if (event.key.keysym.sym != SDLK_PRINT)
			{
					KP_screenshot = false;
			}

			if (keys[SDLK_l] && !Editor.KP_toggle_editor) {
					Editor.setEditZone( Globals::getCurrentZone() );
					LuaFunctions::executeLuaFile( "data/tileAdjacency.lua" );
					Editor.setEnabled( true );
					Editor.initFocus( &focus );
					Editor.KP_toggle_editor = true;
			}

			if (!keys[SDLK_l]) {
					Editor.KP_toggle_editor = false;
			}

			if (keys[SDLK_TAB] && !KP_select_next) {
					KP_select_next = true;
					bool FoundNewTarget = false;
					std::vector <CNPC*> NPClist;
					// select next npc on screen
					std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
					for ( size_t curNPCNr = 0; curNPCNr < zoneNPCs.size(); ++curNPCNr ) {
							// if NPC is in on screen (might be changed to line of sight or something)
							// this makes a list of all visible NPCs, easier to select next target this way.
							// also makes sure the NPC isn't invisible or sneaking outside of our vision range.
							CNPC *curNPC = zoneNPCs[curNPCNr];
							double distance = sqrt( pow((curNPC->getXPos()+curNPC->getWidth()/2) - (player->getXPos()+player->getWidth()/2),2)
										 +pow((curNPC->getYPos()+curNPC->getHeight()/2) - (player->getYPos()+player->getHeight()/2),2) );

							if ( DrawingHelpers::isRectOnScreen( curNPC->x_pos, 1, curNPC->y_pos, 1 )
											&& curNPC->isAlive()
											&& ( curNPC->isInvisible() == false || ( curNPC->isInvisible() == true && player->canSeeInvisible() == true ) )
											&& ( curNPC->isSneaking() == false || ( curNPC->isSneaking() == true && ( distance < 260 || player->canSeeSneaking() == true ) ) ) ) {
									NPClist.push_back(curNPC);
							}
					}
					// selects next target in the list, if target = NULL, set target to first NPC on the visible list.
					for ( size_t curNPC = 0; curNPC < NPClist.size(); ++curNPC ) {
							if (!player->getTarget()) {
									player->setTarget(NPClist[0], NPClist[0]->getAttitude());
							}

							if ( player->getTarget() == NPClist[curNPC] ) {
									if ( curNPC+1 == NPClist.size() ) {
											player->setTarget(NPClist[0], NPClist[0]->getAttitude());
									} else {
											player->setTarget(NPClist[curNPC+1], NPClist[curNPC+1]->getAttitude());
									}
									FoundNewTarget = true;
									break;
							}
					}

					if ( !FoundNewTarget && NPClist.size() > 0) {
							player->setTarget(NPClist[0], NPClist[0]->getAttitude());
					}
			}

			if (keys[TOOLTIP_KEY])
			{
					Globals::getCurrentZone()->getGroundLoot()->enableTooltips();
			}

			if (!keys[TOOLTIP_KEY])
			{
					Globals::getCurrentZone()->getGroundLoot()->disableTooltips();
			}

			if (!keys[SDLK_TAB]) {
					KP_select_next = false;
			}

			if (keys[SDLK_ESCAPE] && !KP_toggle_showOptionsWindow ) {
					KP_toggle_showOptionsWindow = true;
					optionsWindow->toggle();
			}

			if ( !keys[SDLK_ESCAPE] ) {
					KP_toggle_showOptionsWindow = false;
			}

			if ( keys[SDLK_c] && !KP_toggle_showCharacterInfo ) {
					KP_toggle_showCharacterInfo = true;
					characterInfoScreen->toggle();
			}

			if ( !keys[SDLK_c] ) {
					KP_toggle_showCharacterInfo = false;
			}

			if ( keys[SDLK_b] && !KP_toggle_showSpellbook ) {
					KP_toggle_showSpellbook = true;
					spellbook->toggle();
			}

			if ( !keys[SDLK_b] ) {
					KP_toggle_showSpellbook = false;
			}

			if ( keys[SDLK_i] && !KP_toggle_showInventory ) {
					KP_toggle_showInventory = true;
					inventoryScreen->toggle();
			}

			if ( !keys[SDLK_i] ) {
					KP_toggle_showInventory = false;
			}

			if ( keys[SDLK_q] && !KP_toggle_showQuestWindow ) {
					KP_toggle_showQuestWindow = true;
					questWindow->toggle();
			}

			if ( !keys[SDLK_q] ) {
					KP_toggle_showQuestWindow = false;
			}

			actionBar->handleKeys();

			if (keys[SDLK_5] && !KP_interrupt) {
					KP_interrupt = true;
					player->CastingInterrupted();
			}

			if (!keys[SDLK_5]) {
					KP_interrupt = false;
			}

//			if (keys[SDLK_BACKSPACE] && player->getTarget() != NULL) {
//				GLfloat color[] = {255, 255, 255, 255};
//				DawnInterface::addTextToLogWindow(color, "TarX:%d TarY:%d", player->getTarget()->getXPos(), player->getTarget()->getYPos());
//			}
		} //else

		DrawScene();
		focus.updateFocus();
	}
	std::cout << "numTexturesDrawn:   " << numTexturesDrawn << std::endl;
}

void game_loop()
{
	SDL_Event lastEvent;
	// activate first game loop handler
	if ( currentGameLoopHandler != NULL ) {
		currentGameLoopHandler->activate( &lastEvent );
	}
	
	while ( currentGameLoopHandler != NULL ) {
		currentGameLoopHandler->handleEvents();
		currentGameLoopHandler->updateScene();

		// reset drawing context
		currentGameLoopHandler->drawScene();

		if ( currentGameLoopHandler->isDone() ) {
			currentGameLoopHandler->finish();
			currentGameLoopHandler = nextGameLoopHandler;
			nextGameLoopHandler = NULL;
			if ( currentGameLoopHandler != NULL ) {
				currentGameLoopHandler->activate( &lastEvent );
			}
		}
	}
}

#include "LoadingManager.h"

int main(int argc, char* argv[])
{
	LuaFunctions::executeLuaFile("settings.lua");
	
	if(dawn_init(argc, argv))
	{
		nextGameLoopHandler = new LoadingScreenHandler( loadingScreen.get(), new DawnInitObject() );		
		game_loop();
	}

	return 0;
}
