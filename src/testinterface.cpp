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

#ifdef TESTINTERFACE // TESTINTERFACE BEGIN

#include "TestInterface.h"
#include "globals.h"
#include "dawnstate.h"
#include "luainterface.h"

void deactivateCurrentGameLoopHandler();

namespace TestInterface
{
    static Label *testChooseClass;
    static Label *testOptionsFrame;

    TestRunner::TestRunner( std::string fileToRun )
        : fileToRun( fileToRun ),
          started( false )
    {
        SetThreadType(ThreadTypeEventDriven);
    }

    BOOL TestRunner::OnTask()
    {
        executeScript();
	    return true;
    }

    void TestRunner::executeScript()
    {
        LuaFunctions::executeLuaTestFile( fileToRun );
    }

    TestRunner *testRunner;

    void executeTest( std::string fileToRun )
    {
        TestInterface::testRunner = new TestRunner( fileToRun );
        dawnSleep(1);
        testRunner->Event();
    }

    void publishChooseClass( Label *chooseClass )
    {
        testChooseClass = chooseClass;
    }

    void publishOptions( Label *optionsFrame )
    {
        testOptionsFrame = optionsFrame;
    }

    /// begin exported functions

    void dawnSleep( int seconds )
    {
        #ifdef _WIN32 // sleep on windows
            Sleep( seconds * 1000 );
        #else       // sleep on Linux
            sleep( seconds );
        #endif
    }

    void quitDawn( int returnValue )
    {
        exit( returnValue );
    }

    DawnState::DawnState getDawnState()
    {
        return DawnState::getDawnState();
    }

    void clickOnNewGame()
    {
        testChooseClass->execute();
    }

    void chooseClass( CharacterClass::CharacterClass characterClass )
    {
        dawnSleep( 1 ); // sleep for 1 second to allow game to catch up.
        Globals::getPlayer()->setClass( characterClass );
        deactivateCurrentGameLoopHandler();
    }

    void saveGame()
    {

    }

    void loadGame()
    {

    }

    void getQuest( Quest *quest )
    {

    }

    void finishQuest( Quest *quest )
    {

    }

    /// end exported functions
}

#endif // TESTINTERFACE END
