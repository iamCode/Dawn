/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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

#ifndef INTERACTIONPOINT_H
#define INTERACTIONPOINT_H

#include <string>

class InteractionPoint;
class CharacterInteractionPoint;
class CCharacter;

namespace InteractionType
{
    enum InteractionType
    {
        Quest,
        Shop,
        Zone
    };
}

namespace DawnInterface
{
	InteractionPoint* addInteractionPoint();
	InteractionPoint *addCharacterInteractionPoint( CCharacter *character );
	void removeInteractionPoint( InteractionPoint *pointToRemove );
};

class CTexture;

class InteractionPoint
{
	public:
		~InteractionPoint();
		void setPosition( int posX, int posY, int width, int height );
		void setInteractionType( InteractionType::InteractionType interactionType );
		void setBackgroundTexture( std::string texturename );
		void setInteractionCode( std::string interactionCode );

		virtual bool isMouseOver( int mouseX, int mouseY ) const;
		virtual bool isInRange( int characterXpos, int characterYpos ) const;
		virtual void draw();
		virtual void drawInteractionSymbol( int mouseX, int mouseY, int characterXpos, int characterYpos );
		void startInteraction( int characterXpos, int characterYpos );

		bool isMarkedDeletable() const;

		virtual std::string getLuaSaveText() const;

	protected:
		InteractionPoint();

		CTexture *interactionTexture;
		CTexture *backgroundTexture;
		std::string interactionCode;
		InteractionType::InteractionType interactionType;

	private:
		friend InteractionPoint* DawnInterface::addInteractionPoint();
		friend void DawnInterface::removeInteractionPoint( InteractionPoint *pointToRemove );

		void markAsDeletable();

		int posX;
		int posY;
		int width;
		int height;

		bool markedAsDeletable;
};

class CharacterInteractionPoint : public InteractionPoint
{
	public:
		virtual bool isMouseOver( int mouseX, int mouseY ) const;
		virtual bool isInRange( int characterXpos, int characterYpos ) const;
		virtual void draw();

		virtual std::string getLuaSaveText() const;
	private:
		friend InteractionPoint* DawnInterface::addCharacterInteractionPoint( CCharacter *character );

		CharacterInteractionPoint( CCharacter *character );
		CCharacter *interactionCharacter;
};

namespace InteractionControl
{
	void cleanupInteractionList();
	void purgeInteractionList();
}

#endif // INTERACTIONPOINT_H
