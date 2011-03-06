#include "ControlElement.h"

#include "CDrawingHelpers.h"
#include "GLFT_Font.h"

#include <iostream>

/// class Label

Label::Label( GLFT_Font *font_, std::string text_ )
{
	setFont( font_ );
	setText( text_ );
	setBaseColor( 0.0f, 0.0f, 0.0f, 0.0f );
	setSelectColor( 0.0f, 0.0f, 0.0f, 0.0f );
	onClickedFunc = NULL;
}

void Label::setText( std::string newText )
{
	text = newText;
}

void Label::setFont( GLFT_Font *newFont )
{
	font = newFont;
}

void Label::setOnClicked( SimpleFunctionObject* onClickedFunc )
{
	this->onClickedFunc = onClickedFunc;
}

void Label::draw( int mouseX, int mouseY )
{
	if ( font == NULL || text == "" )
		return;

	if (  onClickedFunc != NULL
			&& mouseX > getPosX() && mouseX < getPosX() + font->calcStringWidth( text )
			&& mouseY > getPosY() && mouseY < getPosY() + font->getHeight() )
		glColor4f( selectColorRed, selectColorGreen, selectColorBlue, selectColorAlpha );
	else
		glColor4f( baseColorRed, baseColorGreen, baseColorBlue, baseColorAlpha );
	font->drawText( getPosX(), getPosY(), text );

	// draw child controls if any
	FramesBase::draw( mouseX, mouseY );
}

void Label::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	if ( onClickedFunc != NULL )
	{
		if ( mouseX > getPosX() && mouseX < getPosX() + font->calcStringWidth( text )
				&& mouseY > getPosY() && mouseY < getPosY() + font->getHeight() )
		{
			std::cout << "clicked on label " << text << std::endl;
			(*onClickedFunc)();
			return; // true;
		}
	}
	//return false;
}

int Label::getWidth() const
{
	return font->calcStringWidth( text );
}

int Label::getHeight() const
{
	return font->getHeight();
}

void Label::setBaseColor( float red, float green, float blue, float alpha )
{
	baseColorRed = red;
	baseColorGreen = green;
	baseColorBlue = blue;
	baseColorAlpha = alpha;
}

void Label::setSelectColor( float red, float green, float blue, float alpha )
{
	selectColorRed = red;
	selectColorGreen = green;
	selectColorBlue = blue;
	selectColorAlpha = alpha;
}

