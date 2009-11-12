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

#include "Spellbook.h"
#include "CDrawingHelpers.h"
#include "CCharacter.h"
#include "Player.h"

void sSpellSlot::initFont()
{
	font = new GLFT_Font("data/verdana.ttf", 11);
}

Spellbook::Spellbook( Player *player_ )
        :   posX( 200 ),
            posY( 150 ),
            visible ( false ),
            player( player_ )
{
    // spellslots on the left side of the book.
    spellSlot.push_back(sSpellSlot(100,400,50,50));
    spellSlot.push_back(sSpellSlot(220,400,50,50));

    spellSlot.push_back(sSpellSlot(95,290,50,50));
    spellSlot.push_back(sSpellSlot(215,290,50,50));

    spellSlot.push_back(sSpellSlot(90,180,50,50));
    spellSlot.push_back(sSpellSlot(210,180,50,50));

    spellSlot.push_back(sSpellSlot(85,70,50,50));
    spellSlot.push_back(sSpellSlot(205,70,50,50));

    // do this in a learnSpell / scribeSpell / memorizeSpell function later.
    spellSlot[0].action = SpellCreation::createActionFactoryByName( "Lightning", player );
    spellSlot[0].tooltip = new spellTooltip( spellSlot[0].action, player );
    spellSlot[1].action = SpellCreation::createActionFactoryByName( "Heal Other", player );
    spellSlot[1].tooltip = new spellTooltip( spellSlot[1].action, player );
    spellSlot[2].action = SpellCreation::createActionFactoryByName( "Healing", player );
    spellSlot[2].tooltip = new spellTooltip( spellSlot[2].action, player );
    spellSlot[3].action = SpellCreation::createActionFactoryByName( "Magic Missile", player );
    spellSlot[3].tooltip = new spellTooltip( spellSlot[3].action, player );
}

Spellbook::~Spellbook()
{
    for ( size_t ss = 0; ss < spellSlot.size(); ss++ )
    {
        if ( spellSlot[ss].font != NULL )
        {
            delete spellSlot[ss].font;
        }
    }
}

void Spellbook::loadTextures()
{
    textures.texture.reserve( 3 );
    textures.LoadIMG( "data/interface/spellbook/base.tga", 0 );
    textures.LoadIMG( "data/interface/spellbook/placeholder.tga", 1 );
    textures.LoadIMG( "data/white2x2pixel.tga", 2 );
}

void Spellbook::draw()
{
    // draw spellbook base
    DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
                                        world_x + posX, textures.texture[0].width,
                                        world_y + posY, textures.texture[0].height );

    // draw placeholders, the actual spell symbol and title of the spell.
    for ( size_t x = 0; x < spellSlot.size(); x++ )
    {
        DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                        world_x + spellSlot[x].posX+posX, spellSlot[x].width,
                                        world_y + spellSlot[x].posY+posY, spellSlot[x].height );

        if ( spellSlot[x].action != NULL )
        {
            spellSlot[x].action->draw( world_x + spellSlot[x].posX+posX+2, 46,
                                       world_y + spellSlot[x].posY+posY+2, 46 );
            spellSlot[x].font->drawText( static_cast<float>( world_x ) + spellSlot[x].posX+posX-20,
                                         static_cast<float>( world_y ) + spellSlot[x].posY+posY-spellSlot[x].font->getHeight()-5,
                                         spellSlot[x].action->getName() );
        }
    }

}

void Spellbook::drawSpellTooltip( int x, int y )
{
    int spellSlotId = getMouseOverSpellSlotId( x, y );
    if ( spellSlotId >= 0 && spellSlot[spellSlotId].tooltip != NULL )
    {
        spellSlot[spellSlotId].tooltip->draw( x, y );
    }
}

bool Spellbook::isVisible() const
{
    return visible;
}

void Spellbook::setVisible( bool newVisible )
{
    visible = newVisible;
}

bool Spellbook::isMouseOver( int x, int y ) const
{

}

void Spellbook::clicked( int clickX, int clickY )
{
}

int8_t Spellbook::getMouseOverSpellSlotId( int x, int y ) const
{
    for ( size_t index = 0; index < spellSlot.size(); index++ )
    {
        if ( x > spellSlot[index].posX + posX
        && x < spellSlot[index].posX + spellSlot[index].width + posX
        && y > spellSlot[index].posY + posY
        && y < spellSlot[index].posY + spellSlot[index].height + posY )
        {
            return index;
        }
    }
    return -1;
}
