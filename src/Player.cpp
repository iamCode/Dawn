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

#include "Player.h"
#include "inventory.h"
#include "StatsSystem.h"

#include <limits>
#include <cassert>

const uint16_t NULLABLE_ATTRIBUTE_MIN = 0;
const uint16_t NON_NULLABLE_ATTRIBUTE_MIN = 1;

extern Player character;
extern std::vector<Item*> groundItems;
extern std::vector<std::pair<int,int> > groundPositions;

namespace DawnInterface
{
	void giveItemToPlayer( Item *item )
	{
		Inventory *playerInventory = character.getInventory();
		bool wasInserted = playerInventory->insertItem( item );
		if ( ! wasInserted )
		{
			groundItems.push_back( item );
			groundPositions.push_back( std::pair<int,int>( character.getXPos(), character.getYPos() ) );
		}
	}
}

Player::Player()
	:	inventory( Inventory( 10, 4, this ) )
{
    setName("Enylyn");
}

CCharacter* Player::getTarget() const
{
	return Target;
}

void Player::Draw()
{
	CalculateStats();
	direction_texture = GetDirectionTexture();
	if (alive == true) {
		texture->DrawTexture(x_pos,y_pos,direction_texture);
	}
}

Direction Player::GetDirection()
{
	keys = SDL_GetKeyState(NULL);

	if (keys[SDLK_UP]) {
		if (keys[SDLK_LEFT]) {
			return NW;
		} else if (keys[SDLK_RIGHT]) {
			return NE;
		} else {
			return N;
		}
	}

	if (keys[SDLK_DOWN]) {
		if (keys[SDLK_LEFT]) {
			return SW;
		} else if (keys[SDLK_RIGHT]) {
			return SE;
		} else {
			return S;
		}
	}

	if (keys[SDLK_LEFT]) {
		return W;
	}

	if (keys[SDLK_RIGHT]) {
		return E;
	}

	return STOP;
}

Inventory* Player::getInventory()
{
	return &inventory;
}

void Player::setTarget(CCharacter *newTarget)
{
	Target = newTarget;
}

void Player::regenerateLifeMana(uint32_t regenPoints)
{
    /** Regenerate life, mana and energy every 500 ms.
	For now, we're regenerating a static amount.
	In the future this will be calculated based on characters stats. **/

	remainingRegenPoints += regenPoints;

	if ( remainingRegenPoints > 500 ) {
		modifyCurrentMana( 1 );
		modifyCurrentHealth( 1 );
		modifyCurrentEnergy( 1 );
		remainingRegenPoints -= 500;
	}
}

void Player::Move()
{
	CCharacter::Move();
}

bool Player::isPlayer() const
{
	return true;
}

static int16_t getStrengthHelper( Item * item ) { return item->getStrength(); }
static int16_t getDexterityHelper( Item * item ) { return item->getDexterity(); }
static int16_t getVitalityHelper( Item * item ) { return item->getVitality(); }
static int16_t getIntellectHelper( Item * item ) { return item->getIntellect(); }
static int16_t getWisdomHelper( Item * item ) { return item->getWisdom(); }
static int16_t getHealthHelper( Item * item ) { return item->getHealth(); }
static int16_t getManaHelper( Item * item ) { return item->getMana(); }
static int16_t getEnergyHelper( Item * item ) { return item->getEnergy(); }
static int16_t getArmorHelper( Item * item ) { return item->getArmor(); }
static int16_t getDamageModifierPointsHelper( Item * item ) { return item->getDamageModifierPoints(); }
static int16_t getHitModifierPointsHelper( Item * item ) { return item->getHitModifierPoints(); }
static int16_t getEvadeModifierPointsHelper( Item * item ) { return item->getEvadeModifierPoints(); }
static int16_t getBlockModifierPointsHelper( Item * item ) { return item->getBlockModifierPoints(); }
static int16_t getMeleeCriticalModifierPointsHelper( Item * item ) { return item->getMeleeCriticalModifierPoints(); }
static int16_t getResistElementModifierPointsHelper( ElementType::ElementType elementType, Item * item ) { return item->getResistElementModifierPoints( elementType ) + item->getResistAllModifierPoints(); }
static int16_t getSpellEffectElementModifierPointsHelper( ElementType::ElementType elementType, Item * item ) { return item->getSpellEffectElementModifierPoints( elementType ) + item->getSpellEffectAllModifierPoints(); }
static int16_t getSpellCriticalModifierPointsHelper( Item * item ) { return item->getSpellCriticalModifierPoints(); }

static int16_t getMinDamageHelper( Item * item ) { return item->getMinDamage(); }
static int16_t getMaxDamageHelper( Item * item ) { return item->getMaxDamage(); }

