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

std::vector<Item*> allItems;

namespace DawnInterface
{
	Item* createNewItem(std::string name,
	                    int sizeX,
	                    int sizeY,
	                    std::string symbolFile,
	                    ItemQuality::ItemQuality itemQuality,
	                    EquipPosition::EquipPosition equipPos,
	                    ItemType::ItemType itemType,
	                    ArmorType::ArmorType armorType,
	                    WeaponType::WeaponType weaponType )
	{
		Item *newItem = new Item( name, sizeX, sizeY, symbolFile, itemQuality, equipPos, itemType, armorType, weaponType );
		allItems.push_back( newItem );
		return newItem;
	}
}

Item::Item( std::string name_, size_t sizeX_, size_t sizeY_, std::string symbolFile,
        ItemQuality::ItemQuality itemQuality_,
        EquipPosition::EquipPosition equipPosition_,
        ItemType::ItemType itemType_,
        ArmorType::ArmorType armorType_,
        WeaponType::WeaponType weaponType_ )
	:	name( name_ ),
		sizeX( sizeX_ ),
		sizeY( sizeY_ ),
		itemQuality ( itemQuality_ ),
		itemType ( itemType_ ),
		armorType ( armorType_ ),
		weaponType ( weaponType_ ),
		equipPosition ( equipPosition_ ),
		strengthModifier( 0 ),
		dexterityModifier( 0 ),
		intellectModifier( 0 ),
		vitalityModifier( 0 ),
		wisdomModifier( 0 ),
		healthModifier( 0 ),
		manaModifier( 0 ),
		energyModifier( 0 ),
		armorModifier( 0 ),
		damageModifier( 0 ),
		hitModifier( 0 ),
		evadeModifier( 0 ),
		blockModifier( 0 ),
		meleeCriticalModifier( 0 ),
		resistElementModifier( NULL ),
		resistAllModifier( 0 ),
		spellEffectElementModifier( NULL ),
		spellEffectAllModifier( 0 ),
		spellCriticalModifier( 0 ),
		minDamage( 0 ),
		maxDamage( 0 ),
		levelReq( 0 )
{
	resistElementModifier = new int16_t[ static_cast<size_t>( ElementType::Count ) ];
	spellEffectElementModifier = new int16_t[ static_cast<size_t>( ElementType::Count ) ];
	for ( size_t curElement=0; curElement<static_cast<size_t>( ElementType::Count ); ++curElement ) {
		resistElementModifier[ curElement ] = 0;
		spellEffectElementModifier[ curElement ] = 0;
	}
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

int16_t Item::getDamageModifierPoints() const
{
	return damageModifier;
}

int16_t Item::getHitModifierPoints() const
{
	return hitModifier;
}

int16_t Item::getEvadeModifierPoints() const
{
	return evadeModifier;
}

int16_t Item::getBlockModifierPoints() const
{
	return blockModifier;
}

int16_t Item::getMeleeCriticalModifierPoints() const
{
	return meleeCriticalModifier;
}

int16_t Item::getResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return resistElementModifier[ static_cast<size_t>(elementType) ];
}

int16_t Item::getResistAllModifierPoints() const
{
	return resistAllModifier;
}

int16_t Item::getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return spellEffectElementModifier[ static_cast<size_t>(elementType) ];
}

int16_t Item::getSpellEffectAllModifierPoints() const
{
	return spellEffectAllModifier;
}

int16_t Item::getSpellCriticalModifierPoints() const
{
	return spellCriticalModifier;
}

uint8_t Item::getMinDamage() const
{
    return minDamage;
}

uint8_t Item::getMaxDamage() const
{
    return maxDamage;
}

uint8_t Item::getLevelReq() const
{
    return levelReq;
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

void Item::setDamageModifierPoints( int16_t damageModifierPoints )
{
	this->damageModifier = damageModifierPoints;
}

void Item::setHitModifierPoints( int16_t hitModifierPoints )
{
	this->hitModifier = hitModifierPoints;
}

void Item::setEvadeModifierPoints( int16_t evadeModifierPoints )
{
	this->evadeModifier = evadeModifierPoints;
}

void Item::setBlockModifierPoints( int16_t blockModifierPoints )
{
	this->blockModifier = blockModifierPoints;
}

void Item::setMeleeCriticalModifierPoints( int16_t meleeCriticalModifierPoints )
{
	this->meleeCriticalModifier = meleeCriticalModifierPoints;
}

void Item::setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints )
{
	this->resistElementModifier[ static_cast<size_t>( elementType ) ] = resistModifierPoints;
}

void Item::setResistAllModifierPoints( int16_t resistAllModifierPoints )
{
	this->resistAllModifier = resistAllModifierPoints;
}

void Item::setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints )
{
	this->spellEffectElementModifier[ static_cast<size_t>( elementType ) ] = spellEffectElementModifierPoints;
}

void Item::setSpellEffectAllModifierPoints( int16_t spellEffectAllModifierPoints )
{
	this->spellEffectAllModifier = spellEffectAllModifierPoints;
}

void Item::setSpellCriticalModifierPoints( int16_t spellCriticalModifierPoints )
{
	this->spellCriticalModifier = spellCriticalModifierPoints;
}

void Item::setMinDamage( uint8_t minDamage_ )
{
    minDamage = minDamage_;
}

void Item::setMaxDamage( uint8_t maxDamage_ )
{
    maxDamage = maxDamage_;
}

void Item::setLevelReq( uint8_t levelReq_ )
{
    levelReq = levelReq_;
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
        case ArmorType::NO_ARMOR: 
            dawn_debug_fatal( "Armor item of type NO_ARMOR found. This should not be." );
            abort();
        break;
    }
    dawn_debug_fatal("Reached end of Item::getArmorTypeText without finding a suitable armor type. This should not be." );
	abort();
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
        case WeaponType::ONEHAND_AXE:
            return "One handed axe";
        break;
        case WeaponType::TWOHAND_AXE:
            return "Two handed axe";
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
		case WeaponType::NO_WEAPON:
			dawn_debug_fatal( "Armor item of type NO_ARMOR found. This should not be." );
			abort();
		break;
    }
	dawn_debug_fatal( "Reached end of getWeaponTypeText without finding a suitable weapon type. This should not be." );
	abort();
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
        case EquipPosition::BELT:
            return "Belt";
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
        case EquipPosition::NONE:
            return "Unequippable";
        break;
    }
	dawn_debug_fatal("Reached end of Item::getEquipPositionText without finding a suitable position. This should not be");
    abort();
}
