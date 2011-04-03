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

bool Resolution::checkResolution( Resolution checkRes )
{
	Uint32 flags = SDL_OPENGL;
	if ( checkRes.fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}
	int suggestedBpp = SDL_VideoModeOK( checkRes.width, checkRes.height, checkRes.bpp, flags );
	return suggestedBpp != 0;
}

bool Resolution::checkResolutionAndAdjustBpp( Resolution &checkRes )
{
	Uint32 flags = SDL_OPENGL;
	if ( checkRes.fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}
	int suggestedBpp = SDL_VideoModeOK( checkRes.width, checkRes.height, checkRes.bpp, flags );
	if ( suggestedBpp >= 24 ) {
		dawn_debug_info("Changing bpp to %d instead of %d for resolution %dx%d", suggestedBpp, checkRes.bpp, checkRes.width, checkRes.height );
		checkRes.bpp = suggestedBpp;
	} else {
		dawn_debug_warn("Given bpp %d for resolution %dx%d probably don't work. Will try anyway since SDL suggested small bpp value of %d.", checkRes.bpp, checkRes.width, checkRes.height, suggestedBpp );
	}
	return suggestedBpp >= 24;
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

	checkResolutionAndAdjustBpp( setRes );
	
	Uint32 flags = SDL_OPENGL;
	if ( setRes.fullscreen ) {
		flags |= SDL_FULLSCREEN;
	}
	
	screen = SDL_SetVideoMode( setRes.width, setRes.height, setRes.bpp, flags );
	assert( screen != NULL );
}

void Resolution::scanPossibleResolutions()
{
	SDL_Rect** modes = SDL_ListModes(NULL, SDL_OPENGL|SDL_FULLSCREEN);
	
	for ( int curModeNr=0; modes[curModeNr]; ++curModeNr ) {
		Resolution tryRes = Resolution( modes[curModeNr]->w, modes[curModeNr]->h, 24, true );
		if ( checkResolutionAndAdjustBpp( tryRes ) ) {
			if ( tryRes.width >= 800 && tryRes.height >= 600 ) {
				possibleResolutions.push_back( tryRes );
				tryRes.fullscreen = false;
				possibleResolutions.push_back( tryRes );				
			}
		}
	}
}

void Resolution::clearPossibleResolutions()
{
	possibleResolutions.clear();
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
