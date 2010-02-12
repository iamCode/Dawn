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

#ifndef STATS_SYSTEM_H
#define STATS_SYSTEM_H

class CCharacter;

#include <cstring> // size_t
#include "elements.h"

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
		double maxBlockChance;
		double maxMeleeCriticalChance;
		double maxResistElementChance;
		double maxSpellEffectElementModifier;
		double maxSpellCriticalChance;

	public:
		~StatsSystem();

		static const StatsSystem *getStatsSystem();

		double complexGetDamageModifier( int myLevel, int myDamageModifierPoints, int opponentLevel ) const;
		double complexGetHitChance( int myLevel, int myHitModifierPoints, int opponentLevel ) const;
		double complexGetEvadeChance( int myLevel, int myEvadeModifierPoints, int opponentLevel ) const;
		double complexGetDamageReductionModifier( int myLevel, int myDamageReductionPoints, int opponentLevel ) const;
		double complexGetBlockChance( int myLevel, int myBlockModifierPoints, int opponentLevel ) const;
		double complexGetMeleeCriticalStrikeChance( int myLevel, int myMeleeCriticalModifierPoints, int opponentLevel ) const;
		double complexGetResistElementChance( int myLevel, int myResistElementModifierPoints, int opponentLevel ) const;
		double complexGetSpellEffectElementModifier( int myLevel, int mySpellEffectElementModifierPoints, int opponentLevel ) const;
		double complexGetSpellCriticalStrikeChance( int myLevel, int mySpellCriticalModifierPoints, int opponentLevel ) const;

		int calculateDamageModifierPoints( const CCharacter *character ) const;
		int calculateHitModifierPoints( const CCharacter *character ) const;
		int calculateEvadeModifierPoints( const CCharacter *character ) const;
		int calculateDamageReductionPoints( const CCharacter *character ) const;
		int calculateBlockModifierPoints( const CCharacter *character ) const;
		int calculateMeleeCriticalModifierPoints( const CCharacter *character ) const;
		int calculateResistElementModifierPoints( ElementType::ElementType elementType, const CCharacter *character ) const;
		int calculateSpellEffectElementModifierPoints( ElementType::ElementType elementType, const CCharacter *character ) const;
		int calculateSpellCriticalModifierPoints( const CCharacter *character ) const;
};

#endif // STATS_SYSTEM_H
