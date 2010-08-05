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
#include "CSpell.h"
#include <memory>
#include <cassert>
#include "fontcache.h"

extern std::auto_ptr<Spellbook> spellbook;

ActionBar::ActionBar( Player *player_ )
	:	player( player_ ),
        posX ( 420 ),
        posY ( 9 ),
        width ( 680 ),
        height ( 49 ),
        spellQueue( NULL )
{
    shortcutFont = NULL;
    cooldownFont = NULL;
    button.push_back( sButton(0, 0, 50, 50, "1", SDLK_1) );
    button.push_back( sButton(60, 0, 50, 50, "2", SDLK_2) );
    button.push_back( sButton(120, 0, 50, 50, "3", SDLK_3) );
    button.push_back( sButton(180, 0, 50, 50, "4", SDLK_4) );
    button.push_back( sButton(240, 0, 50, 50, "5", SDLK_5) );
    button.push_back( sButton(300, 0, 50, 50, "6", SDLK_6) );
    button.push_back( sButton(360, 0, 50, 50, "7", SDLK_7) );
    button.push_back( sButton(420, 0, 50, 50, "8", SDLK_8) );
    button.push_back( sButton(480, 0, 50, 50, "9", SDLK_9) );
    button.push_back( sButton(540, 0, 50, 50, "0", SDLK_0) );
}

ActionBar::~ActionBar()
{
}

void ActionBar::initFonts()
{
	shortcutFont = FontCache::getFontFromCache( "data/verdana.ttf", 9 );
	cooldownFont = FontCache::getFontFromCache( "data/verdana.ttf", 11 );
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
	DrawingHelpers::mapTextureToRect( textures.texture[0],
	                                  world_x + posX - 20, RES_X - posX + 20,
	                                  world_y, 80 );

	for ( size_t buttonId = 0; buttonId < 10; buttonId++ )
	{
	    shortcutFont->drawText( static_cast<float>( world_x ) + 420 + buttonId * 60 - 8,
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

	    DrawingHelpers::mapTextureToRect( textures.texture[1],
		                                  world_x+ 420 + buttonId * 60, 50,
		                                  world_y+ 8, 50 );

        glColor3f( 1.0f, 1.0f, 1.0f );

        drawCooldownText = false;

        if ( button[buttonId].action != NULL )
	    {
	        /** make the spellicon darker if:
                    * not enough mana
                    * out of range
                    * it's on cooldown       **/
            bool isSpellUseable = true;

            if ( dynamic_cast<CAction*>( button[buttonId].action ) != NULL ) {
                if ( button[buttonId].action->getSpellCost() > player->getCurrentFatigue() ) {
                        isSpellUseable = false;
                }
            } else if ( dynamic_cast<CSpell*>( button[buttonId].action ) != NULL ) {
                if ( button[buttonId].action->getSpellCost() > player->getCurrentMana() ) {
                    isSpellUseable = false;
                }
            }

            if ( player->getTarget() != NULL ) {
                uint16_t distance = sqrt( pow( ( player->getXPos() + player->getWidth() / 2 ) - ( player->getTarget()->getXPos() + player->getTarget()->getWidth() / 2 ),2) + pow( ( player->getYPos() + player->getHeight() / 2 ) - ( player->getTarget()->getYPos() + player->getTarget()->getHeight() / 2 ),2) );
                if ( button[buttonId].action->isInRange( distance ) == false ) {
                    isSpellUseable = false;
                }
            }

	        for (size_t curSpell = 0; curSpell < cooldownSpells.size(); curSpell++)
	        {
	            if ( cooldownSpells[curSpell].first->getName() == button[buttonId].action->getName() )
	            {
                    isSpellUseable = false;
                    drawCooldownText = true;
                    cooldownText = TimeConverter::convertTime( cooldownSpells[curSpell].second, cooldownSpells[curSpell].first->getCooldown() );
	            }
            }

            if ( isSpellUseable == false ) {
                glColor3f( 0.4f, 0.4f, 0.4f );
            }

	        button[buttonId].action->drawSymbol( world_x + 420 + buttonId * 60 + 2, 46, world_y + 10, 46 );

            if ( drawCooldownText == true )
            {
                glColor3f( 1.0f, 0.0f, 0.0f );
                unsigned int xModifier = cooldownFont->calcStringWidth( cooldownText );
	            cooldownFont->drawText( static_cast<float>( world_x ) + 420 + buttonId * 60 + 6 + (static_cast<float>(50)-xModifier) / 2,
                                        static_cast<float>( world_y ) + 28, cooldownText.c_str() );
            }
            glColor3f( 1.0f, 1.0f, 1.0f );
	    }
	}
}

void ActionBar::clicked( int clickX, int clickY )
{
    int buttonId = getMouseOverButtonId( clickX, clickY );
    if ( buttonId >= 0 )
    {
        // we clicked a button which has an action and has no floating spell on the mouse (we're launching an action from the actionbar)
        if ( button[buttonId].action != NULL && !spellbook->hasFloatingSpell() )
        {
            spellQueue = &button[buttonId];
        }

        // check to see if we're holding a floating spell on the mouse. if we do, we want to place it in the actionbar slot...
        if ( spellbook->hasFloatingSpell() )
        {

            if ( isButtonUsed( &button[buttonId] ) )
            {
                unbindAction( &button[buttonId] );
            }
            bindAction( &button[buttonId], spellbook->getFloatingSpell()->action );
        }
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
                    player->castSpell( dynamic_cast<CSpellActionBase*>( curAction ) );
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
        return false;
    } else {
        return true;
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
    textures.texture.resize(2);
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
                player->castSpell( dynamic_cast<CSpellActionBase*>( curAction ) );
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

std::string ActionBar::getLuaSaveText()
{
	std::ostringstream oss;
	oss << "-- action bar" << std::endl;
	for ( size_t curButtonNr=0; curButtonNr<button.size(); ++curButtonNr ) {
		if ( isButtonUsed( &button[ curButtonNr ] ) ) {
			oss << "DawnInterface.restoreActionBar( " << curButtonNr << ", "
			            << "spellDatabase[ \"" << button[ curButtonNr ].action->getID() << "\" ] );" << std::endl;
		}
	}
	return oss.str();
}

void ActionBar::bindActionToButtonNr( int buttonNr, CSpellActionBase *action )
{
	assert( ! isButtonUsed( &button[ buttonNr ] ) );
	bindAction( &button[ buttonNr ], action );
}

void ActionBar::clear()
{
	for ( size_t curButtonNr=0; curButtonNr<button.size(); ++curButtonNr ) {
		if ( isButtonUsed( &button[ curButtonNr ] ) ) {
			unbindAction( &button[ curButtonNr ] );
		}
	}
}

extern std::auto_ptr<ActionBar> actionBar;

namespace DawnInterface
{
	std::string getActionbarSaveText()
	{
		return actionBar->getLuaSaveText();
	}

	void restoreActionBar( int buttonNr, CSpellActionBase *action )
	{
		actionBar->bindActionToButtonNr( buttonNr, action );
	}
}

