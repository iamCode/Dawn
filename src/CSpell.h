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

// system planned:
// CSpellActionBase is it's own factory, i.e. the spell/action class has no
// static members any more. Instead it has functions getText, etc. directly
// The real spell is created by the function create( caster, target ).
// This is the refactoring part with the goal to get rid of the nasty static functions.
//
// Furthermore only general spell classes (effect categories) shall be created here
// the real spells are created from those by lua configuration script.
// e.g. here we create the effect damage (singletarget, ball), healing (single target),
// damage (singletarget, direct) and in lua we create
// * magic missile as singletarget, ball (element air) - several levels
// * fireball as singletarget, ball (element fire), perhaps with additional continuous damage (fire) effect - several levels
// * heal self - several levels
// * heal other - several levels
// * lightning as singletarget, direct (element air) - several levels
// ....
// This is a new feature and will need only some static factory method, hopefully nothing more :)
//
// Further thoughts on this:
// A ball spell might consist of a serious of two things:
// a) a delay effect for the spell (the movement). This might also serve to increase / decrease the following effect.
// b) the actual damage effect (with separate animation)
//
// Some further thought: we could probably even put part of the spell logic to lua for the creation for very general
// custom spells. Need to think on this.

// NOTE: Not used yet, deactivate this comment once that changes ;)
class CSpellActionBase
{
	protected:
		CSpellActionBase();
	public:
		// Question: What about different target types, such as position (for region damage spells)
		/// \brief Creates a spell to really cast as a copy from this one with a fixed target and creator.
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target ) = 0;
		virtual ~CSpellActionBase();
		
		/// Info about the spell, both for the game (mana cost, etc) and for the player (name, info, etc)
		
		/// \brief Returns the time needed to cast a spell.
		/// \todo Should the spell meta information be put in a separate info object?
		virtual uint16_t getCastTime() const = 0;
		virtual uint16_t getManaCost() const = 0;
		virtual std::string getName() const = 0;
		virtual std::string getInfo() const = 0;
		virtual CTexture* getSymbol() const = 0;
		virtual EffectType::EffectType getEffectType() const = 0;
		
		/// Note: The following functions may only be called on spells that where really created,
		///       i.e. for spells created by cast function.
		
		/// \brief Draws the graphical representation of the spell effect.
		virtual void drawEffect() = 0;
		
		/// \brief Called directly after creation of the spell and is thought for an initial effect.
		virtual void startEffect() = 0;
		/// \brief Called while the spell is not yet completed and thought for continuous effects.
		/// Needs to mark the spell as completed unless that has already been done,
		/// e.g. because the effect is not continuous.
		virtual void inEffect() = 0;
		
		/// \brief Whether the spell has done its work and the object can be destroyed.
		bool isEffectComplete() const;
		void unbindFromCreator();
		bool isBoundToCreator() const;
		void beginPreparationOfSpellAction();
		void markSpellActionAsFinished();
		
		void drawSymbol( int left, int width, int bottom, int height ) const;
protected:
	CCharacter *creator;
	bool boundToCreator;
	bool finished;
};

class CSpell : public CSpellActionBase
{
	public:
		CSpell() {}
};

namespace SpellCreation
{
	void initSpells();
	CSpellActionBase* getMagicMissileSpell();
	CSpellActionBase* getLightningSpell();
	CSpellActionBase* getHealOtherSpell();
	CSpellActionBase* getHealingSpell();
}

#endif // __C_SPELL_H_
