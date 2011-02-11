/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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

#ifndef __LOGWINDOW_H__
#define __LOGWINDOW_H__

#include "CTexture.h"
#include "GLFT_Font.h"

namespace DawnInterface {
    void addTextToLogWindow( GLfloat color[], const char *text, ... );
}

struct sTextLine {
    std::string text;
    GLfloat color[4];

    sTextLine( std::string text_, GLfloat color_[] )
    {
        text = text_;
        color[0] = color_[0];
        color[1] = color_[1];
        color[2] = color_[2];
        color[3] = 1.0f;
    }
};

class LogWindow {

    public:
        LogWindow();
        ~LogWindow();
        void addTextToLog( std::string text, GLfloat color[] );
        void loadTextures();
        void draw();
        void clear();


    private:
        CTexture textures;
        GLFT_Font *font;
        int posX;
        int posY;
        int width;
        int height;
        std::vector <sTextLine> textDatabase;
};

#endif
