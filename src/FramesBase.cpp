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
{
}

FramesBase::FramesBase( int posX_, int posY_, int width_, int height_ )
    :   posX( posX_ ),
        posY( posY_ ),
        width( width_ ),
        height( height_ )
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
	if ( x < posX
	     || y < posY
	     || x > posX + width
	     || y > posY + height ) {
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
