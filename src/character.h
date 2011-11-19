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

#ifndef C_CHARACTER_H
#define C_CHARACTER_H

#include "GLee/GLee.h" // OpenGL Easy Extention Library
#include <SDL/SDL.h>
#include <cmath>
#include <string>
#include <vector>

#include "direction.h"
#include "elements.h"
#include "debug.h"
#include "configuration.h"

namespace Attitude
{
	enum Attitude
	{
		FRIENDLY,
		NEUTRAL,
		HOSTILE
	};
}

extern int world_x, world_y;

class CSpellActionBase;
class GeneralBuffSpell;
class CSpell;
class CAction;
class CInterface;
class CTexture;
class Item;

namespace CharacterClass
{
	enum CharacterClass
	{
		NOCLASS,
		ANYCLASS,
		Liche,
		Ranger,
		Warrior
	};

	inline std::string getCharacterClassName( CharacterClass::CharacterClass characterClass )
	{
		switch ( characterClass )
		{
			case NOCLASS:
				return "NOCLASS";
			break;
			case ANYCLASS:
				return "ANYCLASS";
			break;
			case Liche:
				return "Liche";
			break;
			case Ranger:
				return "Ranger";
			break;
			case Warrior:
				return "Warrior";
			break;
		}
		return "";
	}

	inline std::string getCharacterClassPortrait( CharacterClass::CharacterClass characterClass )
	{
		switch ( characterClass )
		{
		case Liche:
			return "data/interface/Portrait/Liche.tga";
			break;
		case Ranger:
			return "data/interface/Portrait/Ranger.tga";
			break;
		case Warrior:
			return "data/interface/Portrait/Warrior.tga";
			break;
		default:
			dawn_debug_fatal("getCharacterClassPortrait() was called without a valid playable class. Shoult not be. Exiting!");
			return "";
			break;
		}
	}
}

namespace CharacterArchType
{
	enum CharacterArchType
	{
		Fighter,
		Caster
	};
}

namespace ActivityType
{
	enum ActivityType
	{
		Walking,
		Casting,
		Attacking,
		Shooting,
		Dying,
		Count
	};
}

namespace CharacterStates
{
	enum CharacterStates
	{
		Channeling,
		Charmed,
		Confused,
		Feared,
		Invisible,
		Mesmerized,
		Movementspeed,
		SeeInvisible,
		SeeSneaking,
		Sneaking,
		Stunned,
		NOEFFECT
	};

	inline bool isStateConsideredHarmfull( CharacterStates::CharacterStates characterState, float characterStateValue )
	{
		switch( characterState )
		{
		case CharacterStates::Channeling:
			return false;
			break;
		case CharacterStates::Charmed:
			return true;
			break;
		case CharacterStates::Confused:
			return true;
			break;
		case CharacterStates::Feared:
			return true;
			break;
		case CharacterStates::Invisible:
			return false;
			break;
		case CharacterStates::Mesmerized:
			return true;
			break;
		case CharacterStates::Movementspeed:
			if( characterStateValue >= 1.0 )
			{
				return false;
			}
			else
			{
				return true;
			}
			break;
		case CharacterStates::SeeInvisible:
			return false;
			break;
		case CharacterStates::SeeSneaking:
			return false;
			break;
		case CharacterStates::Sneaking:
			return false;
			break;
		case CharacterStates::Stunned:
			return true;
			break;
		case CharacterStates::NOEFFECT:
			return false;
			break;
		}
	}
}

struct sLootTable
{
	Item* item;
	double dropChance;
	sLootTable( Item* item_, double dropChance_ )
	{
		item = item_;
		dropChance = dropChance_;
	}
};

class CCharacter
{
	friend class CSpellActionBase;
	friend class SpellActionBaseNew;

	std::string classID;

public:
	CCharacter();
	virtual ~CCharacter();

	GLuint frame;
	int x_pos, y_pos;

