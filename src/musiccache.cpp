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

#include "musiccache.h"

#include "debug.h"

MusicCache::MusicCache()
{
}

MusicCache::~MusicCache()
{
	for ( std::map<std::string, Mix_Music*>::iterator it = internalMap.begin(); it != internalMap.end(); ++it ) {
		Mix_FreeMusic( it->second );
	}
}

Mix_Music* MusicCache::getMusicFromCache( std::string filename )
{
	Mix_Music *music = NULL;
	if ( internalMap.count( filename ) > 0 ) {
		return internalMap[ filename ];
	}
	music = Mix_LoadMUS(filename.c_str());
	if ( music == NULL ) {
		dawn_debug_fatal( "Could not load music file %s: %s", filename.c_str(), Mix_GetError() );
	}
	internalMap[ filename ] = music;
	return internalMap[ filename ];
}

SoundCache::SoundCache()
{
}

SoundCache::~SoundCache()
{
	for ( std::map<std::string, Mix_Chunk*>::iterator it = internalMap.begin(); it != internalMap.end(); ++it ) {
		Mix_FreeChunk( it->second );
	}
}

Mix_Chunk* SoundCache::getSoundFromCache( std::string filename )
{
	Mix_Chunk *sound = NULL;
	if ( internalMap.count( filename ) > 0 ) {
		return internalMap[ filename ];
	}
	sound = Mix_LoadWAV(filename.c_str());
	if ( sound == NULL ) {
		dawn_debug_fatal( "Could not load music file %s: %s", filename.c_str(), Mix_GetError() );
	}
	internalMap[ filename ] = sound;
	return internalMap[ filename ];
}

