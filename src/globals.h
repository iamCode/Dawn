/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <map>
#include <stdint.h>
#include <vector>
#include <assert.h>

// ideally this file should not add any include dependency on dawn files
class CZone;
class Player;
class CSpellActionBase;

namespace Globals
{
	extern std::map< std::string, CZone* > allZones;
	extern std::vector<std::pair<CSpellActionBase*, uint32_t> > activeAoESpells;
	CZone *getCurrentZone();
	void setCurrentZone( CZone *newCurZone );
	bool isSavingAllowed();
	void setSavingAllowed( bool savingAllowed );
	Player *getPlayer();
	void addActiveAoESpell( CSpellActionBase *spell );
	std::vector<std::pair<CSpellActionBase*, uint32_t> > getActiveAoESpells();
	void cleanupActiveAoESpells();
	void clearActiveAoESpells();
	void removeActiveAoESpell( CSpellActionBase* activeSpell );
}

#endif // GLOBALS_H
