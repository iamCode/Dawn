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
#include "CSpell.h"
#include <memory>
#include <cassert>

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

TriggerSpellOnItem::TriggerSpellOnItem( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType, bool castOnSelf )
{
    assert( spellToTrigger != NULL );
    this->spellToTrigger = spellToTrigger;
    this->chanceToTrigger = chanceToTrigger;
    this->triggerType = triggerType;
    this->castOnSelf = castOnSelf;
}

CSpellActionBase *TriggerSpellOnItem::getSpellToTrigger() const
{
    return spellToTrigger;
}

float TriggerSpellOnItem::getChanceToTrigger() const
{
    return chanceToTrigger;
}

TriggerType::TriggerType TriggerSpellOnItem::getTriggerType() const
{
    return triggerType;
}

bool TriggerSpellOnItem::getCastOnSelf() const
{
    return castOnSelf;
}

std::string TriggerSpellOnItem::getTooltipText() const
{

    std::string toReturn = "chance to cast ";
    toReturn.append( getSpellToTrigger()->getName() );
    if ( getCastOnSelf() == true ) {
        toReturn.append( " on yourself when " );
    } else {
        toReturn.append( " on your target when " );
    }

    if ( getTriggerType() == TriggerType::EXECUTING_ACTION ) {
        toReturn.append( "casting spells." );
    } else if ( getTriggerType() == TriggerType::TAKING_DAMAGE ) {
        toReturn.append( "taking damage." );
    }

    return toReturn;
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
		requiredLevel( 1 ),
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

std::string Item::getID() const
{
	std::ostringstream idstream;
	for ( size_t curChar=0; curChar<name.size(); ++curChar ) {
		if ( isspace( name[curChar] ) ) {
			// ignore
		} else if ( isupper( name[curChar] ) ) {
			idstream << char( tolower( name[curChar] ) );
		} else {
			idstream << char( name[curChar] );
		}
	}
	if ( spell != NULL && spell->getRank() > 1 ) {
		idstream << "rank" << static_cast<int>(spell->getRank());
	}
	return idstream.str();
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

uint8_t Item::getRequiredLevel() const
{
    return requiredLevel;
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

void Item::setRequiredLevel( uint8_t requiredLevel )
{
    this->requiredLevel = requiredLevel;
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

void Item::addTriggerSpellOnSelf( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType )
{
    assert ( spellToTrigger != NULL );

    triggerSpells.push_back( new TriggerSpellOnItem( spellToTrigger, chanceToTrigger, triggerType, true ) );
}

void Item::addTriggerSpellOnTarget( CSpellActionBase* spellToTrigger, float chanceToTrigger, TriggerType::TriggerType triggerType )
{
    assert ( spellToTrigger != NULL );

    triggerSpells.push_back( new TriggerSpellOnItem( spellToTrigger, chanceToTrigger, triggerType, false ) );
}

std::vector<TriggerSpellOnItem*> Item::getTriggerSpells() const
{
    return triggerSpells;
}

bool Item::isTwoHandedWeapon() const
{
    switch ( getWeaponType() ) {
        case WeaponType::TWOHAND_AXE:
            return true;
        break;
        case WeaponType::TWOHAND_CLUB:
        break;
            return true;
        case WeaponType::TWOHAND_MACE:
        break;
            return true;
        case WeaponType::TWOHAND_SWORD:
            return true;
        break;
        case WeaponType::BOW:
            return true;
        break;
        case WeaponType::CROSSBOW:
            return true;
        break;
        case WeaponType::STAFF:
            return true;
        break;
        default:
            return false;
        break;
    }

    return false;
}

std::string Item::getUseableDescription() const
{
    switch ( itemType )
    {
        case ItemType::DRINK:
            if ( getSpell() != NULL ) {
                return std::string("Drink: ").append( getSpell()->getInfo() );
            }
        break;
        case ItemType::FOOD:
            if ( getSpell() != NULL ) {
                return std::string("Eat: ").append( getSpell()->getInfo() );
            }
        break;
        case ItemType::NEWSPELL:
            if ( getSpell() != NULL )
            {
                char rank[10];
                sprintf(rank, " (rank %d)", getSpell()->getRank() );
                return std::string("Memorize: Inscribes ").append( getSpell()->getName() ).append( rank ).append(" to spellbook.");
            }
        break;
        case ItemType::POTION:
            if ( getSpell() != NULL )
            {
                return std::string("Quaff: ").append(getSpell()->getInfo() );
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
	symbolTexture.LoadIMG( "data/items/coins.tga", 0 );
}

size_t GoldHeap::numCoins() const
{
	return coins;
}


