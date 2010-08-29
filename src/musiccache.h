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

#endif // MUSICCACHE_H
