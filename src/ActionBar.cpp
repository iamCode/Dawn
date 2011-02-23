/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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
#include "globals.h"

extern std::auto_ptr<Spellbook> spellbook;
extern int mouseX, mouseY, world_x, world_y;

ActionBar::ActionBar( Player *player_ )
	:	player( player_ ),
        posY ( 13 ),
        width ( 630 ),
        height ( 49 ),
        spellQueue( NULL ),
        preparingAoESpell( false ),
        cursorRadius( 0 )
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
	posX = Configuration::screenWidth-width+20;
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
	DrawingHelpers::mapTextureToRect( textures.getTexture(0),
	                                  world_x + Configuration::screenWidth-width, width,
	                                  world_y, 80 );

	for ( size_t buttonId = 0; buttonId < 10; buttonId++ )
	{
	    shortcutFont->drawText( world_x + Configuration::screenWidth-width+20 + buttonId * 60 - 8,
                                world_y + 54, button[buttonId].number.c_str() );

	    glColor3f( 0.4f, 0.4f, 0.4f );
	    if ( player->getIsPreparing() && button[buttonId].action != NULL )
	    {
	        if ( player->getCurrentSpellActionName() == button[buttonId].action->getName() )
            {
                // current spell / action we're drawing is being cast. color it.

                glColor3f( 0.8f, 0.8f, 0.8f );
            }
	    }

	    DrawingHelpers::mapTextureToRect( textures.getTexture(1),
		                                  world_x+ Configuration::screenWidth-width+20 + buttonId * 60, 50,
		                                  world_y+ 12, 50 );

        glColor3f( 1.0f, 1.0f, 1.0f );

        drawCooldownText = false;

        if ( button[buttonId].action != NULL )
	    {
	        /** make the spellicon darker if:
                    * not enough mana
                    * out of range
                    * it's on cooldown
                    * we are stunned
                    * spell has a weapon requirement not met
                    * the player is casting an AoE spell **/
            bool useableSpell = isSpellUseable( button[ buttonId ].action );

            // is the spell on cooldown?
            for (size_t curSpell = 0; curSpell < cooldownSpells.size(); curSpell++)
            {
                if ( cooldownSpells[curSpell].first->getName() == button[buttonId].action->getName() )
                {
                    useableSpell = false;
                    drawCooldownText = true;
                    cooldownText = TimeConverter::convertTime( cooldownSpells[curSpell].second, cooldownSpells[curSpell].first->getCooldown() );
                }
            }

            if ( useableSpell == false ) {
                glColor3f( 0.4f, 0.4f, 0.4f );
            }

	        button[buttonId].action->drawSymbol( world_x + Configuration::screenWidth-width+20 + buttonId * 60 + 2, 46, world_y + 14, 46 );

            if ( drawCooldownText == true )
            {
                glColor3f( 1.0f, 0.0f, 0.0f );
                unsigned int xModifier = cooldownFont->calcStringWidth( cooldownText );
	            cooldownFont->drawText( world_x + Configuration::screenWidth-width+20 + buttonId * 60 + 6 + (static_cast<float>(50)-xModifier) / 2,
                                        world_y + 32, cooldownText.c_str() );
            }
            glColor3f( 1.0f, 1.0f, 1.0f );
	    }
	}

	// draw the cursor if it's supposed to be drawn
	if( isPreparingAoESpell() == true )
	{
		DrawingHelpers::mapTextureToRect(textures.getTexture(2), mouseX+world_x-cursorRadius, cursorRadius*2, mouseY+world_y-cursorRadius, cursorRadius*2);
	}
}

bool ActionBar::isSpellUseable( CSpellActionBase *action )
{
    // do we have enough fatigue to cast?
    if ( dynamic_cast<CAction*>( action ) != NULL ) {
        if ( action->getSpellCost() > player->getCurrentFatigue() ) {
                return false;
        }

    // do we have enough mana to cast?
    } else if ( dynamic_cast<CSpell*>( action ) != NULL ) {
        if ( action->getSpellCost() > player->getCurrentMana() ) {
            return false;
        }
    }
    // do we have a target? if so, are we in range? (doesn't check for selfaffectign spells)
    if ( player->getTarget() != NULL && action->getEffectType() != EffectType::SelfAffectingSpell ) {
        uint16_t distance = sqrt( pow( ( player->getXPos() + player->getWidth() / 2 ) - ( player->getTarget()->getXPos() + player->getTarget()->getWidth() / 2 ),2) + pow( ( player->getYPos() + player->getHeight() / 2 ) - ( player->getTarget()->getYPos() + player->getTarget()->getHeight() / 2 ),2) );
        if ( action->isInRange( distance ) == false ) {
            return false;
        }
    }

    // are we stunned?
    if ( player->isStunned() == true || player->isFeared() == true || player->isMesmerized() == true || player->isCharmed() == true ) {
        return false;
    }

    // does the spell / action require a weapon of any sort?
    if ( action->getRequiredWeapons() != 0 ) {
        if ( ( action->getRequiredWeapons() & ( player->getInventory()->getWeaponTypeBySlot( ItemSlot::MAIN_HAND ) | player->getInventory()->getWeaponTypeBySlot( ItemSlot::OFF_HAND ) ) ) == 0 ) {
            return false;
        }
    }
    return true;
}

