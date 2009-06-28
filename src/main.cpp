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

#include "main.h"

SDL_Surface *screen;
extern CZone zone1;
extern CMessage message;
CCharacter character;

CEditor Editor;

CInterface GUI;

extern int RES_X, RES_Y, RES_BPP, world_x, world_y, mouseX, mouseY, done;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

GLFT_Font fpsFont;

// **** Global Settings ****
// Thought: I think this should be expanded so that there is an
// actual game settings class
bool fullscreenenabled = false;

// Handle command line arguments, returns 1 if the game loop is
// not supposed to run.
static bool HandleCommandLineAurguments(int argc, char** argv) {
    bool shouldExit = 0;
    for(int i = 1 ; i < argc ; ++i) {
        std::string currentarg(argv[i]);
	if(currentarg == "-f" || currentarg == "--fullscreen") {
            fullscreenenabled = true;
            shouldExit = false;
        } else if(currentarg == "-h" || currentarg == "--help") {
            printf("Dawn-RPG Startup Parameters\n\n");
            printf(" -f, --fullscreen         Run Dawn in fullscreen mode\n");
            printf(" -h, --help               Show this help screen\n");
            shouldExit = true;
        }
    }
    return shouldExit;
}

void DrawScene() {
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

    if (Editor.enabled) {
        Editor.DrawEditor();
    } else {
        GUI.DrawInterface();
    }

    // note: we need to cast fpsFont.getHeight to int since otherwise the whole expression would be an unsigned int
    //       causing overflow and not drawing the font if it gets negative
    fpsFont.drawText(world_x, world_y+RES_Y - static_cast<int>(fpsFont.getHeight()), "FPS: %d     world_x: %d, world_y: %d      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps, world_x,world_y, character.x_pos, character.y_pos, mouseX, mouseY);

    message.DrawAll();
    message.DeleteDecayed();

    SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) {
    Uint8 *keys;

    done = HandleCommandLineAurguments(argc, argv);

    // Skip the init steps if true was set as a result of the command line parameters
    if(!done) {

        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) { // start up SDL
            printf("Unable to init SDL: %s\n", SDL_GetError());
            exit(1);
        }
        atexit(SDL_Quit);

        if(fullscreenenabled)
    	    screen=SDL_SetVideoMode(RES_X,RES_Y,RES_BPP,SDL_OPENGL | SDL_FULLSCREEN);
        else
            screen=SDL_SetVideoMode(RES_X,RES_Y,RES_BPP,SDL_OPENGL);

        if ( screen == NULL ) {
            printf("Unable to set resolution %dx%d video: %s\n", RES_X,RES_Y,SDL_GetError());
            exit(1);
        }

        glEnable( GL_TEXTURE_2D );

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glViewport( 0, 0, RES_X, RES_Y );

        glClear( GL_COLOR_BUFFER_BIT );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity(); // reset view to 0,0

        glOrtho(0.0f, RES_X, 0.0f, RES_Y, -1.0f, 1.0f);
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();  // reset view to 0,0

        glEnable( GL_BLEND ); // enable blending
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

        zone1.LoadZone("data/zone1");

        character.texture.texture.reserve(10);
        character.texture.LoadIMG("data/character/pacman/pacman_n.tga",1);
        character.texture.LoadIMG("data/character/pacman/pacman_ne.tga",2);
        character.texture.LoadIMG("data/character/pacman/pacman_e.tga",3);
        character.texture.LoadIMG("data/character/pacman/pacman_se.tga",4);
        character.texture.LoadIMG("data/character/pacman/pacman_s.tga",5);
        character.texture.LoadIMG("data/character/pacman/pacman_sw.tga",6);
        character.texture.LoadIMG("data/character/pacman/pacman_w.tga",7);
        character.texture.LoadIMG("data/character/pacman/pacman_nw.tga",8);
        character.Init((RES_X/2),(RES_Y/2));

        Editor.LoadTextures();
        GUI.LoadTextures();

        // initialize fonts where needed
        fpsFont.open("data/verdana.ttf", 12);
        message.initFonts();
        Editor.initFonts();

        SDL_ShowCursor(0);
    }

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



