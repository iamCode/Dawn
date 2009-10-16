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
#include "CAction.h"
#include "debug.h"
#include "CharacterInfoScreen.h"
#include "item.h"
#include <memory>

/* Global settings now reside in the
   dawn_configuration namespace, variables
   are added to this across multiple files.
   current headers adding to it:
   debug.h
 */
namespace dawn_configuration {
	bool fullscreenenabled = true;
	int screenWidth = 1024;
	int screenHeight = 768;
	int bpp = 32;
}
// FIXME: This is a temp hack until the 
// 	objects dont need those variables.
//	david: I'll have this sorted pretty
//	quick.
int RES_X = dawn_configuration::screenWidth;
int RES_Y = dawn_configuration::screenHeight;

SDL_Surface *screen;
extern CZone zone1;
extern CMessage message;
Player character;
cameraFocusHandler focus(dawn_configuration::screenWidth, dawn_configuration::screenHeight);

CEditor Editor;

CInterface GUI;

std::vector <CNPC*> NPC;
std::vector<CActionFactory*> quickSlots;
std::vector<Item*> groundItems;
std::vector<std::pair<int,int> > groundPositions;

bool KP_damage, KP_heal, KP_magicMissile, KP_healOther, KP_interrupt, KP_select_next = false, KP_attack = false;
bool KP_toggle_showCharacterInfo = false;
bool KP_toggle_showInventory = false;

extern int world_x, world_y, mouseX, mouseY;

float lastframe,thisframe;           // FPS Stuff
int ff, fps;                         // FPS Stuff

std::auto_ptr<GLFT_Font> fpsFont;
std::auto_ptr<CharacterInfoScreen> characterInfoScreen;
std::auto_ptr<InventoryScreen> inventoryScreen;

std::vector<CSpellActionBase*> activeSpellActions;

void enqueueActiveSpellAction( CSpellActionBase *spellaction )
{
	activeSpellActions.push_back( spellaction );
}

void cleanupActiveSpellActions()
{
	size_t curActiveNr = 0;
	while ( curActiveNr < activeSpellActions.size() ) {
		if ( activeSpellActions[ curActiveNr ]->isEffectComplete() ) {
			delete activeSpellActions[ curActiveNr ];
			activeSpellActions.erase( activeSpellActions.begin() + curActiveNr );
		} else {
			++curActiveNr;
		}
	}
}

static bool HandleCommandLineAurguments(int argc, char** argv)
{
	bool run_game = true;
	std::string executable(argv[0]);
#ifdef _WIN32
	freopen( "CON", "wt", stdout ); // Redirect stdout to the command line
#endif
	for (int i=1 ; i < argc ; ++i) {
		std::string currentarg(argv[i]);
		if (currentarg == "-f" || currentarg == "--fullscreen") {
			dawn_configuration::fullscreenenabled = true;
			run_game = true;
		} else if (currentarg == "-w" || currentarg == "--window") {
			dawn_configuration::fullscreenenabled = false;
			run_game = true;
		} else if (currentarg == "-h" || currentarg == "--help") {
			std::cout << "Dawn-RPG Startup Parameters" <<
			          std::endl << std::endl <<
			          " -f, --fullscreen         Run Dawn in fullscreen mode" <<
			          std::endl <<
			          " -w, --window             Run Dawn inside a window" <<
			          std::endl <<
			          " -h, --help               Show this help screen" <<
			          std::endl;
			run_game = false;
		} else {
			std::cout << std::endl <<"\"" << currentarg <<
			          "\" is not a recognised option" << std::endl << std::endl <<
			          "Please type \"" << executable <<
			          " -h\" for all available options" << std::endl <<
			          std::endl;
			run_game = false;
			break;
		}
	}
#ifdef _WIN32
	freopen( "stdout.txt", "wt", stdout ); // Redirect stdout back to the file
#endif
	return run_game;
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
		newMob->setActiveGUI( &GUI );
		NPC.push_back( newMob );
	}
}

