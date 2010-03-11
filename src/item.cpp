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

#include "item.h"
#include <memory>

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
        WeaponType::WeaponType weaponType_, bool loadSymbol )
	:	name( name_ ),
		sizeX( sizeX_ ),
		sizeY( sizeY_ ),
		itemQuality ( itemQuality_ ),
		itemType ( itemType_ ),
		armorType ( armorType_ ),
		weaponType ( weaponType_ ),
		equipPosition ( equipPosition_ ),
		useableItem( false ),
		statsModifier( NULL ),
		resistElementModifier( NULL ),
		spellEffectElementModifier( NULL ),
		minDamage( 0 ),
		maxDamage( 0 ),
		levelReq( 0 ),
		value( 0 ),
		spellCharges( 0 ),
		spell( NULL )
{
	resistElementModifier = new int16_t[ static_cast<size_t>( ElementType::Count ) ];
	spellEffectElementModifier = new int16_t[ static_cast<size_t>( ElementType::Count ) ];
	statsModifier = new int16_t[ static_cast<size_t>( StatsType::Count ) ];
	for ( size_t curElement=0; curElement<static_cast<size_t>( ElementType::Count ); ++curElement ) {
		resistElementModifier[ curElement ] = 0;
		spellEffectElementModifier[ curElement ] = 0;
	}
	for (size_t curStat=0; curStat<static_cast<size_t>( StatsType::Count ); ++curStat )
	{
	    statsModifier[ curStat ] = 0;
	}

	symbolTexture.texture.reserve(1);
	// note: This is for use in derived classes that set their own texture ID only
	if ( loadSymbol ) {
		symbolTexture.LoadIMG( symbolFile, 0 );
	}

	if ( itemType == ItemType::DRINK
	  || itemType == ItemType::FOOD
	  || itemType == ItemType::POTION
	  || itemType == ItemType::NEWSPELL
	  || itemType == ItemType::SCROLL )
    {
        useableItem = true;
    }
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

int16_t Item::getStats( StatsType::StatsType statsType ) const
{
    return statsModifier[ static_cast<size_t>(statsType) ];
}

int16_t Item::getResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return resistElementModifier[ static_cast<size_t>(elementType) ];
}

int16_t Item::getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return spellEffectElementModifier[ static_cast<size_t>(elementType) ];
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

uint32_t Item::getValue() const
{
    return value;
}

uint8_t Item::getSpellCharges() const
{
    return spellCharges;
}

CSpell *Item::getSpell() const
{
    return spell;
}

void Item::setStats( StatsType::StatsType statsType, int16_t amount )
{
	this->statsModifier[ static_cast<size_t>( statsType) ] = amount;
}

void Item::setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints )
{
	this->resistElementModifier[ static_cast<size_t>( elementType ) ] = resistModifierPoints;
}

void Item::setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints )
{
	this->spellEffectElementModifier[ static_cast<size_t>( elementType ) ] = spellEffectElementModifierPoints;
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

void Item::setValue( uint32_t newValue )
{
    value = newValue;
}

void Item::reduceSpellCharges()
{
    spellCharges--;
}

void Item::setSpellCharges( uint8_t newSpellCharges )
{
    spellCharges = newSpellCharges;
}

void Item::setSpell( CSpell *newSpell )
{
    spell = newSpell;
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

std::string Item::getUseableDescription() const
{
    switch ( itemType )
    {
        case ItemType::DRINK:
            return std::string("Drink: "); // later on add .append(getUsableSpellDescription) or so..
        break;
        case ItemType::FOOD:
            return std::string("Food: "); // later on add .append(getUsableSpellDescription) or so..
        break;
        case ItemType::NEWSPELL:
            if ( getSpell() != NULL )
            {
                // TODO: add actual rank of spell.
                return std::string("Memorize: Inscribes ").append( getSpell()->getName() ).append( " (rank X)" ).append(" to spellbook.");
            }
        break;
        case ItemType::POTION:
            if ( getSpell() != NULL )
            {
                return std::string("Drink: ").append(getSpell()->getInfo() );
            }
        break;
        case ItemType::SCROLL:
            if ( getSpell() != NULL )
            {
                return std::string("Read: ").append(getSpell()->getInfo() );
            }
        break;
        default:
        break;
    }
    return "";
}

bool Item::isUseable() const
{
    return useableItem;
}

static std::auto_ptr<CTexture> goldHeapTexture( NULL );

sTexture getGoldHeapTexture()
{
	if ( goldHeapTexture.get() == NULL ) {
		goldHeapTexture = std::auto_ptr<CTexture>(new CTexture());
		goldHeapTexture->texture.reserve( 1 );
		goldHeapTexture->LoadIMG( "data/items/coins.tga", 0 );
	}
	return goldHeapTexture->texture[0];
}

GoldHeap::GoldHeap( size_t coins_ )
	:	Item( "Coins", 1, 1, "data/items/coins.tga",
		      ItemQuality::NORMAL,
		      EquipPosition::NONE,
		      ItemType::MISCELLANEOUS,
		      ArmorType::NO_ARMOR,
		      WeaponType::NO_WEAPON,
		      false ),
		coins( coins_ )
{
	symbolTexture.texture[0] = getGoldHeapTexture();
}

size_t GoldHeap::numCoins() const
{
	return coins;
}


