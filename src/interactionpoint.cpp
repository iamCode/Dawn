#include "interactionpoint.h"

#include "CTexture.h"
#include "CDrawingHelpers.h"
#include "CLuaFunctions.h"

#include <cassert>

std::vector<InteractionPoint*> allInteractionPoints;

InteractionPoint::InteractionPoint()
	: interactionTexture( NULL ),
	  backgroundTexture( NULL ),
	  posX(0),
	  posY(0),
	  width(0),
	  height(0),
	  interactionCode(""),
	  markedAsDeletable(false)
{
}

InteractionPoint::~InteractionPoint()
{
	if ( interactionTexture != NULL ) {
		delete interactionTexture;
	}
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
}

void InteractionPoint::setPosition( int posX, int posY, int width, int height )
{
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
}

void InteractionPoint::setInteractionTexture( std::string texturename )
{
	// We explicitely want to allow an interaction texture to change
	if ( interactionTexture != NULL ) {
		delete interactionTexture;
	}
	interactionTexture = new CTexture();
	interactionTexture->texture.reserve(1);
	interactionTexture->LoadIMG( texturename, 0 );
}

void InteractionPoint::setBackgroundTexture( std::string texturename )
{
	// We explicitely want to allow a background texture to change
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
	backgroundTexture = new CTexture();
	backgroundTexture->texture.reserve(1);
	backgroundTexture->LoadIMG( texturename, 0 );
}

void InteractionPoint::setInteractionCode( std::string interactionCode )
{
	this->interactionCode = interactionCode;
}

bool InteractionPoint::isMouseOver( int mouseX, int mouseY ) const
{
	if ( mouseX+world_x > posX
		&& mouseX+world_x < posX + width
		&& mouseY+world_y > posY
		&& mouseY+world_y < posY + height ) {
		return true;
	}
	return false;
}

void InteractionPoint::draw()
{
	assert( backgroundTexture != NULL );
	if ( markedAsDeletable ) {
		return;
	}
	
	DrawingHelpers::mapTextureToRect( backgroundTexture->texture[0].texture, posX, width, posY, height );
}

void InteractionPoint::drawInteractionSymbol( int mouseX, int mouseY )
{
	assert( interactionTexture != NULL );
	if ( markedAsDeletable ) {
		return;
	}
	
	if ( ! isMouseOver( mouseX, mouseY ) ) {
		return;
	}
	
	DrawingHelpers::mapTextureToRect( interactionTexture->texture[0].texture,
	                                  mouseX+world_x,
	                                  interactionTexture->texture[0].width,
	                                  mouseY+world_y,
	                                  interactionTexture->texture[0].height );
}

void InteractionPoint::startInteraction()
{
	if ( markedAsDeletable ) {
		return;
	}

	LuaFunctions::executeLuaScript( interactionCode );
}

bool InteractionPoint::isMarkedDeletable() const
{
	return markedAsDeletable;
}

void InteractionPoint::markAsDeletable()
{
	markedAsDeletable = true;
}

namespace DawnInterface
{
	InteractionPoint* addInteractionPoint()
	{
		InteractionPoint *newInteractionPoint = new InteractionPoint();
		allInteractionPoints.push_back( newInteractionPoint );
		return newInteractionPoint;
	}

	void removeInteractionPoint( InteractionPoint *pointToRemove )
	{
		pointToRemove->markAsDeletable();
	}
}

namespace InteractionControl
{
	void cleanupInteractionList()
	{
		size_t curInteractionNr = 0;
		while ( curInteractionNr < allInteractionPoints.size() ) {
			InteractionPoint *curInteraction = allInteractionPoints[ curInteractionNr ];
			if ( curInteraction->isMarkedDeletable() ) {
				// return from list
				allInteractionPoints[ curInteractionNr ] = allInteractionPoints[ allInteractionPoints.size() - 1 ];
				allInteractionPoints.resize( allInteractionPoints.size() - 1 );
				delete curInteraction;
			} else {
				++curInteractionNr;
			}
		}
	}
	
	void purgeInteractionList()
	{
		for ( size_t curInteractionNr=0; curInteractionNr < allInteractionPoints.size(); ++curInteractionNr ) {
			InteractionPoint *curInteraction = allInteractionPoints[ curInteractionNr ];
			delete curInteraction;
		}
		allInteractionPoints.resize(0);
	}
}
