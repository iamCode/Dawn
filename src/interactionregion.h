/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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

#ifndef INTERACTIONREGION_H
#define INTERACTIONREGION_H

#include <string>

class Player;
class InteractionRegion;

namespace DawnInterface
{
	InteractionRegion* addInteractionRegion();
	void removeInteractionRegion( InteractionRegion *regionToRemove );
};

class InteractionRegion
{
	public:
		void setPosition( int left, int bottom, int width, int height );
		void getPosition( int &left, int &bottom, int &width, int &height ) const;
		void setOnEnterText( std::string enterCode );
		std::string getOnEnterText() const;
		void setOnLeaveText( std::string leaveCode );
		std::string getOnLeaveText() const;
		void interactWithPlayer( Player *player );
		
		std::string getLuaSaveText() const;
		
		bool isMarkedDeletable() const;
	
	private:
		friend InteractionRegion* DawnInterface::addInteractionRegion();
		friend void DawnInterface::removeInteractionRegion( InteractionRegion *regionToRemove );

		InteractionRegion();

		void markAsDeletable();
		
		int left;
		int bottom;
		int width;
		int height;

		bool playerInside;

		std::string onEnterCode;
		std::string onLeaveCode;
		
		bool markedAsDeletable;
};

namespace InteractionControl
{
	void cleanupInteractionRegionList();
}

#endif // INTERACTIONREGION_H
