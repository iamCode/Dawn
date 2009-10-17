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

#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include "CTexture.h"

namespace ItemSlot
{
    enum ItemSlot
    {
        HEAD,
        AMULET,
        MAIN_HAND,
        OFF_HAND,
        BELT,
        LEGS,
        SHOULDER,
        CHEST,
        GLOVES,
        CLOAK,
        BOOTS,
        RING_ONE,
        RING_TWO,
        COUNT // this is always the last and gives the size of the enum
    };
}

namespace EquipPosition
{
    enum EquipPosition
    {
        MAIN_HAND,
        OFF_HAND,
        CHEST,
        LEGS,
        BELT,
        BOOTS,
        RING,
        GLOVES,
        HEAD,
        CLOAK,
        AMULET,
        SHOULDER,
        NONE
    };
}

namespace ItemType
{
    enum ItemType
    {
        QUESTITEM,
        MISCELLANEOUS,
        ARMOR,
        WEAPON,
        JEWELRY,
        COUNT
    };
}

namespace ArmorType
{
    enum ArmorType
    {
        NO_ARMOR,
        CLOTH,
        LEATHER,
        MAIL,
        PLATE,
    };
}

namespace WeaponType
{
    enum WeaponType
    {
        NO_WEAPON,
        ONEHAND_SWORD,
        TWOHAND_SWORD,
        DAGGER,
        STAFF,
        ONEHAND_CLUB,
        TWOHAND_CLUB,
        WAND,
        SPELLBOOK, // offhand spellbooks for caster classes.
        ONEHAND_MACE,
        TWOHAND_MACE,
        ONEHAND_AXE,
        TWOHAND_AXE,
        BOW,
        SLINGSHOT,
        CROSSBOW,
        SHIELD,
    };
}

namespace ItemQuality
{
    enum ItemQuality
    {
        POOR,
        NORMAL,
        ENHANCED,
        RARE,
        LORE,
    };
}

class Item
{
	public:
		Item( std::string name, size_t sizeX, size_t sizeY, std::string symbolFile,
		ItemQuality::ItemQuality itemQuality,
		EquipPosition::EquipPosition equipPosition,
		ItemType::ItemType itemType,
		ArmorType::ArmorType armorType,
		WeaponType::WeaponType weaponType );
		// probably like CCharacter: baseOnType

		std::string getName() const;
        std::string getDescription() const;
        void setDescription( std::string description );

        int16_t getStrength() const;
        int16_t getDexterity() const;
        int16_t getIntellect() const;
        int16_t getVitality() const;
        int16_t getWisdom() const;
        int16_t getHealth() const;
        int16_t getMana() const;
        int16_t getEnergy() const;
        int16_t getArmor() const;

        uint8_t getMinDamage() const;
        uint8_t getMaxDamage() const;

        void setStrength( int16_t strength );
		void setDexterity( int16_t dexterity );
		void setIntellect( int16_t intellect );
		void setVitality( int16_t vitality );
		void setWisdom( int16_t wisdom );
		void setHealth( int16_t health );
		void setMana( int16_t mana );
		void setEnergy( int16_t energy );
		void setArmor( int16_t armor );
        void setMinDamage( uint8_t minDamage );
        void setMaxDamage( uint8_t maxDamage );

		size_t getSizeX() const;
		size_t getSizeY() const;

        ItemQuality::ItemQuality getItemQuality() const;
		ItemSlot::ItemSlot getItemSlot() const;
		ItemType::ItemType getItemType() const;
		ArmorType::ArmorType getArmorType() const;
		WeaponType::WeaponType getWeaponType() const;
		EquipPosition::EquipPosition getEquipPosition() const;

		std::string getArmorTypeText() const;
		std::string getWeaponTypeText() const;
		std::string getEquipPositionText() const;

		CTexture* getSymbolTexture();

	private:
		std::string name;
		std::string description;

		size_t sizeX;
		size_t sizeY;

		ItemQuality::ItemQuality itemQuality;
		ItemType::ItemType itemType;
		ArmorType::ArmorType armorType;
		WeaponType::WeaponType weaponType;
		EquipPosition::EquipPosition equipPosition;

		int16_t strengthModifier;
        int16_t dexterityModifier;
        int16_t intellectModifier;
        int16_t vitalityModifier;
        int16_t wisdomModifier;
        int16_t healthModifier;
        int16_t manaModifier;
        int16_t energyModifier;
        int16_t armorModifier;

        uint8_t minDamage;
        uint8_t maxDamage;

		CTexture symbolTexture;
};

#endif // __ITEM_H__
