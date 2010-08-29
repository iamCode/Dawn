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