void ActionBar::setSpellQueue( sButton &button, bool actionReadyToCast )
{
    spellQueue = &button;
    spellQueue->actionReadyToCast = actionReadyToCast;
}

bool ActionBar::isPreparingAoESpell() const
{
    return preparingAoESpell;
}

void ActionBar::stopCastingAoE()
{
    if ( isPreparingAoESpell() == true ) {
        spellQueue = NULL;
        preparingAoESpell = false;
    }
}

void ActionBar::clicked( int clickX, int clickY )
{
    // if the right mouse button is pressed you exit "disabled" mode and remove the cursor
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))
	{
		stopCastingAoE();
	}

    // did we click outside of the actionbar and have prepared an aoe spell?
	if ( isPreparingAoESpell() == true ) { // we've prepared a spellqueue before. so now it's time to let it finish
        preparingAoESpell = false;
        spellQueue->actionReadyToCast = true;
        spellQueue->areaOfEffectOnSpecificLocation = true;
        spellQueue->actionSpecificXPos = clickX;
        spellQueue->actionSpecificYPos = clickY;
    } else {
        int buttonId = getMouseOverButtonId( clickX, clickY );
        if ( buttonId >= 0 )
        {
            // we clicked a button which has an action and has no floating spell on the mouse (we're launching an action from the actionbar)
            if ( button[buttonId].action != NULL && !spellbook->hasFloatingSpell() )
            {
                if ( button[ buttonId ].action->getEffectType() == EffectType::AreaTargetSpell && player->getTarget() == NULL && isSpellUseable( button[ buttonId ].action ) == true ) { // AoE spell with specific position
                    setSpellQueue( button[buttonId], false );
                    preparingAoESpell = true;
                    cursorRadius = button[buttonId].action->getRadius();
                } else { // "regular" spell
                    setSpellQueue( button[buttonId] );
                }
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

						if ( effectType == EffectType::SingleTargetSpell && player->getTarget() != NULL )
						{
							curAction = button[buttonId].action->cast( player, player->getTarget() );
						}
						else if ( effectType == EffectType::SelfAffectingSpell )
						{
							curAction = button[buttonId].action->cast( player, player );
						}
						else if ( effectType == EffectType::AreaTargetSpell ) // AoE spell
						{
							if ( player->getTarget() != NULL ) // is there a target?
							{
								curAction = button[buttonId].action->cast( player, player->getTarget() );
							} else {
							    setSpellQueue( button[ buttonId ], false );
							    preparingAoESpell = true;
							    cursorRadius = button[buttonId].action->getRadius();
							}
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
    if ( buttonId >= 0 && button[buttonId].tooltip != NULL && isPreparingAoESpell() == false )
    {
        button[buttonId].tooltip->draw( x, y );
    }
}

void ActionBar::loadTextures()
{
		textures.LoadIMG("data/interface/blended_bg.tga",0);
		textures.LoadIMG("data/border.tga",1);
		textures.LoadIMG("data/cursors/circle1_enabled.tga",2);
		textures.LoadIMG("data/cursors/circle1_disabled.tga",3);
}

void ActionBar::executeSpellQueue()
{
    if ( spellQueue != NULL )
    {
        if ( spellQueue->action != NULL && spellQueue->actionReadyToCast == true )
        {
            CSpellActionBase *curAction = NULL;

            EffectType::EffectType effectType = spellQueue->action->getEffectType();

            if ( effectType == EffectType::SingleTargetSpell
                     && player->getTarget() != NULL ) {
                curAction = spellQueue->action->cast( player, player->getTarget() );
            } else if ( effectType == EffectType::SelfAffectingSpell ) {
                curAction = spellQueue->action->cast( player, player );
            } else if ( effectType == EffectType::AreaTargetSpell ) {
                if ( player->getTarget() != NULL ) { // AoE spell cast on target
                    curAction = spellQueue->action->cast( player, player->getTarget() );
                } else if ( spellQueue->areaOfEffectOnSpecificLocation == true ) { // AoE spell cast on specific position
                    curAction = spellQueue->action->cast( player, spellQueue->actionSpecificXPos, spellQueue->actionSpecificYPos );
                }
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
            spellbook->setFloatingSpell( spellQueue->action );
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
