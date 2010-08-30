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

#ifndef MUSICCACHE_H
#define MUSICCACHE_H

#include <string>
#include <map>
#include <SDL/SDL_mixer.h>

/// This class is used by the SoundEngine to keep track of loaded music
class MusicCache
{
	private:
		std::map< std::string, Mix_Music* > internalMap;
	public:
		MusicCache();
		~MusicCache();
		Mix_Music* getMusicFromCache( std::string musicFile );
};

/// This class is used by the SoundEngine to keep track of loaded sounds
class SoundCache
{
	private:
		std::map< std::string, Mix_Chunk* > internalMap;
	public:
		SoundCache();
		~SoundCache();
		Mix_Chunk* getSoundFromCache( std::string soundFile );
};

#endif // MUSICCACHE_H