void DrawScene()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslated(-focus.getX(), -focus.getY(),0);

	glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 50% Alpha ( NEW )

	zone1.DrawZone();
	
	// draw items on the ground
	for ( size_t curItemNr=0; curItemNr<groundItems.size(); ++curItemNr ) {
		Item *curItem = groundItems[ curItemNr ];
		int posX = groundPositions[ curItemNr ].first;
		int posY = groundPositions[ curItemNr ].second;
		
		DrawingHelpers::mapTextureToRect( curItem->getSymbolTexture()->texture[0].texture,
		                                  posX,
		                                  curItem->getSizeX() * 32,
		                                  posY,
		                                  curItem->getSizeY() * 32 );
	}
	
	character.Draw();
	for (unsigned int x=0; x<NPC.size(); x++) {
		NPC[x]->Draw();
		if ( character.getTarget() == NPC[x] )
			fpsFont->drawText(NPC[x]->x_pos, NPC[x]->y_pos+100 - static_cast<int>(fpsFont->getHeight()), "%s, Health: %d",NPC[x]->getName().c_str(),NPC[x]->getCurrentHealth());
	}

	// draws the character's target's lifebar, if we have any target.
	if (character.getTarget())
		character.getTarget()->DrawLifebar();

	for ( size_t curActiveSpellNr = 0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
		if ( ! activeSpellActions[ curActiveSpellNr ]->isEffectComplete() ) {
			activeSpellActions[ curActiveSpellNr ]->drawEffect();
		}
	}

	// check our FPS and output it
	thisframe=SDL_GetTicks();     // Count the FPS
	ff++;
	if ((thisframe-lastframe) > 1000) {
		fps=ff;
		ff=0;
		lastframe=thisframe;
	}

	/* FIXME, TEMPORARY HACK: this is a quick fix, world_* should be
	 * removed once Editor and GUI don't need them */
	world_x = focus.getX();
	world_y = focus.getY();

	if (Editor.isEnabled() ) {
		Editor.DrawEditor();
	} else {
		GUI.DrawInterface();
	}

	if ( characterInfoScreen->isVisible() ) {
		characterInfoScreen->drawScreen();
	}

	if ( inventoryScreen->isVisible() ) {
	    inventoryScreen->draw();
	}
	if ( inventoryScreen->hasFloatingSelection() ) {
	    inventoryScreen->drawItemPlacement( mouseX, mouseY );
		inventoryScreen->drawFloatingSelection( world_x + mouseX, world_y + mouseY );
	}

	// note: we need to cast fpsFont.getHeight to int since otherwise the whole expression would be an unsigned int
	//       causing overflow and not drawing the font if it gets negative

	// I've removed this text for now, just for a cleaner look. Enable it if you need some info while coding. /Arnestig
	// fpsFont->drawText(focus.getX(), focus.getY()+RES_Y - static_cast<int>(fpsFont->getHeight()), "FPS: %d     world_x: %2.2f, world_y: %2.2f      Xpos: %d, Ypos: %d      MouseX: %d, MouseY: %d",fps,focus.getX(),focus.getY(), character.x_pos, character.y_pos, mouseX, mouseY);
	// Only FPS
	//fpsFont->drawText(focus.getX()+RES_X-100, focus.getY()+RES_Y - static_cast<int>(fpsFont->getHeight()), "FPS: %d",fps);

	message.DrawAll();
	message.DeleteDecayed();

	SDL_GL_SwapBuffers();
}

