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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h> // Nothing uses this, perhaps it could be removed?
#endif

#include <vector>
#include <math.h>

#include "GLee/GLee.h" // OpenGL Easy Extention Library

#include <SDL/SDL.h> // SDL
#include <SDL/SDL_opengl.h> // SDL OpenGL
#include <SDL/SDL_image.h> // SDL Image library (image formats: BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV)

#include <GL/gl.h> // OpenGL
#include <GL/glu.h> // OpenGL Utility Library. This will have to be changed in updated versions, as it changes for different OS's

#include "CTexture.h"

#include "GLFT_Font.h"

#include "pnglite/pnglite.h"

#include "CZone.h"
#include "CInterface.h"
#include "CCharacter.h"
#include "CEditor.h"
#include "CMessage.h"
#include "InventoryScreen.h"
#include "cameraFocusHandler.h"
#include "utils.h"
#include "tooltip.h"
#include "ActionBar.h"
#include "Spellbook.h"
#include "BuffWindow.h"
#include "shop.h"

int world_x = 0, world_y = 0;
int mouseX, mouseY;
int done = 0;
CZone zone1;
CMessage message;
