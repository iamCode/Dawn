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

#include "CLuaFunctions.h"

SDL_Surface *screen;
extern CZone zone1;
extern CMessage message;
CCharacter character;

CEditor Editor;

CInterface GUI;

std::vector <CNPC*> NPC;

bool KP_damage, KP_heal, KP_interrupt;

extern int RES_X, RES_Y, RES_BPP, world_x, world_y, mouseX, mouseY, done;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

GLFT_Font fpsFont;

// **** Global Settings ****
// Thought: I think this should be expanded so that there is an
// actual game settings class
bool fullscreenenabled = true;

// Handle command line arguments, returns 1 if the game loop is
// not supposed to run.
static bool HandleCommandLineAurguments(int argc, char** argv) {
    bool shouldExit = 0;
    std::string executable(argv[0]);
#ifdef _WIN32
    freopen( "CON", "wt", stdout ); // Redirect stdout to the command line
#endif
    for(int i=1 ; i < argc ; ++i) {
        std::string currentarg(argv[i]);
	    if(currentarg == "-f" || currentarg == "--fullscreen") {
            fullscreenenabled = true;
            shouldExit = false;
        } else if(currentarg == "-w" || currentarg == "--window") {
            fullscreenenabled = false;
            shouldExit = false;
        } else if(currentarg == "-h" || currentarg == "--help") {
            std::cout << "Dawn-RPG Startup Parameters" <<
            std::endl << std::endl <<
            " -f, --fullscreen         Run Dawn in fullscreen mode" <<
            std::endl <<
            " -w, --window             Run Dawn inside a window" <<
            std::endl <<
            " -h, --help               Show this help screen" <<
            std::endl;
            shouldExit = true;
        } else {
            std::cout << std::endl <<"\"" << currentarg <<
            "\" is not a recognised option" << std::endl << std::endl <<
            "Please type \"" << executable <<
            " -h\" for all available options" << std::endl <<
            std::endl;
            shouldExit = true;
            break;
        }
    }
#ifdef _WIN32
    freopen( "stdout.txt", "wt", stdout ); // Redirect stdout back to the file
#endif
    return shouldExit;
}

namespace DawnInterface
{
    CZone* getCurrentZone()
    {
        return &zone1;
    }

    void addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn, CZone *zone )
    {
        CNPC *newMob = new CNPC(0, 0, 0, 0, 0, NULL);
        newMob->texture = NULL;
        newMob->lifebar = NULL;
        newMob->baseOnType( mobID );
        newMob->setSpawnInfo( x_pos, y_pos, respawn_rate, do_respawn, zone );
        NPC.push_back( newMob );
    }
}

void DrawScene() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslated(-world_x,-world_y,0);

    glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 50% Alpha ( NEW )

    zone1.DrawZone();

    character.Draw();
    for (unsigned int x=0; x<NPC.size(); x++) {
        NPC[x]->Draw();
    }

    // check our FPS and output it
    thisframe=SDL_GetTicks();     // Count the FPS
    ff++;
    if((thisframe-lastframe) > 1000) {
        fps=ff;
        ff=0;
        lastframe=thisframe;
    }

    if (Editor.isEnabled() ) {
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

int main(int argc, char* argv[]) {
    Uint8 *keys;

    done = HandleCommandLineAurguments(argc, argv);

    // Skip the init steps if true was set as a result of the command line parameters
    if(!done) {

        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) { // start up SDL
            std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }
        atexit(SDL_Quit);



        if(fullscreenenabled == false)
            screen=SDL_SetVideoMode(RES_X,RES_Y,RES_BPP,SDL_OPENGL);
        else
            screen=SDL_SetVideoMode(RES_X,RES_Y,RES_BPP,SDL_OPENGL | SDL_FULLSCREEN);

        if ( screen == NULL ) {
            std::cout << "Unable to set resolution " << RES_X <<
            "x" << RES_Y << " video:" << SDL_GetError();
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

        LuaFunctions::executeLuaFile("data/mobdata.all");

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
        GUI.SetPlayer(&character);

        // initialize fonts where needed
        fpsFont.open("data/verdana.ttf", 12);
        message.initFonts();
        Editor.initFonts();

        //SDL_ShowCursor(SDL_DISABLE);
    }

    Uint32 lastTicks = SDL_GetTicks();
    Uint32 curTicks  = lastTicks;
    Uint32 ticksDiff = 0;

    while(done == 0) {
        if (Editor.isEnabled()) {
            Editor.HandleKeys();

            lastTicks = SDL_GetTicks();
            curTicks  = lastTicks;
            ticksDiff = 0;
        } else {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)  { done = 1; }

                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
                    if (event.key.keysym.sym == SDLK_SPACE) { }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    switch (event.button.button) {
                        case 1:
                            for (unsigned int x=0; x<NPC.size(); x++) {
                                NPC[x]->CheckMouseOver(mouseX+world_x,mouseY+world_y);
                            }
                        break;
                    }
                }

                if (event.type == SDL_MOUSEMOTION) {
                    mouseX = event.motion.x;
                    mouseY = RES_Y - event.motion.y - 1;
                }
            }

            keys = SDL_GetKeyState(NULL);

            curTicks  = SDL_GetTicks();
            ticksDiff = curTicks - lastTicks;
            lastTicks = curTicks;

            character.giveMovePoints( ticksDiff );
            character.Move();

            for (unsigned int x=0; x<NPC.size(); x++) {
                NPC[x]->Respawn();
                NPC[x]->Wander();
            }

            if (keys[SDLK_k]) { // kill all NPCs in the zone. testing purposes.
                for (unsigned int x=0; x<NPC.size(); x++) {
                    NPC[x]->Die();
                }
            }

            if (keys[SDLK_l] && !Editor.KP_toggle_editor) {
                Editor.setEditZone( &zone1 );
                Editor.setEnabled( true );
                Editor.KP_toggle_editor = true;
            }

            if (!keys[SDLK_l]) {
                Editor.KP_toggle_editor = false;
            }

            if (keys[SDLK_1] && !KP_damage) {
                KP_damage = true;
                for (unsigned int x=0; x<NPC.size(); x++) {
                    if (NPC[x]->in_target == true) {
                        character.CastSpell(3.0f,NPC[x], -rand() % 60 - 30);
                    }
                }
            }

            if (!keys[SDLK_1]) {
                KP_damage = false;
            }

            if (keys[SDLK_2] && !KP_heal) {
                KP_heal = true;
                for (unsigned int x=0; x<NPC.size(); x++) {
                    if (NPC[x]->in_target == true) {
                        character.CastSpell(1.5f,NPC[x],rand() % 30);
                    }
                }
            }

            if (!keys[SDLK_2]) {
                KP_heal = false;
            }

            if (keys[SDLK_3] && !KP_interrupt) {
                KP_interrupt = true;
                character.CastingInterrupted();
            }

            if (!keys[SDLK_3]) {
                KP_interrupt = false;
            }
        }
        DrawScene();
    }
  return 0;
}
