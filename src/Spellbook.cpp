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

#include "Spellbook.h"
#include "CDrawingHelpers.h"
#include "CCharacter.h"
#include "Player.h"

#include <cassert>
#include <memory>
#include "fontcache.h"
#include "FramesBase.h"

void sSpellSlot::initFont()
{
	font = FontCache::getFontFromCache("data/verdana.ttf", 11);
}


Spellbook::Spellbook( Player *player_ ) : FramesBase( 125, 50, 454, 672, 13, 15 )
{
    addMoveableFrame( 454, 22, 13, 665 );
    addCloseButton( 22, 22, 444, 666 );

    player = player_;
    curPage = 0;
    floatingSpell = NULL;

    // spellslots in the spellbook
    spellSlot.push_back(sSpellSlot(139,539,50,50));
    spellSlot.push_back(sSpellSlot(291,539,50,50));

    spellSlot.push_back(sSpellSlot(139,422,50,50));
    spellSlot.push_back(sSpellSlot(291,422,50,50));

    spellSlot.push_back(sSpellSlot(139,307,50,50));
    spellSlot.push_back(sSpellSlot(291,307,50,50));

    spellSlot.push_back(sSpellSlot(139,190,50,50));
    spellSlot.push_back(sSpellSlot(291,190,50,50));

    nextPageButtonOffsetX = 386;
    nextPageButtonOffsetY = 53;

    previousPageButtonOffsetX = 63;
    previousPageButtonOffsetY = 53;

    pageButtonWidth = 32;
    pageButtonHeight = 32;
}

Spellbook::~Spellbook()
{
}

void Spellbook::loadTextures()
{
    textures.texture.resize( 5 );
    textures.LoadIMG( "data/interface/spellbook/base.tga", 0 );
    textures.LoadIMG( "data/interface/spellbook/placeholder.tga", 1 );
    textures.LoadIMG( "data/white2x2pixel.tga", 2 );
    textures.LoadIMG( "data/interface/spellbook/arrow_right.tga", 3 );
    textures.LoadIMG( "data/interface/spellbook/arrow_left.tga", 4 );
}

void Spellbook::draw( int mouseX, int mouseY )
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
            spellSlot[x].action->drawSymbol( world_x + spellSlot[x].posX+posX+2, 46,
                                       world_y + spellSlot[x].posY+posY+2, 46 );
            glColor3f( 0.35f, 0.0f, 0.0f );
            spellSlot[x].font->drawText( static_cast<float>( world_x ) + spellSlot[x].posX+posX + 25 - spellSlot[x].font->calcStringWidth( spellSlot[x].action->getName() ) / 2,
                                         static_cast<float>( world_y ) + spellSlot[x].posY+posY-spellSlot[x].font->getHeight()-5,
                                         spellSlot[x].action->getName() );
            glColor3f( 1.0f, 1.0f, 1.0f );
        }
    }

    // draw the right arrowsymbol if there are spells on the next page
    size_t numSlots = spellSlot.size();
	size_t numSpells = inscribedSpells.size();
    if ( numSlots * (curPage+1) < numSpells ) {
        DrawingHelpers::mapTextureToRect( textures.texture[3].texture,
                                            world_x + posX + nextPageButtonOffsetX, pageButtonWidth,
                                            world_y + posY + nextPageButtonOffsetY, pageButtonHeight );
    }

    // if we are on another page than first page, draw left arrowsymbol to show that there are spells on a previous page.
    if ( curPage > 0 )
    {
        DrawingHelpers::mapTextureToRect( textures.texture[4].texture,
                                            world_x + posX + previousPageButtonOffsetX, pageButtonWidth,
                                            world_y + posY + previousPageButtonOffsetY, pageButtonHeight );
    }

    if ( !hasFloatingSpell() )
    {
        drawSpellTooltip( mouseX, mouseY );
    }
}

void Spellbook::drawSpellTooltip( int mouseX, int mouseY )
{
    int spellSlotId = getMouseOverSpellSlotId( mouseX, mouseY );
    if ( spellSlotId >= 0 && spellSlot[spellSlotId].tooltip != NULL )
    {
        spellSlot[spellSlotId].tooltip->draw( mouseX, mouseY );
    }
}

void Spellbook::drawFloatingSpell( int mouseX, int mouseY )
{
    if ( floatingSpell != NULL )
    {
        // draw background and borders
        DrawingHelpers::mapTextureToRect( textures.texture[1].texture,
                                          world_x + mouseX, 50,
                                          world_y + mouseY + 20, 50 );

        // draw the spell icon
        floatingSpell->action->drawSymbol( world_x + mouseX + 2, 46,
                                   world_y + mouseY + 20 + 2, 46 );
        // draw the spell name
        floatingSpell->font->drawText( static_cast<float>( world_x ) + mouseX + 25 - floatingSpell->font->calcStringWidth( floatingSpell->action->getName() ) / 2,
                                     static_cast<float>( world_y ) + mouseY + 20 - floatingSpell->font->getHeight()-5,
                                     floatingSpell->action->getName() );
    }
}

