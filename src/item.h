/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include "CTexture.h"
#include "CSpell.h"
#include "elements.h"
#include "stats.h"

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
        SCROLL,
        POTION,
        FOOD,
        DRINK,
        NEWSPELL,
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
        PLATE
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
        SHIELD
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
        LORE
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
		WeaponType::WeaponType weaponType,
		bool loadSymbol = true );
		// probably like CCharacter: baseOnType

		std::string getName() const;
		std::string getID() const;
        std::string getDescription() const;
        void setDescription( std::string description );

        bool isUseable() const;
        std::string getUseableDescription() const;

        bool isTwoHandedWeapon() const;

		int16_t getStats( StatsType::StatsType statsType ) const;
		int16_t getResistElementModifierPoints( ElementType::ElementType elementType ) const;
		int16_t getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const;
        uint8_t getMinDamage() const;
        uint8_t getMaxDamage() const;
        uint32_t getValue() const;
        uint8_t getRequiredLevel() const;
        uint8_t getSpellCharges() const;
        CSpell *getSpell() const;

        void setStats( StatsType::StatsType statsType, int16_t amount );
        void setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints );
		void setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints );
		void setMinDamage( uint8_t minDamage );
        void setMaxDamage( uint8_t maxDamage );
        void setValue( uint32_t newValue );
        void setRequiredLevel( uint8_t requiredLevel );
        void setSpellCharges( uint8_t newSpellCharges );
        void reduceSpellCharges();
        void setSpell( CSpell *newSpell );

		size_t getSizeX() const;
		size_t getSizeY() const;

        ItemQuality::ItemQuality getItemQuality() const;
		ItemType::ItemType getItemType() const;
		ArmorType::ArmorType getArmorType() const;
		WeaponType::WeaponType getWeaponType() const;
		EquipPosition::EquipPosition getEquipPosition() const;

		std::string getArmorTypeText() const;
		std::string getWeaponTypeText() const;
		std::string getEquipPositionText() const;

		virtual CTexture* getSymbolTexture();

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

		bool useableItem;

		int16_t *statsModifier;
		int16_t *resistElementModifier;
		int16_t *spellEffectElementModifier;

        uint8_t minDamage;
        uint8_t maxDamage;

        uint8_t requiredLevel;

        uint32_t value;

        uint8_t spellCharges;
        CSpell *spell;

	protected:
		CTexture symbolTexture;
};

class GoldHeap : public Item
{
	public:
		GoldHeap( size_t coins_ );
		size_t numCoins() const;

	private:
		size_t coins;
};

#endif // __ITEM_H__
