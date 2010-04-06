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

#ifndef __C_SPELL_H_
#define __C_SPELL_H_

#include <string>
#include <stdint.h>

#include "elements.h"
#include "stats.h"

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
		virtual uint16_t getCooldown() const = 0;
		virtual uint16_t getManaCost() const = 0;
		virtual std::string getName() const = 0;
		virtual std::string getID() const;
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
	CSpellActionBase* getGeneralRayDamageSpell();
	CSpellActionBase* getGeneralBoltDamageSpell();
	CSpellActionBase* getGeneralHealingSpell();
	CSpellActionBase* getGeneralBuffSpell();
}

class ConfigurableSpell : public CSpell
{
	public:
		void setCastTime( uint16_t newCastTime );
		virtual uint16_t getCastTime() const;
		void setCooldown( uint16_t newCooldown );
		virtual uint16_t getCooldown() const;
		void setManaCost( uint16_t newManaCost );
		virtual uint16_t getManaCost() const;
		void setName( std::string newName );
		virtual std::string getName() const;
		void setInfo( std::string newInfo );
		virtual std::string getInfo() const;

		void setSpellSymbol( std::string symbolFile );
		CTexture* getSymbol() const;

	protected:
		ConfigurableSpell();
		ConfigurableSpell( ConfigurableSpell *other );

		uint16_t castTime;
		uint16_t manaCost;
		uint16_t cooldown;

		std::string name;
		std::string info;

		CTexture *spellSymbol;
};

class GeneralDamageSpell : public ConfigurableSpell
{
	public:
		void setDirectDamage( uint16_t newMinDirectDamage, uint16_t newMaxDirectDamage, ElementType::ElementType newElementDirect );
		void setContinuousDamage( double newMinContDamagePerSec, double newMaxContDamagePerSec, uint16_t newContDamageTime, ElementType::ElementType newContDamageElement );

		virtual EffectType::EffectType getEffectType() const;

		void dealDirectDamage();
		double calculateContinuousDamage( uint64_t timePassed );

	protected:
		GeneralDamageSpell();
		GeneralDamageSpell( GeneralDamageSpell *other );

		CCharacter *target;

		uint16_t minDirectDamage; // This should be a list of effects
		uint16_t maxDirectDamage;
		ElementType::ElementType elementDirect;

		double minContinuousDamagePerSecond;
		double maxContinuousDamagePerSecond;
		ElementType::ElementType elementContinuous;
		uint16_t continuousDamageTime;
};

class GeneralRayDamageSpell : public GeneralDamageSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target );
		void setNumAnimations( int count );
		void setAnimationTexture( int num, std::string filename );

		virtual void startEffect();
		virtual void inEffect();
		void finishEffect();

		virtual void drawEffect();

	protected:
		GeneralRayDamageSpell();
		GeneralRayDamageSpell( GeneralRayDamageSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralRayDamageSpell();

		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;
		double remainingEffect;

		int numTextures;
		CTexture *spellTexture;
};

class GeneralBoltDamageSpell : public GeneralDamageSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target );
		void setMoveSpeed( int newMoveSpeed );
		void setExpireTime( int newExpireTime );
		void setNumAnimations( int count );
		void setAnimationTexture( int num, std::string filename );

		virtual void startEffect();
		virtual void inEffect();
		void finishEffect();

		virtual void drawEffect();

	protected:
		GeneralBoltDamageSpell();
		GeneralBoltDamageSpell( GeneralBoltDamageSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralBoltDamageSpell();

		uint32_t moveSpeed;
		uint32_t expireTime;
		int posx, posy;
		double moveRemaining;

		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;

		int numBoltTextures;
		CTexture *boltTexture;
};

class GeneralHealingSpell : public ConfigurableSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target );

		void setEffectType( EffectType::EffectType newEffectType );
		EffectType::EffectType getEffectType() const;
		void setHealEffect( int healEffectMin, int healEffectMax, ElementType::ElementType healEffectElement );
		int getHealEffectMin() const;
		int getHealEffectMax() const;
		ElementType::ElementType getElementType() const;

		virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();

	protected:
		GeneralHealingSpell();
		GeneralHealingSpell( GeneralHealingSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralHealingSpell();

		CCharacter *target;

		EffectType::EffectType effectType;
		int healEffectMin;
		int healEffectMax;
		ElementType::ElementType healEffectElement;
};

class GeneralBuffSpell : public ConfigurableSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target );

		void setEffectType( EffectType::EffectType newEffectType );
		EffectType::EffectType getEffectType() const;
		uint16_t getDuration() const;
		void setDuration( uint16_t newDuration );
        int16_t getStats( StatsType::StatsType statsType ) const;
		void setStats( StatsType::StatsType statsType, int16_t amount );
		int16_t getResistElementModifierPoints( ElementType::ElementType elementType ) const;
        void setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints );
		int16_t getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
		void setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints );

		virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();

	protected:
		GeneralBuffSpell();
		GeneralBuffSpell( GeneralBuffSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralBuffSpell();

		CCharacter *target;

		EffectType::EffectType effectType;
		uint16_t duration;
		int16_t *statsModifier;
		int16_t *resistElementModifier;
		int16_t *spellEffectElementModifier;
};

#endif // __C_SPELL_H_
