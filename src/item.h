/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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
#include "elements.h"
#include "stats.h"
#include "CCharacter.h"

class CSpell;

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

    inline std::string getEquipPositionText( EquipPosition::EquipPosition equipPosition )
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
        dawn_debug_fatal("Reached end of EquipPosition::getEquipPositionText without finding a suitable position. This should not be");
        abort();
    }
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

    inline ArmorType::ArmorType getHighestArmorTypeByClass( CharacterClass::CharacterClass characterClass )
    {
        switch ( characterClass )
        {
            case CharacterClass::Liche:
                return ArmorType::CLOTH;
            break;
            case CharacterClass::Ranger:
                return ArmorType::LEATHER;
            break;
            case CharacterClass::Warrior:
                return ArmorType::PLATE;
            break;
            case CharacterClass::NOCLASS:
                dawn_debug_fatal( "getHighestArmorTypeByClass caught NOCLASS. This shouldn't be." );
                abort();
            break;
            case CharacterClass::ANYCLASS:
                dawn_debug_fatal( "getHighestArmorTypeByClass caught ANYCLASS. This shouldn't be." );
                abort();
            break;
        }
        dawn_debug_fatal( "getHighestArmorTypeByClass caught an unknown class. This *REALLY* shouldn't be." );
        abort();
    }

    inline std::string getArmorTypeText( ArmorType::ArmorType armorType )
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
        dawn_debug_fatal("Reached end of ArmorType::getArmorTypeText() without finding a suitable armor type. This should not be." );
        abort();
    }
}

namespace WeaponType
{
    enum WeaponType
    {
        NO_WEAPON       = 0x01,
        ONEHAND_SWORD   = 0x02,
        TWOHAND_SWORD   = 0x04,
        DAGGER          = 0x08,
        STAFF           = 0x10,
        ONEHAND_CLUB    = 0x20,
        TWOHAND_CLUB    = 0x40,
        WAND            = 0x80,
        SPELLBOOK       = 0x100, // offhand spellbooks for caster classes.
        ONEHAND_MACE    = 0x200,
        TWOHAND_MACE    = 0x400,
        ONEHAND_AXE     = 0x800,
        TWOHAND_AXE     = 0x1000,
        BOW             = 0x2000,
        SLINGSHOT       = 0x4000,
        CROSSBOW        = 0x8000,
        SHIELD          = 0x10000,
        COUNT           = 0x20000
    };

    inline std::string getWeaponTypeText ( WeaponType::WeaponType weaponType )
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
                dawn_debug_fatal( "Weapon item of type NO_WEAPON found. This should not be." );
                abort();
            break;
            case WeaponType::COUNT:
                dawn_debug_fatal( "Weapon item of type COUNT found. This should not be." );
                abort();
            break;
        }
        dawn_debug_fatal( "Reached end of WeaponType::getWeaponTypeText() without finding a suitable weapon type. This should not be." );
        abort();
    }
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

namespace TriggerType
{
    /// defined here is the different types of trigger we can have for our triggerSpells. Many more could be added later on. Example: BLOCKING, AVOIDING, PARRY, CRITICALHIT, etc...
    enum TriggerType
    {
        TAKING_DAMAGE,
        EXECUTING_ACTION
    };
}

class TriggerSpellOnItem
{
    public:
        TriggerSpellOnItem( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType, bool castOnSelf );
        CSpellActionBase *getSpellToTrigger() const;
        float getChanceToTrigger() const;
        TriggerType::TriggerType getTriggerType() const;
        bool getCastOnSelf() const;
        std::string getTooltipText() const;

    private:
        CSpellActionBase *spellToTrigger;
        float chanceToTrigger;
        TriggerType::TriggerType triggerType;
        bool castOnSelf;
};

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
        CSpell *getSpell() const;

        void setStats( StatsType::StatsType statsType, int16_t amount );
        void setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints );
		void setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints );
		void setMinDamage( uint8_t minDamage );
        void setMaxDamage( uint8_t maxDamage );
        void setValue( uint32_t newValue );
        void setRequiredLevel( uint8_t requiredLevel );
        void setSpell( CSpell *newSpell );

        ///\brief This section handles the spells that can be triggered from actions on the item
        void addTriggerSpellOnSelf( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType );
        void addTriggerSpellOnTarget( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType );
        std::vector<TriggerSpellOnItem*> getTriggerSpells() const;

        size_t getMaxStackSize() const;
        void setMaxStackSize( size_t maxStackSize );
        bool isItemStackable() const;

		size_t getSizeX() const;
		size_t getSizeY() const;

        ItemQuality::ItemQuality getItemQuality() const;
		ItemType::ItemType getItemType() const;
		ArmorType::ArmorType getArmorType() const;
		WeaponType::WeaponType getWeaponType() const;
		EquipPosition::EquipPosition getEquipPosition() const;

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

		std::vector <TriggerSpellOnItem*> triggerSpells;

		bool useableItem;

		int16_t *statsModifier;
		int16_t *resistElementModifier;
		int16_t *spellEffectElementModifier;

        uint8_t minDamage;
        uint8_t maxDamage;

        size_t maxStackSize;

        uint8_t requiredLevel;

        uint32_t value;

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
