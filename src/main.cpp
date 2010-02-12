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

#include "Thread.h"

#include "main.h"

#include "CLuaFunctions.h"
#include "CSpell.h"
#include "CAction.h"
#include "debug.h"
#include "CharacterInfoScreen.h"
#include "item.h"
#include "interactionpoint.h"
#include "textwindow.h"
#include "questwindow.h"
#include "optionswindow.h"
#include <memory>
#include <signal.h>
#include <SDL/SDL_getenv.h>
#include "loadingscreen.h"

/* Global settings now reside in the
   dawn_configuration namespace, variables
   are added to this across multiple files.
   current headers adding to it:
   debug.h
 */
namespace dawn_configuration {
	bool fullscreenenabled = true;
	int screenWidth = 1024;
	int screenHeight = 768;
	int bpp = 32;
}
// FIXME: This is a temp hack until the
// 	objects dont need those variables.
//	david: I'll have this sorted pretty
//	quick.
int RES_X = dawn_configuration::screenWidth;
int RES_Y = dawn_configuration::screenHeight;

SDL_Surface *screen;
extern CZone zone1;
extern CMessage message;
Player character;
cameraFocusHandler focus(dawn_configuration::screenWidth, dawn_configuration::screenHeight);

CEditor Editor;

CInterface GUI;

std::vector <CNPC*> NPC;
std::vector<Item*> groundItems;
std::vector<std::pair<int,int> > groundPositions;
extern std::vector<InteractionPoint*> allInteractionPoints;
extern std::vector<TextWindow*> allTextWindows;

bool KP_damage, KP_heal, KP_magicMissile, KP_healOther, KP_interrupt, KP_select_next = false, KP_attack = false;
bool KP_toggle_showCharacterInfo = false;
bool KP_toggle_showInventory = false;
bool KP_toggle_showSpellbook = false;
bool KP_toggle_showQuestWindow = false;
bool KP_toggle_showOptionsWindow = false;

extern int world_x, world_y, mouseX, mouseY;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

std::auto_ptr<GLFT_Font> fpsFont;
std::auto_ptr<CharacterInfoScreen> characterInfoScreen;
std::auto_ptr<InventoryScreen> inventoryScreen;
std::auto_ptr<ActionBar> actionBar;
std::auto_ptr<Spellbook> spellbook;
std::auto_ptr<BuffWindow> buffWindow;
std::auto_ptr<QuestWindow> questWindow;
std::auto_ptr<OptionsWindow> optionsWindow;

std::vector<CSpellActionBase*> activeSpellActions;

void enqueueActiveSpellAction( CSpellActionBase *spellaction )
{
	activeSpellActions.push_back( spellaction );
}

void cleanupActiveSpellActions()
{
	size_t curActiveNr = 0;
	while ( curActiveNr < activeSpellActions.size() ) {
		if ( activeSpellActions[ curActiveNr ]->isEffectComplete() ) {
			delete activeSpellActions[ curActiveNr ];
			activeSpellActions.erase( activeSpellActions.begin() + curActiveNr );
		} else {
			++curActiveNr;
		}
	}
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
			dawn_configuration::fullscreenenabled = true;
			run_game = true;
		} else if (currentarg == "-w" || currentarg == "--window") {
			dawn_configuration::fullscreenenabled = false;
			run_game = true;
		} else if (currentarg == "-h" || currentarg == "--help") {
			std::cout << "Dawn-RPG Startup Parameters" <<
			          std::endl << std::endl <<
			          " -f, --fullscreen         Run Dawn in fullscreen mode" <<
			          std::endl <<
			          " -w, --window             Run Dawn inside a window" <<
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
	CZone* getCurrentZone()
	{
		return &zone1;
	}

	CNPC *addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn, CZone *zone )
	{
		CNPC *newMob = new CNPC(0, 0, 0, 0, 0, NULL);
		newMob->lifebar = NULL;
		newMob->baseOnType( mobID );
		newMob->setSpawnInfo( x_pos, y_pos, respawn_rate, do_respawn, zone );
		newMob->setActiveGUI( &GUI );
		NPC.push_back( newMob );
		return newMob;
	}

	void removeMobSpawnPoint( CNPC *mobSpawnPoint )
	{
		for ( size_t curSpawnPointNr=0; curSpawnPointNr<NPC.size(); ++curSpawnPointNr ) {
			CNPC *curNPC = NPC[ curSpawnPointNr ];
			if ( curNPC == mobSpawnPoint ) {
				curNPC->markAsDeleted();
				break;
			}
		}
	}
}

