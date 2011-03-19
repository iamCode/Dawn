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

#ifndef LOADINGMANAGER_H
#define LOADINGMANAGER_H

#include "threadObject/Thread.h"

#include <string>

class LoadingManager : public CThread
{
  public:
	virtual bool isFinished() = 0;
	virtual std::string getActivityText() = 0;
	virtual double getProgress() = 0;
	virtual void startBackgroundThread() = 0;
	virtual void executeMainThreadActions() = 0;
	virtual void finish() = 0;
};

#include <deque>

#include "CTexture.h"
#include "GLFT_Font.h"
#include "globals.h"
#include "CLuaFunctions.h"

#include "CEditor.h"
#include "CInterface.h"
#include "CharacterInfoScreen.h"
#include "InventoryScreen.h"
#include "ActionBar.h"
#include "Spellbook.h"
#include "LogWindow.h"
#include "BuffWindow.h"
#include "questwindow.h"
#include "optionswindow.h"
#include "shop.h"
#include "CZone.h"

extern bool threadedMode;
extern CEditor Editor;
extern CInterface GUI;
extern std::auto_ptr<CharacterInfoScreen> characterInfoScreen;
extern std::auto_ptr<InventoryScreen> inventoryScreen;
extern std::auto_ptr<ActionBar> actionBar;
extern std::auto_ptr<Spellbook> spellbook;
extern std::auto_ptr<LogWindow> logWindow;
extern std::auto_ptr<BuffWindow> buffWindow;
extern std::auto_ptr<QuestWindow> questWindow;
extern std::auto_ptr<OptionsWindow> optionsWindow;
extern std::auto_ptr<Shop> shopWindow;

class DawnInitObject;
extern DawnInitObject *curTextureProcessor;

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

class DawnInitObject : public LoadingManager
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

	virtual void executeMainThreadActions()
	{
		processCurTexture();
		processCurFont();
	}

	std::string getActivityText()
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
		dawn_debug_info( "setCurrentTextureToProcess called for %s", textureFile.c_str() );
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
		player->Init(512,400);
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

	virtual void startBackgroundThread()
	{
		threadedMode = true;
		curTextureProcessor = this;
		do {
			this->Event();
			Sleep( 10 );
		} while ( ! started );
	}

	virtual void finish()
	{
		threadedMode = false;
		curTextureProcessor = NULL;
	}
};

#endif // LOADINGMANAGER_H
