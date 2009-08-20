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

#ifndef __C_SPELL_H_
#define __C_SPELL_H_

#include <string>
#include <stdint.h>

class CCharacter;
class CTexture;

namespace EffectType
{
	enum EffectType {
		SingleTargetSpell,
		SelfAffectingSpell
	};
}

class CSpellActionBase
{
	public:
		CSpellActionBase( CCharacter *Creator, uint16_t castTime, uint16_t manaCost, std::string name, std::string info );
		virtual ~CSpellActionBase();

		/// \brief Returns the time needed to cast a spell in ms.
		uint16_t getCastTime() const;
		uint16_t getManaCost() const;

		std::string getName() const;
		std::string getInfo() const;

		void beginPreparationOfSpellAction();
		virtual void drawEffect() = 0;
		virtual void startEffect() = 0;
		virtual void inEffect() = 0;
		void markSpellActionAsFinished();
		bool isEffectComplete();

		virtual CTexture* getSymbol() const = 0;

		void unbindFromCreator();
		bool isBoundToCreator() const;

	protected:
		CCharacter *creator;

	private:
		uint16_t castTime;
		uint16_t manaCost;
		std::string name;
		std::string info;
		bool boundToCreator;
		bool finished;
};

class CSpell : public CSpellActionBase
{
	public:
		CSpell( CCharacter *creator_, uint16_t castTime, uint16_t manaCost, std::string name, std::string info )
				: CSpellActionBase( creator_, castTime, manaCost, name, info ) {}
};

namespace SpellCreation
{
	void initSpells();
	CTexture* getSpellSymbolByName( std::string name );
	CSpell* createSingleTargetSpellByName( std::string name, CCharacter *caster, CCharacter *target );
	CSpell* createSelfAffectingSpellByName( std::string name, CCharacter *caster );
}

#endif // __C_SPELL_H_