bool dawn_init(int argc, char** argv)
{		
		if(!HandleCommandLineAurguments(argc, argv))
			return false;
		
		dawn_debug_info("Initializing...");
		dawn_debug_info("Checking if the game data exists");
		
		if(!utils::file_exists("data/mobdata.all"))
			dawn_debug_fatal("The LUA script \"mobdata.all\", " 
				"Could not be found");
		if(!utils::file_exists("data/verdana.ttf"))
			dawn_debug_fatal("Font  \"verdana.ttf\", " 
				"Could not be found");

		if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
			dawn_debug_fatal("Unable to init SDL: %s", SDL_GetError());

		atexit(SDL_Quit);

		if (dawn_configuration::fullscreenenabled)
			screen = SDL_SetVideoMode(dawn_configuration::screenWidth, 
				dawn_configuration::screenHeight, dawn_configuration::bpp, 
				SDL_OPENGL | SDL_FULLSCREEN);
		else
			screen = SDL_SetVideoMode(dawn_configuration::screenWidth, 
				dawn_configuration::screenHeight, dawn_configuration::bpp, SDL_OPENGL);

		if ( !screen )
			dawn_debug_fatal("Unable to set resolution");
		
		glEnable( GL_TEXTURE_2D );

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glViewport( 0, 0, dawn_configuration::screenWidth, dawn_configuration::screenHeight );

		glClear( GL_COLOR_BUFFER_BIT );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity(); // reset view to 0,0

		glOrtho(0.0f, dawn_configuration::screenWidth, 0.0f, dawn_configuration::screenHeight, -1.0f, 1.0f);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  // reset view to 0,0

		glEnable( GL_BLEND ); // enable blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

		dawn_debug_info("Loading the game data files and objects");
		
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
		character.Init(dawn_configuration::screenWidth/2,dawn_configuration::screenHeight/2);
		character.setActiveGUI( &GUI );
		character.setMaxHealth(400);
		character.setMaxMana(250);
		character.setStrength(40);

		Editor.LoadTextures();
		GUI.LoadTextures();
		GUI.SetPlayer(&character);
		characterInfoScreen = std::auto_ptr<CharacterInfoScreen>( new CharacterInfoScreen( &character ) );
		characterInfoScreen->LoadTextures();
		inventoryScreen = std::auto_ptr<InventoryScreen>( new InventoryScreen( &character ) );
		inventoryScreen->LoadTextures();

		// initialize fonts where needed
		fpsFont = std::auto_ptr<GLFT_Font>(new GLFT_Font("data/verdana.ttf", 12));
		message.initFonts();
		Editor.initFonts();
		GUI.initFonts();
		characterInfoScreen->initFonts();

		SpellCreation::initSpells();
		ActionCreation::initActions();

		return true;
}

void initQuickSlotBar( const int nrOfQuickSlots, std::vector<CActionFactory*> &quickSlots, std::vector<bool> &wasPressed )
{
	// initialize quick slot bar.
	// this should be done dynamically in the future as set by the player
	quickSlots.reserve( nrOfQuickSlots ); // one for each key [0-9], + Space (last)
	wasPressed.reserve( nrOfQuickSlots );

	for ( size_t curQuickSlotNr = 0; curQuickSlotNr < nrOfQuickSlots; ++curQuickSlotNr ) {
		quickSlots[ curQuickSlotNr ] = NULL;
		wasPressed[ curQuickSlotNr ] = false;
	}
	quickSlots[1] = SpellCreation::createActionFactoryByName( "Lightning", &character );
	quickSlots[2] = SpellCreation::createActionFactoryByName( "Healing", &character );
	quickSlots[3] = SpellCreation::createActionFactoryByName( "Heal Other", &character );
	quickSlots[4] = SpellCreation::createActionFactoryByName( "Magic Missile", &character );	
}

void initializePlayerDebugInventory()
{
	Inventory *playerInventory = character.getInventory();
	Item *shield = new Item("shield", 2, 2, "data/items/shield.tga", EquipPosition::OFF_HAND);
	Item *sword =  new Item("sword", 1, 3, "data/items/sword.tga", EquipPosition::MAIN_HAND);
	playerInventory->insertItem( shield );
	playerInventory->insertItem( sword );
}