void Spellbook::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
    int spellSlotIndex = getMouseOverSpellSlotId( mouseX, mouseY );
    if (  spellSlotIndex >= 0 && spellSlot[spellSlotIndex].action != NULL )
    {
        floatingSpell = &spellSlot[spellSlotIndex];
    } else if ( isMouseOverNextPageArea( mouseX, mouseY ) ) {
		nextPage();
	} else if ( isMouseOverPreviousPageArea( mouseX, mouseY ) ) {
		previousPage();
	} else {
        floatingSpell = NULL;
    }
}

bool Spellbook::isMouseOverNextPageArea( int mouseX, int mouseY )
{
	if ( mouseX > posX + nextPageButtonOffsetX
        && mouseX < posX + nextPageButtonOffsetX + pageButtonWidth
        && mouseY > posY + nextPageButtonOffsetY
        && mouseY < posY + nextPageButtonOffsetY + pageButtonHeight )
        {
            return true;
        }
	return false;
}

bool Spellbook::isMouseOverPreviousPageArea( int mouseX, int mouseY )
{
    if ( mouseX > posX + previousPageButtonOffsetX
    && mouseX < posX + previousPageButtonOffsetX + pageButtonWidth
    && mouseY > posY + previousPageButtonOffsetY
    && mouseY < posY + previousPageButtonOffsetY + pageButtonHeight )
    {
        return true;
    }
	return false;
}

int8_t Spellbook::getMouseOverSpellSlotId( int mouseX, int mouseY ) const
{
    for ( size_t index = 0; index < spellSlot.size(); index++ )
    {
        if ( mouseX > spellSlot[index].posX + posX
        && mouseX < spellSlot[index].posX + spellSlot[index].width + posX
        && mouseY > spellSlot[index].posY + posY
        && mouseY < spellSlot[index].posY + spellSlot[index].height + posY )
        {
            return index;
        }
    }
    return -1;
}

sSpellSlot *Spellbook::getFloatingSpell() const
{
    return floatingSpell;
}

sSpellSlot *Spellbook::getSpellSlotBySpell( CSpellActionBase *spell) const
{
    for ( size_t index = 0; index < spellSlot.size(); index++ )
    {
        if ( spellSlot[index].action == spell )
        {
            return const_cast<sSpellSlot *> (&spellSlot[index]);
        }
    }
    abort();
}

void Spellbook::setFloatingSpell( sSpellSlot *newFloatingSpell )
{
    floatingSpell = newFloatingSpell;
}

void Spellbook::unsetFloatingSpell()
{
    floatingSpell = NULL;
}

bool Spellbook::hasFloatingSpell() const
{
    if ( floatingSpell == NULL )
    {
        return false;
    } else {
        return true;
    }
}

void Spellbook::inscribeSpell( CSpellActionBase *spell )
{
	assert( spell != NULL );
	inscribedSpells.push_back(spell);
	refreshPage();
}

void Spellbook::clear()
{
	inscribedSpells.clear();
	refreshPage();
}

void Spellbook::nextPage()
{
	// don't go to a page with no spells on it
	size_t numSlots = spellSlot.size();
	size_t numSpells = inscribedSpells.size();
	if ( numSlots * (curPage+1) >= numSpells ) {
		return;
	}
	++curPage;
	refreshPage();
}

void Spellbook::previousPage()
{
	// don't go further than first page
	if ( curPage == 0 ) {
		return;
	}
	--curPage;
	refreshPage();
}

void Spellbook::refreshPage()
{
	size_t spellsOnPreviousPages = curPage * spellSlot.size();

	for ( size_t curSlot=0; curSlot<spellSlot.size(); ++curSlot ) {
		// reset slot to empty
		spellSlot[curSlot].action = NULL;
		if ( spellSlot[curSlot].tooltip != NULL ) {
			delete spellSlot[curSlot].tooltip;
		}
		spellSlot[curSlot].tooltip = NULL;
		// fill slot with spells from this page
		size_t curSpellNr = spellsOnPreviousPages + curSlot;
		if ( curSpellNr < inscribedSpells.size() ) {
			spellSlot[curSlot].action = inscribedSpells[ curSpellNr ];
			spellSlot[curSlot].tooltip = new spellTooltip( inscribedSpells[ curSpellNr ], player );
		}
	}
}

std::string Spellbook::getLuaSaveText() const
{
	std::ostringstream oss;
	for ( size_t curSpellNr=0; curSpellNr<inscribedSpells.size(); ++curSpellNr ) {
		CSpellActionBase *curSpell = inscribedSpells[ curSpellNr ];
		oss << "DawnInterface.inscribeSpellInPlayerSpellbook( "
		            << "spellDatabase[ \"" << curSpell->getID() << "\" ] );" << std::endl;
	}
	return oss.str();
}

extern std::auto_ptr<Spellbook> spellbook;

namespace DawnInterface
{
	void inscribeSpellInPlayerSpellbook( CSpellActionBase *inscribedSpell )
	{
		spellbook->inscribeSpell( inscribedSpell );
	}

	std::string getSpellbookSaveText()
	{
		return spellbook->getLuaSaveText();
	}
}
