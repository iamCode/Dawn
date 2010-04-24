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

#include "FramesBase.h"
#include <vector>

extern std::vector <FramesBase*> activeFrames;

FramesBase::FramesBase()
    :   visible( false )
{
}

FramesBase::FramesBase( int posX_, int posY_, int frameWidth_, int frameHeight_, int frameOffsetX_, int frameOffsetY_, int titleWidth_, int titleHeight_, int titleOffsetX_, int titleOffsetY_ )
    :   posX( posX_ ),
        posY( posY_ ),
        frameWidth( frameWidth_ ),
        frameHeight( frameHeight_ ),
        frameOffsetX( frameOffsetX_ ),
        frameOffsetY( frameOffsetY_ ),
        titleWidth( titleWidth_ ),
        titleHeight( titleHeight_ ),
        titleOffsetX( titleOffsetX_ ),
        titleOffsetY( titleOffsetY_ ),
        visible( false )
{
}

void FramesBase::draw( int mouseX, int mouseY )
{
}

void FramesBase::clicked( int mouseX, int mouseY )
{
}

bool FramesBase::isOnThisScreen( int x, int y ) const
{
	if ( x < posX + frameOffsetX
	     || y < posY + frameOffsetY
	     || x > posX + frameOffsetX + frameWidth
	     || y > posY + frameOffsetY + frameHeight ) {
	    return false;
	}
	return true;
}

bool FramesBase::isVisible() const
{
    return visible;
}

void FramesBase::setVisible( bool visible )
{
    this->visible = visible;
}

void FramesBase::toggle()
{
    // is the frame visible?
    if ( isVisible() )
    {
        // then loop through all frames and remove the frame and make it unvisible.
        for ( size_t curFrame = 0; curFrame < activeFrames.size(); curFrame++ )
        {
            if ( this == activeFrames[ curFrame ] )
            {
                setVisible( false );
                activeFrames.erase( activeFrames.begin() + curFrame );
                return;
            }
        }
    } else {
        // else add it to the frame vector and make it visible.
        activeFrames.push_back( this );
        setVisible( true );
    }
}

void FramesBase::setOnTop()
{
    // loop through all frames and put that on top.
    for ( size_t curFrame = 0; curFrame < activeFrames.size(); curFrame++ )
    {
        if ( this == activeFrames[ curFrame ] )
        {
            activeFrames.erase( activeFrames.begin() + curFrame );
            activeFrames.push_back( this );
            return;
        }
    }
}
