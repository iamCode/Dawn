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

#include "optionswindow.h"

#include "CTexture.h"
#include "GLFT_Font.h"
#include "CDrawingHelpers.h"
#include "fontcache.h"
#include "CLuaFunctions.h"
#include "questwindow.h"
#include "interactionpoint.h"
#include "CZone.h"
#include "Player.h"
#include "globals.h"
#include "shop.h"
#include "Spellbook.h"
#include "ActionBar.h"
#include "FramesBase.h"
#include "configuration.h"
#include "utils.h"
#include <memory>

extern std::auto_ptr<QuestWindow> questWindow;

namespace DawnInterface
{
    void clearLogWindow();
    void addTextToLogWindow( GLfloat color[], const char *text, ... );
}

OptionsWindow::OptionsWindow() : FramesBase ( 0, 0, 279, 217, 20, 19 )
{
	visible = false;
	font = NULL;
	backgroundTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 20);
	backgroundTexture = new CTexture();
	backgroundTexture->LoadIMG( "data/interface/OptionsScreen/optionsScreen.tga", 0 );
}

void OptionsWindow::setTextureDependentPositions()
{
	// at this point the background texture has been loaded
	frameWidth = backgroundTexture->getTexture(0).width;
	frameHeight = backgroundTexture->getTexture(0).height;
	// center on screen
	posX = (Configuration::screenWidth - frameWidth) / 2;
	posY = (Configuration::screenHeight - frameHeight) / 2;
}

OptionsWindow::~OptionsWindow()
{
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
}

extern int mouseX;
extern int mouseY;

void OptionsWindow::draw( int mouseX, int mouseY )
{
	// show screen
	DrawingHelpers::mapTextureToRect( backgroundTexture->getTexture(0),
	                                  posX + world_x, frameWidth,
	                                  posY + world_y, frameHeight );

	// show option names (continue, quit, load, save, settings)
	int textX = world_x + posX + 64;
	int textY = world_y + posY + frameHeight - 64 - font->getHeight();
	std::string curText = "Quit Game";
	int selectedEntry = -1;
	if ( mouseX < posX + 64 || mouseX > posX + frameWidth  - 64 || posY + frameHeight - 64 < mouseY) {
		selectedEntry = -1;
	} else {
		selectedEntry = (posY + frameHeight - 64 - mouseY) / static_cast<int>(font->getHeight()*1.5);
		if ( (posY + frameHeight - 64 - mouseY) % static_cast<int>(font->getHeight()*1.5) > static_cast<int>(font->getHeight()) ) {
			selectedEntry = -1;
		}
	}

	if ( selectedEntry == 0 ) {
		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	}
	font->drawText( textX, textY, "Quit Game" );
	if ( selectedEntry == 0 ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 1 ) {
        if ( utils::file_exists( "savegame.lua" ) == true ) {
            glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
        } else {
            glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
        }
	} else if ( utils::file_exists( "savegame.lua" ) == false ) {
        glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
	}
	font->drawText( textX, textY, "Load Game" );
	if ( selectedEntry == 1 || utils::file_exists( "savegame.lua" ) == false ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 2 ) {
		if ( Globals::isSavingAllowed() ) {
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
		} else {
			glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		}
	} else if ( ! Globals::isSavingAllowed() ) {
		glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
	}
	font->drawText( textX, textY, "Save Game" );
	if ( selectedEntry == 2 || ! Globals::isSavingAllowed() ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 3 ) {
		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	}
	font->drawText( textX, textY, "Continue" );
	if ( selectedEntry == 3 ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
}

void setQuitGame();

extern std::auto_ptr<Shop> shopWindow;
extern std::auto_ptr<Spellbook> spellbook;
extern std::auto_ptr<ActionBar> actionBar;

void OptionsWindow::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	// check for quit and the other options
	if ( ! isMouseOnFrame( mouseX, mouseY ) ) {
		return;
	}

	int selectedEntry = -1;
	if ( mouseX < posX + 64 || mouseX > posX + frameWidth  - 64 || posY + frameHeight - 64 < mouseY) {
		selectedEntry = -1;
	} else {
		selectedEntry = (posY + frameHeight - 64 - mouseY) / static_cast<int>(font->getHeight()*1.5);
		if ( (posY + frameHeight - 64 - mouseY) % static_cast<int>(font->getHeight()*1.5) > static_cast<int>(font->getHeight()) ) {
			selectedEntry = -1;
		}
	}

	if ( selectedEntry == 0 ) {
		setQuitGame();
	} else if ( selectedEntry == 1 && utils::file_exists( "savegame.lua" ) == true ) {
		// Load Game

		// clear current game data
		Globals::getCurrentZone()->purgeInteractionList();
		Globals::getCurrentZone()->purgeInteractionRegionList();
		questWindow->removeAllQuests();
		for ( std::map< std::string, CZone* >::iterator it = Globals::allZones.begin(); it != Globals::allZones.end(); ++it ) {
			delete it->second;
			it->second = NULL;
		}
		Globals::allZones.clear();

		Globals::getPlayer()->clearInventory();
		// clear shop data
		shopWindow = std::auto_ptr<Shop>( new Shop( Globals::getPlayer(), NULL ) );
		// clear spellbook
		spellbook->clear();
		// clear action bar
		actionBar->clear();
		// clear cooldowns
		Globals::getPlayer()->clearCooldownSpells();
		// clear buffs
		Globals::getPlayer()->clearActiveSpells();

		// reenter map
		// 1. Load all zones
		// TODO: Load all zones
		// 2. Restore lua variables
		LuaFunctions::executeLuaScript( "loadGame( 'savegame' )" );
		//CZone *newZone = Globals::allZones["data/zone1"];
		//newZone->LoadZone("data/zone1");
		LuaFunctions::executeLuaFile( "data/quests_wood.lua" );
		DawnInterface::clearLogWindow();
	} else if ( selectedEntry == 2 ) {
		if ( Globals::isSavingAllowed() ) {
			// Save Game
			LuaFunctions::executeLuaScript( "saveGame( 'savegame' )" );
			GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
            DawnInterface::addTextToLogWindow( yellow, "Game saved.");
		}
	} else if ( selectedEntry == 3 ) {
		toggle(); // close the window
	}
}

