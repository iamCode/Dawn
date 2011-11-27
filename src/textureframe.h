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

#ifndef TEXTUREFRAME_H
#define TEXTUREFRAME_H

#include <iostream>

class TextureFrame
{
	private:
		unsigned char* buffer;
		size_t width;
		size_t height;
		size_t curX;
		size_t curY;
		size_t maxY;
		GLuint texID;
		size_t curTextures;
		size_t usedSpace;

	public:
		TextureFrame()
		{
			width = 512;
			height = 512;
			curX=0;
			curY=0;
			maxY=0;
			curTextures=0;
			usedSpace = 0;
			buffer = new unsigned char[width * height * 20];
			memset( buffer, 0, width*height*20 );
			// Have OpenGL generate a texture object handle for us
			glGenTextures(1, &texID);
		}

		size_t getWidth() const
		{
			return width;
		}

		size_t getHeight() const
		{
			return height;
		}

		void addTexture( sTexture &stexture, char *texture, size_t w, size_t h )
		{
			if ( w > width || h > height )
				abort();
			if ( width - curX < w )
			{
				curX = 0;
				curY = maxY;
			}
			if ( height - curY < h )
			{
				finishFrame();
			}
			for ( size_t row=0; row<h; ++row )
			{
				// just 4 byte so far
				memcpy( buffer+(((curY+row)*width+curX)*4), texture+(w*row*4), 4*w );
			}
			stexture.x1=((float)curX+0.5)/width;
			stexture.x2=((float)curX+w-0.5)/width;
			stexture.y1=((float)curY+0.5)/height;
			stexture.y2=((float)curY+h-0.5)/height;
			stexture.width = w;
			stexture.height = h;
			stexture.texture = texID;
			curX += w;
			maxY = std::max(maxY, curY+h);
			++curTextures;
			usedSpace += w*h;
		}

		void finishFrame()
		{
			if ( curX == 0 && curY == 0 ) return;

			// Bind the texture object
			glBindTexture(GL_TEXTURE_2D, texID);

			// Set the texture's stretching properties
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, buffer);

			dawn_debug_info( "texture frame finished with %d textures on it and %.2f% of space used", curTextures, float(usedSpace)/(width*height)*100);
			memset( buffer, 0, width*height*20 );

			curX=0;
			curY=0;
			maxY=0;
			curTextures = 0;
			usedSpace = 0;

			// Have OpenGL generate a texture object handle for us
			glGenTextures(1, &texID);
		}
};

#endif // __TEXTUREFRAME_H__
