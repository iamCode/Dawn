#ifndef _CharacterInfoScreen_h_
#define _CharacterInfoScreen_h_

#include "CTexture.h"

class Player;
class GLFT_Font;

class CharacterInfoScreen
{
	private:
		Player *player;
		bool visible;
		int posX, posY, width, height;
		CTexture textures;
		GLFT_Font *infoFont;

	public:
		CharacterInfoScreen( Player *player_ );
		~CharacterInfoScreen();
		
		void setVisible( bool newVisible );
		bool isVisible() const;
		
		void LoadTextures();
		void initFonts();
		
		void drawScreen();
};

#endif // _CharacterInfoScreen_h_
