/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#include "player.h"
#include "inventory.h"
#include "groundloot.h"
#include "statssystem.h"
#include "zone.h"
#include "globals.h"
#include "soundengine.h"

#include <limits>
#include <cassert>
#include <memory>

const uint16_t NULLABLE_ATTRIBUTE_MIN = 0;
const uint16_t NON_NULLABLE_ATTRIBUTE_MIN = 1;

namespace DawnInterface
{
	void addTextToLogWindow( GLfloat color[], const char* text, ... );

	void giveItemToPlayer( Item* item )
	{
		Inventory* playerInventory = Globals::getPlayer()->getInventory();
		bool wasInserted = playerInventory->insertItem( item );
		if ( !wasInserted )
		{
			Player* player = Globals::getPlayer();
			Globals::getCurrentZone()->getGroundLoot()->addItem( player->getXPos(), player->getYPos(), item );
		}
		else
		{
			GLfloat blue[] = { 0.4f, 0.4f, 0.8f };
			DawnInterface::addTextToLogWindow( blue, "You receive %s.", item->getName().c_str() );
		}
	}

	void giveExpToPlayer( uint16_t experience )
	{
		Player *player = Globals::getPlayer();
		player->gainExperience( experience );
	}
}

Player::Player()
	:	inventory( Inventory( 10, 4, this ) )
{
	setName("Enylyn");
	movementSpeed = 1;
}

void Player::Draw()
{
	CalculateStats();
	cleanupActiveSpells();
	cleanupCooldownSpells();
	direction_texture = GetDirectionTexture();
	ActivityType::ActivityType curActivity = getCurActivity();
	if (alive == true)
	{
		int drawX = x_pos;
		int drawY = y_pos;
		if( getUseBoundingBox() )
		{
			drawX -= getBoundingBoxX();
			drawY -= getBoundingBoxY();
		}

		float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		// if player is invisible we draw at 0.2 transparency.. if sneaking we draw at 0.5 and with darker colors (shade)
		if( isSneaking() == true )
		{
		    color[0] = 0.7f;
		    color[1] = 0.7f;
		    color[2] = 0.7f;
		    color[3] = 0.5f;
		}
		else if ( isInvisible() == true )
		{
			color[3] = 0.2f;
		}
		texture[ static_cast<size_t>(curActivity) ]->DrawTexture( drawX, drawY, direction_texture, color[3], color[0], color[1], color[2] );
	}
}

Direction Player::GetDirection()
{
	keys = SDL_GetKeyState(NULL);

	if( keys[SDLK_UP] || keys[SDLK_w] )
	{
		if( keys[SDLK_LEFT] || keys[SDLK_a] )
		{
			return NW;
		}
		else if( keys[SDLK_RIGHT] || keys[SDLK_d] )
		{
			return NE;
		}
		else
		{
			return N;
		}
	}

	if( keys[SDLK_DOWN] || keys[SDLK_s] )
	{
		if( keys[SDLK_LEFT] || keys[SDLK_a] )
		{
			return SW;
		}
		else if( keys[SDLK_RIGHT] || keys[SDLK_d] )
		{
			return SE;
		}
		else
		{
			return S;
		}
	}

	if( keys[SDLK_LEFT] || keys[SDLK_a] )
	{
		return W;
	}

	if( keys[SDLK_RIGHT] || keys[SDLK_d] )
	{
		return E;
	}

	return STOP;
}

Inventory* Player::getInventory()
{
	return &inventory;
}

void Player::clearInventory()
{
	inventory.clear();
}

void Player::Move()
{
	int oldX = getXPos();
	int oldY = getYPos();

	CCharacter::MoveSpecific( movementSpeed );

	dx = getXPos()-oldX;
	dy = getYPos()-oldY;

	// if the character has moved, enable walking sound
	if( oldX != getXPos() || oldY != getYPos() )
	{
		SoundEngine::useWalkingSound( true );
	}
	else
	{
		SoundEngine::useWalkingSound( false );
	}
}

void Player::Die()
{
	alive = false;
}

bool Player::isPlayer() const
{
	return true;
}

bool Player::canWearArmorType( Item* item ) const
{
	if( ArmorType::getHighestArmorTypeByClass( getClass() ) < item->getArmorType() )
	{
		return false;
	}
	return true;
}

