/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "testsuite.h"
#include <vector>
#include <stdlib.h>

TestCase::TestCase( std::string name, std::string description, std::string LUAfile )
	: name(name),
	  description(description),
	  LUAfile(LUAfile)
{
}


std::string TestCase::getName() const
{
	return name;
}

std::string TestCase::getDescription() const
{
	return description;
}

std::string TestCase::getLUAfile() const
{
	return LUAfile;
}

int TestCase::getResult() const
{
	return result;
}

void TestCase::setResult( int result )
{
	this->result = result;
}

void handle_arguments( int argc, char *argv[] )
{
    for ( int index = 1; index < argc; index++ ) {
        std::string current_arg( argv[index] );
        if ( current_arg == "--junit-output" ) {
            logWithJUnit = true;
        }
    }
}

int main( int argc, char *argv[] )
{
	std::vector<TestCase*> testCases;
	std::string dawnExecutable;
	#ifdef _WIN32 // if we're on windows, we try to execute Dawn.exe
		dawnExecutable = "Dawn.exe --test ";
	#else 			// and on Linux, ./dawn-rpg
		dawnExecutable = "./dawn-rpg --test ";
	#endif

	handle_arguments( argc, argv );

	if ( logWithJUnit == true ) {
	    std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><testsuite>" << std::endl;
	}

	testCases.push_back( new TestCase( "StartQuitDawn", "Starts Dawn and then quits.", "tests/start_quit.lua" ) );
	testCases.push_back( new TestCase( "SaveLoadGame", "Save a game and then load it", "tests/save_load.lua" ) );

	for (unsigned int curTestCase = 0; curTestCase <testCases.size(); curTestCase++)
	{
	    std::string testToRun( dawnExecutable + testCases[ curTestCase ]->getLUAfile() );
		testCases[curTestCase]->setResult( system( testToRun.c_str() ) );
	}

	for (unsigned int curTestCase = 0; curTestCase <testCases.size(); curTestCase++)
	{
	    if ( logWithJUnit == true ) {
	        std::cout << "<testcase name=\"" << testCases[curTestCase]->getName() << "\">" << std::endl;
		} else {
		    std::cout << "Test: " << testCases[curTestCase]->getName() << " ==> ";
		}

		if ( testCases[curTestCase]->getResult() != 0 ) {
			if ( logWithJUnit == true ) {
                std::cout << "<result type=\"failure\">" << std::endl
                << testCases[curTestCase]->getDescription()
                << "</result>" << std::endl;
		    } else {
                std::cout << "FAILED" << std::endl;
                std::cout << "Description: " << testCases[curTestCase]->getDescription() << std::endl;
		    }
		} else {
			if ( logWithJUnit == false ) {
			    std::cout << "OK" << std::endl;
			}
		}
		if ( logWithJUnit == true ) {
	        std::cout << "</testcase>" << std::endl;
		} else {
		    std::cout << std::endl;
		}
	}

	if ( logWithJUnit == true ) {
        std::cout << "</testsuite>" << std::endl;
	}

	return 0;
}

/** TODO:
	* Add subtests to testcases.
	* Start specific tests using commandline argument. like `./testsuite --all` or `./testsuite --StartQuitDawn --SaveLoadGame --allSpells`
		and then all those testcases would be loaded in to the vector.
    * Add XML format output (jUnit/xUnit) for parsing in Jenkins.
**/
