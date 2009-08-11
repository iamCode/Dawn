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
#include "CSpell.h"

SDL_Surface *screen;
extern CZone zone1;
extern CMessage message;
Player character;

CEditor Editor;

CInterface GUI;

std::vector <CNPC*> NPC;

bool KP_damage, KP_heal, KP_magicMissile, KP_healOther, KP_interrupt, KP_select_next = false;

extern int RES_X, RES_Y, RES_BPP, world_x, world_y, mouseX, mouseY, done;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

GLFT_Font fpsFont;

// **** Global Settings ****
// Thought: I think this should be expanded so that there is an
// actual game settings class
bool fullscreenenabled = true;

std::vector<CSpell*> activeSpells;

void enqueueActiveSpell( CSpell *spell )
{
    activeSpells.push_back( spell );
}

void cleanupActiveSpells()
{
    size_t curActiveNr = 0;
    while ( curActiveNr < activeSpells.size() )
    {
        if ( activeSpells[ curActiveNr ]->isEffectComplete() )
        {
            delete activeSpells[ curActiveNr ];
            activeSpells.erase( activeSpells.begin() + curActiveNr );
        }
        else
        {
            ++curActiveNr;
        }
    }
}

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
    for (unsigned int x=0; x<NPC.size(); x++)
    {
        NPC[x]->Draw();
        if ( character.getTarget() == NPC[x] )
            fpsFont.drawText(NPC[x]->x_pos, NPC[x]->y_pos+100 - static_cast<int>(fpsFont.getHeight()), "%s, Health: %d",NPC[x]->getName().c_str(),NPC[x]->getCurrentHealth());
    }

    // draws the character's target's lifebar, if we have any target.
    if ( character.getTarget() != NULL )
        character.getTarget()->DrawLifebar();

    for ( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpells.size(); ++curActiveSpellNr )
    {
        if ( ! activeSpells[ curActiveSpellNr ]->isEffectComplete() )
        {
            activeSpells[ curActiveSpellNr ]->drawSpellEffect();
        }
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
        character.setMoveTexture( N, "data/character/pacman/pacman_n.tga" );
        character.setMoveTexture( NE, "data/character/pacman/pacman_ne.tga" );
        character.setMoveTexture( E, "data/character/pacman/pacman_e.tga" );
        character.setMoveTexture( SE, "data/character/pacman/pacman_se.tga" );
        character.setMoveTexture( S, "data/character/pacman/pacman_s.tga" );
        character.setMoveTexture( SW, "data/character/pacman/pacman_sw.tga" );
        character.setMoveTexture( W, "data/character/pacman/pacman_w.tga" );
        character.setMoveTexture( NW, "data/character/pacman/pacman_nw.tga" );
        character.setMoveTexture( STOP, "data/character/pacman/pacman_s.tga" );
        character.Init(RES_X/2,RES_Y/2);

        Editor.LoadTextures();
        GUI.LoadTextures();
        GUI.SetPlayer(&character);

        // initialize fonts where needed
        fpsFont.open("data/verdana.ttf", 12);
        message.initFonts();
        Editor.initFonts();
        GUI.initFonts();

        SpellCreation::initSpells();

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
                            character.setTarget( NULL );

                            for (unsigned int x=0; x<NPC.size(); x++) {
                                if ( NPC[x]->CheckMouseOver(mouseX+world_x,mouseY+world_y) )
                                {
                                    character.setTarget( NPC[x] );
                                }
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
                NPC[x]->giveMovePoints( ticksDiff );
                NPC[x]->Move();
                NPC[x]->Respawn();
                NPC[x]->Wander();
            }

            // making sure our target is still alive, if not well set our target to NULL.
            if ( character.getTarget() != NULL )
            {
                if ( !character.getTarget()->isAlive() )
                character.setTarget( NULL );
            }

            for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpells.size(); ++curActiveSpellNr )
            {
                activeSpells[ curActiveSpellNr ]->inEffect();
            }

            cleanupActiveSpells();

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

            if (keys[SDLK_TAB] && !KP_select_next)
            {
                KP_select_next = true;
                bool FoundNewTarget = false;
                std::vector <CNPC*> NPClist;
                // select next npc on screen
                for ( size_t curNPC = 0; curNPC < NPC.size(); ++curNPC )
                {
                    // if NPC is in on screen (might be changed to line of sight or something)
                    // this makes a list of all visible NPCs, easier to select next target this way.
                    if ( DrawingHelpers::isRectOnScreen( NPC[curNPC]->x_pos, 1, NPC[curNPC]->y_pos, 1 )
                         && NPC[curNPC]->isAlive() )
                    {
                        NPClist.push_back(NPC[curNPC]);
                    }
                }
                // selects next target in the list, if target = NULL, set target to first NPC on the visible list.
                for ( size_t curNPC = 0; curNPC < NPClist.size(); ++curNPC )
                {
                    if ( character.getTarget() == NULL)
                    {
                        character.setTarget( NPClist[0] );
                    }

                    if ( character.getTarget() == NPClist[curNPC] )
                    {
                        if ( curNPC+1 == NPClist.size() ) {
                            character.setTarget(NPClist[0]);
                        } else {
                            character.setTarget(NPClist[curNPC+1]);
                        }
                        FoundNewTarget = true;
                        break;
                    }
                }

                if ( !FoundNewTarget && NPClist.size() > 0)
                {
                    character.setTarget( NPClist[0] );
                }
            }

            if (!keys[SDLK_TAB])
            {
                KP_select_next = false;
            }

            if (keys[SDLK_1] && !KP_damage) {
                KP_damage = true;
                if ( character.getTarget() != NULL )
                {
                    CSpell *spell = SpellCreation::createSingleTargetSpellByName( "Lightning", &character, character.getTarget() );
                    character.CastSpell(spell);
                }
            }

            if (!keys[SDLK_1]) {
                KP_damage = false;
            }

            if (keys[SDLK_2] && !KP_heal) {
                KP_heal = true;
                CSpell *spell = SpellCreation::createSelfAffectingSpellByName( "Healing", &character );
                character.CastSpell( spell );
            }

            if (!keys[SDLK_2]) {
                KP_heal = false;
            }

            if (keys[SDLK_3] && !KP_magicMissile) {
                KP_magicMissile = true;
                if ( character.getTarget() != NULL )
                {
                    CSpell *spell = SpellCreation::createSingleTargetSpellByName( "Magic Missile", &character, character.getTarget() );
                    character.CastSpell(spell);
                }
            }

            if (!keys[SDLK_3]) {
                KP_magicMissile = false;
            }

            if (keys[SDLK_4] && !KP_healOther) {
                KP_healOther = true;
                if ( character.getTarget() != NULL )
                {
                    CSpell *spell = SpellCreation::createSingleTargetSpellByName( "Heal Other", &character, character.getTarget() );
                    character.CastSpell(spell);
                }
            }

            if (!keys[SDLK_4]) {
                KP_healOther = false;
            }

            if (keys[SDLK_5] && !KP_interrupt) {
                KP_interrupt = true;
                character.CastingInterrupted();
            }

            if (!keys[SDLK_5]) {
                KP_interrupt = false;
            }
        }
        DrawScene();
    }
  return 0;
}
