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

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"
#include "inventory.h"

class Player : public CCharacter
{
	private:
		uint32_t ticketForItemTooltip;
		uint32_t ticketForSpellTooltip;
		Inventory inventory;
		uint8_t movementSpeed;

	public:
		Player();
		bool isPlayer() const;
		void Move();
		void Draw();
		void Die();
		Direction GetDirection();

		uint16_t getModifiedArmor() const;
		uint16_t getModifiedDamageModifierPoints() const;
		uint16_t getModifiedHitModifierPoints() const;
		uint16_t getModifiedEvadeModifierPoints() const;
		uint16_t getModifiedParryModifierPoints() const;
		uint16_t getModifiedBlockModifierPoints() const;
		uint16_t getModifiedMeleeCriticalModifierPoints() const;
		uint16_t getModifiedResistElementModifierPoints( ElementType::ElementType elementType ) const;
		uint16_t getModifiedSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
		uint16_t getModifiedSpellCriticalModifierPoints() const;

		uint16_t getModifiedStrength() const;
		uint16_t getModifiedDexterity() const;
		uint16_t getModifiedVitality() const;
		uint16_t getModifiedIntellect() const;
		uint16_t getModifiedWisdom() const;

		uint16_t getModifiedMaxHealth() const;
		uint16_t getModifiedMaxMana() const;
		uint16_t getModifiedMaxFatigue() const;

		uint16_t getModifiedHealthRegen() const;
		uint16_t getModifiedManaRegen() const;
		uint16_t getModifiedFatigueRegen() const;

		uint16_t getModifiedMinDamage() const;
		uint16_t getModifiedMaxDamage() const;

		void setTicketForItemTooltip ();
		void setTicketForSpellTooltip ();
		uint32_t getTicketForItemTooltip() const;
		uint32_t getTicketForSpellTooltip() const;

		Inventory* getInventory();
		void clearInventory();

		bool isSpellInscribedInSpellbook( CSpellActionBase *spell ) const;
		bool canWearArmorType( Item *item ) const;

		std::string getSaveText() const;

		void setMovementSpeed( uint8_t n );
};

#endif // __PLAYER_H__

