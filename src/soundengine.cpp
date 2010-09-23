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

static std::string currentlyPlayedMusic = "";
static bool currentMusicInLoop = false;

void SoundEngine::initSound()
{
	if ( ! Configuration::soundenabled )
		return;

	// This seems to be done, but since I found it in the library documentation it might be code
	// needed for a higher version of SDL_Mixer
	//int flags = MIX_INIT_OGG;
	//int initedFlags = Mix_Init( flags );
	//if ( initedFlags != flags )
	//{
	//	dawn_debug_fatal( "Could not initialize all sound modes (Mix_Init left error message \"%s\")", Mix_GetError() );
	//}
	
	// Chunksize is 256 since this is the smallest my system can handle.
	// Higher chunk sizes seem to make time between click and click sound noticable
	if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 256) == -1 )
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

	if ( currentlyPlayedMusic == musicFile && currentMusicInLoop == playInLoop )
		return;

	Mix_Music *musicSample = musicCache->getMusicFromCache( musicFile );
	int loops = 1;
	if ( playInLoop )
		loops = -1;
	if ( Mix_PlayMusic( musicSample, loops ) == -1 ) {
		dawn_debug_fatal( "Could not play music %s: %s", musicFile.c_str(), Mix_GetError() );
	}
	currentlyPlayedMusic = musicFile;
	currentMusicInLoop = playInLoop;
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

static int walkingChannel = -1;

void SoundEngine::useWalkingSound( bool enabled )
{
	if ( ! Configuration::soundenabled )
		return;

	if ( !enabled && walkingChannel >= 0 ) {
		if ( ! Mix_Paused( walkingChannel ) ) {
			Mix_Pause( walkingChannel );
		}
	} else if ( enabled ) {
		if ( walkingChannel == -1 ) {
			std::string soundFile = "data/sound/walking.ogg";
			Mix_Chunk *soundSample = soundCache->getSoundFromCache( soundFile.c_str() );
			walkingChannel = Mix_PlayChannel( -1, soundSample, -1 );
			if ( walkingChannel == -1 ) {
				dawn_debug_fatal( "Could not play sound %s: %s", soundFile.c_str(), Mix_GetError() );
			}
		} else if ( Mix_Paused( walkingChannel ) ) {
			Mix_Resume( walkingChannel );
		}
	}
}

namespace DawnInterface
{
	void setBackgroundMusic( std::string filename )
	{
		SoundEngine::playMusic( filename, true );
	}
}