void cleanupSpawnPointList()
{
	size_t curSpawnPointNr = 0;
	while ( curSpawnPointNr < NPC.size() ) {
		CNPC *curNPC = NPC[ curSpawnPointNr ];
		if ( curNPC->isMarkedAsDeletable() ) {
			NPC.erase( NPC.begin() + curSpawnPointNr );
			// TODO: delete curNPC. There seem to be some problems at the moment.
			//delete curNPC;
		} else {
			++curSpawnPointNr;
		}
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

	zone1.DrawZone();

	// draw items on the ground
	for ( size_t curItemNr=0; curItemNr<groundItems.size(); ++curItemNr ) {
		Item *curItem = groundItems[ curItemNr ];
		int posX = groundPositions[ curItemNr ].first;
		int posY = groundPositions[ curItemNr ].second;

		DrawingHelpers::mapTextureToRect( curItem->getSymbolTexture()->texture[0].texture,
		                                  posX,
		                                  curItem->getSizeX() * 32,
		                                  posY,
		                                  curItem->getSizeY() * 32 );
	}

	for ( size_t curInteractionNr=0; curInteractionNr<allInteractionPoints.size(); ++curInteractionNr ) {
		InteractionPoint *curInteraction = allInteractionPoints[ curInteractionNr ];
		curInteraction->draw();
		if ( curInteraction->isMouseOver(mouseX, mouseY) ) {
			curInteraction->drawInteractionSymbol(mouseX, mouseY);
		}
	}

	character.Draw();
	for (unsigned int x=0; x<NPC.size(); x++) {
		NPC[x]->Draw();
		if ( character.getTarget() == NPC[x] )
			fpsFont->drawText(NPC[x]->x_pos, NPC[x]->y_pos+NPC[x]->getHeight() + 12, "%s, Health: %d",NPC[x]->getName().c_str(),NPC[x]->getCurrentHealth());
	}

	// draws the character's target's lifebar, if we have any target.
	if (character.getTarget())
		character.getTarget()->DrawLifebar();

	for ( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
		if ( ! activeSpellActions[ curActiveSpellNr ]->isEffectComplete() ) {
			activeSpellActions[ curActiveSpellNr ]->drawEffect();
		}
	}

	// draw textwindows
	for ( size_t curTextWindowNr=0; curTextWindowNr<allTextWindows.size(); ++curTextWindowNr ) {
		TextWindow *curTextWindow = allTextWindows[ curTextWindowNr ];
		curTextWindow->draw();
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
		actionBar->draw();
		GUI.DrawInterface();
	}

	buffWindow->draw();

	if ( characterInfoScreen->isVisible() ) {
		characterInfoScreen->drawScreen();
	}

	if ( inventoryScreen->isVisible() ) {
	    inventoryScreen->draw();
	}

	if ( inventoryScreen->hasFloatingSelection() ) {
	    inventoryScreen->drawItemPlacement( mouseX, mouseY );
		inventoryScreen->drawFloatingSelection( world_x + mouseX, world_y + mouseY );
	}

	if ( inventoryScreen->isVisible() )
	{
	    inventoryScreen->drawItemTooltip( mouseX, mouseY );
	}

	if ( actionBar->isMouseOver( mouseX, mouseY ) && !spellbook->hasFloatingSpell() )
	{
	    actionBar->drawSpellTooltip( mouseX, mouseY );
	}

	if ( spellbook->isVisible() )
	{
	    spellbook->draw();
		if ( spellbook->isOnThisScreen( mouseX, mouseY ) && !spellbook->hasFloatingSpell() )
		{
			spellbook->drawSpellTooltip( mouseX, mouseY );
		}
	}

    if ( spellbook->hasFloatingSpell() ) {
	    spellbook->drawFloatingSpell( mouseX, mouseY );
	}

	if ( questWindow->isVisible() ) {
		questWindow->draw();
	}

	if ( optionsWindow->isVisible() ) {
		optionsWindow->draw();
	}

	// note: we need to cast fpsFont.getHeight to int since otherwise the whole expression would be an unsigned int
	//       causing overflow and not drawing the font if it gets negative

	// I've removed this text for now, just for a cleaner look. Enable it if you need some info while coding. /Arnestig
	// fpsFont->drawText(focus.getX(), focus.getY()+RES_Y - static_cast<int>(fpsFont->getHeight()), "FPS: %d     world_x: %2.2f, world_y: %2.2f      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps,focus.getX(),focus.getY(), character.x_pos, character.y_pos, mouseX, mouseY);
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
bool processFilesDirectly = true;
DawnInitObject *curTextureProcessor = NULL;
void processTextureInOpenGLThread( CTexture *texture, std::string texturefile, int textureIndex );

class DawnInitObject : public CThread
{
private:
	bool finished;
	CTexture *curTexture;
	std::string curTextureFile;
	int curTextureIndex;
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
	      curTexture( NULL ),
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
		result = finished;
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

	void setCurrentTextureToProcess( CTexture *texture, std::string textureFile, int textureIndex )
	{
		accessMutex.Lock();
		curTexture = texture;
		curTextureFile = textureFile;
		curTextureIndex = textureIndex;
		accessMutex.Unlock();
		while ( curTexture != NULL ) {
			Sleep(1);
		}
	}

	void processCurTexture()
	{
		accessMutex.Lock();
		if ( curTexture != NULL ) {
			dawn_debug_info( "loading texture %s\n", curTextureFile.c_str());
			processFilesDirectly = true;
			curTexture->LoadIMG( curTextureFile, curTextureIndex );
			processFilesDirectly = false;
			curTexture = NULL;
		}
		accessMutex.Unlock();
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
			processFilesDirectly = true;
			curFont->open( curFontFile, curFontSize );
			processFilesDirectly = false;
			curFont = NULL;
		}
		accessMutex.Unlock();
	}

	void init()
	{
		dawn_debug_info("Starting initialization");
		progressString = "Initializing Editor";
		Editor.LoadTextures();
		progressString = "Initializing GUI";
		progress = 0.025;
		GUI.LoadTextures();
		GUI.SetPlayer(&character);
		progressString = "Initializing Character Screen";
		progress = 0.05;
		characterInfoScreen = std::auto_ptr<CharacterInfoScreen>( new CharacterInfoScreen( &character ) );
		characterInfoScreen->LoadTextures();
		progressString = "Initializing Inventory Screen";
		progress = 0.075;
		inventoryScreen = std::auto_ptr<InventoryScreen>( new InventoryScreen( &character ) );
		inventoryScreen->loadTextures();
		progressString = "Initializing Action Bar";
		progress = 0.1;
		actionBar = std::auto_ptr<ActionBar>( new ActionBar( &character ) );
		actionBar->loadTextures();
		progressString = "Initializing Spellbook";
		progress = 0.125;
		spellbook = std::auto_ptr<Spellbook>( new Spellbook( &character ) );
		spellbook->loadTextures();
		progressString = "Initializing Buff Display";
		progress = 0.15;
		buffWindow = std::auto_ptr<BuffWindow>( new BuffWindow( &character ) );
		progressString = "Initializing Quest Screen";
		progress = 0.175;
		questWindow = std::auto_ptr<QuestWindow>( new QuestWindow );
		progressString = "Initializing Menu Screen";
		progress = 0.2;
		optionsWindow = std::auto_ptr<OptionsWindow>( new OptionsWindow );

		dawn_debug_info("Loading the game data files and objects");
		progressString = "Loading Spell Data";
		progress = 0.225;
        LuaFunctions::executeLuaFile("data/spells.lua");
        progressString = "Loading Item Data";
        progress = 0.375;
        LuaFunctions::executeLuaFile("data/itemdatabase.lua");
        progressString = "Loading Mob Data";
        progress = 0.525;
		LuaFunctions::executeLuaFile("data/mobdata.all");
		dawn_debug_info("Loading completed");

		progressString = "Loading Character Data";
		progress = 0.7;
		zone1.LoadZone("data/zone1");
		ActivityType::ActivityType activity = ActivityType::Walking;
		character.setNumMoveTexturesPerDirection( activity, 8 );
		for ( size_t curIndex=0; curIndex<8; ++curIndex ) {
			std::ostringstream ostr;
			ostr << "000" << curIndex;
			std::string numberString = ostr.str();
			character.setMoveTexture( activity, N, curIndex, std::string("data/character/swordsman/walking n").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NE, curIndex, std::string("data/character/swordsman/walking ne").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, E, curIndex, std::string("data/character/swordsman/walking e").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SE, curIndex, std::string("data/character/swordsman/walking se").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, S, curIndex, std::string("data/character/swordsman/walking s").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SW, curIndex, std::string("data/character/swordsman/walking sw").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, W, curIndex, std::string("data/character/swordsman/walking w").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NW, curIndex, std::string("data/character/swordsman/walking nw").append(numberString).append(".tga" ) );
		}
		activity = ActivityType::Attacking;
		character.setNumMoveTexturesPerDirection( activity, 13 );
		for ( size_t curIndex=0; curIndex<13; ++curIndex ) {
			std::ostringstream ostr;
			if ( curIndex < 10 )
				ostr << "000" << curIndex;
			else
				ostr << "00" << curIndex;

			std::string numberString = ostr.str();
			character.setMoveTexture( activity, N, curIndex, std::string("data/character/swordsman/attacking n").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NE, curIndex, std::string("data/character/swordsman/attacking ne").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, E, curIndex, std::string("data/character/swordsman/attacking e").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SE, curIndex, std::string("data/character/swordsman/attacking se").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, S, curIndex, std::string("data/character/swordsman/attacking s").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SW, curIndex, std::string("data/character/swordsman/attacking sw").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, W, curIndex, std::string("data/character/swordsman/attacking w").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NW, curIndex, std::string("data/character/swordsman/attacking nw").append(numberString).append(".tga" ) );
		}
		activity = ActivityType::Casting;
		character.setNumMoveTexturesPerDirection( activity, 13 );
		for ( size_t curIndex=0; curIndex<13; ++curIndex ) {
			std::ostringstream ostr;
			if ( curIndex < 10 )
				ostr << "000" << curIndex;
			else
				ostr << "00" << curIndex;

			std::string numberString = ostr.str();
			character.setMoveTexture( activity, N, curIndex, std::string("data/character/swordsman/attacking n").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NE, curIndex, std::string("data/character/swordsman/attacking ne").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, E, curIndex, std::string("data/character/swordsman/attacking e").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SE, curIndex, std::string("data/character/swordsman/attacking se").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, S, curIndex, std::string("data/character/swordsman/attacking s").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, SW, curIndex, std::string("data/character/swordsman/attacking sw").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, W, curIndex, std::string("data/character/swordsman/attacking w").append(numberString).append(".tga" ) );
			character.setMoveTexture( activity, NW, curIndex, std::string("data/character/swordsman/attacking nw").append(numberString).append(".tga" ) );
		}




		character.setMoveTexture( ActivityType::Walking, STOP, 0, "data/character/swordsman/walking s0000.tga" );
		character.setBoundingBox( 18, 20, 64, 64 );
		character.setUseBoundingBox( true );
		character.Init(dawn_configuration::screenWidth/2,dawn_configuration::screenHeight/2);
		character.setActiveGUI( &GUI );
		character.setMaxHealth(400);
		character.setMaxMana(250);
		character.setStrength(15);
		character.setVitality(15);
		character.setDexterity(20);
		character.setWisdom(10);
		character.setIntellect(10);
		dawn_debug_info("Character completed");

		progressString = "Loading Game Init Data";
		progress = 0.95;
		LuaFunctions::executeLuaFile("data/gameinit.lua");

		// initialize random number generator
		progressString = "Initializing Random Number Generator";
		progress = 0.99;
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

void processTextureInOpenGLThread( CTexture *texture, std::string textureFile, int textureIndex )
{
	curTextureProcessor->setCurrentTextureToProcess( texture, textureFile, textureIndex );
}

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

		if (dawn_configuration::fullscreenenabled)
			screen = SDL_SetVideoMode(dawn_configuration::screenWidth,
			                          dawn_configuration::screenHeight, dawn_configuration::bpp,
			                          SDL_OPENGL | SDL_FULLSCREEN);
		else
			screen = SDL_SetVideoMode(dawn_configuration::screenWidth,
			                          dawn_configuration::screenHeight, dawn_configuration::bpp,
			                          SDL_OPENGL);


		if ( !screen )
			dawn_debug_fatal("Unable to set resolution");

		glEnable( GL_TEXTURE_2D );

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glViewport( 0, 0, dawn_configuration::screenWidth, dawn_configuration::screenHeight );

		glClear( GL_COLOR_BUFFER_BIT );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity(); // reset view to 0,0

		glOrtho(0.0f, dawn_configuration::screenWidth, 0.0f, dawn_configuration::screenHeight, -1.0f, 1.0f);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  // reset view to 0,0

		glEnable( GL_BLEND ); // enable blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

		std::auto_ptr<LoadingScreen> loadingScreen( new LoadingScreen() );
		DawnInitObject obj;
		processFilesDirectly = false;
		curTextureProcessor = &obj;
		do {
			obj.Event();
			Sleep( 10 );
		} while ( ! obj.started );

		while ( ! obj.isFinished() ) {
			obj.processCurTexture();
			obj.processCurFont();
			loadingScreen->setCurrentText( obj.getCurrentText() );
			loadingScreen->setProgress( obj.getProgress() );
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			loadingScreen->draw();
			SDL_GL_SwapBuffers();
		}

		processFilesDirectly = true;
		curTextureProcessor = NULL;

		// initialize fonts where needed
		fpsFont = std::auto_ptr<GLFT_Font>(new GLFT_Font("data/verdana.ttf", 12));
		message.initFonts();
		Editor.initFonts();
		characterInfoScreen->initFonts();
        actionBar->initFonts();

		ActionCreation::initActions();



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

    focus.setFocus(&character);



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
                    if ( ( inventoryScreen->isVisible()
					       && inventoryScreen->isOnThisScreen( mouseX, mouseY ) )
					     || inventoryScreen->hasFloatingSelection() ) {
						inventoryScreen->clicked( mouseX, mouseY, event.button.button );
					} else if ( characterInfoScreen->isVisible()
                            && characterInfoScreen->isOnThisScreen( mouseX, mouseY ) ) {
                        characterInfoScreen->clicked( mouseX, mouseY );
                    } else if ( actionBar->isMouseOver( mouseX, mouseY ) ) {
                        if ( spellbook->hasFloatingSpell() )
                        {
                            actionBar->clicked( mouseX, mouseY, spellbook->getFloatingSpell()->action );
                            spellbook->unsetFloatingSpell();
                        } else {
                            actionBar->clicked( mouseX, mouseY );
                        }
                    } else if ( spellbook->isVisible()
                                && (spellbook->isOnThisScreen( mouseX, mouseY )
                                || spellbook->hasFloatingSpell()) ) {
                        spellbook->clicked( mouseX, mouseY );
					} else if ( questWindow->isVisible()
					            && (questWindow->isOnThisScreen( mouseX, mouseY ) ) ) {
						questWindow->clicked( mouseX, mouseY );
					} else if ( optionsWindow->isVisible()
					            && ( optionsWindow->isOnThisScreen( mouseX, mouseY ) ) ) {
						optionsWindow->clicked( mouseX, mouseY );
					} else if ( optionsWindow->isVisible()
					            && (optionsWindow->isOnThisScreen( mouseX, mouseY ) ) ) {
						optionsWindow->clicked( mouseX, mouseY );
					} else {
						switch (event.button.button) {
							case 1:
								// search for new target
								bool foundSomething = false;

								for (unsigned int x=0; x<NPC.size(); x++) {
									if ( NPC[x]->CheckMouseOver(mouseX+world_x,mouseY+world_y) ) {
										character.setTarget( NPC[x] );
										foundSomething = true;
										break;
									}
								}

								if ( !foundSomething ) {
									// search for items
									for ( size_t curItemNr=0; curItemNr<groundItems.size(); ++curItemNr ) {
										Item *curItem = groundItems[ curItemNr ];
										int posX = groundPositions[ curItemNr ].first;
										int posY = groundPositions[ curItemNr ].second;

										int worldMouseX = world_x + mouseX;
										int worldMouseY = world_y + mouseY;
										if ( worldMouseX >= posX
										     && worldMouseX <= static_cast<int>(posX + curItem->getSizeX() * 32)
										     && worldMouseY >= posY
										     && worldMouseY <= static_cast<int>(posY + curItem->getSizeY() * 32) ) {
											foundSomething = true;
											if ( inventoryScreen->isVisible() ) {
												inventoryScreen->selectFloating( new InventoryItem( curItem, 0, 0, &character ) );
												groundItems[ curItemNr ] = groundItems[ groundItems.size() - 1 ];
												groundItems.resize( groundItems.size() - 1 );
												groundPositions[ curItemNr ] = groundPositions[ groundPositions.size() - 1 ];
												groundPositions.resize( groundPositions.size() - 1 );
											} else {
												bool inserted = character.getInventory()->insertItem( curItem );
												if ( inserted ) {
													groundItems[ curItemNr ] = groundItems[ groundItems.size() - 1 ];
													groundItems.resize( groundItems.size() - 1 );
													groundPositions[ curItemNr ] = groundPositions[ groundPositions.size() - 1 ];
													groundPositions.resize( groundPositions.size() - 1 );
												}
											}
											break;
										}
									}

									if ( ! foundSomething ) {
										for ( size_t curInteractionNr=0; curInteractionNr < allInteractionPoints.size(); ++curInteractionNr ) {
											InteractionPoint *curInteraction = allInteractionPoints[ curInteractionNr ];
											if ( curInteraction->isMouseOver( mouseX, mouseY ) ) {
												foundSomething = true;
												curInteraction->startInteraction();
												break;
											}
										}
									}
								}
							break;
						}
					}
				}

				if (event.type == SDL_MOUSEMOTION)
				{
				    if ( sqrt(pow(mouseDownXY.first-mouseX,2) + pow(mouseDownXY.second-mouseY,2)) > 25 )
					{
					    actionBar->dragSpell();
					}
				}

				if (event.type == SDL_MOUSEBUTTONUP)
				{
                    actionBar->executeSpellQueue();
				}

				if (event.type == SDL_MOUSEMOTION)
				{
					mouseX = event.motion.x;
					mouseY = dawn_configuration::screenHeight - event.motion.y - 1;
				}
			}

			keys = SDL_GetKeyState(NULL);

			curTicks  = SDL_GetTicks();
			ticksDiff = curTicks - lastTicks;
			lastTicks = curTicks;

			character.giveMovePoints( ticksDiff );
			character.Move();
			character.regenerateLifeMana( ticksDiff );


			for (unsigned int x=0; x<NPC.size(); x++) {
				if ( NPC[x]->isAlive() ) {
					NPC[x]->giveMovePoints( ticksDiff );
					NPC[x]->Move();
				}
				NPC[x]->Respawn();
				NPC[x]->Wander();
			}

			// making sure our target is still alive, if not well set our target to NULL.
			if (character.getTarget()) {
				if ( !character.getTarget()->isAlive() )
					character.setTarget(0);
			}

			for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
				activeSpellActions[ curActiveSpellNr ]->inEffect();
			}

			cleanupActiveSpellActions();
			cleanupSpawnPointList();

			if (keys[SDLK_k]) { // kill all NPCs in the zone. testing purposes.
				for (unsigned int x=0; x<NPC.size(); x++) {
					NPC[x]->Die();
				}
			}

			if (keys[SDLK_l] && !Editor.KP_toggle_editor) {
				Editor.setEditZone( &zone1 );
				Editor.setEnabled( true );
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
				for ( size_t curNPC = 0; curNPC < NPC.size(); ++curNPC ) {
					// if NPC is in on screen (might be changed to line of sight or something)
					// this makes a list of all visible NPCs, easier to select next target this way.
					if ( DrawingHelpers::isRectOnScreen( NPC[curNPC]->x_pos, 1, NPC[curNPC]->y_pos, 1 )
					        && NPC[curNPC]->isAlive() ) {
						NPClist.push_back(NPC[curNPC]);
					}
				}
				// selects next target in the list, if target = NULL, set target to first NPC on the visible list.
				for ( size_t curNPC = 0; curNPC < NPClist.size(); ++curNPC ) {
					if (!character.getTarget()) {
						character.setTarget(NPClist[0]);
					}

					if ( character.getTarget() == NPClist[curNPC] ) {
						if ( curNPC+1 == NPClist.size() ) {
							character.setTarget(NPClist[0]);
						} else {
							character.setTarget(NPClist[curNPC+1]);
						}
						FoundNewTarget = true;
						break;
					}
				}

				if ( !FoundNewTarget && NPClist.size() > 0) {
					character.setTarget(NPClist[0]);
				}
			}

			if (!keys[SDLK_TAB]) {
				KP_select_next = false;
			}

			if (keys[SDLK_ESCAPE] && !KP_toggle_showOptionsWindow ) {
				KP_toggle_showOptionsWindow = true;
				optionsWindow->setVisible( ! optionsWindow->isVisible() );
			}

			if ( !keys[SDLK_ESCAPE] ) {
				KP_toggle_showOptionsWindow = false;
			}

			if ( keys[SDLK_c] && !KP_toggle_showCharacterInfo ) {
				KP_toggle_showCharacterInfo = true;
				characterInfoScreen->setVisible( ! characterInfoScreen->isVisible() );
			}

			if ( !keys[SDLK_c] ) {
				KP_toggle_showCharacterInfo = false;
			}

			if ( keys[SDLK_b] && !KP_toggle_showSpellbook ) {
				KP_toggle_showSpellbook = true;
				spellbook->setVisible( ! spellbook->isVisible() );
			}

			if ( !keys[SDLK_b] ) {
				KP_toggle_showSpellbook = false;
			}

			if ( keys[SDLK_i] && !KP_toggle_showInventory ) {
			    KP_toggle_showInventory = true;
			    inventoryScreen->setVisible( !inventoryScreen->isVisible() );
			}

			if ( !keys[SDLK_i] ) {
			    KP_toggle_showInventory = false;
			}

			if ( keys[SDLK_q] && !KP_toggle_showQuestWindow ) {
			    KP_toggle_showQuestWindow = true;
			    questWindow->setVisible( !questWindow->isVisible() );
			}

			if ( !keys[SDLK_q] ) {
				KP_toggle_showQuestWindow = false;
			}

			actionBar->handleKeys();

			if (keys[SDLK_5] && !KP_interrupt) {
				KP_interrupt = true;
				character.CastingInterrupted();
			}

			if (!keys[SDLK_5]) {
				KP_interrupt = false;
			}

			if (keys[SDLK_SPACE] && !KP_attack) {
				KP_attack = true;
				if ( character.getTarget() != NULL ) {
					CAction *action = ActionCreation::createAttackAction( &character, character.getTarget() );
					character.executeAction(action);
				}
			}

			if (!keys[SDLK_SPACE]) {
				KP_attack = false;
			}
		}
		DrawScene();
		focus.updateFocus();
	}
}

int main(int argc, char* argv[])
{
	dawn_configuration::logfile = "dawn-log.log";
	dawn_configuration::debug_stdout = true;
	dawn_configuration::debug_fileout = true;
	dawn_configuration::show_info_messages = true;
	dawn_configuration::show_warn_messages = true;

	if(dawn_init(argc, argv))
		game_loop();

	return 0;
}
