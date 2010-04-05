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

#include "interactionpoint.h"

#include "CTexture.h"
#include "CDrawingHelpers.h"
#include "CLuaFunctions.h"
#include "CCharacter.h"
#include "CZone.h"
#include "globals.h"
#include "CLuaInterface.h"

#include <cassert>

InteractionPoint::InteractionPoint()
	: interactionTexture( NULL ),
	  backgroundTexture( NULL ),
	  interactionCode(""),
	  posX(0),
	  posY(0),
	  width(0),
	  height(0),
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
	interactionTexture->texture.resize(1);
	interactionTexture->LoadIMG( texturename, 0 );
}

void InteractionPoint::setBackgroundTexture( std::string texturename )
{
	// We explicitely want to allow a background texture to change
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
	backgroundTexture = new CTexture();
	backgroundTexture->texture.resize(1);
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

std::string InteractionPoint::getLuaSaveText() const
{
	std::ostringstream oss;
	std::string objectName = "curInteractionPoint";
	
	oss << "local " << objectName << " = DawnInterface.addInteractionPoint();" << std::endl;
	oss << objectName << ":setPosition( " << posX << ", " << posY << ", " << width << ", " << height << " );" << std::endl;
	if ( backgroundTexture != NULL ) {
		oss << objectName << ":setBackgroundTexture( \"" << backgroundTexture->texture[0].textureFile << "\" );" << std::endl;
	}
	if ( interactionTexture != NULL ) {
		oss << objectName << ":setInteractionTexture( \"" << interactionTexture->texture[0].textureFile << "\" );" << std::endl;
	}
	oss << objectName << ":setInteractionCode( [[" << interactionCode << "]] );" << std::endl;
	
	return oss.str();
}

CharacterInteractionPoint::CharacterInteractionPoint( CCharacter *character_ )
	: interactionCharacter( character_ )
{
}

bool CharacterInteractionPoint::isMouseOver( int mouseX, int mouseY ) const
{
	int posX = interactionCharacter->getXPos();
	int posY = interactionCharacter->getYPos();
	int width = interactionCharacter->getWidth();
	int height = interactionCharacter->getHeight();

	if ( mouseX+world_x > posX
		&& mouseX+world_x < posX + width
		&& mouseY+world_y > posY
		&& mouseY+world_y < posY + height ) {
		return true;
	}
	return false;
}

void CharacterInteractionPoint::draw()
{
	// no drawing since the character is what is drawn
}

std::string CharacterInteractionPoint::getLuaSaveText() const
{
	std::ostringstream oss;
	std::string objectName = "curInteractionPoint";
	std::string characterReference = DawnInterface::getItemReferenceRestore( interactionCharacter );
	oss << "local " << objectName << " = DawnInterface.addCharacterInteractionPoint( " << characterReference << " );" << std::endl;
	if ( backgroundTexture != NULL ) {
		oss << objectName << ":setBackgroundTexture( \"" << backgroundTexture->texture[0].textureFile << "\" );" << std::endl;
	}
	if ( interactionTexture != NULL ) {
		oss << objectName << ":setInteractionTexture( \"" << interactionTexture->texture[0].textureFile << "\" );" << std::endl;
	}
	oss << objectName << ":setInteractionCode( [[" << interactionCode << "]] );" << std::endl;
	
	return oss.str();
}

namespace DawnInterface
{
	InteractionPoint* addInteractionPoint()
	{
		InteractionPoint *newInteractionPoint = new InteractionPoint();
		Globals::getCurrentZone()->addInteractionPoint( newInteractionPoint );
		return newInteractionPoint;
	}

	InteractionPoint* addCharacterInteractionPoint( CCharacter *character )
	{
		InteractionPoint *newInteractionPoint = new CharacterInteractionPoint( character );
		Globals::getCurrentZone()->addInteractionPoint( newInteractionPoint );
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
		Globals::getCurrentZone()->cleanupInteractionList();
	}
}
