#include "CInterface.h"

void CInterface::LoadTextures() {
    interfacetextures.texture.reserve(10);
    interfacetextures.LoadIMG("data/interface/blended_bg.tga",0);
    interfacetextures.LoadIMG("data/interface/lifemana.tga",1);
};

void CInterface::DrawInterface() {
    // background, black and nicely blended.
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, interfacetextures.texture[0].texture);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x, world_y+RES_Y-interfacetextures.texture[0].height, 0.0f);
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+RES_X, world_y+RES_Y-interfacetextures.texture[0].height, 0.0f);
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+RES_X, world_y+RES_Y, 0.0f);
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x, world_y+RES_Y, 0.0f);
    glEnd();

    // life and mana bars
    glBindTexture( GL_TEXTURE_2D, interfacetextures.texture[1].texture);
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(world_x, world_y+RES_Y-interfacetextures.texture[1].height, 0.0f);
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(world_x+interfacetextures.texture[1].width, world_y+RES_Y-interfacetextures.texture[1].height, 0.0f);
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(world_x+interfacetextures.texture[1].width, world_y+RES_Y, 0.0f);
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(world_x, world_y+RES_Y, 0.0f);
    glEnd();
    glDisable(GL_BLEND);
}
