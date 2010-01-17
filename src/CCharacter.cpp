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

#include "CCharacter.h"
#include <cassert>
#include "CDrawingHelpers.h"
#include "CSpell.h"
#include "CInterface.h"
#include "CAction.h"
#include "StatsSystem.h"

#include "CNPC.h"
#include "Player.h"

#include <map>
#include <string>
#include <limits>
#include <iostream>

void enqueueActiveSpellAction( CSpellActionBase *spellaction );

std::map< std::string, CCharacter* > allMobTypes;
extern std::vector<Item*> groundItems;
extern std::vector<std::pair<int,int> > groundPositions;

// Dawn LUA Interface
namespace DawnInterface
{
	CCharacter* createNewMobType( std::string typeID )
	{
		CCharacter *newMobType = new CNPC(0, 0, 0, 0, 0, NULL);
		newMobType->lifebar = NULL;
		allMobTypes[ typeID ] = newMobType;
		return newMobType;
	}
}

void CCharacter::baseOnType( std::string otherName )
{
	CCharacter *other;
	if ( allMobTypes.count( otherName ) != 1 ) {
		std::cerr << "mob type \"" << otherName << "\" found " << allMobTypes.count( otherName ) << " times!!! aborting." << std::endl;
		abort();
	}
	other = allMobTypes[ otherName ];
	setStrength( other->getStrength() );
	setDexterity( other->getDexterity() );
	setVitality( other->getVitality() );
	setIntellect( other->getIntellect() );
	setWisdom( other->getWisdom() );
	setMaxHealth( other->getMaxHealth() );
	setMaxMana( other->getMaxMana() );
	setMinDamage( other->getMinDamage() );
	setMaxDamage( other->getMaxDamage() );
	size_t numActivities=static_cast<size_t>(ActivityType::Count);
	for ( size_t curActivity=0; curActivity<numActivities; ++curActivity ) {
		ActivityType::ActivityType curActivityType = static_cast<ActivityType::ActivityType>( curActivity );
		setNumMoveTexturesPerDirection( curActivityType, other->numMoveTexturesPerDirection[ curActivity ] );
		setTexture( curActivityType, other->getTexture(curActivityType) );
	}
	setLifebar( other->getLifebar() );
	setArmor( other->getArmor() );
	setDamageModifierPoints( other->getDamageModifierPoints() );
	setHitModifierPoints( other->getHitModifierPoints() );
	setEvadeModifierPoints( other->getEvadeModifierPoints() );
	setBlockModifierPoints( other->getBlockModifierPoints() );
	setMeleeCriticalModifierPoints( other->getMeleeCriticalModifierPoints() );
	setResistAllModifierPoints( other->getResistAllModifierPoints() );
	setSpellEffectAllModifierPoints( other->getSpellEffectAllModifierPoints() );
	for ( size_t curElement=0; curElement<static_cast<size_t>(ElementType::Count); ++curElement ) {
		ElementType::ElementType curElementType = static_cast<ElementType::ElementType>(curElement);
		setResistElementModifierPoints( curElementType, other->getResistElementModifierPoints( curElementType ) );
		setSpellEffectElementModifierPoints( curElementType, other->getSpellEffectElementModifierPoints( curElementType ) );
	}
	setSpellCriticalModifierPoints( other->getSpellCriticalModifierPoints() );
	setWanderRadius ( other->getWanderRadius() );
	setName( other->getName() );
	setLevel( other->getLevel() );
	setLootTable( other->getLootTable() );
	setBoundingBox( other->getBoundingBoxX(), other->getBoundingBoxY(), other->getBoundingBoxW(), other->getBoundingBoxH() );
	setUseBoundingBox( other->getUseBoundingBox() );
}

const uint16_t NULLABLE_ATTRIBUTE_MIN = 0;
const uint16_t NON_NULLABLE_ATTRIBUTE_MIN = 1;

template <class AttributeType, class ModifierType>
AttributeType getModifiedAttributeValue( AttributeType attributeValue, ModifierType modifier,
                                         AttributeType minValue = std::numeric_limits<AttributeType>::min(),
                                         AttributeType maxValue = std::numeric_limits<AttributeType>::max() )
{
	assert( attributeValue >= minValue && attributeValue <= maxValue );
	// is modified value < minValue? => set to minValue
	if ( modifier < 0 && static_cast<AttributeType>(-modifier) > attributeValue - minValue )
		return minValue;
	// is modified value > maxValue? => set to maxValue
	else if ( modifier > 0 && (maxValue - attributeValue) < modifier )
		return maxValue;
	else
		return (attributeValue + modifier);
}

std::string CCharacter::getName() const
{
	return name;
}

void CCharacter::setName( std::string newName )
{
	name = newName;
}

void CCharacter::setArmor( uint16_t newArmor )
{
    armor = newArmor;
}

uint16_t CCharacter::getArmor() const
{
    return armor;
}

uint16_t CCharacter::getModifiedArmor() const
{
	return getArmor() + StatsSystem::getStatsSystem()->calculateDamageReductionPoints( this );
}

