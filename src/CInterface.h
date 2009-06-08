#ifndef __C_INTERFACE__
#define __C_INTERFACE__

#include "CTexture.h"

extern int RES_X,RES_Y,world_x,world_y;

class CInterface {
    public:
    void LoadTextures();
    bool enabled;
    void DrawInterface();


    private:
    CTexture interfacetextures;
};


#endif
