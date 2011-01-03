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

#include "main.h"

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
int RES_X = Configuration::screenWidth;
int RES_Y = Configuration::screenHeight;

int world_x = 0, world_y = 0;
int mouseX, mouseY;
int done = 0;
CMessage message;

extern uint32_t imgLoadTime;
extern uint32_t sdlLoadTime;
extern uint32_t imgInversionTime;
extern uint32_t mipmapBuildTime;
extern uint32_t debugOutputTime;
uint32_t drawingTime = 0;
uint32_t initStartTicks = 0;

SDL_Surface *screen;
cameraFocusHandler focus(Configuration::screenWidth, Configuration::screenHeight);

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

namespace Globals
{
	std::map< std::string, CZone* > allZones;
}

static bool HandleCommandLineAurguments(int argc, char** argv)
{
	bool run_game = true;
	std::string executable(argv[0]);
	Configuration::soundenabled = true;
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



	// draw NPC's name and lifebar if it's in target
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
	//fpsFont->drawText(focus.getX(), focus.getY()+RES_Y - static_cast<int>(fpsFont->getHeight()), "FPS: %d     world_x: %2.2f, world_y: %2.2f      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps,focus.getX(),focus.getY(), character.x_pos, character.y_pos, mouseX, mouseY);
	// Only FPS
	fpsFont->drawText(focus.getX()+RES_X-100, focus.getY()+RES_Y - static_cast<int>(fpsFont->getHeight()), "FPS: %d",fps);

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
DawnInitObject *curTextureProcessor = NULL;
void processTextureInOpenGLThread( CTexture *texture, std::string texturefile, int textureIndex, int textureOffsetX = 0, int textureOffsetY = 0 );
bool initPhase = false;
struct TextureQueueEntry
{
	TextureQueueEntry( CTexture *texture_, const std::string textureFile_, int textureIndex_, int textureOffsetX_, int textureOffsetY_ )
		: 	texture( texture_ ),
			textureFile( textureFile_ ),
			textureIndex( textureIndex_ ),
			textureOffsetX( textureOffsetX_ ),
			textureOffsetY( textureOffsetY_ )
	{}
	CTexture *texture;
	std::string textureFile;
	int textureIndex, textureOffsetX, textureOffsetY;
};

class DawnInitObject : public CThread
{
private:
	bool finished;
	std::deque<TextureQueueEntry*> textureQueue;

	GLFT_Font *curFont;
	std::string curFontFile;
	unsigned int curFontSize;
	std::string progressString;
	double progress;
	CMutexClass accessMutex;
public:
	bool started;
	DawnInitObject()
	    : finished( false ),
	      curFont( NULL ),
	      progressString( "" ),
	      progress( 0.0 ),
	      accessMutex(),
	      started( false )
	{
		SetThreadType(ThreadTypeEventDriven);
	}

	bool isFinished()
	{
		bool result = false;
		accessMutex.Lock();
		result = finished && (textureQueue.size() == 0);
		accessMutex.Unlock();
		return result;
	}

	std::string getCurrentText()
	{
		return progressString;
	}

	double getProgress()
	{
		return progress;
	}

	void setCurrentTextureToProcess( CTexture *texture, std::string textureFile, int textureIndex, int textureOffsetX, int textureOffsetY )
	{
		accessMutex.Lock();
		TextureQueueEntry *newEntry = new TextureQueueEntry( texture, textureFile, textureIndex, textureOffsetX, textureOffsetY );
		textureQueue.push_back( newEntry );
		// this is just for first tests. later the queue will work autonomously
		accessMutex.Unlock();
		// return without waiting for completion. This might cause some problems if the init thread accesses the texture
		// which it should not do
	}

	void processCurTexture()
	{
		if ( textureQueue.size() > 0 ) {
			accessMutex.Lock();
			TextureQueueEntry *curEntry = textureQueue.front();
			accessMutex.Unlock();
			dawn_debug_info( "loading texture %s\n", curEntry->textureFile.c_str());
            curEntry->texture->LoadIMG( curEntry->textureFile, curEntry->textureIndex, true, curEntry->textureOffsetX, curEntry->textureOffsetY );
			delete curEntry;
			accessMutex.Lock();
			textureQueue.pop_front();
			accessMutex.Unlock();
		}
	}

	void setCurrentFontToProcess( GLFT_Font *font, std::string fontFile, unsigned int fontSize )
	{
		accessMutex.Lock();
		curFont = font;
		curFontFile = fontFile;
		curFontSize = fontSize;
		accessMutex.Unlock();
		while ( curFont != NULL ) {
			Sleep(1);
		}
	}

	void processCurFont()
	{
		accessMutex.Lock();
		if ( curFont != NULL ) {
			dawn_debug_info( "loading font %s\n", curFontFile.c_str());
			threadedMode = false;
			curFont->open( curFontFile, curFontSize );
			threadedMode = true;
			curFont = NULL;
		}
		accessMutex.Unlock();
	}

	void setProgress( double newProgress )
	{
		// wait for texture loading
		size_t curSize;
		while ( ( curSize = textureQueue.size() ) > 0 )
		{
			Sleep( 1 );
		}
		progress = newProgress;
	}

	void init()
	{
		dawn_debug_info("Starting initialization");
		progressString = "Initializing Editor";
		Editor.LoadTextures();
		setProgress( 0.025 );
		progressString = "Initializing GUI";
		GUI.LoadTextures();
		GUI.SetPlayer(Globals::getPlayer());
		setProgress( 0.05 );
		progressString = "Initializing Character Screen";
		characterInfoScreen = std::auto_ptr<CharacterInfoScreen>( new CharacterInfoScreen( Globals::getPlayer() ) );
		characterInfoScreen->LoadTextures();
		setProgress( 0.075 );
		progressString = "Initializing Inventory Screen";
		inventoryScreen = std::auto_ptr<InventoryScreen>( new InventoryScreen( Globals::getPlayer() ) );
		inventoryScreen->loadTextures();
		setProgress( 0.1 );
		progressString = "Initializing Action Bar";
		actionBar = std::auto_ptr<ActionBar>( new ActionBar( Globals::getPlayer() ) );
		actionBar->loadTextures();
		setProgress( 0.125 );
		progressString = "Initializing Spellbook";
		spellbook = std::auto_ptr<Spellbook>( new Spellbook( Globals::getPlayer() ) );
		spellbook->loadTextures();
		setProgress( 0.15 );
		progressString = "Initializing Log Window";
		logWindow = std::auto_ptr<LogWindow>( new LogWindow );
		logWindow->loadTextures();
		setProgress( 0.16 );
		progressString = "Initializing Buff Display";
		buffWindow = std::auto_ptr<BuffWindow>( new BuffWindow( Globals::getPlayer() ) );
		setProgress( 0.175 );
		progressString = "Initializing Quest Screen";
		questWindow = std::auto_ptr<QuestWindow>( new QuestWindow );
		setProgress( 0.2 );
		progressString = "Initializing Menu Screen";
		optionsWindow = std::auto_ptr<OptionsWindow>( new OptionsWindow );

		/// testing the shop, should not be initialized like this!!!
		shopWindow = std::auto_ptr<Shop>( new Shop( Globals::getPlayer(), NULL /* was dynamic_cast<CNPC*>( &character ) [=NULL] */ ) );

		dawn_debug_info("Loading the game data files and objects");
		setProgress( 0.225 );
		progressString = "Loading Spell Data";
		LuaFunctions::executeLuaFile("data/spells.lua");
        setProgress( 0.375 );
		progressString = "Loading Item Data";
        LuaFunctions::executeLuaFile("data/itemdatabase.lua");
        setProgress( 0.525 );
		progressString = "Loading Mob Data";
        LuaFunctions::executeLuaFile("data/mobdata.all");
		dawn_debug_info("Loading completed");

		setProgress( 0.7 );

		progressString = "Loading Character Data";

		std::string characterDataString = "data/character/";

		Player *player = Globals::getPlayer();

		if ( player->getClass() == CharacterClass::Liche ) {
		    characterDataString.append( "wizard/" );
		} else if ( player->getClass() == CharacterClass::Warrior ) {
		    characterDataString.append( "swordsman/" );
		} else if ( player->getClass() == CharacterClass::Ranger ) {
            characterDataString.append( "ranger/" );
		}

		ActivityType::ActivityType activity = ActivityType::Walking;
		player->setNumMoveTexturesPerDirection( activity, 8 );
		for ( size_t curIndex=0; curIndex<8; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;
			std::string numberString = ostr.str();
			player->setMoveTexture( activity, N, curIndex, std::string("").append( characterDataString ).append("walking n").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NE, curIndex, std::string("").append( characterDataString ).append("walking ne").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, E, curIndex, std::string("").append( characterDataString ).append("walking e").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SE, curIndex, std::string("").append( characterDataString ).append("walking se").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, S, curIndex, std::string("").append( characterDataString ).append("walking s").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SW, curIndex, std::string("").append( characterDataString ).append("walking sw").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, W, curIndex, std::string("").append( characterDataString ).append("walking w").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NW, curIndex, std::string("").append( characterDataString ).append("walking nw").append(numberString).append(".tga" ) );
		}
		activity = ActivityType::Attacking;
		player->setNumMoveTexturesPerDirection( activity, 13 );
		for ( size_t curIndex=0; curIndex<13; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;

			std::string numberString = ostr.str();
			player->setMoveTexture( activity, N, curIndex, std::string("").append( characterDataString ).append("attacking n").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NE, curIndex, std::string("").append( characterDataString ).append("attacking ne").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, E, curIndex, std::string("").append( characterDataString ).append("attacking e").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SE, curIndex, std::string("").append( characterDataString ).append("attacking se").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, S, curIndex, std::string("").append( characterDataString ).append("attacking s").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SW, curIndex, std::string("").append( characterDataString ).append("attacking sw").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, W, curIndex, std::string("").append( characterDataString ).append("attacking w").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NW, curIndex, std::string("").append( characterDataString ).append("attacking nw").append(numberString).append(".tga" ) );
		}
		activity = ActivityType::Casting;
		player->setNumMoveTexturesPerDirection( activity, 13 );
		for ( size_t curIndex=0; curIndex<13; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;

			std::string numberString = ostr.str();
			player->setMoveTexture( activity, N, curIndex, std::string("").append( characterDataString ).append("attacking n").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NE, curIndex, std::string("").append( characterDataString ).append("attacking ne").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, E, curIndex, std::string("").append( characterDataString ).append("attacking e").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SE, curIndex, std::string("").append( characterDataString ).append("attacking se").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, S, curIndex, std::string("").append( characterDataString ).append("attacking s").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SW, curIndex, std::string("").append( characterDataString ).append("attacking sw").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, W, curIndex, std::string("").append( characterDataString ).append("attacking w").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NW, curIndex, std::string("").append( characterDataString ).append("attacking nw").append(numberString).append(".tga" ) );
		}

        activity = ActivityType::Shooting;
		player->setNumMoveTexturesPerDirection( activity, 13 );
		for ( size_t curIndex=0; curIndex<13; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;

			std::string numberString = ostr.str();
			player->setMoveTexture( activity, N, curIndex, std::string("").append( characterDataString ).append("attacking n").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NE, curIndex, std::string("").append( characterDataString ).append("attacking ne").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, E, curIndex, std::string("").append( characterDataString ).append("attacking e").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SE, curIndex, std::string("").append( characterDataString ).append("attacking se").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, S, curIndex, std::string("").append( characterDataString ).append("attacking s").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SW, curIndex, std::string("").append( characterDataString ).append("attacking sw").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, W, curIndex, std::string("").append( characterDataString ).append("attacking w").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NW, curIndex, std::string("").append( characterDataString ).append("attacking nw").append(numberString).append(".tga" ) );
		}

        activity = ActivityType::Dying;
        size_t numOfMoves = 0;
        if ( player->getClass() == CharacterClass::Warrior ) {
            numOfMoves = 9;
        } else if ( player->getClass() == CharacterClass::Ranger ) {
            numOfMoves = 11;
        } else if ( player->getClass() == CharacterClass::Liche ) {
            numOfMoves = 13;
        }
		player->setNumMoveTexturesPerDirection( activity, numOfMoves );
		for ( size_t curIndex=0; curIndex<numOfMoves; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;

			std::string numberString = ostr.str();
			player->setMoveTexture( activity, N, curIndex, std::string("").append( characterDataString ).append("dying n").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NE, curIndex, std::string("").append( characterDataString ).append("dying ne").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, E, curIndex, std::string("").append( characterDataString ).append("dying e").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SE, curIndex, std::string("").append( characterDataString ).append("dying se").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, S, curIndex, std::string("").append( characterDataString ).append("dying s").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, SW, curIndex, std::string("").append( characterDataString ).append("dying sw").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, W, curIndex, std::string("").append( characterDataString ).append("dying w").append(numberString).append(".tga" ) );
			player->setMoveTexture( activity, NW, curIndex, std::string("").append( characterDataString ).append("dying nw").append(numberString).append(".tga" ) );
		}

		player->setMoveTexture( ActivityType::Walking, STOP, 0, std::string("").append( characterDataString ).append("walking s0000.tga" ) );
		player->setBoundingBox( 18, 20, 64, 64 );
		player->setUseBoundingBox( true );
		player->Init(Configuration::screenWidth/2,Configuration::screenHeight/2);
		player->setActiveGUI( &GUI );
		player->setMaxHealth(400);
		player->setMaxMana(250);
		player->setMaxFatigue(100);
		player->setStrength(15);
		player->setVitality(15);
		player->setDexterity(20);
		player->setWisdom(10);
		player->setIntellect(10);
		player->setHealthRegen(1);
		player->setManaRegen(2);
		player->setFatigueRegen( 5 );
		player->giveCoins( 576 );

		// setting initial actions in the action bar
		const std::vector<CSpellActionBase*> inscribedSpells = player->getSpellbook();
		for ( size_t curEntry=0; curEntry<=9 && curEntry < inscribedSpells.size(); ++curEntry ) {
			actionBar->bindActionToButtonNr( curEntry, inscribedSpells[ curEntry ] );
		}

		dawn_debug_info("Character completed");

		setProgress( 0.92 );
		progressString = "Initializing load/save functions";
		LuaFunctions::executeLuaFile("data/loadsave.lua");
		setProgress( 0.95 );
		progressString = "Loading Game Init Data";

		CZone *newZone = new CZone();
		newZone->LoadZone("data/zone1");

		LuaFunctions::executeLuaFile("data/gameinit.lua");

		// initialize random number generator
		setProgress( 0.99 );
		progressString = "Initializing Random Number Generator";
		srand( time( 0 ) );

		accessMutex.Lock();
		finished = true;
		accessMutex.Unlock();
	}

	virtual BOOL OnTask()
	{
		if ( started )
			return true;
		started = true;
		init();
		return true;
	}
};

void processTextureInOpenGLThread( CTexture *texture, std::string textureFile, int textureIndex, int textureOffsetX, int textureOffsetY )
{
	curTextureProcessor->setCurrentTextureToProcess( texture, textureFile, textureIndex, textureOffsetX, textureOffsetY );
}

extern int64_t numCharactersDrawn;
int64_t numTexturesDrawn = 0;

TextureFrame *textureFrame = NULL;

void processFontInOpenGLThread( GLFT_Font *font, const std::string &filename, unsigned int size )
{
	curTextureProcessor->setCurrentFontToProcess( font, filename, size );
}

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

		textureFrame = new TextureFrame();
		initPhase = true;
		/// choose class here. Will be moved later when we have a real character creation page, start page etc.. works for now.
		std::auto_ptr<ChooseClassScreen> chooseClassScreen( new ChooseClassScreen() );
		chooseClassScreen->setTextureDependentPositions();
		textureFrame->finishFrame();

		while ( chooseClassScreen->isDone() == false )
		{
            SDL_Event event;
            SDL_PollEvent(&event);

			if (event.type == SDL_MOUSEBUTTONDOWN) {
                chooseClassScreen->clicked( event.motion.x, Configuration::screenHeight - event.motion.y - 1, event.button.button );
			}
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			chooseClassScreen->draw( event.motion.x, Configuration::screenHeight - event.motion.y - 1 );
			SDL_GL_SwapBuffers();

		}

		initStartTicks = SDL_GetTicks();
		imgLoadTime = 0;
		sdlLoadTime = 0;
		imgInversionTime = 0;
		debugOutputTime = 0;
		drawingTime = 0;

		std::auto_ptr<LoadingScreen> loadingScreen( new LoadingScreen() );
		textureFrame->finishFrame();
		DawnInitObject obj;
		threadedMode = true;
		curTextureProcessor = &obj;
		do {
			obj.Event();
			Sleep( 10 );
		} while ( ! obj.started );

		uint32_t lastTicks = SDL_GetTicks();
		uint32_t curTicks = lastTicks;
		while ( ! obj.isFinished() ) {
			obj.processCurTexture();
			obj.processCurFont();
			curTicks = SDL_GetTicks();
			if ( curTicks-lastTicks >= 100 )
			{
				lastTicks = curTicks;
				loadingScreen->setCurrentText( obj.getCurrentText() );
				loadingScreen->setProgress( obj.getProgress() );
				glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				loadingScreen->draw();
				SDL_GL_SwapBuffers();
				drawingTime += SDL_GetTicks()-curTicks;
			}
		}
		textureFrame->finishFrame();
		delete textureFrame;
		initPhase = false;

		optionsWindow->setTextureDependentPositions();
		inventoryScreen->setTextureDependentPositions();

		uint32_t initTime = SDL_GetTicks()-initStartTicks;
		std::cout << "initialization took " << initTime << " ms" << std::endl;
		std::cout << "included are " << imgLoadTime << " ms for image loading (" << sdlLoadTime << " ms for IMG_Load, " << imgInversionTime << " for image Y-inversion, " << mipmapBuildTime << " ms for mipmap-building, total >= " << (100*(sdlLoadTime+imgInversionTime+mipmapBuildTime))/imgLoadTime << "% of LoadIMG submeasured)" << std::endl;
		std::cout << "included are " << debugOutputTime << " ms for debug output" << std::endl;
		std::cout << "included are " << drawingTime << " ms for menu drawing" << std::endl;
		std::cout << "total submeasures cover >= " << (100*(imgLoadTime+debugOutputTime+drawingTime)/initTime) << "% of init time" << std::endl;

		threadedMode = false;
		curTextureProcessor = NULL;

		// initialize fonts where needed
		fpsFont = FontCache::getFontFromCache("data/verdana.ttf", 12);
		message.initFonts();
		Editor.initFonts();
		characterInfoScreen->initFonts();
        actionBar->initFonts();
        GUI.initFonts();
        logWindow->clear();
		return true;
}

