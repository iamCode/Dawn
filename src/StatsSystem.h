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

#ifndef STATS_SYSTEM_H
#define STATS_SYSTEM_H

class CCharacter;

#include <cstring> // size_t

class StatsSystem
{
	private:
		// thought as a singleton. created by getStatsSystem
		StatsSystem();
		void calculateTables( size_t maxLevel, double relativeIncreasePerLevel );

		int maxLevel;
		int *maxStatsPointsForLevel;
		int *maxArmorPointsForLevel;
		double maxDamageModifier;
		double maxHitChance;
		double maxEvadeChance;
		double maxDamageReductionModifier;
		
	public:
		~StatsSystem();

		static const StatsSystem *getStatsSystem();
		
		double getDamageModifier( const CCharacter *character, int opponentLevel ) const;
		double getHitChance( const CCharacter *character, int opponentLevel ) const;
		double getEvadeChance( const CCharacter *character, int opponentLevel ) const;
		double getDamageReductionModifier( const CCharacter *character, int opponentLevel ) const;
		
		double complexGetDamageModifier( int myLevel, int myDamageModifierPoints, int opponentLevel ) const;
		double complexGetHitChance( int myLevel, int myHitModifierPoints, int opponentLevel ) const;
		double complexGetEvadeChance( int myLevel, int myEvadeModifierPoints, int opponentLevel ) const;
		double complexGetDamageReductionModifier( int myLevel, int myDamageReductionPoints, int opponentLevel ) const;
		
		int calculateDamageModifierPoints( const CCharacter *character ) const;
		int calculateHitModifierPoints( const CCharacter *character ) const;
		int calculateEvadeModifierPoints( const CCharacter *character ) const;
		int calculateDamageReductionPoints( const CCharacter *character ) const;
};

#endif // STATS_SYSTEM_H
