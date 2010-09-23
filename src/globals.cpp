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

#include "globals.h"

#include "Player.h"
Player thePlayer;

namespace Globals
{

CZone *currentZone;
bool savingAllowed = false;

CZone *getCurrentZone()
{
	return currentZone;
}

void setCurrentZone( CZone *newCurZone )
{
	currentZone = newCurZone;
}

bool isSavingAllowed()
{
	return savingAllowed;
}

void setSavingAllowed( bool savingAllowed_ )
{
	savingAllowed = savingAllowed_;
}

Player* getPlayer()
{
	return &thePlayer;
}

} // namespace Globals

namespace DawnInterface
{
	bool isSavingAllowed()
	{
		return Globals::isSavingAllowed();
	}

	void setSavingAllowed( bool savingAllowed )
	{
		Globals::setSavingAllowed( savingAllowed );
	}
	
	Player* getPlayer()
	{
		return &thePlayer;
	}
}
