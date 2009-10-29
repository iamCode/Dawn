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
}

StatsSystem::~StatsSystem()
{
	if ( maxStatsPointsForLevel != NULL )
	{
		delete[] maxStatsPointsForLevel;
	}
}

void StatsSystem::calculateTables( int maxLevel, double relativeIncreasePerLevel )
{
	if ( maxStatsPointsForLevel != NULL ) {
		return;
	}
	
	assert( maxLevel > 0 );
	
	this->maxLevel = maxLevel;
	
	// calculate the stats points needed for each level
	maxStatsPointsForLevel = new int[ maxLevel + 1 ];
	
	maxStatsPointsForLevel[0] = 100;
	
	for ( size_t curLevel=1; curLevel<=maxLevel; ++curLevel ) {
		maxStatsPointsForLevel[ curLevel ] = maxStatsPointsForLevel[0] * pow( relativeIncreasePerLevel, curLevel );
	}
	
	// set the allowed maximal percentages for different attributes
	maxDamageModifier = std::numeric_limits<double>::max();
	maxHitChance = 1.0;
	maxEvadeChance = 0.5;
	maxDamageReductionModifier = 0.75;
}

double StatsSystem::getDamageModifier( const CCharacter *character, int opponentLevel ) const
{
	int modifierPoints = calculateDamageModifierPoints( character );
	return complexGetDamageModifier( character->getLevel(), modifierPoints, opponentLevel );
}

double StatsSystem::getHitChance( const CCharacter *character, int opponentLevel ) const
{
	int modifierPoints = calculateHitModifierPoints( character );
	return complexGetHitChance( character->getLevel(), modifierPoints, opponentLevel );
}

double StatsSystem::getEvadeChance( const CCharacter *character, int opponentLevel ) const
{
	int modifierPoints = calculateEvadeModifierPoints( character );
	return complexGetEvadeChance( character->getLevel(), modifierPoints, opponentLevel );
}

double StatsSystem::getDamageReductionModifier( const CCharacter *character, int opponentLevel ) const
{
	int modifierPoints = calculateDamageReductionPoints( character );
	return complexGetDamageReductionModifier( character->getLevel(), modifierPoints, opponentLevel );
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
	                          maxStatsPointsForLevel[ myLevel ],
	                          maxStatsPointsForLevel[ opponentLevel ],
	                          maxDamageReductionModifier );
}

int StatsSystem::calculateDamageModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedStrength() );
}

int StatsSystem::calculateHitModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedDexterity() * 10 );
}

int StatsSystem::calculateEvadeModifierPoints( const CCharacter *character ) const
{
	return ( character->getModifiedDexterity() / 4 );
}

int StatsSystem::calculateDamageReductionPoints( const CCharacter *character ) const
{
	return ( character->getModifiedArmor() );
}

