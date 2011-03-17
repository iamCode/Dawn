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
