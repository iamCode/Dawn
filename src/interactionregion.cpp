/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#include "interactionregion.h"

#include "luafunctions.h"
#include "player.h"
#include "globals.h"
#include "zone.h"

#include <cassert>

InteractionRegion::InteractionRegion()
	: left( 0 ),
	  bottom( 0 ),
	  width( 0 ),
	  height( 0 ),
	  playerInside( false ),
	  markedAsDeletable( false )
{
}

void InteractionRegion::setPosition( int left_, int bottom_, int width_, int height_ )
{
	assert( width_ > 0 );
	assert( height_ > 0 );
	left = left_;
	bottom = bottom_;
	width = width_;
	height = height_;
}

void InteractionRegion::getPosition( int &left_, int &bottom_, int &width_, int &height_ ) const
{
	left_   = left;
	bottom_ = bottom;
	width_  = width;
	height_ = height;
}

void InteractionRegion::setOnEnterText( std::string enterCode )
{
	this->onEnterCode = enterCode;
}

std::string InteractionRegion::getOnEnterText() const
{
	return onEnterCode;
}

void InteractionRegion::setOnLeaveText( std::string leaveCode )
{
	this->onLeaveCode = leaveCode;
}

std::string InteractionRegion::getOnLeaveText() const
{
	return onLeaveCode;
}

void InteractionRegion::interactWithPlayer( Player *player )
{
	int px = player->getXPos();
	int pw = player->getWidth();
	int py = player->getYPos();
	int ph = player->getWidth();
	bool playerNowInside = ( px >= left && px + pw <= left + width && py >= bottom && py + ph <= bottom + height );
	if ( playerNowInside &&  ! playerInside ) {
		playerInside = true;
		if (  onEnterCode != "" ) {
			LuaFunctions::executeLuaScript( onEnterCode );
		}
	}
	else if ( ! playerNowInside && playerInside ) {
		playerInside = false;
		if ( onLeaveCode != "" ) {
			LuaFunctions::executeLuaScript( onLeaveCode );
		}
	}
}

std::string InteractionRegion::getLuaSaveText() const
{
	std::ostringstream oss;
	oss << "local curInteractionRegion = DawnInterface.addInteractionRegion();" << std::endl;
	oss << "curInteractionRegion:setPosition( " << left << ", " << bottom << ", " << width << ", " << height << " );" << std::endl;
	if ( onEnterCode != "" ) {
		oss << "curInteractionRegion:setOnEnterText( [[" << onEnterCode << "]] );" << std::endl;
	}
	if ( onLeaveCode != "" ) {
		oss << "curInteractionRegion:setOnLeaveText( [[" << onLeaveCode << "]] );" << std::endl;
	}

	return oss.str();
}

bool InteractionRegion::isMarkedDeletable() const
{
	return markedAsDeletable;
}

void InteractionRegion::markAsDeletable()
{
	markedAsDeletable = true;
}

namespace DawnInterface
{
	InteractionRegion* addInteractionRegion()
	{
		InteractionRegion *newInteractionRegion = new InteractionRegion();
		Globals::getCurrentZone()->addInteractionRegion( newInteractionRegion );
		return newInteractionRegion;
	}

	void removeInteractionRegion( InteractionRegion *regionToRemove )
	{
		regionToRemove->markAsDeletable();
	}
}
