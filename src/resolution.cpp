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

#include "resolution.h"

#include "SDL/SDL.h"
#include <fstream>
#include <cassert>

#include "debug.h"
#include "CLuaFunctions.h"

static std::vector<Resolution> possibleResolutions;

Resolution::Resolution( int width_, int height_, int bpp_, bool fullscreen_ )
	: width( width_ ),
      height( height_ ),
      bpp( bpp_ ),
      fullscreen( fullscreen_ )
{
}

std::vector< Resolution > getResolutionsToCheck()
{
	std::vector< Resolution > potentialResolutions;
	potentialResolutions.push_back( Resolution( 1024, 768, 24, true ) );
	potentialResolutions.push_back( Resolution( 1024, 768, 32, true ) );
	potentialResolutions.push_back( Resolution( 1024, 600, 24, true ) );
	potentialResolutions.push_back( Resolution( 1024, 600, 32, true ) );
	potentialResolutions.push_back( Resolution( 1152, 864, 24, true ) );
	potentialResolutions.push_back( Resolution( 1152, 864, 32, true ) );
	potentialResolutions.push_back( Resolution( 1280, 800, 24, true ) );
	potentialResolutions.push_back( Resolution( 1280, 800, 32, true ) );
	potentialResolutions.push_back( Resolution( 1280, 1024, 24, true ) );
	potentialResolutions.push_back( Resolution( 1280, 1024, 32, true ) );
	potentialResolutions.push_back( Resolution( 1366, 768, 24, true ) );
	potentialResolutions.push_back( Resolution( 1366, 768, 32, true ) );
	potentialResolutions.push_back( Resolution( 1440, 900, 24, true ) );
	potentialResolutions.push_back( Resolution( 1440, 900, 32, true ) );
	potentialResolutions.push_back( Resolution( 1600, 900, 24, true ) );
	potentialResolutions.push_back( Resolution( 1600, 900, 32, true ) );
	potentialResolutions.push_back( Resolution( 1680, 1050, 24, true ) );
	potentialResolutions.push_back( Resolution( 1680, 1050, 32, true ) );
	potentialResolutions.push_back( Resolution( 1920, 1080, 24, true ) );
	potentialResolutions.push_back( Resolution( 1920, 1080, 32, true ) );
	potentialResolutions.push_back( Resolution( 1920, 1200, 24, true ) );
	potentialResolutions.push_back( Resolution( 1920, 1200, 32, true ) );

	potentialResolutions.push_back( Resolution( 1024, 768, 24, false ) );
	potentialResolutions.push_back( Resolution( 1024, 768, 32, false ) );
	potentialResolutions.push_back( Resolution( 1024, 600, 24, false ) );
	potentialResolutions.push_back( Resolution( 1024, 600, 32, false ) );
	potentialResolutions.push_back( Resolution( 1152, 864, 24, false ) );
	potentialResolutions.push_back( Resolution( 1152, 864, 32, false ) );
	potentialResolutions.push_back( Resolution( 1280, 800, 24, false ) );
	potentialResolutions.push_back( Resolution( 1280, 800, 32, false ) );
	potentialResolutions.push_back( Resolution( 1280, 1024, 24, false ) );
	potentialResolutions.push_back( Resolution( 1280, 1024, 32, false ) );
	potentialResolutions.push_back( Resolution( 1366, 768, 24, false ) );
	potentialResolutions.push_back( Resolution( 1366, 768, 32, false ) );
	potentialResolutions.push_back( Resolution( 1440, 900, 24, false ) );
	potentialResolutions.push_back( Resolution( 1440, 900, 32, false ) );
	potentialResolutions.push_back( Resolution( 1600, 900, 24, false ) );
	potentialResolutions.push_back( Resolution( 1600, 900, 32, false ) );
	potentialResolutions.push_back( Resolution( 1680, 1050, 24, false ) );
	potentialResolutions.push_back( Resolution( 1680, 1050, 32, false ) );
	potentialResolutions.push_back( Resolution( 1920, 1080, 24, false ) );
	potentialResolutions.push_back( Resolution( 1920, 1080, 32, false ) );
	potentialResolutions.push_back( Resolution( 1920, 1200, 24, false ) );
	potentialResolutions.push_back( Resolution( 1920, 1200, 32, false ) );

	return potentialResolutions;
}

bool Resolution::checkResolution( Resolution checkRes )
{
	Uint32 flags = SDL_OPENGL;
	if ( checkRes.fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}
	SDL_Surface *testScreen = SDL_SetVideoMode( checkRes.width, checkRes.height, checkRes.bpp, flags );
	
	bool success = (testScreen != NULL);
	
	if ( testScreen != NULL ) {
		SDL_FreeSurface( testScreen );
	}
	
	return success;
}

Resolution Resolution::getBestResolution( bool fullscreenPreferred )
{
	for ( std::vector<Resolution>::iterator it=possibleResolutions.begin(); it!=possibleResolutions.end(); ++it ) {
		Resolution &curRes = *it;
		if ( curRes.fullscreen == fullscreenPreferred )
			return curRes;
	}
	
	// no resolution with wanted fullscreen-mode found. Return first resolution available
	if ( possibleResolutions.size() > 0 ) {
		return possibleResolutions[0];
	}
		
	dawn_debug_fatal("no working resolutions found");
	abort();
}

void Resolution::setResolution( SDL_Surface *&screen, Resolution setRes )
{
	dawn_debug_info( "now setting resolution %dx%d, bpp: %d, fullscreen: %d", setRes.width, setRes.height, setRes.bpp, setRes.fullscreen );
	if ( screen != NULL ) {
		SDL_FreeSurface( screen );
	}

	Uint32 flags = SDL_OPENGL;
	if ( setRes.fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}
	screen = SDL_SetVideoMode( setRes.width, setRes.height, setRes.bpp, flags );
	assert( screen != NULL );
}

void Resolution::scanPossibleResolutions()
{
	std::vector< Resolution > resolutionToCheck = getResolutionsToCheck();
	possibleResolutions.clear();
	
	// try each resolution in turn and set in resultvector if it works
	for ( std::vector<Resolution>::iterator it=resolutionToCheck.begin(); it!=resolutionToCheck.end(); ++it ) {
		Resolution &curRes = *it;

		if ( Resolution::checkResolution( curRes ) ) {		
			dawn_debug_info( "found supported resolution %dx%d, bpp %d, fullscreen %d", curRes.width, curRes.height, curRes.bpp, curRes.fullscreen );
			possibleResolutions.push_back( curRes );
		}
	}
}

void Resolution::writePossibleResolutionsToFile( std::string filename )
{
	std::ofstream ofs( filename.c_str() );
	for ( std::vector<Resolution>::iterator it=possibleResolutions.begin(); it!=possibleResolutions.end(); ++it ) {
		Resolution &curRes = *it;
		ofs << "Configuration.addPossibleResolution( " << curRes.width << ", " << curRes.height << ", " << curRes.bpp << ", " << std::boolalpha << curRes.fullscreen << " );" << std::endl;
	}
}

void Resolution::clearPossibleResolutions()
{
	possibleResolutions.clear();
}

void Resolution::loadResolutionsFromFile( std::string filename )
{
	LuaFunctions::executeLuaFile( filename );
}

std::vector< Resolution > Resolution::getPossibleResolutions()
{
	return possibleResolutions;
}

namespace Configuration
{
	void addPossibleResolution( int width, int height, int bpp, bool fullscreen )
	{
		possibleResolutions.push_back( Resolution( width, height, bpp, fullscreen ) );
	}
}
