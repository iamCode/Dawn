/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

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

#ifndef __C_ACTION_H_
#define __C_ACTION_H_

#include "CSpell.h" // only for CSpellActionBase which should be moved to a separate file...

class CAction : public CSpellActionBase
{
	public:
		CAction( CCharacter *creator_, uint16_t castTime, uint16_t manaCost, std::string name, std::string info )
				: CSpellActionBase( creator_, castTime, manaCost, name, info ) {}
		virtual double getProgress() const = 0;
};

namespace ActionCreation
{
	void initActions();
	CTexture* getActionSymbolByName( std::string name );
	CAction* createAttackAction( CCharacter *attacker, CCharacter *target );
}

#endif // __C_ACTION_H_
