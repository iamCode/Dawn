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

#include "soundengine.h"

#include <memory>
#include <SDL/SDL_mixer.h>

#include "musiccache.h"
#include "debug.h"
#include "configuration.h"

std::auto_ptr<MusicCache> musicCache( new MusicCache() );
std::auto_ptr<SoundCache> soundCache( new SoundCache() );

void SoundEngine::initSound()
{
	if ( ! Configuration::soundenabled )
		return;

	//int flags = MIX_INIT_OGG;
	//int initedFlags = Mix_Init( flags );
	//if ( initedFlags != flags )
	//{
	//	dawn_debug_fatal( "Could not initialize all sound modes (Mix_Init left error message \"%s\")", Mix_GetError() );
	//}
	// use default setting for audio and check for chunk callbacks every 64 bytes (don't know what is a good default here)
	if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512) == -1 )
	{
		dawn_debug_fatal( "Could not open audio (Mix_OpenAudio exited with error message \"%s\")", Mix_GetError() );
	}
}

void SoundEngine::cleanupSound()
{
	if ( ! Configuration::soundenabled )
		return;

	Mix_CloseAudio();
	//Mix_Quit();
}

void SoundEngine::playMusic( std::string musicFile, bool playInLoop )
{
	if ( ! Configuration::soundenabled )
		return;

	Mix_Music *musicSample = musicCache->getMusicFromCache( musicFile );
	int loops = 1;
	if ( playInLoop )
		loops = -1;
	if ( Mix_PlayMusic( musicSample, loops ) == -1 ) {
		dawn_debug_fatal( "Could not play music %s: %s", musicFile.c_str(), Mix_GetError() );
	}
}

void SoundEngine::playSound( std::string soundFile )
{
	if ( ! Configuration::soundenabled )
		return;

	Mix_Chunk *soundSample = soundCache->getSoundFromCache( soundFile );
	if ( Mix_PlayChannel( -1, soundSample, 0 ) == -1 ) {
		dawn_debug_fatal( "Could not play sound %s: %s", soundFile.c_str(), Mix_GetError() );
	}
}