static uint16_t getModifiedAttribute( const Inventory &inventory, uint16_t basicAttributeValue, int16_t (*getItemAttribute)( Item* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		Item *curItem = equippedItems[ curItemNr ]->getItem();
		assert( curItem != NULL );
		attributeModifier += getItemAttribute( curItem );
	}
	if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier < static_cast<int32_t>( minValue ) ) {
		return minValue;
	}
	else if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier > static_cast<int32_t>( maxValue ) ) {
		return maxValue;
	} else {
		return basicAttributeValue + attributeModifier;
	}
}

static uint16_t getModifiedAttribute( ElementType::ElementType elementType, const Inventory &inventory, uint16_t basicAttributeValue, int16_t (*getItemAttribute)( ElementType::ElementType, Item* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		Item *curItem = equippedItems[ curItemNr ]->getItem();
		assert( curItem != NULL );
		attributeModifier += getItemAttribute( elementType, curItem );
	}
	if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier < static_cast<int32_t>( minValue ) ) {
		return minValue;
	}
	else if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier > static_cast<int32_t>( maxValue ) ) {
		return maxValue;
	} else {
		return basicAttributeValue + attributeModifier;
	}
}


uint16_t Player::getModifiedArmor() const
{
	return getModifiedAttribute( inventory, getArmor(), &getArmorHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateDamageReductionPoints( this );
}

uint16_t Player::getModifiedDamageModifierPoints() const
{
	return getModifiedAttribute( inventory, getDamageModifierPoints(), &getDamageModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateDamageModifierPoints( this );
}

uint16_t Player::getModifiedHitModifierPoints() const
{
	return getModifiedAttribute( inventory, getHitModifierPoints(), &getHitModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateHitModifierPoints( this );
}

uint16_t Player::getModifiedEvadeModifierPoints() const
{
	return getModifiedAttribute( inventory, getEvadeModifierPoints(), &getEvadeModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateEvadeModifierPoints( this );
}

uint16_t Player::getModifiedBlockModifierPoints() const
{
	return getModifiedAttribute( inventory, getBlockModifierPoints(), &getBlockModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateBlockModifierPoints( this );
}

uint16_t Player::getModifiedMeleeCriticalModifierPoints() const
{
	return getModifiedAttribute( inventory, getMeleeCriticalModifierPoints(), &getMeleeCriticalModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateMeleeCriticalModifierPoints( this );
}

uint16_t Player::getModifiedResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getModifiedAttribute( elementType, inventory, getResistElementModifierPoints( elementType ) + getResistAllModifierPoints(), &getResistElementModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateResistElementModifierPoints( elementType, this );
}

uint16_t Player::getModifiedSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getModifiedAttribute( elementType, inventory, getSpellEffectElementModifierPoints( elementType ) + getSpellEffectAllModifierPoints(), &getSpellEffectElementModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateSpellEffectElementModifierPoints( elementType, this );
}

uint16_t Player::getModifiedSpellCriticalModifierPoints() const
{
	return getModifiedAttribute( inventory, getSpellCriticalModifierPoints(), &getSpellCriticalModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateSpellCriticalModifierPoints( this );
}

uint16_t Player::getModifiedStrength() const
{
	return getModifiedAttribute( inventory, getStrength(), &getStrengthHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedDexterity() const
{
	return getModifiedAttribute( inventory, getDexterity(), &getDexterityHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedVitality() const
{
	return getModifiedAttribute( inventory, getVitality(), &getVitalityHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedIntellect() const
{
	return getModifiedAttribute( inventory, getIntellect(), &getIntellectHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedWisdom() const
{
	return getModifiedAttribute( inventory, getWisdom(), &getWisdomHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMaxHealth() const
{
	return getModifiedAttribute( inventory, getMaxHealth(), &getHealthHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMaxMana() const
{
	return getModifiedAttribute( inventory, getMaxMana(), &getManaHelper, NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMaxEnergy() const
{
	return getModifiedAttribute( inventory, getMaxEnergy(), &getEnergyHelper, NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMinDamage() const
{
	uint16_t inventoryMinDamage = getModifiedAttribute( inventory, 0, &getMinDamageHelper, NON_NULLABLE_ATTRIBUTE_MIN );
	return inventoryMinDamage;
}

uint16_t Player::getModifiedMaxDamage() const
{
	uint16_t inventoryMaxDamage = getModifiedAttribute( inventory, 0, &getMaxDamageHelper, getModifiedMinDamage() );
	return inventoryMaxDamage;
}

