/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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
#include "TimeConverterHelper.h"
#include "CAction.h"
#include "CSpell.h"
#include <memory>

extern std::auto_ptr<Spellbook> spellbook;

ActionBar::ActionBar( Player *player_ )
	:	player( player_ ),
        posX ( 300 ),
        posY ( 9 ),
        width ( 680 ),
        height ( 49 ),
        spellQueue( NULL )
{
    shortcutFont = NULL;
    cooldownFont = NULL;
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
}

ActionBar::~ActionBar()
{
	if ( shortcutFont != NULL )
	{
		delete shortcutFont;
	}

	if ( cooldownFont != NULL )
	{
	    delete cooldownFont;
	}
}

void ActionBar::initFonts()
{
	shortcutFont = new GLFT_Font();
	shortcutFont->open("data/verdana.ttf", 9);

	cooldownFont = new GLFT_Font();
	cooldownFont->open("data/verdana.ttf", 11);
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
    bool drawCooldownText;
    std::string cooldownText;
    cooldownSpells = player->getCooldownSpells();

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

        drawCooldownText = false;

        if ( button[buttonId].action != NULL )
	    {
	        for (size_t curSpell = 0; curSpell < cooldownSpells.size(); curSpell++)
	        {
	            if ( cooldownSpells[curSpell].first->getName() == button[buttonId].action->getName() )
	            {
                    // make the spellicon darker if it's on cooldown.
                    glColor3f( 0.4f, 0.4f, 0.4f );
                    drawCooldownText = true;
                    cooldownText = TimeConverter::convertTime( cooldownSpells[curSpell].second, cooldownSpells[curSpell].first->getCooldown() );
	            }
            }

	        button[buttonId].action->drawSymbol( world_x + 300 + buttonId * 70 + 2, 46, world_y + 10, 46 );

            if ( drawCooldownText == true )
            {
                glColor3f( 1.0f, 0.0f, 0.0f );
                unsigned int xModifier = cooldownFont->calcStringWidth( cooldownText );
	            cooldownFont->drawText( static_cast<float>( world_x ) + 300 + buttonId * 70 + 6 + (static_cast<float>(50)-xModifier) / 2,
                                        static_cast<float>( world_y ) + 28, cooldownText.c_str() );
                glColor3f( 1.0f, 1.0f, 1.0f );
            }
	    }
	}
}

void ActionBar::clicked( int clickX, int clickY )
{
    int buttonId = getMouseOverButtonId( clickX, clickY );
    if ( buttonId >= 0 && button[buttonId].action != NULL )
    {
        spellQueue = &button[buttonId];
    }
}

void ActionBar::clicked( int clickX, int clickY, CSpellActionBase* floatingSpell )
{
    int buttonId = getMouseOverButtonId( clickX, clickY );
    if ( buttonId >= 0 )
    {
        if ( isButtonUsed( &button[buttonId] ) )
        {
            unbindAction( &button[buttonId] );
        }
        bindAction( &button[buttonId], floatingSpell );
    }
}

void ActionBar::handleKeys()
{
    Uint8 *keys = SDL_GetKeyState(NULL);

    for ( size_t buttonId = 0; buttonId < 10; buttonId++ ) {
        // TODO: use a conversion table here from quickslot nr to keycode
        if ( keys[ button[buttonId].key ] && ! button[buttonId].wasPressed ) {
            button[buttonId].wasPressed = true;
            if ( button[buttonId].action != NULL ) {
                CSpellActionBase *curAction = NULL;

                EffectType::EffectType effectType = button[buttonId].action->getEffectType();

                if ( effectType == EffectType::SingleTargetSpell
                         && player->getTarget() != NULL ) {
                    curAction = button[buttonId].action->cast( player, player->getTarget() );
                } else if ( effectType == EffectType::SelfAffectingSpell ) {
                    curAction = button[buttonId].action->cast( player, player );
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

void ActionBar::bindAction( sButton *button, CSpellActionBase* action )
{
    button->action = action;
    button->tooltip = new spellTooltip( button->action, player );

    /** this could be added to game settings, making the player choose to
    display a full tooltip when hoovering spells in the actionbar.**/
    button->tooltip->enableSmallTooltip();
}

void ActionBar::unbindAction( sButton *button )
{
    button->action = NULL;
    delete button->tooltip;
    button->tooltip = NULL;
}

bool ActionBar::isButtonUsed( sButton *button ) const
{
    if ( button->action == NULL )
    {
        return true;
    } else {
        return false;
    }
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

void ActionBar::executeSpellQueue()
{
    if ( spellQueue != NULL )
    {
        if ( spellQueue->action != NULL )
        {
            CSpellActionBase *curAction = NULL;

            EffectType::EffectType effectType = spellQueue->action->getEffectType();

            if ( effectType == EffectType::SingleTargetSpell
                     && player->getTarget() != NULL ) {
                curAction = spellQueue->action->cast( player, player->getTarget() );
            } else if ( effectType == EffectType::SelfAffectingSpell ) {
                curAction = spellQueue->action->cast( player, player );
            }

            if ( curAction != NULL ) {
                // TODO: This is a hack. just create a single type of action
                if ( dynamic_cast<CSpell*>( curAction ) != NULL ) {
                    player->castSpell( dynamic_cast<CSpell*>( curAction ) );
                } else {
                    player->executeAction( dynamic_cast<CAction*>( curAction ) );
                }
            }
            spellQueue = NULL;
        }
    }
}

void ActionBar::dragSpell()
{
    if ( spellQueue != NULL )
    {
        if ( spellQueue->action != NULL )
        {
            spellbook->setFloatingSpell( spellbook->getSpellSlotBySpell( spellQueue->action ) );
            unbindAction( spellQueue );
            spellQueue = NULL;
        }
    }
}
