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

#include "ActionBar.h"
#include "CCharacter.h"
#include "Player.h"
#include "CDrawingHelpers.h"
#include "CAction.h"
#include "CSpell.h"

ActionBar::ActionBar( Player *player_ )
	:	player( player_ ),
        posX ( 300 ),
        posY ( 9 ),
        width ( 680 ),
        height ( 49 )
{
    shortcutFont = NULL;
    button.push_back( sButton(0, 0, 50, 50, "1", SDLK_1) );
    button.push_back( sButton(70, 0, 50, 50, "2", SDLK_2) );
    button.push_back( sButton(140, 0, 50, 50, "3", SDLK_3) );
    button.push_back( sButton(210, 0, 50, 50, "4", SDLK_4) );
    button.push_back( sButton(280, 0, 50, 50, "5", SDLK_5) );
    button.push_back( sButton(350, 0, 50, 50, "6", SDLK_6) );
    button.push_back( sButton(420, 0, 50, 50, "7", SDLK_7) );
    button.push_back( sButton(490, 0, 50, 50, "8", SDLK_8) );
    button.push_back( sButton(560, 0, 50, 50, "9", SDLK_9) );
    button.push_back( sButton(630, 0, 50, 50, "0", SDLK_0) );

    bindAction( &button[0], "Lightning" );
    bindAction( &button[1], "Healing" );
    bindAction( &button[2], "Heal Other" );
    bindAction( &button[3], "Magic Missile" );
}

ActionBar::~ActionBar()
{
	if ( shortcutFont != NULL ) {
		delete shortcutFont;
	}
}

void ActionBar::initFonts()
{
	shortcutFont = new GLFT_Font();
	shortcutFont->open("data/verdana.ttf", 9);
}

bool ActionBar::isMouseOver( int x, int y )
{
    if ( x > posX
    && x < posX + width
    && y > posY
    && y < posY + height )
    {
        return true;
    }
    return false;
}

void ActionBar::draw()
{

    // background at bottom of screen, black and nicely blended.
	DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
	                                  world_x, RES_X,
	                                  world_y, 80 );

	for ( size_t buttonId = 0; buttonId < 10; buttonId++ )
	{
	    shortcutFont->drawText( static_cast<float>( world_x ) + 300 + buttonId * 70 - 10,
                                static_cast<float>( world_y ) + 50, button[buttonId].number.c_str() );

	    glColor3f( 0.4f, 0.4f, 0.4f );
	    if ( player->getIsPreparing() && button[buttonId].action != NULL )
	    {
	        if ( player->getCurrentSpellActionName() == button[buttonId].action->getName() )
            {
                // current spell / action we're drawing is being cast. color it.
                glColor3f( 0.8f, 0.8f, 0.8f );
            }
	    }

	    DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
		                                  world_x+ 300 + buttonId * 70, 50,
		                                  world_y+ 8, 50 );

        glColor3f( 1.0f, 1.0f, 1.0f );
        if ( button[buttonId].action != NULL )
	    {
	        button[buttonId].action->draw( world_x + 300 + buttonId * 70 + 2, 46, world_y + 10, 46 );
	    }


	}
}

void ActionBar::clicked( int clickX, int clickY )
{
    int buttonId = getMouseOverButtonId( clickX, clickY );
    if ( buttonId >= 0 && button[buttonId].action != NULL )
    {
        CSpellActionBase *curAction = NULL;

        EffectType::EffectType effectType = button[buttonId].action->getEffectType();

        if ( effectType == EffectType::SingleTargetSpell
                 && player->getTarget() != NULL ) {
            curAction = button[buttonId].action->create( player->getTarget() );
        } else if ( effectType == EffectType::SelfAffectingSpell ) {
            curAction = button[buttonId].action->create( player);
        }

        if ( curAction != NULL ) {
            // TODO: This is a hack. just create a single type of action
            if ( dynamic_cast<CSpell*>( curAction ) != NULL ) {
                player->castSpell( dynamic_cast<CSpell*>( curAction ) );
            } else {
                player->executeAction( dynamic_cast<CAction*>( curAction ) );
            }
        }
    }
}

void ActionBar::handleKeys()
{
    Uint8 *keys = SDL_GetKeyState(NULL);

    for ( size_t buttonId = 0; buttonId < 10; buttonId++ ) {
        // TODO: use a conversion table here from quickslot nr to keycode
        if ( keys[ button[buttonId].key ] && ! button[buttonId].wasPressed ) {
            if ( button[buttonId].action != NULL ) {
                CSpellActionBase *curAction = NULL;

                EffectType::EffectType effectType = button[buttonId].action->getEffectType();

                if ( effectType == EffectType::SingleTargetSpell
                         && player->getTarget() != NULL ) {
                    curAction = button[buttonId].action->create( player->getTarget() );
                } else if ( effectType == EffectType::SelfAffectingSpell ) {
                    curAction = button[buttonId].action->create( player);
                }

                if ( curAction != NULL ) {
                    // TODO: This is a hack. just create a single type of action
                    if ( dynamic_cast<CSpell*>( curAction ) != NULL ) {
                        player->castSpell( dynamic_cast<CSpell*>( curAction ) );
                    } else {
                        player->executeAction( dynamic_cast<CAction*>( curAction ) );
                    }
                }
            }
        }

        if ( ! keys[ button[buttonId].key ] ) {
            button[buttonId].wasPressed = false;
        }
    }
}

int8_t ActionBar::getMouseOverButtonId( int x, int y )
{
    for ( size_t buttonIndex = 0; buttonIndex < button.size(); buttonIndex++ )
    {
        if ( x > button[buttonIndex].posX + posX
        && x < button[buttonIndex].posX + button[buttonIndex].width + posX
        && y > button[buttonIndex].posY + posY
        && y < button[buttonIndex].posY + button[buttonIndex].height + posY )
        {
            return buttonIndex;
        }
    }
    return -1;
}

void ActionBar::bindAction( sButton *button, std::string action )
{
    button->action = SpellCreation::createActionFactoryByName( action , player );
    button->tooltip = new spellTooltip( button->action );

    /** this could be added to game settings, making the player choose to
    display a full tooltip when hoovering spells in the actionbar.**/
    button->tooltip->enableSmallTooltip();
}

void ActionBar::unbindAction( sButton *button )
{
    button->action = NULL;
    delete button->tooltip;
}

void ActionBar::drawSpellTooltip( int x, int y )
{
    int buttonId = getMouseOverButtonId( x, y );
    if ( buttonId >= 0 && button[buttonId].tooltip != NULL )
    {
        button[buttonId].tooltip->draw( x, y );
    }
}

void ActionBar::loadTextures()
{
    textures.texture.reserve(2);
	textures.LoadIMG("data/interface/blended_bg.tga",0);
	textures.LoadIMG("data/border.tga",1);
}