	virtual void Draw() = 0;
	virtual void Move() = 0;
	void MoveSpecific( uint8_t n );
	void MoveUp( uint8_t n );
	void MoveDown( uint8_t n );
	void MoveLeft( uint8_t n );
	void MoveRight( uint8_t n );
	void giveMovePoints( uint32_t movePoints );
	void Init(int x, int y)
	{
		x_pos = x;
		y_pos = y;
		direction_texture = S;
		remainingMovePoints = 0;
		isPreparing = false;
		alive = true;
		hasDrawnDyingOnce = false;
		hasChoosenFearDirection = false;
		hasChoosenDyingDirection = false;
		curSpellAction = NULL;
		experience = 0;
		coins = 0;
		dyingTransparency = 1.0f;
	}

	virtual bool isPlayer() const;

	int CollisionCheck(Direction direction);

	CTexture* getPortraitTexture() const;

	// casting spells and executing actions
	void executeSpellWithoutCasting( CSpellActionBase* spell, CCharacter* target );
	bool castSpell( CSpellActionBase* spell );
	void giveToPreparation( CSpellActionBase* toPrepare );
	bool continuePreparing();
	void startSpellAction();
	void CastingAborted();
	void CastingInterrupted();
	void abortCurrentSpellAction();
	std::string getCurrentSpellActionName() const;
	float getPreparationPercentage() const;
	bool getIsPreparing() const;

	void regenerateLifeManaFatigue( uint32_t regenPoints );

	CCharacter* getTarget() const;
	Attitude::Attitude getTargetAttitude();
	void setTarget( CCharacter* target );
	void setTarget( CCharacter* target, Attitude::Attitude attitude );

	//active buffs and debuffs
	void addActiveSpell( CSpellActionBase* spell );
	void cleanupActiveSpells();
	void clearActiveSpells();
	std::vector<std::pair<CSpellActionBase*, uint32_t> > getActiveSpells() const;
	void removeSpellsWithCharacterState( CharacterStates::CharacterStates characterState );
	void removeActiveSpell( CSpellActionBase* activeSpell );

	//active cooldowns on spells
	void addCooldownSpell( CSpellActionBase* spell );
	void cleanupCooldownSpells();
	void clearCooldownSpells();
	std::vector<std::pair<CSpellActionBase*, uint32_t> > getCooldownSpells() const;
	uint32_t getTicksOnCooldownSpell( std::string spellName ) const;
	bool isSpellOnCooldown( std::string spellName ) const;

	void inscribeSpellInSpellbook( CSpellActionBase* spell );
	std::vector<CSpellActionBase*> getSpellbook() const;
	void setSpellbook( std::vector<CSpellActionBase*> spellbook );

	// position access functions
	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
	void setPosition( int xpos, int ypos );

	virtual Direction GetDirection() = 0;
	Direction getDirectionTowardsWaypointAt( int x_pos, int y_pos ) const;
	Direction getDirectionTowards( int x_pos, int y_pos ) const;
	ActivityType::ActivityType getCurActivity() const;

	Direction WanderDirection, MovingDirection, fearDirection, dyingDirection;

	Uint8* keys;

	int GetDirectionTexture();
	int current_texture, direction_texture;
	int CheckForCollision(int x, int y);
	uint32_t remainingMovePoints;

	CCharacter* target;
	bool hasTarget( CCharacter* target );

	void baseOnType( std::string otherType );
	std::string getClassID() const;

	std::string getName() const;
	void setName( std::string newName );

	void setArmor( uint16_t newArmor );
	virtual uint16_t getModifiedArmor() const;
	uint16_t getArmor() const;
	void modifyArmor( int16_t armorModifier );

	void setDamageModifierPoints( uint16_t newDamageModifierPoints );
	virtual uint16_t getModifiedDamageModifierPoints() const;
	uint16_t getDamageModifierPoints() const;
	void modifyDamageModifierPoints( int16_t damageModifierModifierPoints );

	void setHitModifierPoints( uint16_t newHitModifierPoints );
	virtual uint16_t getModifiedHitModifierPoints() const;
	uint16_t getHitModifierPoints() const;
	void modifyHitModifierPoints( int16_t hitModifierModifierPoints );

