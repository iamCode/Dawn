#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <math.h>

#include "GLee/GLee.h" // OpenGL Easy Extention Library

#include <SDL/SDL.h> // SDL
#include <SDL/SDL_opengl.h> // SDL OpenGL
#include <SDL/SDL_image.h> // SDL Image library (image formats: BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV)

#include <GL/gl.h> // OpenGL
#include <GL/glu.h> // OpenGL Utility Library

#include "CTexture.h"

#include "GLFT_Font.h"

#include "CZone.h"
#include "CInterface.h"
#include "CCharacter.h"
#include "CEditor.h"

int RES_X = 1024,RES_Y = 768, RES_BPP = 32;
int world_x = 0, world_y = 0;
int mouseX, mouseY;
int done = 0;
CZone zone1;
