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

#include "StatsSystem.h"

#include "CCharacter.h"

#include <memory>
#include <limits>
#include <cmath>
#include <cassert>

std::auto_ptr<StatsSystem> theStatsSystem;

const StatsSystem *StatsSystem::getStatsSystem()
{
	if ( theStatsSystem.get() == NULL ) {
		theStatsSystem = std::auto_ptr<StatsSystem>( new StatsSystem() );
		theStatsSystem->calculateTables( 99, 1.1 );
		dawn_debug_info( "StatsSystem initialized" );
	}

	return theStatsSystem.get();
}

StatsSystem::StatsSystem()
{
	maxStatsPointsForLevel = NULL;
	maxArmorPointsForLevel = NULL;
}

StatsSystem::~StatsSystem()
{
	if ( maxStatsPointsForLevel != NULL ) {
		delete[] maxStatsPointsForLevel;
	}
	if ( maxArmorPointsForLevel != NULL ) {
		delete[] maxArmorPointsForLevel;
	}
}

void StatsSystem::calculateTables( size_t maxLevel, double relativeIncreasePerLevel )
{
	if ( maxStatsPointsForLevel != NULL ) {
		assert( maxArmorPointsForLevel != NULL );
		return;
	}

	assert( maxLevel > 0 );

	this->maxLevel = maxLevel;

	// calculate the stats points needed for each level
	maxStatsPointsForLevel = new int[ maxLevel + 1 ];
	maxArmorPointsForLevel = new int[ maxLevel + 1 ];

	maxStatsPointsForLevel[0] = 100;
	maxArmorPointsForLevel[0] = 300;

	for ( size_t curLevel=1; curLevel<=maxLevel; ++curLevel ) {
		maxStatsPointsForLevel[ curLevel ] = maxStatsPointsForLevel[0] * pow( relativeIncreasePerLevel, curLevel );
		maxArmorPointsForLevel[ curLevel ] = maxArmorPointsForLevel[0] * pow( relativeIncreasePerLevel, curLevel );
	}

	// set the allowed maximal percentages for different attributes
	maxDamageModifier = std::numeric_limits<double>::max();
	maxHitChance = 1.0;
	maxEvadeChance = 0.5;
	maxDamageReductionModifier = 0.75;
	maxBlockChance = 0.6;
	maxMeleeCriticalChance = 0.5;
	maxResistElementChance = 0.75;
	maxSpellEffectElementModifier = std::numeric_limits<double>::max();
	maxSpellCriticalChance = 0.5;
}

static double getModifierCommon( int myModifierPoints, int maxModifierPointsOwn, int maxModifierPointsOpponent, double maxModifierValue )
{
	int usePoints = myModifierPoints;

	if ( usePoints > maxModifierPointsOwn ) {
		usePoints = maxModifierPointsOwn;
	}

	if ( usePoints > maxModifierPointsOpponent )
	{
		usePoints = maxModifierPointsOpponent;
	}

	double result = (static_cast<double>(usePoints) / static_cast<double>( maxModifierPointsOpponent ));

	if ( result > maxModifierValue ) {
		return maxModifierValue;
	} else {
		return result;
	}
}

double StatsSystem::complexGetDamageModifier( int myLevel, int myDamageModifierPoints, int opponentLevel ) const
{
	return 1 + (static_cast<double>(myDamageModifierPoints) / 100.0);
}

double StatsSystem::complexGetHitChance( int myLevel, int myHitModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myHitModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxHitChance );
}

double StatsSystem::complexGetEvadeChance( int myLevel, int myEvadeModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myEvadeModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxEvadeChance );
}

double StatsSystem::complexGetDamageReductionModifier( int myLevel, int myDamageReductionPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myDamageReductionPoints,
	                          maxArmorPointsForLevel[ myLevel ],
	                          maxArmorPointsForLevel[ opponentLevel ],
	                          maxDamageReductionModifier );
}

double StatsSystem::complexGetBlockChance( int myLevel, int myBlockModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myBlockModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxBlockChance );
}

double StatsSystem::complexGetMeleeCriticalStrikeChance( int myLevel, int myMeleeCriticalModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myMeleeCriticalModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxMeleeCriticalChance );
}

double StatsSystem::complexGetResistElementChance( int myLevel, int myResistElementModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( myResistElementModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxResistElementChance );
}

double StatsSystem::complexGetSpellEffectElementModifier( int myLevel, int mySpellEffectElementModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return 1 + (static_cast<double>(mySpellEffectElementModifierPoints) / 100.0);
}

double StatsSystem::complexGetSpellCriticalStrikeChance( int myLevel, int mySpellCriticalModifierPoints, int opponentLevel ) const
{
	assert( myLevel <= maxLevel && opponentLevel <= maxLevel );

	return getModifierCommon( mySpellCriticalModifierPoints,
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxSpellCriticalChance );
}

int StatsSystem::calculateDamageModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedStrength() );
}

int StatsSystem::calculateHitModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedDexterity() * 4 );
}

int StatsSystem::calculateEvadeModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedDexterity() / 4 );
}

int StatsSystem::calculateDamageReductionPoints( const CCharacter *character ) const
{
	return 0;
}

int StatsSystem::calculateBlockModifierPoints( const CCharacter *character ) const
{
	return ( (character->getModifiedDexterity() + character->getModifiedStrength()) / 5 );
}

int StatsSystem::calculateMeleeCriticalModifierPoints( const CCharacter *character ) const
{
	return ( (character->getModifiedIntellect() + character->getModifiedWisdom()) / 5 );
}

int StatsSystem::calculateResistElementModifierPoints( ElementType::ElementType elementType, const CCharacter *character ) const
{
	return character->getModifiedWisdom() / 4;
}

int StatsSystem::calculateSpellEffectElementModifierPoints( ElementType::ElementType elementType, const CCharacter *character ) const
{
	return character->getModifiedIntellect();
}

int StatsSystem::calculateSpellCriticalModifierPoints( const CCharacter *character ) const
{
	return ( (character->getModifiedIntellect() + character->getModifiedWisdom()) / 5 );
}
