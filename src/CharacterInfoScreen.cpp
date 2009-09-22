#include "CharacterInfoScreen.h"

#include "CDrawingHelpers.h"
#include "CCharacter.h"
#include "GLFT_Font.h"

CharacterInfoScreen::CharacterInfoScreen( Player *player_ )
	:	player( player_ ),
		posX(50),
		posY(100),
		width(350),
		height(400),
		visible(false)
{
	infoFont = NULL;
}

CharacterInfoScreen::~CharacterInfoScreen()
{
	if ( infoFont != NULL ) {
		delete infoFont;
	}
}

void CharacterInfoScreen::setVisible( bool newVisible )
{
	visible = newVisible;
}

bool CharacterInfoScreen::isVisible() const
{
	return visible;
}

void CharacterInfoScreen::LoadTextures()
{
	textures.texture.reserve(1);
	textures.LoadIMG("data/interface/characterinfo_background.tga",0);
}

void CharacterInfoScreen::initFonts()
{
	infoFont = new GLFT_Font("data/DejaVuSerif-Italic.ttf", 20);
}

void CharacterInfoScreen::drawScreen()
{
	DrawingHelpers::mapTextureToRect( textures.texture[0].texture,
									  world_x + posX, width, world_y + posY, height );
	int curLine = 0;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Level" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getLevel() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Health" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d / %d", player->getCurrentHealth(), player->getMaxHealth() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Mana" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d / %d", player->getCurrentMana(), player->getMaxMana() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Strength" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getStrength() );
	curLine++;
	infoFont->drawText( world_x + posX + 20, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "Damage" );
	infoFont->drawText( world_x + posX + 160, world_y + posY + height - (20 + curLine*30 + infoFont->getHeight()), "%d", player->getStrength() );
	curLine++;
}