/// helperfunctions for items.
static int16_t getItemStrengthHelper( Item* item ) { return item->getStats( StatsType::Strength ); }
static int16_t getItemDexterityHelper( Item* item ) { return item->getStats( StatsType::Dexterity ); }
static int16_t getItemVitalityHelper( Item* item ) { return item->getStats( StatsType::Vitality ); }
static int16_t getItemIntellectHelper( Item* item ) { return item->getStats( StatsType::Intellect ); }
static int16_t getItemWisdomHelper( Item* item ) { return item->getStats( StatsType::Wisdom ); }
static int16_t getItemHealthHelper( Item* item ) { return item->getStats( StatsType::Health ); }
static int16_t getItemManaHelper( Item* item ) { return item->getStats( StatsType::Mana ); }
static int16_t getItemFatigueHelper( Item* item ) { return item->getStats( StatsType::Fatigue ); }
static int16_t getItemArmorHelper( Item* item ) { return item->getStats( StatsType::Armor ); }
static int16_t getItemDamageModifierPointsHelper( Item* item ) { return item->getStats( StatsType::DamageModifier ); }
static int16_t getItemHitModifierPointsHelper( Item* item ) { return item->getStats( StatsType::HitModifier ); }
static int16_t getItemEvadeModifierPointsHelper( Item* item ) { return item->getStats( StatsType::EvadeModifier ); }
static int16_t getItemParryModifierPointsHelper( Item* item ) { return item->getStats( StatsType::ParryModifier ); }
static int16_t getItemBlockModifierPointsHelper( Item* item ) { return item->getStats( StatsType::BlockModifier ); }
static int16_t getItemMeleeCriticalModifierPointsHelper( Item* item ) { return item->getStats( StatsType::MeleeCritical ); }
static int16_t getItemResistElementModifierPointsHelper( ElementType::ElementType elementType, Item* item ) { return item->getResistElementModifierPoints( elementType ) + item->getStats( StatsType::ResistAll ); }
static int16_t getItemSpellEffectElementModifierPointsHelper( ElementType::ElementType elementType, Item* item ) { return item->getSpellEffectElementModifierPoints( elementType ) + item->getStats( StatsType::SpellEffectAll ); }
static int16_t getItemSpellCriticalModifierPointsHelper( Item* item ) { return item->getStats( StatsType::SpellCritical ); }
static int16_t getItemHealthRegenHelper( Item* item ) { return item->getStats( StatsType::HealthRegen ); }
static int16_t getItemManaRegenHelper( Item * item ) { return item->getStats( StatsType::ManaRegen ); }
static int16_t getItemFatigueRegenHelper( Item * item ) { return item->getStats( StatsType::FatigueRegen ); }

static int16_t getItemMinDamageHelper( Item* item ) { return item->getMinDamage(); }
static int16_t getItemMaxDamageHelper( Item* item ) { return item->getMaxDamage(); }

/// helperfunctions for spells (buffs / debuffs)
static int16_t getSpellStrengthHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Strength ); }
static int16_t getSpellDexterityHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Dexterity ); }
static int16_t getSpellVitalityHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Vitality ); }
static int16_t getSpellIntellectHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Intellect ); }
static int16_t getSpellWisdomHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Wisdom ); }
static int16_t getSpellHealthHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Health ); }
static int16_t getSpellManaHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Mana ); }
static int16_t getSpellFatigueHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Fatigue ); }
static int16_t getSpellArmorHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::Armor ); }
static int16_t getSpellDamageModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::DamageModifier ); }
static int16_t getSpellHitModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::HitModifier ); }
static int16_t getSpellEvadeModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::EvadeModifier ); }
static int16_t getSpellParryModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::ParryModifier ); }
static int16_t getSpellBlockModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::BlockModifier ); }
static int16_t getSpellMeleeCriticalModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::MeleeCritical ); }
static int16_t getSpellResistElementModifierPointsHelper( ElementType::ElementType elementType, GeneralBuffSpell* spell ) { return spell->getResistElementModifierPoints( elementType ) + spell->getStats( StatsType::ResistAll ); }
static int16_t getSpellSpellEffectElementModifierPointsHelper( ElementType::ElementType elementType, GeneralBuffSpell* spell ) { return spell->getSpellEffectElementModifierPoints( elementType ) + spell->getStats( StatsType::SpellEffectAll ); }
static int16_t getSpellSpellCriticalModifierPointsHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::SpellCritical ); }
static int16_t getSpellHealthRegenHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::HealthRegen ); }
static int16_t getSpellManaRegenHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::ManaRegen); }
static int16_t getSpellFatigueRegenHelper( GeneralBuffSpell* spell ) { return spell->getStats( StatsType::FatigueRegen); }

static int16_t getSpellMinDamageHelper( GeneralBuffSpell* spell ) { return 0; } // not used yet
static int16_t getSpellMaxDamageHelper( GeneralBuffSpell* spell ) { return 0; } // not used yet


