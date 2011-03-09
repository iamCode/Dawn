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

#ifndef __C_SPELL_H_
#define __C_SPELL_H_

#include <string>
#include <stdint.h>
#include <vector>

#include "elements.h"
#include "stats.h"
#include "CCharacter.h"
#include "item.h"

class CCharacter;
class CTexture;

namespace EffectType
{
	enum EffectType {
		SingleTargetSpell,
		SelfAffectingSpell,
		AreaTargetSpell
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

class GeneralRayDamageSpell;
class GeneralAreaDamageSpell;
class GeneralBoltDamageSpell;
class GeneralHealingSpell;
class GeneralBuffSpell;
class MeleeDamageAction;
class RangedDamageAction;

class CSpellActionBase
{
	protected:
		CSpellActionBase();
	public:
		// Question: What about different target types, such as position (for region damage spells)
		/// \brief Creates a spell to really cast as a copy from this one with a fixed target and creator.
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child=false ) = 0;
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y ) = 0;
		virtual ~CSpellActionBase();

		/// Info about the spell, both for the game (mana cost, etc) and for the player (name, info, etc)

		/// \brief Returns the time needed to cast a spell.
		/// \todo Should the spell meta information be put in a separate info object?
		virtual uint16_t getCastTime() const = 0;
		virtual uint16_t getCooldown() const = 0;
		virtual uint16_t getSpellCost() const = 0;
		virtual uint16_t getDuration() const = 0;
		virtual uint16_t getRadius() const = 0;
		virtual int16_t getX() const = 0;
		virtual int16_t getY() const = 0;
		virtual bool isInRange( uint16_t distance ) const = 0;
		virtual bool isSpellHostile() const = 0;
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

		/// \brief Functions for defining and playing sounds.
		void setSoundSpellCasting( std::string soundSpellCasting );
		void setSoundSpellStart( std::string soundSpellStart );
		void setSoundSpellHit( std::string soundSpellHit );
		void playSoundSpellCasting();
		void playSoundSpellStart();
		void playSoundSpellHit();
		void stopSoundSpellCasting();
		void stopSoundSpellStart();
		void stopSoundSpellHit();

        /// add additional spells to this spell, to be executed based on chance when the spell is finished.
		void addAdditionalSpellOnTarget( CSpellActionBase *spell, double chanceToExecute );
		void addAdditionalSpellOnCreator( CSpellActionBase *spell, double chanceToExecute );

		/// which class can use the spell
		void setRequiredClass( CharacterClass::CharacterClass requiredClass );
		CharacterClass::CharacterClass getRequiredClass() const;

		/// which equipment (weapon) is required to cast the spell.
		void addRequiredWeapon( WeaponType::WeaponType weaponType );
		uint32_t getRequiredWeapons() const;

		/// what level we can use the spell
		void setRequiredLevel( uint8_t requiredLevel );
		uint8_t getRequiredLevel() const;

		/// rank of the spell
		void setRank( uint8_t rank );
		uint8_t getRank() const;

		/// instant spells, doesn't require spell to "hit" the target to do damge (ranged + bolt spells)
		void setInstant( bool instant );
		bool getInstant( ) const;

		/// characterStates which affects the target. Stunned, charmed etc...
		void setCharacterState( CharacterStates::CharacterStates characterState, float value = 1.0f );
		std::pair<CharacterStates::CharacterStates, float> getCharacterState() const;

		void drawSymbol( int left, int width, int bottom, int height ) const;

		/// this resets the luaID to empty. It is only to be used in copySpell-function because there we want to create a new spell which
		/// will be inscribed in the spell database so it will get an ID.
		void unsetLuaID();
	protected:
		CCharacter *creator;
		CCharacter *target;
		bool boundToCreator;
		bool finished;
		bool instant; // makes the spell instant, doesn't require the spell to "hit" the target. (ranged + bolt spells)
		mutable std::string luaID; // for caching the id and not having to get it every time again
		CharacterClass::CharacterClass requiredClass;
		std::string soundSpellCasting;
		std::string soundSpellStart;
		std::string soundSpellHit;
		uint8_t requiredLevel;
		uint32_t requiredWeapons;
		uint8_t rank;
		std::vector< std::pair<CSpellActionBase*,double> > additionalSpellsOnTarget;
		std::vector< std::pair<CSpellActionBase*,double> > additionalSpellsOnCreator;
		std::pair<CharacterStates::CharacterStates,float> characterStateEffects;
};

class CSpell : public CSpellActionBase
{
	public:
		CSpell() {}
};

class CAction : public CSpellActionBase
{
	public:
		CAction() {}
		virtual double getProgress() const = 0;
};

class GeneralBoltDamageSpell;

