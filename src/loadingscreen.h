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
		CTexture *backgroundTexture;
		CTexture *progressTexture;
		GLFT_Font *font;
		std::string curText;
		double progress;
};

#endif // LOADINGWINDOW_H
