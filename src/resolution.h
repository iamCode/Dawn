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

#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <vector>
#include <string>

class SDL_Surface;

class Resolution
{
public:
	int width;
	int height;
	int bpp;
	bool fullscreen;

	Resolution( int width, int height, int bpp, bool fullscreen );
	
	static void scanPossibleResolutions();
	static void clearPossibleResolutions();
	static std::vector< Resolution > getPossibleResolutions();	
	static bool checkResolution( Resolution checkRes );
	static bool checkResolutionAndAdjustBpp( Resolution &checkRes );
	static Resolution getBestResolution( bool fullscreenPreferred );
	static void setResolution( SDL_Surface *&screen, Resolution setRes );
};

#endif // RESOLUTION_H
