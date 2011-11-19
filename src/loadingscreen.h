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

#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <string>

class CTexture;
class GLFT_Font;

class LoadingScreen
{
	public:
		LoadingScreen();
		~LoadingScreen();
		void draw();
		void setCurrentText( std::string text );
		void setProgress( double progress );

	private:
		int posX;
		int posY;
		int width;
		int height;
		size_t backgroundToDraw;
		CTexture *backgroundTexture;
		CTexture *progressTexture;
		GLFT_Font *font;
		std::string curText;
		double progress;
};

#endif // LOADINGWINDOW_H
