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
	cleanupActiveSpells();
	direction_texture = GetDirectionTexture();
	ActivityType::ActivityType curActivity = getCurActivity();
	if (alive == true) {
		int drawX = x_pos;
		int drawY = y_pos;
		if ( getUseBoundingBox() ) {
			drawX -= getBoundingBoxX();
			drawY -= getBoundingBoxY();
		}
		texture[ static_cast<size_t>(curActivity) ]->DrawTexture(drawX,drawY,direction_texture);
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
    /** Regenerate life and mana every 500 ms.
	For now, we're regenerating a static amount.
	In the future this will be calculated based on characters stats. **/

	remainingRegenPoints += regenPoints;

	if ( remainingRegenPoints > 500 ) {
		modifyCurrentMana( 1 );
		modifyCurrentHealth( 1 );
		remainingRegenPoints -= 500;
	}
}

void Player::Move()
{
	CCharacter::Move();
}

void Player::Die()
{
    alive = false;
}

bool Player::isPlayer() const
{
	return true;
}

/// helperfunctions for items.
static int16_t getItemStrengthHelper( Item * item ) { return item->getStats( StatsType::Strength ); }
static int16_t getItemDexterityHelper( Item * item ) { return item->getStats( StatsType::Dexterity ); }
static int16_t getItemVitalityHelper( Item * item ) { return item->getStats( StatsType::Vitality ); }
static int16_t getItemIntellectHelper( Item * item ) { return item->getStats( StatsType::Intellect ); }
static int16_t getItemWisdomHelper( Item * item ) { return item->getStats( StatsType::Wisdom ); }
static int16_t getItemHealthHelper( Item * item ) { return item->getStats( StatsType::Health ); }
static int16_t getItemManaHelper( Item * item ) { return item->getStats( StatsType::Mana ); }
static int16_t getItemArmorHelper( Item * item ) { return item->getStats( StatsType::Armor ); }
static int16_t getItemDamageModifierPointsHelper( Item * item ) { return item->getStats( StatsType::DamageModifier ); }
static int16_t getItemHitModifierPointsHelper( Item * item ) { return item->getStats( StatsType::HitModifier ); }
static int16_t getItemEvadeModifierPointsHelper( Item * item ) { return item->getStats( StatsType::EvadeModifier ); }
static int16_t getItemBlockModifierPointsHelper( Item * item ) { return item->getStats( StatsType::BlockModifier ); }
static int16_t getItemMeleeCriticalModifierPointsHelper( Item * item ) { return item->getStats( StatsType::MeleeCritical ); }
static int16_t getItemResistElementModifierPointsHelper( ElementType::ElementType elementType, Item * item ) { return item->getResistElementModifierPoints( elementType ) + item->getStats( StatsType::ResistAll ); }
static int16_t getItemSpellEffectElementModifierPointsHelper( ElementType::ElementType elementType, Item * item ) { return item->getSpellEffectElementModifierPoints( elementType ) + item->getStats( StatsType::SpellEffectAll ); }
static int16_t getItemSpellCriticalModifierPointsHelper( Item * item ) { return item->getStats( StatsType::SpellCritical ); }

static int16_t getItemMinDamageHelper( Item * item ) { return item->getMinDamage(); }
static int16_t getItemMaxDamageHelper( Item * item ) { return item->getMaxDamage(); }

/// helperfunctions for spells (buffs / debuffs)
static int16_t getSpellStrengthHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Strength ); }
static int16_t getSpellDexterityHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Dexterity ); }
static int16_t getSpellVitalityHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Vitality ); }
static int16_t getSpellIntellectHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Intellect ); }
static int16_t getSpellWisdomHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Wisdom ); }
static int16_t getSpellHealthHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Health ); }
static int16_t getSpellManaHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Mana ); }
static int16_t getSpellArmorHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::Armor ); }
static int16_t getSpellDamageModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::DamageModifier ); }
static int16_t getSpellHitModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::HitModifier ); }
static int16_t getSpellEvadeModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::EvadeModifier ); }
static int16_t getSpellBlockModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::BlockModifier ); }
static int16_t getSpellMeleeCriticalModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::MeleeCritical ); }
static int16_t getSpellResistElementModifierPointsHelper( ElementType::ElementType elementType, GeneralBuffSpell *spell ) { return spell->getResistElementModifierPoints( elementType ) + spell->getStats( StatsType::ResistAll ); }
static int16_t getSpellSpellEffectElementModifierPointsHelper( ElementType::ElementType elementType, GeneralBuffSpell *spell ) { return spell->getSpellEffectElementModifierPoints( elementType ) + spell->getStats( StatsType::SpellEffectAll ); }
static int16_t getSpellSpellCriticalModifierPointsHelper( GeneralBuffSpell *spell ) { return spell->getStats( StatsType::SpellCritical ); }

static int16_t getSpellMinDamageHelper( GeneralBuffSpell *spell ) { return 0; } // not used yet
static int16_t getSpellMaxDamageHelper( GeneralBuffSpell *spell ) { return 0; } // not used yet