	void setEvadeModifierPoints( uint16_t newEvadeModifierPoints );
	virtual uint16_t getModifiedEvadeModifierPoints() const;
	uint16_t getEvadeModifierPoints() const;
	void modifyEvadeModifierPoints( int16_t evadeModifierModifierPoints );

	void setParryModifierPoints( uint16_t newParryModifierPoints );
	virtual uint16_t getModifiedParryModifierPoints() const;
	uint16_t getParryModifierPoints() const;
	void modifyParryModifierPoints( int16_t parryModifierModifierPoints );

	void setBlockModifierPoints( uint16_t newBlockModifierPoints );
	virtual uint16_t getModifiedBlockModifierPoints() const;
	uint16_t getBlockModifierPoints() const;
	void modifyBlockModifierPoints( int16_t blockModifierPoints );

	void setMeleeCriticalModifierPoints( uint16_t newMeleeCriticalModifierPoints );
	virtual uint16_t getModifiedMeleeCriticalModifierPoints() const;
	uint16_t getMeleeCriticalModifierPoints() const;
	void modifyMeleeCriticalModifierPoints( int16_t meleeCriticalModifierPoints );

	void setResistElementModifierPoints( ElementType::ElementType elementType, uint16_t newResistElementModifierPoints );
	virtual uint16_t getModifiedResistElementModifierPoints( ElementType::ElementType elementType ) const;
	uint16_t getResistElementModifierPoints( ElementType::ElementType elementType ) const;
	void modifyResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistElementModifierPoints );

	void setResistAllModifierPoints( uint16_t newResistAllModifierPoints );
	uint16_t getResistAllModifierPoints() const;
	void modifyResistAllModifierPoints( int16_t resistAllModifierPoints );

	void setSpellEffectElementModifierPoints( ElementType::ElementType elementType, uint16_t newSpellEffectElementModifierPoints );
	virtual uint16_t getModifiedSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
	uint16_t getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
	void modifySpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints );

	void setSpellEffectAllModifierPoints( uint16_t newSpellEffectAllModifierPoints );
	uint16_t getSpellEffectAllModifierPoints() const;
	void modifySpellEffectAllModifierPoints( int16_t spellEffectAllModifierPoints );

	void setSpellCriticalModifierPoints( uint16_t newSpellCriticalModifierPoints );
	virtual uint16_t getModifiedSpellCriticalModifierPoints() const;
	uint16_t getSpellCriticalModifierPoints() const;
	void modifySpellCriticalModifierPoints( int16_t spellCriticalModifierPoints );

	void setStrength( uint16_t newStrength );
	virtual uint16_t getModifiedStrength() const;
	uint16_t getStrength() const;
	void modifyStrength( int16_t strengthModifier );

	void setDexterity( uint16_t newDexterity );
	virtual uint16_t getModifiedDexterity() const;
	uint16_t getDexterity() const;
	void modifyDexterity( int16_t dexterityModifier );

	void setVitality( uint16_t newVitality );
	virtual uint16_t getModifiedVitality() const;
	uint16_t getVitality() const;
	void modifyVitality( int16_t vitalityModifier );

	void setIntellect( uint16_t newIntellect );
	virtual uint16_t getModifiedIntellect() const;
	uint16_t getIntellect() const;
	void modifyIntellect( int16_t intellectModifier );

	void setWisdom( uint16_t newWisdom );
	virtual uint16_t getModifiedWisdom() const;
	uint16_t getWisdom() const;
	void modifyWisdom( int16_t wisdomModifier );

	uint16_t getMaxHealth() const;
	virtual uint16_t getModifiedMaxHealth() const;
	void setMaxHealth( uint16_t newMaxHealth );
	void modifyMaxHealth( int16_t maxHealthModifier );

	uint16_t getCurrentHealth() const;
	void setCurrentHealth( uint16_t newCurrentHealth );
	void modifyCurrentHealth( int16_t currentHealthModifier);

	uint16_t getMaxMana() const;
	virtual uint16_t getModifiedMaxMana() const;
	void setMaxMana( uint16_t newMaxMana );
	void modifyMaxMana( int16_t maxManaModifier );

	uint16_t getMaxFatigue() const;
	virtual uint16_t getModifiedMaxFatigue() const;
	void setMaxFatigue( uint16_t newMaxFatigue );
	void modifyMaxFatigue( int16_t maxFatigueModifier );

	uint16_t getCurrentMana() const;
	void setCurrentMana( uint16_t newCurrentMana );
	void modifyCurrentMana( int16_t currentManaModifier);

	uint16_t getCurrentFatigue() const;
	void setCurrentFatigue( uint16_t newCurrentFatigue );
	void modifyCurrentFatigue( int16_t currentFatigueModifier);

	void setManaRegen( uint16_t newManaRegen );
	virtual uint16_t getModifiedManaRegen() const;
	uint16_t getManaRegen() const;
	void modifyManaRegen( int16_t manaRegenModifier );

	void setHealthRegen( uint16_t newHealthRegen );
	virtual uint16_t getModifiedHealthRegen() const;
	uint16_t getHealthRegen() const;
	void modifyHealthRegen( int16_t healthRegenModifier );

	void setFatigueRegen( uint16_t newFatigueRegen );
	virtual uint16_t getModifiedFatigueRegen() const;
	uint16_t getFatigueRegen() const;
	void modifyFatigueRegen( int16_t fatigueRegenModifier );

	void setExperienceValue( uint8_t newFatigueRegen );
	uint8_t getExperienceValue() const;

	void setClass( CharacterClass::CharacterClass );
	CharacterClass::CharacterClass getClass() const;
	CharacterArchType::CharacterArchType getArchType() const;
	std::string getClassName() const;

	void addItemToLootTable( Item* item, double dropChance );

	void setExperience( uint64_t experience );
	uint64_t getExperience() const;
	void gainExperience( uint64_t addExp );
	uint64_t getExpNeededForLevel( uint8_t level ) const;
	bool canRaiseLevel() const;
	void raiseLevel();

	void setWanderRadius( uint16_t newWanderRadius );
	uint16_t getWanderRadius() const;

	void setLevel ( uint8_t newLevel );
	uint8_t getLevel() const;

	std::vector<sLootTable> getLootTable() const;
	void setLootTable( std::vector<sLootTable> newLootTable );

	bool isAlive() const
	{
		return alive;
	}

	void setMinDamage( uint16_t newMinDamage );
	uint16_t getMinDamage() const;
	virtual uint16_t getModifiedMinDamage() const;

	void setMaxDamage( uint16_t newMaxDamage );
	uint16_t getMaxDamage() const;
	virtual uint16_t getModifiedMaxDamage() const;

	bool CheckMouseOver(int _x_pos, int _y_pos);
	virtual bool canBeDamaged() const;
	virtual void Damage(int amount, bool criticalHit);
	void Heal(int amount);
	virtual void Die();
	void dropItems();

	void startShopping();
	void stopShopping();
	bool isShopping() const;

	void giveCoins( uint32_t amountOfCoins );
	void reduceCoins( uint32_t amountOfCoins );
	uint32_t getCoins() const;
	void setCoins( uint32_t amountOfCoins );
	void setCoinDrop( uint32_t minCoinDrop, uint32_t maxCoinDrop, double dropChance );

	void setTexture( ActivityType::ActivityType activity, CTexture *newTexture );
	CTexture* getTexture( ActivityType::ActivityType activity ) const;
	void setNumMoveTexturesPerDirection( ActivityType::ActivityType activity, int numTextures );
	void setMoveTexture( ActivityType::ActivityType activity, int direction, int index, std::string filename, int textureOffsetX = 0, int textureOffsetY = 0 );
	CTexture** texture;

	void setActiveGUI( CInterface* GUI_ );
	void addDamageDisplayToGUI( int amount, bool critical, uint8_t damageType );

	void setBoundingBox( int bbx, int bby, int bbw, int bbh );
	void setUseBoundingBox( bool use );
	int getBoundingBoxX() const;
	int getBoundingBoxY() const;
	int getBoundingBoxW() const;
	int getBoundingBoxH() const;
	bool getUseBoundingBox() const;


	bool alive;
	bool hasDrawnDyingOnce;

	// states of the NPC. the functions are from the CharacterStates namespace.
	bool wandering, moving, in_combat;
	bool isStunned() const;
	bool isCharmed() const;
	bool isFeared() const;
	bool isInvisible() const;
	bool isSneaking() const;
	bool isConfused() const;
	bool isChanneling() const;
	bool isMesmerized() const;
	bool canSeeInvisible() const;
	bool canSeeSneaking() const;
	float getMovementSpeed() const;

	int getDeltaX();
	int getDeltaY();

	// timers
	float wander_thisframe, wander_lastframe;
	float respawn_thisframe, respawn_lastframe;
	float dyingStartFrame, reduceDyingTranspFrame;

	// stats
	float life_percentage, mana_percentage, fatigue_percentage;
	void CalculateStats();

	int wander_every_seconds, wander_points_left;
	bool do_respawn;
	int x_spawn_pos, y_spawn_pos;
	int NPC_id;
	int seconds_to_respawn;

	float dyingTransparency;

