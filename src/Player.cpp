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

#include <limits>
#include <cassert>

const uint16_t NULLABLE_ATTRIBUTE_MIN = 0;
const uint16_t NON_NULLABLE_ATTRIBUTE_MIN = 1;

Player::Player()
	:	inventory( Inventory( 10, 4 ) )
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

	InventoryItem *equippedShield = getInventory()->getItemAtSlot( ItemSlot::OFF_HAND );
	if ( equippedShield != NULL ) {
		Item *itemShield = equippedShield->getItem();
		float degrees = 0;
		CTexture *usedTexture = itemShield->getSymbolTexture();
		size_t itemWidth = itemShield->getSizeX() * 30;
		size_t itemHeight = 10;
		size_t xoffset = - (itemWidth/2);
		size_t yoffset = getWidth() / 2 - 5;

		switch( GetDirectionTexture() ) {
			case N:
				break;
			case NW:
				degrees += 45;
				break;
			case W:
				degrees += 90;
				break;
			case SW:
				degrees += 135;
				break;
			case S:
				degrees += 180;
				break;
			case SE:
				degrees -= 135;
				break;
			case E:
				degrees -= 90;
				break;
			case NE:
				degrees -= 45;
				break;
			default:
				break;
		}

		glPushMatrix();
		glTranslatef(getXPos() + (getWidth() / 2), getYPos() + (getHeight() / 2), 0.0f);
		glRotatef(degrees,0.0f,0.0f,1.0f);

		DrawingHelpers::mapTextureToRect( usedTexture->texture[0].texture,
										  xoffset, itemWidth,
			yoffset, itemHeight );
		glPopMatrix();
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

// GETTER_HELPER_MACRO( XXX ) creates a function XXXHelper that
// returns the attribute XXX from an item.
// this is needed for unifying the code for the getModfiedXXX functions
#define GETTER_HELPER_MACRO( GETFUNCNAME ) \
	static int16_t GETFUNCNAME##Helper( Item *item ) \
{ \
		return item->GETFUNCNAME(); \
}

GETTER_HELPER_MACRO( getStrength );
GETTER_HELPER_MACRO( getDexterity );
GETTER_HELPER_MACRO( getVitality );
GETTER_HELPER_MACRO( getIntellect );
GETTER_HELPER_MACRO( getWisdom );
GETTER_HELPER_MACRO( getHealth );
GETTER_HELPER_MACRO( getMana );
GETTER_HELPER_MACRO( getEnergy );
GETTER_HELPER_MACRO( getArmor );

GETTER_HELPER_MACRO( getMinDamage );
GETTER_HELPER_MACRO( getMaxDamage );

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

uint16_t Player::getModifiedArmor() const
{
    return getModifiedAttribute( inventory, getArmor(), &getArmorHelper, NULLABLE_ATTRIBUTE_MIN );
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

	// multiply with strength modifier
	double modifier = getDamageModifier();
	inventoryMinDamage *= modifier;

	return inventoryMinDamage;
}

uint16_t Player::getModifiedMaxDamage() const
{
	uint16_t inventoryMaxDamage = getModifiedAttribute( inventory, 0, &getMaxDamageHelper, getModifiedMinDamage() );

	// multiply with strength modifier
	double modifier = getDamageModifier();
	inventoryMaxDamage *= modifier;

	return inventoryMaxDamage;
}

