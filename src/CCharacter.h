#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "GLee/GLee.h" // OpenGL Easy Extention Library
#include "CTexture.h"
#include "CZone.h"
#include <SDL/SDL.h> // SDL

extern int RES_X,RES_Y,world_x,world_y;
extern CZone zone1;

class CCharacter {
    public:
    GLuint frame;
    int x_pos,y_pos;

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Init(int x, int y) { x_pos = x; y_pos = y; }
    void Draw();

    int CollisionCheck(int direction);

    CTexture texture;

    private:
};


#endif
