#ifndef INTERACTIONPOINT_H
#define INTERACTIONPOINT_H

#include <string>

class InteractionPoint;

namespace DawnInterface
{
	InteractionPoint* addInteractionPoint();
	void removeInteractionPoint( InteractionPoint *pointToRemove );
};

class CTexture;

class InteractionPoint
{
	public:
		~InteractionPoint();
		void setPosition( int posX, int posY, int width, int height );
		void setInteractionTexture( std::string texturename );
		void setBackgroundTexture( std::string texturename );
		void setInteractionCode( std::string interactionCode );
		
		bool isMouseOver( int mouseX, int mouseY ) const;
		void draw();
		void drawInteractionSymbol( int mouseX, int mouseY );
		void startInteraction();
		
		bool isMarkedDeletable() const;
		
	private:
		friend InteractionPoint* DawnInterface::addInteractionPoint();
		friend void DawnInterface::removeInteractionPoint( InteractionPoint *pointToRemove );
		
		InteractionPoint();
		void markAsDeletable();
		
		CTexture *interactionTexture;
		CTexture *backgroundTexture;
		
		int posX;
		int posY;
		int width;
		int height;
		
		std::string interactionCode;
		
		bool markedAsDeletable;
};

namespace InteractionControl
{
	void cleanupInteractionList();
	void purgeInteractionList();
}

#endif // INTERACTIONPOINT_H