namespace SpellCreation
{
	CSpellActionBase* getGeneralRayDamageSpell();
	CSpellActionBase* getGeneralRayDamageSpell( GeneralRayDamageSpell *other );
	CSpellActionBase* getGeneralAreaDamageSpell();
	CSpellActionBase* getGeneralAreaDamageSpell( GeneralAreaDamageSpell *other );
	CSpellActionBase* getGeneralBoltDamageSpell();
	CSpellActionBase* getGeneralBoltDamageSpell( GeneralBoltDamageSpell *other );
	CSpellActionBase* getGeneralHealingSpell();
	CSpellActionBase* getGeneralHealingSpell( GeneralHealingSpell *other );
	CSpellActionBase* getGeneralBuffSpell();
	CSpellActionBase* getGeneralBuffSpell( GeneralBuffSpell *other );
	CSpellActionBase* getMeleeDamageAction();
	CSpellActionBase* getMeleeDamageAction( MeleeDamageAction *other );
	CSpellActionBase* getRangedDamageAction();
	CSpellActionBase* getRangedDamageAction( RangedDamageAction *other );
}

class ConfigurableSpell : public CSpell
{
	public:
		void setCastTime( uint16_t newCastTime );
		virtual uint16_t getCastTime() const;
		void setCooldown( uint16_t newCooldown );
		virtual uint16_t getCooldown() const;
		void setSpellCost( uint16_t spellCost );
		virtual uint16_t getSpellCost() const;
		virtual uint16_t getRadius() const;
		virtual int16_t getX() const;
		virtual int16_t getY() const;
		void setRange( uint16_t minRange, uint16_t maxRange );
		virtual bool isInRange( uint16_t distance ) const;
		virtual bool isSpellHostile() const;
		void setName( std::string newName );
		virtual std::string getName() const;
		void setInfo( std::string newInfo );
		virtual std::string getInfo() const;
		void setDuration( uint16_t newDuration );
		virtual uint16_t getDuration() const;

		void setSpellSymbol( std::string symbolFile );
		CTexture* getSymbol() const;

	protected:
		ConfigurableSpell();
		ConfigurableSpell( ConfigurableSpell *other );

		uint16_t castTime;
		uint16_t spellCost;
		uint16_t cooldown;
		uint16_t duration;
		uint16_t minRange;
		uint16_t maxRange;
		bool hostileSpell;
		uint16_t radius;
		int16_t centerX;
		int16_t centerY;

		std::string name;
		std::string info;

		CTexture *spellSymbol;
};

class ConfigurableAction : public CAction
{
	public:
		void setCastTime( uint16_t newCastTime );
		virtual uint16_t getCastTime() const;
		void setCooldown( uint16_t newCooldown );
		virtual uint16_t getCooldown() const;
		void setSpellCost( uint16_t spellCost );
		virtual uint16_t getSpellCost() const;
		virtual uint16_t getRadius() const;
		virtual int16_t getX() const;
		virtual int16_t getY() const;
		void setRange( uint16_t minRange, uint16_t maxRange );
		virtual bool isInRange( uint16_t distance ) const;
		virtual bool isSpellHostile() const;
		void setName( std::string newName );
		virtual std::string getName() const;
		void setInfo( std::string newInfo );
		virtual std::string getInfo() const;
		void setDuration( uint16_t newDuration );
		virtual uint16_t getDuration() const;

		void setSpellSymbol( std::string symbolFile );
		CTexture* getSymbol() const;

	protected:
		ConfigurableAction();
		ConfigurableAction( ConfigurableAction *other );

		uint16_t castTime;
		uint16_t spellCost;
		uint16_t cooldown;
		uint16_t duration;
		uint16_t minRange;
		uint16_t maxRange;
		bool hostileSpell;

		std::string name;
		std::string info;

		CTexture *spellSymbol;
};

class GeneralDamageSpell : public ConfigurableSpell
{
	public:
		void setDirectDamage( uint16_t newMinDirectDamage, uint16_t newMaxDirectDamage, ElementType::ElementType newElementDirect );
		void setContinuousDamage( double newMinContDamagePerSec, double newMaxContDamagePerSec, uint16_t newContDamageTime, ElementType::ElementType newContDamageElement );

	uint16_t getDirectDamageMin() const;
	uint16_t getDirectDamageMax() const;
	ElementType::ElementType getDirectDamageElement() const;

	uint16_t getContinuousDamageMin() const;
	uint16_t getContinuousDamageMax() const;
	ElementType::ElementType getContinuousDamageElement() const;

		virtual EffectType::EffectType getEffectType() const;

		void dealDirectDamage();
		double calculateContinuousDamage( uint64_t timePassed );

	protected:
		GeneralDamageSpell();
		GeneralDamageSpell( GeneralDamageSpell *other );

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
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

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
		friend CSpellActionBase* SpellCreation::getGeneralRayDamageSpell( GeneralRayDamageSpell *other );

		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;
		double remainingEffect;

		int numTextures;
		CTexture *spellTexture;
};

class GeneralAreaDamageSpell : public GeneralDamageSpell
{
  public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

		void setNumAnimations( int count );
		void setAnimationTexture( int num, std::string filename );

		virtual void startEffect();
		virtual void inEffect();
		void finishEffect();

		virtual void drawEffect();

		EffectType::EffectType getEffectType() const;

		void setRadius( uint16_t newRadius );
		virtual uint16_t getRadius();
		virtual int16_t getX();
		virtual int16_t getY();