void game_loop()
{

	initializePlayerDebugInventory();
	// TODO: Break this down into subroutines

	Uint32 lastTicks = SDL_GetTicks();
	Uint32 curTicks  = lastTicks;
	Uint32 ticksDiff = 0;
	Uint8 *keys;
	bool done = false;

	std::vector<bool> wasPressed;
	const int nrOfQuickSlots = 11;
	initQuickSlotBar( nrOfQuickSlots, quickSlots, wasPressed );

	focus.setFocus(&character);

	while (!done) {

		if (Editor.isEnabled()) {
			Editor.HandleKeys();

			lastTicks = SDL_GetTicks();
			curTicks  = lastTicks;
			ticksDiff = 0;
		} else {
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)  {
					done = true;
				}

				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						done = true;
					}
					if (event.key.keysym.sym == SDLK_SPACE) { }
				}

				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if ( ( inventoryScreen->isVisible() 
					       && inventoryScreen->isOnThisScreen( mouseX, mouseY ) )
					     || inventoryScreen->hasFloatingSelection() ) {
						inventoryScreen->clicked( mouseX, mouseY );
					} else {
						switch (event.button.button) {
							case 1:
								// search for new target
								bool foundSomething = false;

								for (unsigned int x=0; x<NPC.size(); x++) {
									if ( NPC[x]->CheckMouseOver(mouseX+world_x,mouseY+world_y) ) {
										character.setTarget( NPC[x] );
										foundSomething = true;
										break;
									}
								}
								
								if ( !foundSomething ) {
									// search for items
									for ( size_t curItemNr=0; curItemNr<groundItems.size(); ++curItemNr ) {
										Item *curItem = groundItems[ curItemNr ];
										int posX = groundPositions[ curItemNr ].first;
										int posY = groundPositions[ curItemNr ].second;

										int worldMouseX = world_x + mouseX;
										int worldMouseY = world_y + mouseY;
										if ( worldMouseX >= posX
										     && worldMouseX <= posX + curItem->getSizeX() * 32
										     && worldMouseY >= posY
										     && worldMouseY <= posY + curItem->getSizeY() * 32 ) {
											foundSomething = true;
											if ( inventoryScreen->isVisible() ) {
												inventoryScreen->selectFloating( new InventoryItem( curItem, 0, 0 ) );
												groundItems[ curItemNr ] = groundItems[ groundItems.size() - 1 ];
												groundItems.resize( groundItems.size() - 1 );
												groundPositions[ curItemNr ] = groundPositions[ groundPositions.size() - 1 ];
												groundPositions.resize( groundPositions.size() - 1 );
											} else {
												bool inserted = character.getInventory()->insertItem( curItem );
												if ( inserted ) {
													groundItems[ curItemNr ] = groundItems[ groundItems.size() - 1 ];
													groundItems.resize( groundItems.size() - 1 );
													groundPositions[ curItemNr ] = groundPositions[ groundPositions.size() - 1 ];
													groundPositions.resize( groundPositions.size() - 1 );
												}
											}
											break;
										}
									}
								}
							break;
						}
					}
				}

				if (event.type == SDL_MOUSEMOTION) {
					mouseX = event.motion.x;
					mouseY = dawn_configuration::screenHeight - event.motion.y - 1;
				}
			}

			keys = SDL_GetKeyState(NULL);

			curTicks  = SDL_GetTicks();
			ticksDiff = curTicks - lastTicks;
			lastTicks = curTicks;

			character.giveMovePoints( ticksDiff );
			character.Move();
			character.regenerateLifeMana( ticksDiff );


			for (unsigned int x=0; x<NPC.size(); x++) {
				if ( NPC[x]->isAlive() ) {
					NPC[x]->giveMovePoints( ticksDiff );
					NPC[x]->Move();
				}
				NPC[x]->Respawn();
				NPC[x]->Wander();
			}

			// making sure our target is still alive, if not well set our target to NULL.
			if (character.getTarget()) {
				if ( !character.getTarget()->isAlive() )
					character.setTarget(0);
			}

			for (size_t curActiveSpellNr=0; curActiveSpellNr < activeSpellActions.size(); ++curActiveSpellNr ) {
				activeSpellActions[ curActiveSpellNr ]->inEffect();
			}

			cleanupActiveSpellActions();

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

			if (keys[SDLK_TAB] && !KP_select_next) {
				KP_select_next = true;
				bool FoundNewTarget = false;
				std::vector <CNPC*> NPClist;
				// select next npc on screen
				for ( size_t curNPC = 0; curNPC < NPC.size(); ++curNPC ) {
					// if NPC is in on screen (might be changed to line of sight or something)
					// this makes a list of all visible NPCs, easier to select next target this way.
					if ( DrawingHelpers::isRectOnScreen( NPC[curNPC]->x_pos, 1, NPC[curNPC]->y_pos, 1 )
					        && NPC[curNPC]->isAlive() ) {
						NPClist.push_back(NPC[curNPC]);
					}
				}
				// selects next target in the list, if target = NULL, set target to first NPC on the visible list.
				for ( size_t curNPC = 0; curNPC < NPClist.size(); ++curNPC ) {
					if (!character.getTarget()) {
						character.setTarget(NPClist[0]);
					}

					if ( character.getTarget() == NPClist[curNPC] ) {
						if ( curNPC+1 == NPClist.size() ) {
							character.setTarget(NPClist[0]);
						} else {
							character.setTarget(NPClist[curNPC+1]);
						}
						FoundNewTarget = true;
						break;
					}
				}

				if ( !FoundNewTarget && NPClist.size() > 0) {
					character.setTarget(NPClist[0]);
				}
			}

			if (!keys[SDLK_TAB]) {
				KP_select_next = false;
			}

			if ( keys[SDLK_c] && !KP_toggle_showCharacterInfo ) {
				KP_toggle_showCharacterInfo = true;
				characterInfoScreen->setVisible( ! characterInfoScreen->isVisible() );
			}

			if ( !keys[SDLK_c] ) {
				KP_toggle_showCharacterInfo = false;
			}

			if ( keys[SDLK_i] && !KP_toggle_showInventory ) {
			    KP_toggle_showInventory = true;
			    inventoryScreen->setVisible( !inventoryScreen->isVisible() );
			}

			if ( !keys[SDLK_i] ) {
			    KP_toggle_showInventory = false;
			}

			for ( size_t curQuickSlotIndex = 0; curQuickSlotIndex < nrOfQuickSlots; ++ curQuickSlotIndex ) {
				// TODO: use a conversion table here from quickslot nr to keycode
				if ( keys[ SDLK_0 + curQuickSlotIndex ] && ! wasPressed[ curQuickSlotIndex ] ) {
					if ( quickSlots[ curQuickSlotIndex ] != NULL ) {
						CSpellActionBase *curAction = NULL;

						EffectType::EffectType effectType = quickSlots[ curQuickSlotIndex ]->getEffectType();

						if ( effectType == EffectType::SingleTargetSpell
						         && character.getTarget() != NULL ) {
							curAction = quickSlots[ curQuickSlotIndex ]->create( character.getTarget() );
						} else if ( effectType == EffectType::SelfAffectingSpell ) {
							curAction = quickSlots[ curQuickSlotIndex ]->create( &character );
						}

						if ( curAction != NULL ) {
							// TODO: This is a hack. just create a single type of action
							if ( dynamic_cast<CSpell*>( curAction ) != NULL ) {
								character.castSpell( dynamic_cast<CSpell*>( curAction ) );
							} else {
								character.executeAction( dynamic_cast<CAction*>( curAction ) );
							}
						}
					}
				}
				if ( ! keys[ SDLK_0 + curQuickSlotIndex ] ) {
					wasPressed[ curQuickSlotIndex ] = false;
				}
			}

			if (keys[SDLK_5] && !KP_interrupt) {
				KP_interrupt = true;
				character.CastingInterrupted();
			}

			if (!keys[SDLK_5]) {
				KP_interrupt = false;
			}

			if (keys[SDLK_SPACE] && !KP_attack) {
				KP_attack = true;
				if ( character.getTarget() != NULL ) {
					CAction *action = ActionCreation::createAttackAction( &character, character.getTarget() );
					character.executeAction(action);
				}
			}

			if (!keys[SDLK_SPACE]) {
				KP_attack = false;
			}
		}
		DrawScene();
		focus.updateFocus();
	}
}

int main(int argc, char* argv[])
{
	dawn_configuration::logfile = "dawn-log.log";
	dawn_configuration::debug_stdout = true;
	dawn_configuration::debug_fileout = true;
	dawn_configuration::show_info_messages = true;
	dawn_configuration::show_warn_messages = true;

	if(dawn_init(argc, argv))
		game_loop();

	return 0;
}