void setQuitGame()
{
	done = 1;
}

void game_loop()
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
							if( actionBar->isCastingAoESpell() )
							{
								CSpellActionBase *spell = actionBar->getAoESpell();
								spell->cast( player, mouseX, mouseY );
								actionBar->setCastingAoESpell( false );
								Globals::setDisplayCursor( false );
							}
							else
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

												// search for new target
												std::vector<CNPC*> zoneNPCs = curZone->getNPCs();
												for (unsigned int x=0; x<zoneNPCs.size(); x++) {
														CNPC *curNPC = zoneNPCs[x];
														if ( curNPC->CheckMouseOver(mouseX+world_x,mouseY+world_y) ) {
																if ( ! curNPC->getAttitude() == Attitude::FRIENDLY ) {
																		if( !player->hasTarget( curNPC ) )
																			player->setTarget( curNPC );
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

						if ( sqrt(pow(mouseDownXY.first-mouseX,2) + pow(mouseDownXY.second-mouseY,2)) > 25 )
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
				std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpellActions = curNPC->getActiveSpells();
				for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
						activeSpellActions[ curActiveSpellNr ].first->inEffect();
				}
				curNPC->cleanupActiveSpells();
			}

			// check all active AoE spells and see they're finished
			for ( unsigned int i=0; i<Globals::getCurrentZone()->MagicMap.size(); ++i)
			{
				if ( Globals::getCurrentZone()->MagicMap[i].isDone() )
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
									player->setTarget(NPClist[0]);
							}

							if ( player->getTarget() == NPClist[curNPC] ) {
									if ( curNPC+1 == NPClist.size() ) {
											player->setTarget(NPClist[0]);
									} else {
											player->setTarget(NPClist[curNPC+1]);
									}
									FoundNewTarget = true;
									break;
							}
					}

					if ( !FoundNewTarget && NPClist.size() > 0) {
							player->setTarget(NPClist[0]);
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
		} //else

		DrawScene();
		focus.updateFocus();
	}
	std::cout << "numTexturesDrawn:   " << numTexturesDrawn << std::endl;
}

int main(int argc, char* argv[])
{
	Configuration::logfile = "dawn-log.log";
	Configuration::debug_stdout = true;
	Configuration::debug_fileout = true;
	Configuration::show_info_messages = true;
	Configuration::show_warn_messages = true;

	if(dawn_init(argc, argv))
		game_loop();

	return 0;
}
