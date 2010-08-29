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
