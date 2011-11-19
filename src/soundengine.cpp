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
static size_t maxChannelsUsed = 0;

static void logChannelUsage( int curChannel )
{
	if( static_cast<size_t>(curChannel+1) > maxChannelsUsed )
	{
		maxChannelsUsed = static_cast<size_t>(curChannel+1);
		dawn_debug_info("Using a total maximum of %d channels for sound playing", maxChannelsUsed);
	}
}

void SoundEngine::initSound()
{
	if( !Configuration::soundenabled )
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
	if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 256) == -1 )
	{
		dawn_debug_fatal( "Could not open audio (Mix_OpenAudio exited with error message \"%s\")", Mix_GetError() );
	}
	// this should be enough for the beginning, but we might need to group the channels so each group can take care of
	// and fade out old channels if more are needed.
	const int totalNumChannels = 64;
	int numChannels = Mix_AllocateChannels(totalNumChannels);
	dawn_debug_info( "Currently allocated channels for sound = %d", numChannels );
}

void SoundEngine::cleanupSound()
{
	if ( !Configuration::soundenabled )
		return;

	Mix_CloseAudio();
	//Mix_Quit();
}

void SoundEngine::playMusic( std::string musicFile, bool playInLoop )
{
	if( !Configuration::soundenabled )
		return;

	if( currentlyPlayedMusic == musicFile && currentMusicInLoop == playInLoop )
		return;

	Mix_HaltMusic(); // halts the current played music stream so we don't mix music. Perhaps should be handled in other manners.

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
	if( !Configuration::soundenabled )
		return;

	Mix_Chunk *soundSample = soundCache->getSoundFromCache( soundFile );
	int curChannel = Mix_PlayChannel( -1, soundSample, 0 );
	if( curChannel  == -1 )
	{
		dawn_debug_fatal( "Could not play sound %s: %s", soundFile.c_str(), Mix_GetError() );
	}
	logChannelUsage( curChannel );
}

void SoundEngine::stopSound( std::string soundFile )
{
    if( !Configuration::soundenabled && soundFile != "" )
    {
        return;
    }

    /// load our sound file we want to stop in a Mix_Chunk to be able to compare it later.
    Mix_Chunk *ourSample = soundCache->getSoundFromCache( soundFile );

    /// get the number of channels in use.
    int numOfChannelsPlaying = Mix_Playing( -1 );

    /// here we check all channels we have to see if they are playing our chunk we want to stop.
    for( int curChannel = 0; curChannel <= numOfChannelsPlaying; curChannel++ )
    {
        if( ourSample == Mix_GetChunk( curChannel ) )
        {
            Mix_HaltChannel( curChannel );
        }
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
			dawn_debug_info("using channel %d for walking sound", walkingChannel);
			logChannelUsage( walkingChannel );
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

