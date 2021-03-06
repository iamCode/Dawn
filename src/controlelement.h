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

#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include "framesbase.h"

#include <vector>
#include <stdint.h>
#include <string>

class GLFT_Font;

class SimpleFunctionObject
{
	public:
		virtual void operator()() = 0;
};

template <class ArgumentType>
class SingleArgumentCallback
{
	public:
		virtual void operator()( ArgumentType arg ) = 0;
};

class Label : public FramesBase
{
	public:
		Label( GLFT_Font *font = NULL, std::string text = "" );
		~Label();
		virtual void setText( std::string newText );
		virtual void setFont( GLFT_Font *font );

		virtual void draw( int mouseX, int mouseY );
		virtual void clicked( int mouseX, int mouseY, uint8_t mouseState );
		void setOnClicked( SimpleFunctionObject* onClickedFunc );
		void execute();

		virtual int getWidth() const;
		virtual int getHeight() const;

		virtual void setBaseColor( float red, float green, float blue, float alpha );
		virtual void setSelectColor( float red, float green, float blue, float alpha );

	private:
		GLFT_Font *font;
		float baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha;
		float selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha;
		std::string text;
		mutable SimpleFunctionObject *onClickedFunc;
};

class SelectionBox : public FramesBase
{
	public:
		SelectionBox( GLFT_Font *font, GLFT_Font *selectFont );
		~SelectionBox();
		virtual void setFont( GLFT_Font *font );
		virtual void setSelectFont( GLFT_Font *selectFont );
		virtual void setEntries( std::vector<std::string> entries, int initialSelected );
		virtual int getSelected() const;
		virtual void setSelected( int selected );

		virtual void draw( int mouseX, int mouseY );
		virtual void clicked( int mouseX, int mouseY, uint8_t mouseState );

		typedef SingleArgumentCallback<int> CallbackType;
		void setOnSelected( CallbackType *onSelectedFunc );

		virtual int getWidth() const;
		virtual int getHeight() const;

		virtual void setBaseColor( float red, float green, float blue, float alpha );
		virtual void setSelectColor( float red, float green, float blue, float alpha );

	private:
		GLFT_Font *font;
		GLFT_Font *selectFont;
		float baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha;
		float selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha;
		std::vector<std::string> entries;
		int selected;
		int maxWidth;
		int maxSelectedWidth;
		enum State { OPEN, CLOSED } state;
		mutable CallbackType *onSelectedFunc;
};

#endif // CONTROLELEMENT_H
