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

#ifndef __FRAMESBASE_H__
#define __FRAMESBASE_H__

#include <stdint.h>
#include "CTexture.h"

class FramesBase
{
    public:
        FramesBase();
        FramesBase( int16_t posX_, int16_t posY_, uint16_t frameWidth_, uint16_t frameHeight_, int16_t frameOffsetX_, int16_t frameOffsetY_ );

        void addMoveableFrame( uint16_t titleWidth, uint16_t titleHeight, int16_t titleOffsetX, int16_t titleOffsetY );
        void addCloseButton( uint16_t buttonWidth, uint16_t buttonHeight, int16_t buttonOffsetX, int16_t buttonOffsetY );

        void moveFrame( uint16_t mouseX, uint16_t mouseY );
        void stopMovingFrame( uint16_t mouseX, uint16_t mouseY );
        bool isMovingFrame() const;

        bool isMouseOnTitlebar( int mouseX, int mouseY ) const;
        bool isMouseOnCloseButton( int mouseX, int mouseY ) const;
        virtual bool isMouseOnFrame( int mouseX, int mouseY ) const;
        virtual void clicked( int mouseX, int mouseY );
        virtual void draw( int mouseX, int mouseY );

        virtual void toggle();
        void setOnTop();

        bool isVisible() const;
        void setVisible( bool visible );

    protected:
        bool visible;

        int16_t posX;
		int16_t posY;

		uint16_t frameWidth;
		uint16_t frameHeight;
		int16_t frameOffsetX;
		int16_t frameOffsetY;

		uint16_t titleWidth;
		uint16_t titleHeight;
		int16_t titleOffsetX;
		int16_t titleOffsetY;

		uint16_t buttonWidth;
		uint16_t buttonHeight;
		int16_t buttonOffsetX;
		int16_t buttonOffsetY;

		uint16_t startMovingFrameXpos;
        uint16_t startMovingFrameYpos;

    private:
        bool closeButton;
        bool moveableFrame;
        bool movingFrame;
};

#endif
