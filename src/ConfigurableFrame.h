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

#ifndef CONFIGURABLEFRAME_H
#define CONFIGURABLEFRAME_H

#include "FramesBase.h"
#include "ControlElement.h"

class ConfigurableFrame : public FramesBase //, public ControlElement
{
	public:
		ConfigurableFrame( int contentX, int contentY, int contentWidth, int contentHeight, DawnState::DawnState dawnState );
		virtual void draw( int mouseX, int mouseY );
		virtual void clicked( int mouseX, int mouseY, uint8_t mouseState );

		void setAutoresize();
		void setCenteringLayout();
		void setCenterOnScreen();

		virtual void addChildFrame( int relPosX, int relPosY, std::auto_ptr<FramesBase> newChild );
		virtual int getWidth() const;
		virtual int getHeight() const;

	private:
		void applyLayout();
		void resize( int width, int height );
		void recalculatePosition();

		int contentX;
		int contentY;
		int blocksX;
		int blocksY;

		bool autoResize;
		bool centeringLayout;
		bool centerOnScreen;
};

#endif // CONFIGURABLEFRAME_H
