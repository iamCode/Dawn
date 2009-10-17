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

#include "item.h"

Item::Item( std::string name_, size_t sizeX_, size_t sizeY_, std::string symbolFile,
        ItemQuality::ItemQuality itemQuality_,
        EquipPosition::EquipPosition equipPosition_,
        ItemType::ItemType itemType_,
        ArmorType::ArmorType armorType_,
        WeaponType::WeaponType weaponType_ )
	:	name( name_ ),
		sizeX( sizeX_ ),
		sizeY( sizeY_ ),
		armorModifier( 0 ),
		minDamage( 0 ),
		maxDamage( 0 ),
		dexterityModifier( 0 ),
		intellectModifier( 0 ),
		strengthModifier( 0 ),
		vitalityModifier( 0 ),
		wisdomModifier( 0 ),
		healthModifier( 0 ),
		manaModifier( 0 ),
		energyModifier( 0 ),
		itemQuality ( itemQuality_ ),
		equipPosition ( equipPosition_ ),
		itemType ( itemType_ ),
		armorType ( armorType_ ),
		weaponType ( weaponType_ )
{
	symbolTexture.texture.reserve(1);
	symbolTexture.LoadIMG( symbolFile, 0 );
}

std::string Item::getName() const
{
	return name;
}

size_t Item::getSizeX() const
{
	return sizeX;
}

size_t Item::getSizeY() const
{
	return sizeY;
}

CTexture* Item::getSymbolTexture()
{
	return &symbolTexture;
}

ItemQuality::ItemQuality Item::getItemQuality() const
{
    return itemQuality;
}

ItemType::ItemType Item::getItemType() const
{
    return itemType;
}

ArmorType::ArmorType Item::getArmorType() const
{
    return armorType;
}

WeaponType::WeaponType Item::getWeaponType() const
{
    return weaponType;
}

EquipPosition::EquipPosition Item::getEquipPosition() const
{
    return equipPosition;
}

std::string Item::getDescription() const
{
    return description;
}

int16_t Item::getStrength() const
{
    return strengthModifier;
}

int16_t Item::getDexterity() const
{
    return dexterityModifier;
}

int16_t Item::getIntellect() const
{
    return intellectModifier;
}

int16_t Item::getVitality() const
{
    return vitalityModifier;
}

int16_t Item::getWisdom() const
{
    return wisdomModifier;
}

int16_t Item::getHealth() const
{
    return healthModifier;
}

int16_t Item::getMana() const
{
    return manaModifier;
}

int16_t Item::getEnergy() const
{
    return energyModifier;
}

int16_t Item::getArmor() const
{
    return armorModifier;
}

uint8_t Item::getMinDamage() const
{
    return minDamage;
}

uint8_t Item::getMaxDamage() const
{
    return maxDamage;
}

void Item::setStrength( int16_t strength )
{
    strengthModifier = strength;
}

void Item::setDexterity( int16_t dexterity )
{
    dexterityModifier = dexterity;
}


void Item::setIntellect( int16_t intellect )
{
    intellectModifier = intellect;
}

void Item::setVitality( int16_t vitality )
{
    vitalityModifier = vitality;
}

void Item::setWisdom( int16_t wisdom )
{
    wisdomModifier = wisdom;
}

void Item::setHealth( int16_t health )
{
    healthModifier = health;
}

void Item::setMana( int16_t mana )
{
    manaModifier = mana;
}

void Item::setEnergy( int16_t energy )
{
    energyModifier = energy;
}

void Item::setArmor( int16_t armor )
{
    armorModifier = armor;
}

void Item::setMinDamage( uint8_t minDamage_ )
{
    minDamage = minDamage_;
}

void Item::setMaxDamage( uint8_t maxDamage_ )
{
    maxDamage = maxDamage_;
}

void Item::setDescription ( std::string description_ )
{
    description = "\"" + description_ + "\"";
}

std::string Item::getArmorTypeText() const
{
    switch ( armorType )
    {
        case ArmorType::CLOTH:
            return "Cloth";
        break;
        case ArmorType::LEATHER:
            return "Leather";
        break;
        case ArmorType::MAIL:
            return "Mail";
        break;
        case ArmorType::PLATE:
            return "Plate";
        break;
    }
}

std::string Item::getWeaponTypeText() const
{
    switch ( weaponType )
    {
        case WeaponType::ONEHAND_SWORD:
            return "One handed sword";
        break;
        case WeaponType::TWOHAND_SWORD:
            return "Two handed sword";
        break;
        case WeaponType::DAGGER:
            return "Dagger";
        break;
        case WeaponType::STAFF:
            return "Staff";
        break;
        case WeaponType::ONEHAND_CLUB:
            return "One handed club";
        break;
        case WeaponType::TWOHAND_CLUB:
            return "Two handed club";
        break;
        case WeaponType::WAND:
            return "Wand";
        break;
        case WeaponType::SPELLBOOK:
            return "Spellbook";
        break;
        case WeaponType::ONEHAND_MACE:
            return "One handed mace";
        break;
        case WeaponType::TWOHAND_MACE:
            return "Two handed mace";
        break;
        case WeaponType::BOW:
            return "Bow";
        break;
        case WeaponType::SLINGSHOT:
            return "Slingshot";
        break;
        case WeaponType::CROSSBOW:
            return "Crossbow";
        break;
        case WeaponType::SHIELD:
            return "Shield";
        break;
    }
}

std::string Item::getEquipPositionText() const
{
    switch ( equipPosition )
    {
        case EquipPosition::MAIN_HAND:
            return "Main hand";
        break;
        case EquipPosition::OFF_HAND:
            return "Off hand";
        break;
        case EquipPosition::CHEST:
            return "Chest";
        break;
        case EquipPosition::LEGS:
            return "Legs";
        break;
        case EquipPosition::BOOTS:
            return "Boots";
        break;
        case EquipPosition::RING:
            return "Ring";
        break;
        case EquipPosition::GLOVES:
            return "Gloves";
        break;
        case EquipPosition::HEAD:
            return "Head";
        break;
        case EquipPosition::CLOAK:
            return "Cloak";
        break;
        case EquipPosition::AMULET:
            return "Amulet";
        break;
        case EquipPosition::SHOULDER:
            return "Shoulder";
        break;
    }
}