	protected:
		GeneralAreaDamageSpell();
		GeneralAreaDamageSpell( GeneralAreaDamageSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralAreaDamageSpell();
		friend CSpellActionBase* SpellCreation::getGeneralAreaDamageSpell( GeneralAreaDamageSpell *other );

		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;
		double remainingEffect;

		int numTextures;
		CTexture *spellTexture;

		EffectType::EffectType effectType;
		bool child;
};

class GeneralBoltDamageSpell : public GeneralDamageSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

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
		friend CSpellActionBase* SpellCreation::getGeneralBoltDamageSpell( GeneralBoltDamageSpell *other );

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
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

		void setEffectType( EffectType::EffectType newEffectType );
		EffectType::EffectType getEffectType() const;
		void setDirectHealing( int healEffectMin, int healEffectMax, ElementType::ElementType healEffectElement );
		void setContinuousHealing( double minContinuousHealingPerSecond, double maxContinuousHealingPerSecond, uint16_t continuousHealingTime, ElementType::ElementType elementContinuous );
		ElementType::ElementType getDirectElementType() const;
		uint16_t getDirectHealingMin() const;
		uint16_t getDirectHealingMax() const;

		ElementType::ElementType getContinuousElementType() const;
		uint16_t getContinuousHealingMin() const;
		uint16_t getContinuousHealingMax() const;

		virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();
		virtual void finishEffect();
		double calculateContinuousHealing( uint64_t timePassed );

	protected:
		GeneralHealingSpell();
		GeneralHealingSpell( GeneralHealingSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralHealingSpell();
		friend CSpellActionBase* SpellCreation::getGeneralHealingSpell( GeneralHealingSpell *other );

		EffectType::EffectType effectType;
		uint32_t effectStart;
		uint32_t lastEffect;
		double remainingEffect;
		int healEffectMin;
		int healEffectMax;
		double minContinuousHealingPerSecond;
		double maxContinuousHealingPerSecond;
		uint16_t continuousHealingTime;

        ElementType::ElementType elementContinuous;
		ElementType::ElementType healEffectElement;
};

class GeneralBuffSpell : public ConfigurableSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

		void setEffectType( EffectType::EffectType newEffectType );
		EffectType::EffectType getEffectType() const;
        int16_t getStats( StatsType::StatsType statsType ) const;
		void setStats( StatsType::StatsType statsType, int16_t amount );
		int16_t getResistElementModifierPoints( ElementType::ElementType elementType ) const;
        void setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints );
		int16_t getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
		void setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints );

		virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();
        void finishEffect();

	protected:
		GeneralBuffSpell();
		GeneralBuffSpell( GeneralBuffSpell *other );

	private:
		friend CSpellActionBase* SpellCreation::getGeneralBuffSpell();
		friend CSpellActionBase* SpellCreation::getGeneralBuffSpell( GeneralBuffSpell *other );

		EffectType::EffectType effectType;
		int16_t *statsModifier;
		int16_t *resistElementModifier;
		int16_t *spellEffectElementModifier;
        uint32_t effectStart;
};

class MeleeDamageAction : public ConfigurableAction
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

		virtual EffectType::EffectType getEffectType() const;

        virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();
		virtual void finishEffect();

        double getProgress() const;

		void setDamageBonus( double damageBonus );
		double getDamageBonus() const;
		void dealDamage();

	protected:
    	MeleeDamageAction();
		MeleeDamageAction( MeleeDamageAction *other );

    private:
        friend CSpellActionBase* SpellCreation::getMeleeDamageAction();
        friend CSpellActionBase* SpellCreation::getMeleeDamageAction( MeleeDamageAction *other );

		uint32_t effectStart;
		double damageBonus; // How much damage bonus should we add to our min and max weapon damage?
};

class RangedDamageAction : public ConfigurableAction
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target, bool child );
		virtual CSpellActionBase* cast( CCharacter *creator, int x, int y );

		virtual EffectType::EffectType getEffectType() const;

        virtual void drawEffect();
		virtual void startEffect();
		virtual void inEffect();
		virtual void finishEffect();

		double getProgress() const;

        void setMoveSpeed( int newMoveSpeed );
		void setExpireTime( int newExpireTime );
		void setNumAnimations( int count );
		void setAnimationTexture( int num, std::string filename );

		void setDamageBonus( double damageBonus );
		double getDamageBonus() const;
		void dealDamage();

	protected:
    	RangedDamageAction();
		RangedDamageAction( RangedDamageAction *other );

    private:
		friend CSpellActionBase* SpellCreation::getRangedDamageAction();
		friend CSpellActionBase* SpellCreation::getRangedDamageAction( RangedDamageAction *other );

		uint32_t moveSpeed;
		uint32_t expireTime;
		int posx, posy;
		double moveRemaining;

		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;

		int numProjectileTextures;
		CTexture *projectileTexture;

		double damageBonus; // How much damage bonus should we add to our min and max weapon damage?
};

#endif // __C_SPELL_H_