static uint16_t getModifiedAttribute( const Inventory &inventory, const CCharacter *character, uint16_t basicAttributeValue, int16_t (*getItemAttribute)( Item* ), int16_t (*getSpellAttribute)( GeneralBuffSpell* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		Item *curItem = equippedItems[ curItemNr ]->getItem();
		assert( curItem != NULL );
		attributeModifier += getItemAttribute( curItem );
	}

	std::vector<std::pair<GeneralBuffSpell*, uint32_t> > activeSpells;
    activeSpells = character ->getActiveSpells();
    size_t numSpells = activeSpells.size();
    for ( size_t curSpellNr=0; curSpellNr<numSpells; ++curSpellNr ) {
        GeneralBuffSpell* curSpell = activeSpells[ curSpellNr ].first;
        assert( curSpell != NULL );
        attributeModifier += getSpellAttribute( curSpell );
    }

    std::cout << std::endl;

	if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier < static_cast<int32_t>( minValue ) ) {
		return minValue;
	}
	else if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier > static_cast<int32_t>( maxValue ) ) {
		return maxValue;
	} else {
		return basicAttributeValue + attributeModifier;
	}
}

static uint16_t getModifiedAttribute( ElementType::ElementType elementType, const Inventory &inventory, const CCharacter *character, uint16_t basicAttributeValue, int16_t (*getItemAttribute)( ElementType::ElementType, Item* ), int16_t (*getSpellAttribute)( ElementType::ElementType, GeneralBuffSpell* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	for ( size_t curItemNr=0; curItemNr<numItems; ++curItemNr ) {
		Item *curItem = equippedItems[ curItemNr ]->getItem();
		assert( curItem != NULL );
		attributeModifier += getItemAttribute( elementType, curItem );
	}

    std::vector<std::pair<GeneralBuffSpell*, uint32_t> > activeSpells;
    size_t numSpells = activeSpells.size();
    activeSpells = character->getActiveSpells();
    for ( size_t curSpellNr=0; curSpellNr<numSpells; ++curSpellNr ) {
        GeneralBuffSpell* curSpell = activeSpells[ curSpellNr ].first;
        assert( curSpell != NULL );
        attributeModifier += getSpellAttribute( elementType, curSpell );
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
	return getModifiedAttribute( inventory, this, getArmor(), &getItemArmorHelper, &getSpellArmorHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateDamageReductionPoints( this );
}

uint16_t Player::getModifiedDamageModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getDamageModifierPoints(), &getItemDamageModifierPointsHelper, &getSpellDamageModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateDamageModifierPoints( this );
}

uint16_t Player::getModifiedHitModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getHitModifierPoints(), &getItemHitModifierPointsHelper, &getSpellHitModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateHitModifierPoints( this );
}

uint16_t Player::getModifiedEvadeModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getEvadeModifierPoints(), &getItemEvadeModifierPointsHelper, &getSpellEvadeModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateEvadeModifierPoints( this );
}

uint16_t Player::getModifiedBlockModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getBlockModifierPoints(), &getItemBlockModifierPointsHelper, &getSpellBlockModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateBlockModifierPoints( this );
}

uint16_t Player::getModifiedMeleeCriticalModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getMeleeCriticalModifierPoints(), &getItemMeleeCriticalModifierPointsHelper, &getSpellMeleeCriticalModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateMeleeCriticalModifierPoints( this );
}

uint16_t Player::getModifiedResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getModifiedAttribute( elementType, inventory, this, getResistElementModifierPoints( elementType ) + getResistAllModifierPoints(), &getItemResistElementModifierPointsHelper, &getSpellResistElementModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateResistElementModifierPoints( elementType, this );
}

uint16_t Player::getModifiedSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getModifiedAttribute( elementType, inventory, this, getSpellEffectElementModifierPoints( elementType ) + getSpellEffectAllModifierPoints(), &getItemSpellEffectElementModifierPointsHelper, &getSpellSpellEffectElementModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateSpellEffectElementModifierPoints( elementType, this );
}

uint16_t Player::getModifiedSpellCriticalModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getSpellCriticalModifierPoints(), &getItemSpellCriticalModifierPointsHelper, &getSpellSpellCriticalModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateSpellCriticalModifierPoints( this );
}

uint16_t Player::getModifiedStrength() const
{
	return getModifiedAttribute( inventory, this, getStrength(), &getItemStrengthHelper, &getSpellStrengthHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedDexterity() const
{
	return getModifiedAttribute( inventory, this, getDexterity(), &getItemDexterityHelper, &getSpellDexterityHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedVitality() const
{
	return getModifiedAttribute( inventory, this, getVitality(), &getItemVitalityHelper, &getSpellVitalityHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedIntellect() const
{
	return getModifiedAttribute( inventory, this, getIntellect(), &getItemIntellectHelper, &getSpellIntellectHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedWisdom() const
{
	return getModifiedAttribute( inventory, this, getWisdom(), &getItemWisdomHelper, &getSpellWisdomHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMaxHealth() const
{
	return getModifiedAttribute( inventory, this, getMaxHealth(), &getItemHealthHelper, &getSpellHealthHelper, NON_NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMaxMana() const
{
	return getModifiedAttribute( inventory, this, getMaxMana(), &getItemManaHelper, &getSpellManaHelper, NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedMinDamage() const
{
	uint16_t inventoryMinDamage = getModifiedAttribute( inventory, this, 0, &getItemMinDamageHelper, &getSpellMinDamageHelper, NON_NULLABLE_ATTRIBUTE_MIN );
	return inventoryMinDamage;
}

uint16_t Player::getModifiedMaxDamage() const
{
	uint16_t inventoryMaxDamage = getModifiedAttribute( inventory, this, 0, &getItemMaxDamageHelper, &getSpellMaxDamageHelper, getModifiedMinDamage() );
	return inventoryMaxDamage;
}