ChooseClassScreen::ChooseClassScreen() : FramesBase( 0, 0, 279, 313, 20, 19 )
{
	visible = true;
    done = false;
	font = NULL;
	backgroundTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 20);
	backgroundTexture = new CTexture();
	backgroundTexture->LoadIMG( "data/interface/OptionsScreen/classScreen.tga", 0 );
}

ChooseClassScreen::~ChooseClassScreen()
{
}

void ChooseClassScreen::setTextureDependentPositions()
{
	// at this point the background texture has been loaded
	frameWidth = backgroundTexture->getTexture(0).width;
	frameHeight = backgroundTexture->getTexture(0).height;
	// center on screen
	posX = (Configuration::screenWidth - frameWidth) / 2;
	posY = (Configuration::screenHeight - frameHeight) / 2;
}

bool ChooseClassScreen::isDone() const
{
    return done;
}

void ChooseClassScreen::draw( int mouseX, int mouseY )
{
	// show screen
	DrawingHelpers::mapTextureToRect( backgroundTexture->getTexture(0),
	                                  posX + world_x, frameWidth,
	                                  posY + world_y, frameHeight );


    // show class choices
	int textX = world_x + posX + 64;
	int textY = world_y + posY + frameHeight - 96 - font->getHeight();

    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	font->drawText( textX, textY + 32, "Choose class" );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

	std::string curText = "Choose class";
	int selectedEntry = -1;
	if ( mouseX < posX + 64 || mouseX > posX + frameWidth - 64 || posY + frameHeight - 128 < mouseY) {
		selectedEntry = -1;
	} else {
		selectedEntry = (posY + frameHeight - 128 - mouseY) / static_cast<int>(font->getHeight()*1.5);
		if ( (posY + frameHeight - 128 - mouseY) % static_cast<int>(font->getHeight()*1.5) > static_cast<int>(font->getHeight()) ) {
			selectedEntry = -1;
		}
	}

	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 0 ) {
		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	}
	font->drawText( textX, textY, "Liche" );
	if ( selectedEntry == 0 ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 1 ) {
		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	}
	font->drawText( textX, textY, "Ranger" );
	if ( selectedEntry == 1 ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	textY -= font->getHeight() * 1.5;
	if ( selectedEntry == 2 ) {
		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
	}
	font->drawText( textX, textY, "Warrior" );
	if ( selectedEntry == 2 ) {
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	}
}

void ChooseClassScreen::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
    // check for quit and the other options
	if ( ! isMouseOnFrame( mouseX, mouseY ) ) {
        return;
    }

	int selectedEntry = -1;
	if ( mouseX < posX + 64 || mouseX > posX + frameWidth  - 64 || posY + frameHeight - 128 < mouseY) {
		selectedEntry = -1;
	} else {
		selectedEntry = (posY + frameHeight - 128 - mouseY) / static_cast<int>(font->getHeight()*1.5);
		if ( (posY + frameHeight - 128 - mouseY) % static_cast<int>(font->getHeight()*1.5) > static_cast<int>(font->getHeight()) ) {
			selectedEntry = -1;
        }
	}

	if ( selectedEntry == 0 ) { // we choose liche
		Globals::getPlayer()->setClass( CharacterClass::Liche );
		done = true;
	} else if ( selectedEntry == 1 ) { // we choose ranger
	    Globals::getPlayer()->setClass( CharacterClass::Ranger );
		done = true;
    } else { // we choose warrior
        Globals::getPlayer()->setClass( CharacterClass::Warrior );
		done = true;
	}
}
