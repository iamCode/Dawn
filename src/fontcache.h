#ifndef FONTCACHE_H
#define FONTCACHE_H

#include <map>
#include <string>

class GLFT_Font;

class FontCache
{
private:
	std::map<std::string,GLFT_Font*> fonts;

public:
	FontCache();
	~FontCache();
	static GLFT_Font* getFontFromCache( std::string filename, size_t size );
};

#endif // FONTCACHE_H
