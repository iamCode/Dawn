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
    :   visible( false ),
        moveableFrame( false),
        closeButton( false ),
        movingFrame( false )
{
}

FramesBase::FramesBase( int16_t posX_, int16_t posY_, uint16_t frameWidth_, uint16_t frameHeight_, int16_t frameOffsetX_, int16_t frameOffsetY_ )
    :   posX( posX_ ),
        posY( posY_ ),
        frameWidth( frameWidth_ ),
        frameHeight( frameHeight_ ),
        frameOffsetX( frameOffsetX_ ),
        frameOffsetY( frameOffsetY_ ),
        visible( false ),
        moveableFrame( false),
        closeButton( false ),
        movingFrame( false )
{
}

void FramesBase::addMoveableFrame( uint16_t titleWidth, uint16_t titleHeight, int16_t titleOffsetX, int16_t titleOffsetY )
{
    moveableFrame = true;
    this->titleWidth = titleWidth;
    this->titleHeight = titleHeight;
    this->titleOffsetX = titleOffsetX;
    this->titleOffsetY = titleOffsetY;
}

void FramesBase::addCloseButton( uint16_t buttonWidth, uint16_t buttonHeight, int16_t buttonOffsetX, int16_t buttonOffsetY )
{
    closeButton = true;
    this->buttonWidth = buttonWidth;
    this->buttonHeight = buttonHeight;
    this->buttonOffsetX = buttonOffsetX;
    this->buttonOffsetY = buttonOffsetY;
}

void FramesBase::moveFrame( uint16_t mouseX, uint16_t mouseY )
{
    // start moving the frame if we're not.
    // if we are already moving the frame then update the coordinates.
    if ( movingFrame == false )
    {
        movingFrame = true;
        startMovingFrameXpos = mouseX;
        startMovingFrameYpos = mouseY;
    } else {
        posX += mouseX - startMovingFrameXpos;
        posY += mouseY - startMovingFrameYpos;

        startMovingFrameXpos = mouseX;
        startMovingFrameYpos = mouseY;
    }
}

void FramesBase::stopMovingFrame( uint16_t mouseX, uint16_t mouseY )
{
    movingFrame = false;
    startMovingFrameXpos = 0;
    startMovingFrameYpos = 0;
}

bool FramesBase::isMovingFrame() const
{
    return movingFrame;
}

void FramesBase::draw( int mouseX, int mouseY )
{
}

void FramesBase::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
}

bool FramesBase::isMouseOnTitlebar( int mouseX, int mouseY ) const
{
    // if the frame has no titlebar we return false right away...
    if ( moveableFrame == false )
    {
        return false;
    }

    if ( mouseX < posX + titleOffsetX
	     || mouseY < posY + titleOffsetY
	     || mouseX > posX + titleOffsetX + titleWidth
	     || mouseY > posY + titleOffsetY + titleHeight ) {
	    return false;
	}
	return true;
}

bool FramesBase::isMouseOnCloseButton( int mouseX, int mouseY ) const
{
    // if the frame has no closebutton we return false right away...
    if ( closeButton == false )
    {
        return false;
    }

    if ( mouseX < posX + buttonOffsetX
	     || mouseY < posY + buttonOffsetY
	     || mouseX > posX + buttonOffsetX + buttonWidth
	     || mouseY > posY + buttonOffsetY + buttonHeight ) {
	    return false;
	}
	return true;
}

bool FramesBase::isMouseOnFrame( int mouseX, int mouseY ) const
{
	if ( !isVisible() )
	{
	    return false;
	}

	if ( mouseX < posX + frameOffsetX
	     || mouseY < posY + frameOffsetY
	     || mouseX > posX + frameOffsetX + frameWidth
	     || mouseY > posY + frameOffsetY + frameHeight ) {
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
