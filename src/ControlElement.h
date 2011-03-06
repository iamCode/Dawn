#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include "FramesBase.h"

#include <vector>
#include <stdint.h>
#include <string>
class GLFT_Font;


class SimpleFunctionObject
{
	public:
		virtual void operator()() = 0;
};

class Label : public FramesBase
{
	public:
		Label( GLFT_Font *font = NULL, std::string text = "" );
		virtual void setText( std::string newText );
		virtual void setFont( GLFT_Font *font );

		virtual void draw( int mouseX, int mouseY );
		virtual void clicked( int mouseX, int mouseY, uint8_t mouseState );
		void setOnClicked( SimpleFunctionObject* onClickedFunc );

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

#endif // CONTROLELEMENT_H
