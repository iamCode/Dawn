/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

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

#ifndef __C_MESSAGE__
#define __C_MESSAGE__

#include "GLFT_Font.h"
#include <SDL/SDL.h>

#include <string>

struct sBook {
    std::string string;
    float red, green, blue, transparency;
    float lifetime;
    int decayrate;
    int x_pos, y_pos;
    float lastframe, thisframe;
    float startdecaylastframe, startdecaythisframe;

    sBook (std::string _text, int _x_pos, int _y_pos, float _red, float _green, float _blue, float _transparency, int _decayrate, float _lifetime) {
        string = _text; x_pos = _x_pos; y_pos = _y_pos; red = _red; green = _green; blue = _blue; transparency = _transparency; decayrate = _decayrate; lifetime = _lifetime; thisframe = 0.0f; lastframe = 0.0f; startdecaylastframe = 0.0f; startdecaythisframe = 0.0f;
    };
};

class CMessage {
    public:
    void AddText(int x, int y, float red, float green, float blue, float transparency, int decayrate, float lifetime, char *text, ...);
    void DrawAll();
    void DeleteDecayed();

    private:
    std::vector<sBook> MessageBook;
};

#endif
