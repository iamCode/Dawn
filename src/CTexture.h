/**                    Dawn - 2D roleplaying game
    Copyright (C) 2009  Tobias Eliasson (arnestig@users.sourceforge.net)

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

#ifndef __CTILES_H_
#define __CTILES_H_

#include "GLee/GLee.h" // OpenGL Easy Extention Library
#include <SDL/SDL.h> // SDL

#include <vector>

struct sTexture {
    GLuint texture;
    int height, width;
    bool contains_collision_box;
    SDL_Rect collision_box;

    sTexture(int _height, int _width, bool _ccb) { height = _height; width = _width; contains_collision_box = _ccb; };
};

class CTexture {
    public:
    std::vector<sTexture> texture;

    int LoadTextureMap(char *file, bool try_load_collision_box = false);
    void LoadIMG(char *file, int texture_index);
    void DrawTexture(int x, int y, int draw_id, float transparency = 1.0f);
    int NumberOfTextures;

    private:
    SDL_Surface *surface;
    GLenum texture_format;
    GLint nOfColors;
};

#endif
