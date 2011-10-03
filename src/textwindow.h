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

#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <string>
#include <vector>
#include <stdint.h>

#include "FramesBase.h"

namespace PositionType
{
	enum PositionType
	{
		BOTTOMLEFT,
		BOTTOMCENTER,
		LEFTCENTER,
		CENTER
	};
}

class TextWindow;

namespace DawnInterface
{
	TextWindow *createTextWindow();
}

class TextWindow : public FramesBase
{
	public:
		void setText( std::string text );
		void setAutocloseTime( int autocloseTime );
		void setPosition( PositionType::PositionType, int x, int y );
		void center();
		void setOnCloseText( std::string onCloseText );
		bool canBeDeleted() const;
		void close();

		void clicked( int mouseX, int mouseY, uint8_t mouseState );
		void draw( int mouseX, int mouseY );

	private:
		friend TextWindow* DawnInterface::createTextWindow();

		TextWindow();

		void updateFramesPosition();

		PositionType::PositionType positionType;
		int x;
		int y;
		uint32_t autocloseTime;
		uint32_t creationTime;
		std::vector<std::string> textLines;
		std::string executeTextOnClose;
		bool explicitClose;
};

#endif // TEXTWINDOW_H
