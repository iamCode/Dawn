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

#ifdef TESTINTERFACE // TESTINTERFACE BEGIN

#ifndef __TESTINTERFACE_H__
#define __TESTINTERFACE_H__

#include "threadObject/Thread.h"
#include "CCharacter.h"
#include "DawnState.h"
#include "Quest.h"
#include "ControlElement.h"
#include <string>

namespace TestInterface
{
    class TestRunner : public CThread
    {
        public:
            TestRunner( std::string fileToRun );
            ~TestRunner();
            virtual BOOL OnTask();
            void executeScript();

        private:
            std::string fileToRun;
            bool started;
    };

    void executeTest( std::string fileToRun );
    void publishChooseClass( Label *chooseClass );
    void publishOptions( Label *optionsFrame );

    // Specific functions exported to LUA
    void dawnSleep( int seconds );
    void quitDawn( int returnValue );
    DawnState::DawnState getDawnState();
    void chooseClass( CharacterClass::CharacterClass characterClass );
    void clickOnNewGame();
    void saveGame();
    void loadGame();
    void getQuest( Quest *quest );
    void finishQuest( Quest *quest );
    // end exported functions
}


#endif

#endif // TESTINTERFACE END