static uint16_t getModifiedAttribute( const Inventory& inventory, const CCharacter* character, uint16_t basicAttributeValue, int16_t(*getItemAttribute)( Item* ), int16_t(*getSpellAttribute)( GeneralBuffSpell* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	bool readTwoHandedWeapon = false;
	for( size_t curItemNr=0; curItemNr<numItems; ++curItemNr )
	{
		Item* curItem = equippedItems[curItemNr]->getItem();
		assert( curItem != NULL );
		if ( curItem->isTwoHandedWeapon() == false || readTwoHandedWeapon == false )
		{
			attributeModifier += getItemAttribute( curItem );
		}

		// we do this because we only want to read the stats from two-handed weapons once and not two times as it would be since we equip two-handed weapons in both main-hand and off-hand slot.
		if( curItem->isTwoHandedWeapon() )
		{
			readTwoHandedWeapon = true;
		}
	}

	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells;
	activeSpells = character ->getActiveSpells();
	size_t numSpells = activeSpells.size();
	for( size_t curSpellNr=0; curSpellNr<numSpells; ++curSpellNr )
	{
		GeneralBuffSpell *curSpell = dynamic_cast<GeneralBuffSpell*> ( activeSpells[ curSpellNr ].first );
		// since more than Buffspells can be active, we want to check to see that we're getting a buff here...
		if( curSpell != NULL )
		{
			attributeModifier += getSpellAttribute( curSpell );
		}
	}

	if( static_cast<int32_t>( basicAttributeValue ) + attributeModifier < static_cast<int32_t>( minValue ) )
	{
		return minValue;
	}
	else if( static_cast<int32_t>( basicAttributeValue ) + attributeModifier > static_cast<int32_t>( maxValue ) )
	{
		return maxValue;
	}
	else
	{
		return basicAttributeValue + attributeModifier;
	}
}

static uint16_t getModifiedAttribute( ElementType::ElementType elementType, const Inventory &inventory, const CCharacter *character, uint16_t basicAttributeValue, int16_t (*getItemAttribute)( ElementType::ElementType, Item* ), int16_t (*getSpellAttribute)( ElementType::ElementType, GeneralBuffSpell* ), uint16_t minValue = std::numeric_limits<uint16_t>::min(), uint16_t maxValue = std::numeric_limits<uint16_t>::max() )
{
	int32_t attributeModifier = 0;
	std::vector<InventoryItem*> equippedItems = inventory.getEquippedItems();
	size_t numItems = equippedItems.size();
	for( size_t curItemNr=0; curItemNr<numItems; ++curItemNr )
	{
		Item* curItem = equippedItems[ curItemNr ]->getItem();
		assert( curItem != NULL );
		attributeModifier += getItemAttribute( elementType, curItem );
	}

	std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells;
	activeSpells = character->getActiveSpells();
	size_t numSpells = activeSpells.size();
	for( size_t curSpellNr=0; curSpellNr<numSpells; ++curSpellNr )
	{
		GeneralBuffSpell* curSpell = dynamic_cast<GeneralBuffSpell*> ( activeSpells[ curSpellNr ].first );

		// since more than Buffspells can be active, we want to check to see that we're getting a buff here...
		if( curSpell != NULL )
		{
			attributeModifier += getSpellAttribute( elementType, curSpell );
		}
	}

	if( static_cast<int32_t>( basicAttributeValue ) + attributeModifier < static_cast<int32_t>( minValue ) )
	{
		return minValue;
	}
	else if ( static_cast<int32_t>( basicAttributeValue ) + attributeModifier > static_cast<int32_t>( maxValue ) )
	{
		return maxValue;
	}
	else
	{
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

uint16_t Player::getModifiedParryModifierPoints() const
{
	return getModifiedAttribute( inventory, this, getParryModifierPoints(), &getItemParryModifierPointsHelper, &getSpellParryModifierPointsHelper, NULLABLE_ATTRIBUTE_MIN ) + StatsSystem::getStatsSystem()->calculateParryModifierPoints( this );
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

uint16_t Player::getModifiedMaxFatigue() const
{
	return getModifiedAttribute( inventory, this, getMaxFatigue(), &getItemFatigueHelper, &getSpellFatigueHelper, NULLABLE_ATTRIBUTE_MIN );
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

uint16_t Player::getModifiedHealthRegen() const
{
	return getModifiedAttribute( inventory, this, getHealthRegen(), &getItemHealthRegenHelper, &getSpellHealthRegenHelper, NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedManaRegen() const
{
	return getModifiedAttribute( inventory, this, getManaRegen(), &getItemManaRegenHelper, &getSpellManaRegenHelper, NULLABLE_ATTRIBUTE_MIN );
}

uint16_t Player::getModifiedFatigueRegen() const
{
	return getModifiedAttribute( inventory, this, getFatigueRegen(), &getItemFatigueRegenHelper, &getSpellFatigueRegenHelper, NULLABLE_ATTRIBUTE_MIN );
}

void Player::setTicketForItemTooltip ()
{
	ticketForItemTooltip = SDL_GetTicks();
}

void Player::setTicketForSpellTooltip ()
{
	ticketForSpellTooltip = SDL_GetTicks();
}

uint32_t Player::getTicketForItemTooltip() const
{
	return ticketForItemTooltip;
}

uint32_t Player::getTicketForSpellTooltip() const
{
	return ticketForSpellTooltip;
}

bool Player::isSpellInscribedInSpellbook( CSpellActionBase* spell ) const
{
	for( size_t curSpell = 0; curSpell < getSpellbook().size(); curSpell++ )
	{
		if( getSpellbook()[ curSpell ]->getName() == spell->getName() )
		{
			if( getSpellbook()[ curSpell ]->getRank() >= spell->getRank() )
			{
				return true; // yes, spell is already inscribed in spellbook with same or higher rank.
			}
		}
	}
	return false;
}

std::string Player::getSaveText() const
{
	std::ostringstream oss;
	std::string objectName = "thePlayer";
	oss << "-- General status attributes" << std::endl;
	oss << "local " << objectName << " = DawnInterface.getPlayer();" << std::endl;
	oss << objectName << ":setStrength( " << getStrength() << " );" << std::endl;
	oss << objectName << ":setDexterity( " << getDexterity() << " );" << std::endl;
	oss << objectName << ":setVitality( " << getVitality() << " );" << std::endl;
	oss << objectName << ":setIntellect( " << getIntellect() << " );" << std::endl;
	oss << objectName << ":setWisdom( " << getWisdom() << " );" << std::endl;
	oss << objectName << ":setMaxHealth( " << getMaxHealth() << " );" << std::endl;
	oss << objectName << ":setMaxMana( " << getMaxMana() << " );" << std::endl;
	oss << objectName << ":setMaxFatigue( " << getMaxFatigue() << " );" << std::endl;
	oss << objectName << ":setMinDamage( " << getMinDamage() << " );" << std::endl;
	oss << objectName << ":setMaxDamage( " << getMaxDamage() << " );" << std::endl;

	// don't set activity textures here. That is determined by class of Player / NPC

	oss << objectName << ":setDamageModifierPoints( " << getDamageModifierPoints() << " );" << std::endl;
	oss << objectName << ":setHitModifierPoints( " << getHitModifierPoints() << " );" << std::endl;
	oss << objectName << ":setEvadeModifierPoints( " << getEvadeModifierPoints() << " );" << std::endl;
	oss << objectName << ":setParryModifierPoints( " << getParryModifierPoints() << " );" << std::endl;
	oss << objectName << ":setBlockModifierPoints( " << getBlockModifierPoints() << " );" << std::endl;
	oss << objectName << ":setMeleeCriticalModifierPoints( " << getMeleeCriticalModifierPoints() << " );" << std::endl;
	oss << objectName << ":setResistAllModifierPoints( " << getResistAllModifierPoints() << " );" << std::endl;
	oss << objectName << ":setSpellEffectAllModifierPoints( " << getSpellEffectAllModifierPoints() << " );" << std::endl;
	for( size_t curElement=0; curElement<static_cast<size_t>(ElementType::Count); ++curElement )
	{
		ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
		oss << objectName << ":setResistElementModifierPoints( "
		            << curElementType << ", "
		            << getResistElementModifierPoints( curElementType ) << " );" << std::endl;
		oss << objectName << ":setSpellEffectElementModifierPoints( "
		            << curElementType << ", "
		            << getSpellEffectElementModifierPoints( curElementType ) << " );" << std::endl;
	}
	oss << objectName << ":setSpellCriticalModifierPoints( " << getSpellCriticalModifierPoints() << " );" << std::endl;
	oss << objectName << ":setName( \"" << getName() << "\" );" << std::endl;
	// string stream doesn't seem to have a proper overload for uint8_t and makes it the 0-character, so cast to size_t
	oss << objectName << ":setLevel( " << static_cast<size_t>(getLevel()) << " );" << std::endl;
	oss << objectName << ":setExperience( " << getExperience() << " );" << std::endl;
	oss << objectName << ":setClass( CharacterClass." << getClassName() << " );" << std::endl;

	oss << "-- coins" << std::endl;
	oss << objectName << ":setCoins( " << getCoins() << " );" << std::endl;

	oss << "-- position" << std::endl;
	oss << objectName << ":setPosition( " << getXPos() << ", " << getYPos() << " );" << std::endl;

	// no current attributes are set here because after reloading the player is completely refreshed again

	return oss.str();
}

void Player::setMovementSpeed( uint8_t n )
{
	movementSpeed = n;
}
