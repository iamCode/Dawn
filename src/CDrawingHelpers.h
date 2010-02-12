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

#ifndef __C_DRAWING_HELPERS_H_
#define __C_DRAWING_HELPERS_H_

#include "GLee/GLee.h" // OpenGL Easy Extention Library

extern int world_x;
extern int world_y;
extern int RES_X;
extern int RES_Y;

namespace DrawingHelpers
{
	inline void mapTextureToRect( GLuint texture, int left, int width, int bottom, int height )
	{
		// don't rebind texture if it is already bound
		// (this may save a lot of performance, if the texture is not scaled)
		GLuint boundTexture;
		int paramValue;
		glGetIntegerv( GL_TEXTURE_BINDING_2D, &paramValue );
		boundTexture = static_cast<GLuint>(paramValue);

		if ( boundTexture != texture ) {
			glBindTexture( GL_TEXTURE_2D, texture);
		}

		glBegin( GL_QUADS );
		// Bottom-left vertex (corner)
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( left, bottom, 0.0f );
		// Bottom-right vertex (corner)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( left + width, bottom, 0.0f );
		// Top-right vertex (corner)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( left + width, bottom + height, 0.0f );
		// Top-left vertex (corner)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( left, bottom + height, 0.0f );
		glEnd();
	}

	inline bool isRectOnScreen( int left, int width, int bottom, int height )
	{
		if (    left >= (world_x + RES_X)           // object right of screen
		        || bottom >= (world_y + RES_Y)         // object above screen
		        || (left + width) <= world_x           // object left of screen
		        || (bottom + height) <= world_y ) {    // object below screen
			return false;
		}
		return true;
	}
}

#endif // __DRAWING_HELPERS_H

