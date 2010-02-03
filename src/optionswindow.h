#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

class CTexture;
class GLFT_Font;

class OptionsWindow
{
	public:
		OptionsWindow();
		~OptionsWindow();
		void draw();
		bool isOnThisScreen( int posX, int posY ) const;
		void clicked( int mouseX, int mouseY );
		void setVisible( bool visible );
		bool isVisible() const;

	private:
		int posX;
		int posY;
		int width;
		int height;
		bool visible;
		CTexture *backgroundTexture;
		GLFT_Font *font;
};

#endif // OPTIONSWINDOW_H
