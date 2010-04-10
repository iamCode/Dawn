#include "fontcache.h"

#include "GLFT_Font.h"

#include <memory>
#include <cstdlib>

std::auto_ptr<FontCache> theFontCache( new FontCache() );

GLFT_Font* FontCache::getFontFromCache( std::string filename, size_t size )
{
	char buffer[20];
	sprintf( buffer, "%d", size );
	std::string fontCacheName = filename + std::string( "_" ).append( buffer );
	if ( theFontCache->fonts.count( fontCacheName ) > 0 ) {
		return theFontCache->fonts[ fontCacheName ];
	}
	GLFT_Font *newFont = new GLFT_Font( filename, size );
	theFontCache->fonts[ fontCacheName ] = newFont;
	return newFont;
}


FontCache::FontCache()
{
}

FontCache::~FontCache()
{
	for ( std::map<std::string, GLFT_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it ) {
		delete it->second;
	}
}
