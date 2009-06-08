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

#include "main.h"

SDL_Surface *screen;
extern CZone zone1;
CCharacter character;

CEditor Editor;

CInterface GUI;

extern int RES_X, RES_Y, RES_BPP, world_x, world_y, mouseX, mouseY, done;


float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

void DrawScene() {

    /**int xpos = 0, ypos = 0;
    for (unsigned int i=0; i < vTiles.size()-1; i++) {
        vTiles[i].DrawTexture(xpos,ypos, 1);
        xpos += 40;
        if (xpos > 500) {
            xpos = 0;
            ypos += 40;
        }
    }
    //glScalef(0.5f,0.5f,0.0f);

    // Blend the color key into oblivion! (optional)

    glColor4f(0.0f,0.0f,0.0f,shadow);			// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )
    glEnable( GL_BLEND );
    glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

    vTiles[vTiles.size()-1].DrawTexture(xpos-98+world_x,ypos-194+world_y,1);


    glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )
    vTiles[vTiles.size()-2].DrawTexture(xpos-100,ypos-200,1);**/

    /**glBegin(GL_LINES);
    glVertex3f(-1000.0f, (RES_Y/2), 0.0f); // origin of the line
    glVertex3f(1000.0f, (RES_Y/2), 0.0f); // ending point of the line
    glVertex3f((RES_X/2), -1000.0f, 0.0f); // origin of the line
    glVertex3f((RES_X/2), 1000.0f, 0.0f); // ending point of the line
    glEnd( );**/
    glEnable(GL_TEXTURE_2D);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslated(-world_x,-world_y,0);

    glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 50% Alpha ( NEW )

    zone1.DrawZone();

    character.Draw();

    // check our FPS and output it
    thisframe=SDL_GetTicks();     // Count the FPS
    ff++;
    if((thisframe-lastframe) > 1000) {
        fps=ff;
        ff=0;
        lastframe=thisframe;
    }

    GLFT_Font fnt("data/verdana.ttf", 12);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    fnt.drawText(world_x, world_y, "FPS: %d     world_x: %d, world_y: %d      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps, world_x,world_y, character.x_pos, character.y_pos, mouseX, mouseY);
    glDisable(GL_BLEND);

    if (Editor.enabled) {
        Editor.DrawEditor();
    } else {
        GUI.DrawInterface();
    }

    //glColor4f(1.0f,1.0f,1.0f,0.6f);			// Full Brightness, 50% Alpha ( NEW )

    /**glBindTexture( GL_TEXTURE_2D, zone1.ZoneTiles.texture[0].texture);
        glBegin( GL_QUADS );
        //Top-left vertex (corner)
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-2000, -2000, 0.0f );
        //Bottom-left vertex (corner)
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(2000, -2000, 0.0f );
        //Bottom-right vertex (corner)
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(2000, 2000, 0.0f );
        //Top-right vertex (corner)
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-2000, 2000, 0.0f );
    glEnd();

    glColor4f(0.7f,0.4f,0.0f,0.5f);			// Full Brightness, 50% Alpha ( NEW )
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, zone1.ZoneTiles.texture[33].texture);
        glBegin( GL_QUADS );
        //Top-left vertex (corner)
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f(0, 200, 0.0f );

        //Bottom-left vertex (corner)
        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f(80, 200, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f(80, 280, 0.0f );

        //Top-right vertex (corner)
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f(0, 280, 0.0f );
    glEnd();
    **/

    /** Multitexture stuff:
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, zone1.ZoneTiles.texture[33].texture);

    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, zone1.ZoneTiles.texture[1].texture);


    glPushMatrix();
        glBegin(GL_QUADS);
            // bottom left vertex
            glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
            glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 0.0f);
            glVertex3f(0, 200, 0);

            // top left vertex
            glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 0.0f);
            glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 0.0f);
            glVertex3f(40, 200, 0);

            // bottom right vertex
            glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 1.0f);
            glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 1.0f);
            glVertex3f(40, 240, 0);

            // top right vertex
            glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0f);
            glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
            glVertex3f(0, 240, 0);
        glEnd();
    glPopMatrix();

    glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);

    glActiveTextureARB(GL_TEXTURE0_ARB);
    glDisable(GL_TEXTURE_2D);
    **/

   /** if (!toggle_editor) {
        //glColor4f(0.0f,0.7f,0.7f,1.0f);			// Full Brightness, 50% Alpha ( NEW )
        //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )

        glTranslatef((RES_X/2)+world_x-(ball.texture[7].width/2),(RES_Y/2)+world_y-(ball.texture[7].height/2),0.0);
        glRotatef(angle,0.0f,0.0f,1.0f);
        glTranslatef(-(RES_X/2)+world_x-(ball.texture[7].width/2),-(RES_Y/2)+world_y-(ball.texture[7].height/2),0.0);
        angle += 5;

        if (angle >= 360) {
            angle = 0;
        }
    }**/

    SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) {
    Uint8 *keys;

    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) { // start up SDL
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    screen=SDL_SetVideoMode(RES_X,RES_Y,RES_BPP,SDL_OPENGL | SDL_FULLSCREEN);
    if ( screen == NULL ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

    glEnable( GL_TEXTURE_2D );

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glViewport( 0, 0, RES_X, RES_Y );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity(); // reset view to 0,0

    glOrtho(0.0f, RES_X, RES_Y, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();  // reset view to 0,0

    glEnable( GL_BLEND ); // enable blending
    glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

    zone1.LoadZone("data/zone1");

    character.texture.texture.reserve(2);
    character.texture.LoadIMG("data/tile.tga",1);
    character.Init((RES_X/2),(RES_Y/2));

    Editor.LoadTextures();
    GUI.LoadTextures();

    SDL_ShowCursor(0);

    while(done == 0) {
        if (Editor.enabled) {
            Editor.HandleKeys();
        } else {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)  { done = 1; }

                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
                    if (event.key.keysym.sym == SDLK_SPACE) { }
                }

                if (event.type == SDL_MOUSEMOTION) {
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                }
            }

            keys = SDL_GetKeyState(NULL);

            if (keys[SDLK_DOWN]) { character.MoveDown(); }
            if (keys[SDLK_UP]) { character.MoveUp(); }
            if (keys[SDLK_LEFT]) { character.MoveLeft(); }
            if (keys[SDLK_RIGHT]) { character.MoveRight(); }

             if (keys[SDLK_l] && !Editor.KP_toggle_editor) {
                Editor.enabled = true;
                Editor.KP_toggle_editor = true;
            }

            if (!keys[SDLK_l]) {
                Editor.KP_toggle_editor = false;
            }
        }
        DrawScene();
    }
  return 0;
}



