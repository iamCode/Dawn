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

#include <memory>
#include <cassert>
#include "fontcache.h"
#include "LogWindow.h"
#include "CDrawingHelpers.h"

extern void formatMultilineText( std::string text, std::vector< std::string > &textLines, int lineWidth, GLFT_Font *font );

LogWindow::LogWindow()
    :   posX ( 0 ),
        posY ( 0 ),
        width ( 390 ),
        height ( 150 )
{
    font = FontCache::getFontFromCache( "data/verdana.ttf", 12 );
};

LogWindow::~LogWindow()
{
};

void LogWindow::addTextToLog( std::string text, GLfloat color[] )
{
    std::vector<std::string> formattedLines;
    formatMultilineText( text, formattedLines, 370, font );
    for ( size_t curLine = 0; curLine < formattedLines.size(); curLine++ ) {
        textDatabase.insert( textDatabase.begin(), sTextLine( formattedLines[ curLine ], color ) );
    }

}

void LogWindow::loadTextures()
{
    textures.texture.resize(1);
	textures.LoadIMG("data/interface/blended_bg.tga",0);
}

void LogWindow::draw()
{
    DrawingHelpers::mapTextureToRect(   textures.texture[0].texture,
                                        world_x + posX, width,
                                        world_y + posY, height
                                    );
    for ( size_t lineRow = 0; lineRow < textDatabase.size() && lineRow < 10; lineRow++ ) {
        glColor4fv( textDatabase[ lineRow ].color );
        font->drawText( 10 + static_cast<double>( world_x ) + posX, 10 + static_cast<double>( world_y ) + posY + (lineRow * font->getHeight()), textDatabase[ lineRow ].text );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    }
}

void LogWindow::clear()
{
    textDatabase.clear();
}


extern std::auto_ptr<LogWindow> logWindow;

namespace DawnInterface
{
	void addTextToLogWindow( GLfloat color[], const char *text, ... )
	{
		char buffer[1024];
        std::va_list args;

        // writing our text and arguments to the buffer
        va_start(args, text);
        vsnprintf(buffer,1024,text,args);
        va_end(args);

        // push everything to our vector.
        logWindow->addTextToLog( std::string(buffer), color );
	}

	void clearLogWindow()
	{
	    logWindow->clear();
	}
}
