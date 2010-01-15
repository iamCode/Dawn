#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <string>
#include <vector>

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

class TextWindow
{
	public:
		void setText( std::string text );
		void setAutocloseTime( int autocloseTime );
		void setPosition( PositionType::PositionType, int x, int y );
		
		void draw();

	private:
		friend TextWindow* DawnInterface::createTextWindow();
		
		TextWindow();
		PositionType::PositionType positionType;
		int x;
		int y;
		uint32_t autocloseTime;
		uint32_t creationTime;
		std::vector<std::string> textLines;
};

#endif // TEXTWINDOW_H
