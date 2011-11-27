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

#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "framesbase.h"

class CTexture;
class GLFT_Font;

class OptionsWindow : public FramesBase
{
	friend class ChooseClassScreen;
public:
	OptionsWindow();
	~OptionsWindow();
	void draw( int mouseX, int mouseY );
	void setTextureDependentPositions();
	void clicked( int mouseX, int mouseY, uint8_t mouseState );

private:
	CTexture *backgroundTexture;
	GLFT_Font *font;
};

class ChooseClassScreen : public FramesBase
{
public:
	ChooseClassScreen();
	~ChooseClassScreen();
	bool isDone() const;
	void setTextureDependentPositions();
	void draw( int mouseX, int mouseY );
	void clicked( int mouseX, int mouseY, uint8_t mouseState );

private:
	CTexture *backgroundTexture;
	GLFT_Font *font;
	bool done;
};

#endif // OPTIONSWINDOW_H