void CCharacter::modifyArmor( int16_t armorModifier )
{
    setArmor( getModifiedAttributeValue( armor, armorModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setDamageModifierPoints( uint16_t newDamageModifierPoints )
{
	damageModifierPoints = newDamageModifierPoints;
}

uint16_t CCharacter::getModifiedDamageModifierPoints() const
{
	return getDamageModifierPoints() + StatsSystem::getStatsSystem()->calculateDamageModifierPoints( this );
}

uint16_t CCharacter::getDamageModifierPoints() const
{
	return damageModifierPoints;
}

void CCharacter::modifyDamageModifierPoints( int16_t damageModifierPointsModifier )
{
	setDamageModifierPoints( getModifiedAttributeValue( damageModifierPoints, damageModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setHitModifierPoints( uint16_t newHitModifierPoints )
{
	hitModifierPoints = newHitModifierPoints;
}

uint16_t CCharacter::getModifiedHitModifierPoints() const
{
	return getHitModifierPoints() + StatsSystem::getStatsSystem()->calculateHitModifierPoints( this );
}

uint16_t CCharacter::getHitModifierPoints() const
{
	return hitModifierPoints;
}

void CCharacter::modifyHitModifierPoints( int16_t hitModifierPointsModifier )
{
	setHitModifierPoints( getModifiedAttributeValue( hitModifierPoints, hitModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setEvadeModifierPoints( uint16_t newEvadeModifierPoints )
{
	evadeModifierPoints = newEvadeModifierPoints;
}

uint16_t CCharacter::getModifiedEvadeModifierPoints() const
{
	return getEvadeModifierPoints() + StatsSystem::getStatsSystem()->calculateEvadeModifierPoints( this );
}

uint16_t CCharacter::getEvadeModifierPoints() const
{
	return evadeModifierPoints;
}

void CCharacter::modifyEvadeModifierPoints( int16_t evadeModifierPointsModifier )
{
	setEvadeModifierPoints( getModifiedAttributeValue( evadeModifierPoints, evadeModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setBlockModifierPoints( uint16_t newBlockModifierPoints )
{
	blockModifierPoints = newBlockModifierPoints;
}

uint16_t CCharacter::getModifiedBlockModifierPoints() const
{
	return getBlockModifierPoints() + StatsSystem::getStatsSystem()->calculateBlockModifierPoints( this );
}

uint16_t CCharacter::getBlockModifierPoints() const
{
	return blockModifierPoints;
}

void CCharacter::modifyBlockModifierPoints( int16_t blockModifierPointsModifier )
{
	setBlockModifierPoints( getModifiedAttributeValue( blockModifierPoints, blockModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setMeleeCriticalModifierPoints( uint16_t newMeleeCriticalModifierPoints )
{
	meleeCriticalModifierPoints = newMeleeCriticalModifierPoints;
}

uint16_t CCharacter::getModifiedMeleeCriticalModifierPoints() const
{
	return getMeleeCriticalModifierPoints() + StatsSystem::getStatsSystem()->calculateMeleeCriticalModifierPoints( this );
}

uint16_t CCharacter::getMeleeCriticalModifierPoints() const
{
	return meleeCriticalModifierPoints;
}

void CCharacter::modifyMeleeCriticalModifierPoints( int16_t meleeCriticalModifierPointsModifier )
{
	setMeleeCriticalModifierPoints( getModifiedAttributeValue( meleeCriticalModifierPoints, meleeCriticalModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setResistElementModifierPoints( ElementType::ElementType elementType, uint16_t newResistElementModifierPoints )
{
	resistElementModifierPoints[ static_cast<size_t>(elementType) ] = newResistElementModifierPoints;
}

uint16_t CCharacter::getModifiedResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getResistElementModifierPoints( elementType ) + getResistAllModifierPoints() +  StatsSystem::getStatsSystem()->calculateResistElementModifierPoints( elementType, this );
}

uint16_t CCharacter::getResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return resistElementModifierPoints[ static_cast<size_t>(elementType) ];
}

void CCharacter::modifyResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistElementModifierPointsModifier )
{
	setResistElementModifierPoints( elementType, getModifiedAttributeValue( resistElementModifierPoints[ static_cast<size_t>(elementType) ], resistElementModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setResistAllModifierPoints( uint16_t newResistAllModifierPoints )
{
	resistAllModifierPoints = newResistAllModifierPoints;
}

uint16_t CCharacter::getResistAllModifierPoints() const
{
	return resistAllModifierPoints;
}

void CCharacter::modifyResistAllModifierPoints( int16_t resistAllModifierPointsModifier )
{
	setResistAllModifierPoints( getModifiedAttributeValue( resistAllModifierPoints, resistAllModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setSpellEffectElementModifierPoints( ElementType::ElementType elementType, uint16_t newSpellEffectElementModifierPoints )
{
	spellEffectElementModifierPoints[ static_cast<size_t>(elementType) ] = newSpellEffectElementModifierPoints;
}

uint16_t CCharacter::getModifiedSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return getSpellEffectElementModifierPoints( elementType ) + getSpellEffectAllModifierPoints() +  StatsSystem::getStatsSystem()->calculateSpellEffectElementModifierPoints( elementType, this );
}

uint16_t CCharacter::getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return spellEffectElementModifierPoints[ static_cast<size_t>(elementType) ];
}

void CCharacter::modifySpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPointsModifier )
{
	setSpellEffectElementModifierPoints( elementType, getModifiedAttributeValue( spellEffectElementModifierPoints[ static_cast<size_t>(elementType) ], spellEffectElementModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setSpellEffectAllModifierPoints( uint16_t newSpellEffectAllModifierPoints )
{
	spellEffectAllModifierPoints = newSpellEffectAllModifierPoints;
}

uint16_t CCharacter::getSpellEffectAllModifierPoints() const
{
	return spellEffectAllModifierPoints;
}

void CCharacter::modifySpellEffectAllModifierPoints( int16_t spellEffectAllModifierPointsModifier )
{
	setSpellEffectAllModifierPoints( getModifiedAttributeValue( spellEffectAllModifierPoints, spellEffectAllModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

void CCharacter::setSpellCriticalModifierPoints( uint16_t newSpellCriticalModifierPoints )
{
	spellCriticalModifierPoints = newSpellCriticalModifierPoints;
}

uint16_t CCharacter::getModifiedSpellCriticalModifierPoints() const
{
	return getSpellCriticalModifierPoints() + StatsSystem::getStatsSystem()->calculateSpellCriticalModifierPoints( this );
}

uint16_t CCharacter::getSpellCriticalModifierPoints() const
{
	return spellCriticalModifierPoints;
}

void CCharacter::modifySpellCriticalModifierPoints( int16_t spellCriticalModifierPointsModifier )
{
	setSpellCriticalModifierPoints( getModifiedAttributeValue( spellCriticalModifierPoints, spellCriticalModifierPointsModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getStrength() const
{
	return strength;
}

uint16_t CCharacter::getModifiedStrength() const
{
	return getStrength();
}

void CCharacter::setStrength( uint16_t newStrength )
{
	assert( newStrength >= NON_NULLABLE_ATTRIBUTE_MIN );
	strength = newStrength;
}

void CCharacter::modifyStrength( int16_t strengthModifier )
{
	setStrength( getModifiedAttributeValue( strength, strengthModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getDexterity() const
{
	return dexterity;
}

uint16_t CCharacter::getModifiedDexterity() const
{
	return getDexterity();
}

void CCharacter::setDexterity( uint16_t newDexterity )
{
	assert( newDexterity >= NON_NULLABLE_ATTRIBUTE_MIN );
	dexterity = newDexterity;
}

void CCharacter::modifyDexterity( int16_t dexterityModifier )
{
	setDexterity( getModifiedAttributeValue( dexterity, dexterityModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getVitality() const
{
	return vitality;
}

uint16_t CCharacter::getModifiedVitality() const
{
	return getVitality();
}

void CCharacter::setVitality( uint16_t newVitality )
{
	assert( newVitality >= NON_NULLABLE_ATTRIBUTE_MIN );
	vitality = newVitality;
}

void CCharacter::modifyVitality( int16_t vitalityModifier )
{
	setVitality( getModifiedAttributeValue( vitality, vitalityModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getIntellect() const
{
	return intellect;
}

uint16_t CCharacter::getModifiedIntellect() const
{
	return getIntellect();
}

void CCharacter::setIntellect( uint16_t newIntellect )
{
	assert( newIntellect >= NON_NULLABLE_ATTRIBUTE_MIN );
	intellect = newIntellect;
}

void CCharacter::modifyIntellect( int16_t intellectModifier )
{
	setIntellect( getModifiedAttributeValue( intellect, intellectModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getWisdom() const
{
	return wisdom;
}

uint16_t CCharacter::getModifiedWisdom() const
{
	return getWisdom();
}

void CCharacter::setWisdom( uint16_t newWisdom )
{
	assert( newWisdom >= NON_NULLABLE_ATTRIBUTE_MIN );
	wisdom = newWisdom;
}

void CCharacter::modifyWisdom( int16_t wisdomModifier )
{
	setWisdom( getModifiedAttributeValue( wisdom, wisdomModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getMaxHealth() const
{
	return max_health;
}

uint16_t CCharacter::getModifiedMaxHealth() const
{
	return getMaxHealth();
}

void CCharacter::setMaxHealth( uint16_t newMaxHealth )
{
	assert( newMaxHealth >= NON_NULLABLE_ATTRIBUTE_MIN );
	max_health = newMaxHealth;
	// if ( current_health > getModifiedMaxHealth() )
	// {
		current_health = getModifiedMaxHealth();
	// }
}

void CCharacter::modifyMaxHealth( int16_t maxHealthModifier )
{
	setMaxHealth( getModifiedAttributeValue( max_health, maxHealthModifier, NON_NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getCurrentHealth() const
{
	if ( current_health > getModifiedMaxHealth() )
		return getModifiedMaxHealth();

	return current_health;
}

void CCharacter::setCurrentHealth( uint16_t newCurrentHealth )
{
	assert( newCurrentHealth <= getModifiedMaxHealth() );
	current_health = newCurrentHealth;
}

void CCharacter::modifyCurrentHealth( int16_t currentHealthModifier )
{
	setCurrentHealth( getModifiedAttributeValue( getCurrentHealth(), currentHealthModifier, NULLABLE_ATTRIBUTE_MIN, getModifiedMaxHealth() ) );
}

uint16_t CCharacter::getMaxMana() const
{
	return max_mana;
}

uint16_t CCharacter::getModifiedMaxMana() const
{
	return getMaxMana();
}

void CCharacter::setMaxMana( uint16_t newMaxMana )
{
	max_mana = newMaxMana;
	// if ( current_mana > getModifiedMaxMana() )
	// {
		current_mana = getModifiedMaxMana();
	// }
}

void CCharacter::modifyMaxMana( int16_t maxManaModifier )
{
	setMaxMana( getModifiedAttributeValue( max_mana, maxManaModifier, NULLABLE_ATTRIBUTE_MIN ) );
}

uint16_t CCharacter::getCurrentMana() const
{
	if ( current_mana > getModifiedMaxMana() )
		return getModifiedMaxMana();

	return current_mana;
}

void CCharacter::setCurrentMana( uint16_t newCurrentMana )
{
	assert( newCurrentMana <= getModifiedMaxMana() );
	current_mana = newCurrentMana;
}

void CCharacter::modifyCurrentMana( int16_t currentManaModifier )
{
	setCurrentMana( getModifiedAttributeValue( getCurrentMana(), currentManaModifier, NULLABLE_ATTRIBUTE_MIN, getModifiedMaxMana() ) );
}

void CCharacter::setMinDamage( uint16_t newMinDamage )
{
	min_damage = newMinDamage;
}

uint16_t CCharacter::getMinDamage() const
{
	return min_damage;
}

uint16_t CCharacter::getModifiedMinDamage() const
{
	return getMinDamage();
}

void CCharacter::setMaxDamage( uint16_t newMaxDamage )
{
	max_damage = newMaxDamage;
}

uint16_t CCharacter::getMaxDamage() const
{
	return max_damage;
}

uint16_t CCharacter::getModifiedMaxDamage() const
{
	return getMaxDamage();
}

void CCharacter::addItemToLootTable(Item *item, double dropChance )
{
    lootTable.push_back( sLootTable( item, dropChance ) );
}

uint64_t CCharacter::getExperience() const
{
	return experience;
}

void CCharacter::gainExperience( uint64_t addExp )
{
	if ( std::numeric_limits<uint64_t>::max() - addExp < experience ) {
		experience = std::numeric_limits<uint64_t>::max();
		dawn_debug_warn( "max experience reached" );
	} else {
		experience += addExp;
	}

	while ( canRaiseLevel() ) {
		raiseLevel();
	}
}

uint64_t CCharacter::getExpNeededForLevel( uint8_t level ) const
{
	uint64_t result = ((level+1)*level* 50);
	return result;
}

bool CCharacter::canRaiseLevel() const
{
	return ( experience >= getExpNeededForLevel( getLevel() + 1 ) && ( getExpNeededForLevel( getLevel() + 1 ) != getExpNeededForLevel( getLevel() ) ) );
}

void CCharacter::raiseLevel()
{
	if ( canRaiseLevel() ) {
		setMaxHealth( getMaxHealth() * 1.1 );
		setMaxMana( getMaxMana() * 1.1 );
		setStrength( getStrength() * 1.1 );
		setLevel( getLevel() + 1 );
	}
}

void CCharacter::setWanderRadius( uint16_t newWanderRadius )
{
	wander_radius = newWanderRadius;
}

uint16_t CCharacter::getWanderRadius() const
{
	return wander_radius;
}

void CCharacter::setLevel ( uint8_t newLevel )
{
	level = newLevel;
}

uint8_t CCharacter::getLevel() const
{
	return level;
}

void CCharacter::setLootTable( std::vector<sLootTable> newLootTable )
{
    lootTable = newLootTable;
}

std::vector<sLootTable> CCharacter::getLootTable() const
{
    return lootTable;
}

void CCharacter::setTexture( ActivityType::ActivityType activity, CTexture *newTexture )
{
	size_t activityNr = static_cast<size_t>( activity );
	this->texture[ activityNr ] = newTexture;
}

CTexture* CCharacter::getTexture( ActivityType::ActivityType activity ) const
{
	size_t activityNr = static_cast<size_t>( activity );
	return this->texture[ activityNr ];
}

void CCharacter::setLifebar( CTexture *newLifebar )
{
	this->lifebar = newLifebar;
}

CTexture* CCharacter::getLifebar() const
{
	return this->lifebar;
}

void CCharacter::setNumMoveTexturesPerDirection( ActivityType::ActivityType activity, int numTextures )
{
	size_t activityNr = static_cast<size_t>(activity);
	numMoveTexturesPerDirection[ activityNr ] = numTextures;
	assert( texture[ activityNr ] == NULL );

	texture[ activityNr ] = new CTexture();
	texture[ activityNr ]->texture.reserve( 8 * numTextures + 1 );
}

void CCharacter::setMoveTexture( ActivityType::ActivityType activity, int direction, int index, std::string filename )
{
	size_t activityNr = static_cast<size_t>(activity);
	assert( texture[activityNr] != NULL );
	assert( index < numMoveTexturesPerDirection[activityNr] );

	texture[ activityNr ]->LoadIMG( filename, direction + 8*index );
}

void CCharacter::setLifeTexture( std::string filename )
{
	if ( lifebar == NULL ) {
		lifebar = new CTexture();
		lifebar->texture.reserve( 2 );
	}
	lifebar->LoadIMG( filename, 1 );
}

// end of Dawn LUA Interface

CCharacter::CCharacter()
	: strength( 1 ),
	  dexterity( 1 ),
	  vitality( 1 ),
	  intellect( 1 ),
	  wisdom( 1 ),
	  max_health( 1 ),
	  current_health( 1 ),
	  max_mana( 0 ),
	  current_mana( 0 ),
	  armor( 0 ),
	  damageModifierPoints( 0 ),
	  hitModifierPoints( 0 ),
	  evadeModifierPoints( 0 ),
	  blockModifierPoints( 0 ),
	  meleeCriticalModifierPoints( 0 ),
	  resistElementModifierPoints( NULL ),
	  resistAllModifierPoints( 0 ),
	  spellEffectElementModifierPoints( NULL ),
	  spellEffectAllModifierPoints( 0 ),
	  spellCriticalModifierPoints( 0 ),
	  boundingBoxX( 0 ),
	  boundingBoxY( 0 ),
	  boundingBoxW( 0 ),
	  boundingBoxH( 0 ),
	  useBoundingBox( false )
{
	resistElementModifierPoints = new uint16_t[ static_cast<size_t>( ElementType::Count ) ];
	spellEffectElementModifierPoints = new uint16_t[ static_cast<size_t>( ElementType::Count ) ];
	for ( size_t curElement=0; curElement<static_cast<size_t>( ElementType::Count ); ++curElement ) {
		resistElementModifierPoints[ curElement ] = 0;
		spellEffectElementModifierPoints[ curElement ] = 0;
	}
	size_t numActivities = static_cast<size_t>( ActivityType::Count );
	numMoveTexturesPerDirection = new int[ numActivities ];
	texture = new CTexture* [ numActivities ];
	for ( size_t curActivity=0; curActivity<numActivities; ++curActivity ) {
		numMoveTexturesPerDirection[ curActivity ] = 0;
		texture[ curActivity ] = NULL;
	}
	activeDirection = S;
}

CCharacter::~CCharacter()
{
	if ( isPreparing ) {
		// note: if the current spell / action is not null this means
		//       it is still bound to the player. He alone is responsible
		//       for it.
		delete curSpellAction;
	}
	size_t numActivities = static_cast<size_t>( ActivityType::Count );
	for ( size_t curActivity=0; curActivity<numActivities; ++curActivity ) {
		if ( texture[ curActivity ] != NULL ) {
			delete texture[ curActivity ];
		}
	}
	delete[] numMoveTexturesPerDirection;
	delete[] texture;
}

int CCharacter::getXPos() const
{
	return x_pos;
}

int CCharacter::getYPos() const
{
	return y_pos;
}

int CCharacter::getWidth() const
{
	return useBoundingBox ? boundingBoxW : texture[0]->texture[1].width;
}

int CCharacter::getHeight() const
{
	return useBoundingBox ? boundingBoxH : texture[0]->texture[1].height;
}

extern std::vector <CNPC*> NPC;

extern Player character;

static bool hasIntersection( int r1_l, int r1_r, int r1_b, int r1_t, int r2_l, int r2_r, int r2_b, int r2_t )
{
	return ( ! ( (r1_t < r2_b) || (r1_b > r2_t ) || (r1_l > r2_r) || (r1_r < r2_l) ) );
}

int CCharacter::CheckForCollision(int x_pos, int y_pos)
{
	int character_l = x_pos, character_r = x_pos + getWidth(), character_b = y_pos, character_t = y_pos + getHeight();
	for (unsigned int t=0;t<zone1.CollisionMap.size();t++) {
		int other_l = zone1.CollisionMap[t].CR.x, other_r = zone1.CollisionMap[t].CR.x+zone1.CollisionMap[t].CR.w;
		int other_b = zone1.CollisionMap[t].CR.y, other_t = zone1.CollisionMap[t].CR.y+zone1.CollisionMap[t].CR.h;
		if ( hasIntersection( other_l, other_r, other_b, other_t,
		                      character_l, character_r, character_b, character_t )) {
			return 1;
		}
	}

	// check for collision with other characters
	for ( size_t curNPCNr=0; curNPCNr < NPC.size(); ++curNPCNr )
	{
		CCharacter *curNPC = NPC[ curNPCNr ];
		if ( curNPC == this || ! curNPC->isAlive() )
			continue;

		int other_l = curNPC->getXPos(), other_r = curNPC->getXPos() + curNPC->getWidth();
		int other_b = curNPC->getYPos(), other_t = curNPC->getYPos() + curNPC->getHeight();

		if ( hasIntersection( other_l, other_r, other_b, other_t,
		                      character_l, character_r, character_b, character_t ) ) {
				return 1;
		}

	}

	// check for collision with player
	{
		CCharacter *curNPC = &character;
		if ( curNPC != this && curNPC->isAlive() ) {
			int other_l = curNPC->getXPos(), other_r = curNPC->getXPos() + curNPC->getWidth();
			int other_b = curNPC->getYPos(), other_t = curNPC->getYPos() + curNPC->getHeight();

			if ( hasIntersection( other_l, other_r, other_b, other_t,
			                      character_l, character_r, character_b, character_t ) ) {
				return 1;
			}
		}
	}

	return 0;
}

int CCharacter::CollisionCheck(Direction direction)
{

	switch (direction) {
		case N:
			// check upper left corner
			if (CheckForCollision(x_pos,y_pos+1) == 1) {
				return 1;
			}
		break;

		case E:
			// check upper right corner
			if (CheckForCollision(x_pos+1,y_pos) == 1) {
				return 1;
			}
		break;

		case S:
			// check lower left corner
			if (CheckForCollision(x_pos,y_pos-1) == 1) {
				return 1;
			}
		break;

		case W:
			// check upper left corner
			if (CheckForCollision(x_pos-1,y_pos) == 1) {
				return 1;
			}
		break;

		default:
		break;
	}
	return 0;
}

void CCharacter::MoveUp()
{
	if (CollisionCheck(N) == 0) {
		y_pos++;
	}
}

void CCharacter::MoveDown()
{
	if (CollisionCheck(S) == 0) {
		y_pos--;
	}
}

void CCharacter::MoveLeft()
{
	if (CollisionCheck(W) == 0) {
		x_pos--;
	}
}

void CCharacter::MoveRight()
{
	if (CollisionCheck(E) == 0) {
		x_pos++;
	}
}

void CCharacter::Move()
{
	continuePreparing();
	if ( ! mayDoAnythingAffectingSpellActionWithoutAborting() ) {
		if ( ! mayDoAnythingAffectingSpellActionWithAborting() ) {
			remainingMovePoints = 0;
			return;
		}
	}

	Direction movingDirection = GetDirection();
	if (( movingDirection != STOP) && ! mayDoAnythingAffectingSpellActionWithoutAborting() ) {
		CastingAborted();
	}

	unsigned int movePerStep = 10; // moves one step per movePerStep ms

	// To balance moving diagonally boost, movePerStep = 10*sqrt(2)
	if ( movingDirection == NW || movingDirection == NE || movingDirection == SW || movingDirection == SE )
		movePerStep = 14;

	while ( remainingMovePoints > movePerStep ) {
		remainingMovePoints -= movePerStep;
		switch ( movingDirection ) {
			case NW:
				MoveLeft();
				MoveUp();
				break;
			case N:
				MoveUp();
				break;
			case NE:
				MoveRight();
				MoveUp();
				break;
			case W:
				MoveLeft();
				break;
			case E:
				MoveRight();
				break;
			case SW:
				MoveLeft();
				MoveDown();
				break;
			case S:
				MoveDown();
				break;
			case SE:
				MoveRight();
				MoveDown();
				break;
			default:
				break;
		}
	}
}

void CCharacter::giveMovePoints( uint32_t movePoints )
{
	remainingMovePoints += movePoints;
}

Direction CCharacter::getDirectionTowards( int x_pos, int y_pos ) const
{
	int dx = x_pos - (this->x_pos + this->getWidth()) / 2;
	int dy = y_pos - (this->y_pos + this->getHeight()) / 2;

	if ( dx > 0 ) {
		if ( dy > 0 ) {
			return NE;
		} else if ( dy < 0 ) {
			return SE;
		} else {
			return E;
		}
	} else if ( dx < 0 ) {
		if ( dy > 0 ) {
			return NW;
		} else if ( dy < 0 ) {
			return SW;
		} else {
			return W;
		}
	} else {
		if ( dy > 0 ) {
			return N;
		} else if ( dy < 0 ) {
			return S;
		} else {
			return STOP;
		}
	}
}

ActivityType::ActivityType CCharacter::getCurActivity() const
{
	ActivityType::ActivityType curActivity = ActivityType::Walking;
	if ( curSpellAction != NULL ) {
		if ( dynamic_cast<CSpell*>( curSpellAction ) != NULL ) {
			curActivity = ActivityType::Casting;
		}
		else if ( dynamic_cast<CAction*>( curSpellAction ) != NULL ) {
			curActivity = ActivityType::Attacking;
		}
	}
	return curActivity;
}

int CCharacter::GetDirectionTexture()
{
	int direction = GetDirection();
	if ( direction != STOP ) {
		activeDirection = direction;
	}
	ActivityType::ActivityType curActivity = getCurActivity();

	switch ( curActivity ) {
		case ActivityType::Walking:
		{
			if ( direction == STOP )
				return activeDirection;

			int msPerDrawFrame = 100;
			int index = ((SDL_GetTicks() % (msPerDrawFrame * numMoveTexturesPerDirection[ curActivity ] )) / msPerDrawFrame );
			return static_cast<int>(direction) + 8*index;
		}
		break;
		case ActivityType::Casting:
		case ActivityType::Attacking:
		{
			double progress;
			if ( curActivity == ActivityType::Casting ) {
				progress = getPreparationPercentage();
			} else {
				progress = dynamic_cast<CAction*>(curSpellAction)->getProgress();
			}
			int index = progress * numMoveTexturesPerDirection[ curActivity ];
			if ( index >= numMoveTexturesPerDirection[ curActivity ] ) {
				index = numMoveTexturesPerDirection[ curActivity ] - 1;
			}
			return static_cast<int>(activeDirection) + 8*index;
		}
		default:
			assert( false );
			return 0;
		break;
	}
}

// since we dont have any combat class, im putting this spellcasting here.
// in the future we could probably benefit from putting this into the combat class,
// since we probably would use the same functions for NPCs when they are casting spells etc...

void CCharacter::executeAction( CAction *action )
{
	giveToPreparation( action );
}

void CCharacter::castSpell( CSpell *spell )
{
    if ( spell->getManaCost() > getCurrentMana() )
	{
	    /// can't cast, not enough mana. Display message here about it.
	    return;
	}

	for (size_t curSpell = 0; curSpell < cooldownSpells.size(); curSpell++)
	{
	    if ( cooldownSpells[curSpell].first->getName() == spell->getName() )
	    {
	        if ( SDL_GetTicks() < cooldownSpells[curSpell].second + spell->getCooldown() * 1000 )
            {
                /// can't cast, spell has a cooldown on it. Display message about it.
                return;
            }
	    }
	}

	giveToPreparation( spell );
}

void CCharacter::giveToPreparation( CSpellActionBase *toPrepare )
{
	if ( curSpellAction != NULL ) {
		// don't cast / execute. Enqueue in the list of coming actions / spells ?
		delete toPrepare;
	} else {
		// setup all variables for casting / executing
		isPreparing = true;
		curSpellAction = toPrepare;
		toPrepare->beginPreparationOfSpellAction();
		preparationStartTime = SDL_GetTicks();
		continuePreparing();
	}
}

bool CCharacter::continuePreparing()
{
	if ( isPreparing ) {
		bool preparationFinished = (curSpellAction->getCastTime() == 0);
		if ( ! preparationFinished ) {
			preparationCurrentTime = SDL_GetTicks();

			// casting_percentage is mostly just for the castbar display, guess we could alter this code.
			preparationPercentage = (static_cast<float>(preparationCurrentTime-preparationStartTime)) / curSpellAction->getCastTime();
			preparationFinished = ( preparationPercentage >= 1.0f );
		}
		if ( preparationFinished ) {
			startSpellAction();
		}
	}

	return isPreparing;
}

void CCharacter::startSpellAction()
{
	isPreparing = false;
	preparationCurrentTime = 0;
	preparationStartTime = 0;

	// when the spellcasting is complete, we will have a pointer to a spell and the NPC id that will be affected by it.
	// So when this spellcasting is complete, we target the NPC, using the CCombat class not yet developed to to affect the mob.
	// fow now we'll just damage / heal the NPC in target

	enqueueActiveSpellAction( curSpellAction );
	curSpellAction->startEffect();
}

void CCharacter::abortCurrentSpellAction()
{
	assert( curSpellAction != NULL );
	if ( isPreparing ) {
		delete curSpellAction;
		curSpellAction = NULL;
		isPreparing = false;
	}
}

bool CCharacter::getIsPreparing() const
{
    return isPreparing;
}

std::string CCharacter::getCurrentSpellActionName() const
{
    return curSpellAction->getName();
}

void CCharacter::CastingAborted()
{
	// if we moved, got stunned, or in some way unable to complete the spell ritual, spellcasting will fail.
	// If we are following the above instructions to use a pointer to a spell and so on, we should clear that pointer here.
	abortCurrentSpellAction();
}

void CCharacter::CastingInterrupted()
{
	// when casting a spell, mobs attacking us in any way should interfere with our spellcasting, slowing us down a bit.
	// so if we have a spell with 5 seconds spellcast, and we're up at 4 seconds of casting.. getting hit at that moment
	// should set the current_castingtime back to say 3.2 or so..
	preparationStartTime += 500; // for now using a static pushback of the spellcasting, 0.5 seconds.
	if (preparationStartTime > preparationCurrentTime) {
		preparationStartTime = preparationCurrentTime;
	}
}

float CCharacter::getPreparationPercentage() const
{
	if ( isPreparing ) {
		return preparationPercentage;
	} else {
		return 0;
	}
}

bool CCharacter::mayDoAnythingAffectingSpellActionWithoutAborting() const
{
	return ( curSpellAction == NULL );
}

bool CCharacter::mayDoAnythingAffectingSpellActionWithAborting() const
{
	return ( curSpellAction == NULL || isPreparing );
}

void CCharacter::DrawLifebar()
{
	glColor4f(1.0f-life_percentage,life_percentage,0.0f,1.0f);
	DrawingHelpers::mapTextureToRect( lifebar->texture[1].texture,
	                                  getXPos(), getWidth()*life_percentage,
	                                  getYPos()+getHeight(), 8 );
	glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void CCharacter::Damage(int amount, bool criticalHit)
{
	if (alive) {
        addDamageDisplayToGUI( amount, criticalHit, 0 );
		if (current_health <= amount) {
			current_health = 0;
			Die();
		} else {
			modifyCurrentHealth( -amount );
		}
	}
}

void CCharacter::dropItems()
{
    // iterate through the loot table and see if we should drop any items.
    for ( size_t tableID = 0; tableID < lootTable.size(); ++tableID )
    {
        double dropChance = (double)rand()/(double)RAND_MAX;
        if ( dropChance <= lootTable[tableID].dropChance )
        {
            groundItems.push_back( lootTable[tableID].item );
            groundPositions.push_back( std::pair<int,int>( getXPos(), getYPos() ) );
        }
    }
}

void CCharacter::Die()
{


}

void CCharacter::Heal(int amount)
{
	if (alive) {
		uint16_t modifiedDiff = getModifiedMaxHealth() - getCurrentHealth();
	    if ( modifiedDiff <= amount ) {
			amount = modifiedDiff;
		}
		addDamageDisplayToGUI( amount, false, 1 );
		modifyCurrentHealth( amount );
	}
}

void CCharacter::setActiveGUI( CInterface *GUI_ )
{
    activeGUI = GUI_;
}

void CCharacter::addDamageDisplayToGUI( int amount, bool critical, uint8_t damageType )
{
    if (isPlayer())
	{
        activeGUI->addCombatText(amount, critical, damageType, world_x+140,dawn_configuration::screenHeight-40+world_y);
	} else {
	    activeGUI->addCombatText(amount, critical, damageType, getXPos(), getYPos()+getHeight()+20);
	}
}

void CCharacter::setBoundingBox( int bbx, int bby, int bbw, int bbh )
{
	boundingBoxX = bbx;
	boundingBoxY = bby;
	boundingBoxW = bbw;
	boundingBoxH = bbh;
}

void CCharacter::setUseBoundingBox( bool use )
{
	useBoundingBox = use;
}

int CCharacter::getBoundingBoxX() const
{
	return boundingBoxX;
}

int CCharacter::getBoundingBoxY() const
{
	return boundingBoxY;
}

int CCharacter::getBoundingBoxW() const
{
	return boundingBoxW;
}

int CCharacter::getBoundingBoxH() const
{
	return boundingBoxH;
}

bool CCharacter::getUseBoundingBox() const
{
	return useBoundingBox;
}

void CCharacter::CalculateStats()
{
	life_percentage = static_cast<float>(getCurrentHealth()) / static_cast<float>(getModifiedMaxHealth());
	mana_percentage = static_cast<float>(getCurrentMana()) / static_cast<float>(getModifiedMaxMana());
}

bool CCharacter::CheckMouseOver(int _x_pos, int _y_pos)
{
	int myWidth = getWidth();
	int myHeight = getHeight();
	if (((x_pos < _x_pos) && ((x_pos+myWidth) > _x_pos))
	        && (( y_pos < _y_pos) && ((y_pos+myHeight) > _y_pos))) {
		return true;
	} else {
		return false;
	}
}

bool CCharacter::isPlayer() const
{
	return false;
}

void CCharacter::addActiveSpell( CSpellActionBase *spell )
{
    assert( spell != NULL );
    // here we check to see if the current spell cast is already on the character. if it is, then we refresh it.
    for ( size_t curSpell = 0; curSpell < activeSpells.size(); curSpell++ )
    {
        if ( activeSpells[curSpell].first->getName() == spell->getName() )
        {
            // we replace the old spell with a new, in case a more powerful spell is cast (a higher rank)
            activeSpells[curSpell].first = dynamic_cast<GeneralBuffSpell*>( spell );
            activeSpells[curSpell].second = SDL_GetTicks();
            return;
        }
    }

    // add new spell on character.
    activeSpells.push_back( std::pair<GeneralBuffSpell*, uint32_t>( dynamic_cast<GeneralBuffSpell*>( spell ), SDL_GetTicks() ) );
}

void CCharacter::cleanupActiveSpells()
{
    size_t curSpell = 0;
    while ( curSpell < activeSpells.size() ) {
        uint32_t thisDuration = SDL_GetTicks();
        if ( thisDuration - activeSpells[curSpell].second > activeSpells[curSpell].first->getDuration() * 1000u ) {
            delete activeSpells[curSpell].first;
            activeSpells.erase( activeSpells.begin() + curSpell );
        } else {
            curSpell ++;
        }
    }
}

std::vector<std::pair<GeneralBuffSpell*, uint32_t> > CCharacter::getActiveSpells() const
{
    return activeSpells;
}


void CCharacter::addCooldownSpell( CSpell *spell )
{
    assert( spell != NULL );
    cooldownSpells.push_back( std::pair<CSpell*,uint32_t>( spell, SDL_GetTicks() ) );
}

void CCharacter::cleanupCooldownSpells()
{

    size_t curSpell = 0;
    while ( curSpell < cooldownSpells.size() ) {
        uint32_t thisDuration = SDL_GetTicks();
        if ( thisDuration - cooldownSpells[curSpell].second > cooldownSpells[curSpell].first->getCooldown() * 1000u ) {
            delete cooldownSpells[curSpell].first;
            cooldownSpells.erase( cooldownSpells.begin() + curSpell );
        } else {
            curSpell ++;
        }
    }
}

std::vector<std::pair<CSpell*, uint32_t> > CCharacter::getCooldownSpells() const
{
    return cooldownSpells;
}

bool CCharacter::isSpellOnCooldown( std::string spellName ) const
{
    for (size_t curSpell = 0; curSpell < cooldownSpells.size(); curSpell++)
    {
	    if ( cooldownSpells[curSpell].first->getName() == spellName )
        {
            return true;
        }
    }
    return false;
}
