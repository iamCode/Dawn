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

#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "GLee/GLee.h" // OpenGL Easy Extention Library
#include "CTexture.h"
#include "CZone.h"
#include "CDirection.h"
#include "inventory.h"
#include <SDL/SDL.h> // SDL
#include <math.h>

extern int RES_X,RES_Y,world_x,world_y;
extern CZone zone1;

class CSpellActionBase;
class CSpell;
class CAction;
class CInterface;

class CCharacter
{
		friend class CSpellActionBase;

	public:
		CCharacter();
		virtual ~CCharacter();

		GLuint frame;
		int x_pos,y_pos;

		virtual void Draw() = 0;
		virtual void Move() = 0;
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		void giveMovePoints( uint32_t movePoints );
		void Init(int x, int y) {
			x_pos = x;
			y_pos = y;
			direction_texture = S;
			remainingMovePoints = 0;
			isPreparing = false;
			alive = true;
			curSpellAction = NULL;
			experience = 0;
		}

		virtual bool isPlayer() const;

		int CollisionCheck(Direction direction);

		// casting spells and executing actions
		void executeAction( CAction *action );
		void castSpell(CSpell *spell );
		void giveToPreparation( CSpellActionBase *toPrepare );
		bool continuePreparing();
		void startSpellAction();
		void CastingAborted();
		void CastingInterrupted();
		void abortCurrentSpellAction();
		float getPreparationPercentage() const;

		// position access functions
		int getXPos() const;
		int getYPos() const;
		int getWidth() const;
		int getHeight() const;

		virtual Direction GetDirection() = 0;
		Direction getDirectionTowards( int x_pos, int y_pos ) const;

		Direction WanderDirection, MovingDirection;

		Uint8 *keys;

		int GetDirectionTexture();
		int current_texture, direction_texture;
		int CheckForCollision(int x, int y);
		uint32_t remainingMovePoints;

		CCharacter *Target;

		void baseOnType( std::string otherType );

		std::string getName() const;
		void setName( std::string newName );

		void setArmor( uint16_t newArmor );
		virtual uint16_t getModifiedArmor() const;
		uint16_t getArmor() const;
		void modifyArmor( int16_t armorModifier );

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

		uint16_t getCurrentMana() const;
		void setCurrentMana( uint16_t newCurrentMana );
		void modifyCurrentMana( int16_t currentManaModifier);

		uint16_t getMaxEnergy() const;
		virtual uint16_t getModifiedMaxEnergy() const;
		void setMaxEnergy( uint16_t newMaxEnergy );
		void modifyMaxEnergy( int16_t maxEnergyModifier );

		uint16_t getCurrentEnergy() const;
		void setCurrentEnergy( uint16_t newCurrentEnergy );
		void modifyCurrentEnergy( int16_t currentEnergyModifier);

		uint64_t getExperience() const;
		void gainExperience( uint64_t addExp );
		uint64_t getExpNeededForLevel( uint8_t level ) const;
		bool canRaiseLevel() const;
		void raiseLevel();

		void setWanderRadius( uint16_t newWanderRadius );
		uint16_t getWanderRadius() const;

		void setLevel ( uint8_t newLevel );
		uint8_t getLevel() const;

		bool isAlive() const {
			return alive;
		}

		double getDamageModifier() const;

		void setMinDamage( uint16_t newMinDamage );
		uint16_t getMinDamage() const;
		virtual uint16_t getModifiedMinDamage() const;

		void setMaxDamage( uint16_t newMaxDamage );
		uint16_t getMaxDamage() const;
		virtual uint16_t getModifiedMaxDamage() const;

		void DrawLifebar();

		bool CheckMouseOver(int _x_pos, int _y_pos);
		virtual void Damage(int amount);
		void Heal(int amount);
		void Die();

		void setTexture( CTexture *newTexture );
		CTexture *getTexture() const;
		void setLifebar( CTexture *newLifebar );
		CTexture *getLifebar() const;
		void setMoveTexture( int direction, std::string filename );
		void setLifeTexture( std::string filename );
		CTexture *texture;
		CTexture *lifebar;

		void setActiveGUI( CInterface *GUI_ );
		void addDamageDisplayToGUI( int amount, bool critical, uint8_t damageType );


		bool alive;

		// states of the NPC
		bool wandering, moving, in_combat;

		// timers
		float wander_thisframe, wander_lastframe;
		float respawn_thisframe, respawn_lastframe;

		// stats
		float life_percentage, mana_percentage, energy_percentage;
		void CalculateStats();

		int wander_every_seconds, wander_points_left;
		bool do_respawn;
		int x_spawn_pos, y_spawn_pos;
		int NPC_id;
		int seconds_to_respawn;

		CZone *zone;

	protected:
		bool mayDoAnythingAffectingSpellActionWithoutAborting() const;
		bool mayDoAnythingAffectingSpellActionWithAborting() const;

	private:
		// NPC attributes
		std::string name;

		uint16_t strength;
		uint16_t dexterity;
		uint16_t vitality;
		uint16_t intellect;
		uint16_t wisdom;
		uint16_t max_health;
		uint16_t current_health;
		uint16_t max_mana;
		uint16_t current_mana;
		uint16_t max_energy;
		uint16_t current_energy;

		uint16_t armor;


		uint16_t wander_radius;
		uint16_t min_damage, max_damage;
		uint8_t alignment, level;

		// character attributes
		uint64_t experience;

		// casting spells / executing actions
		bool isPreparing;
		CSpellActionBase *curSpellAction;
		uint32_t preparationStartTime, preparationCurrentTime;
		float preparationPercentage;
        CInterface *activeGUI;


};

#endif