protected:
	std::vector<std::pair<CSpellActionBase*, uint32_t> > cooldownSpells;

	bool mayDoAnythingAffectingSpellActionWithoutAborting() const;
	bool mayDoAnythingAffectingSpellActionWithAborting() const;

	int dx, dy;

private:
	// attitude
	Attitude::Attitude targetAttitude;

	// NPC attributes
	std::string name;

	CTexture* portrait;

	uint32_t remainingRegenPoints;

	uint16_t strength;
	uint16_t dexterity;
	uint16_t vitality;
	uint16_t intellect;
	uint16_t wisdom;
	uint16_t max_health;
	uint16_t current_health;
	uint16_t max_mana;
	uint16_t current_mana;
	uint16_t max_fatigue;
	uint16_t current_fatigue;
	uint16_t healthRegen;
	uint16_t manaRegen;
	uint16_t fatigueRegen;
	uint8_t experienceValue;

	uint16_t armor;
	uint16_t damageModifierPoints;
	uint16_t hitModifierPoints;
	uint16_t evadeModifierPoints;
	uint16_t parryModifierPoints;
	uint16_t blockModifierPoints;
	uint16_t meleeCriticalModifierPoints;
	uint16_t *resistElementModifierPoints;
	uint16_t resistAllModifierPoints;
	uint16_t *spellEffectElementModifierPoints;
	uint16_t spellEffectAllModifierPoints;
	uint16_t spellCriticalModifierPoints;

	CharacterClass::CharacterClass characterClass;
	CharacterArchType::CharacterArchType characterArchType;

	uint16_t wander_radius;
	uint16_t min_damage, max_damage;
	uint8_t alignment, level;

	// character attributes
	uint64_t experience;

	// casting spells / executing actions
	bool isPreparing;
	CSpellActionBase* curSpellAction;
	uint32_t preparationStartTime, preparationCurrentTime;
	float preparationPercentage;
	CInterface *activeGUI;

	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells;

	std::vector<CSpellActionBase*> spellbook;

	int boundingBoxX;
	int boundingBoxY;
	int boundingBoxW;
	int boundingBoxH;
	bool useBoundingBox;

	int* numMoveTexturesPerDirection;
	int activeDirection;
	bool hasChoosenFearDirection;
	bool hasChoosenDyingDirection;

	std::vector<sLootTable> lootTable;
	uint32_t coins;
	uint32_t minCoinDrop;
	uint32_t maxCoinDrop;
	double coinDropChance;

	bool isCurrentlyShopping;
};

#endif
