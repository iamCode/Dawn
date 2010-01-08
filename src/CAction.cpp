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

#include "CAction.h"

#include "CDrawingHelpers.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "Player.h"
#include "StatsSystem.h"

#include <memory>

size_t randomSizeT( size_t min, size_t max )
{
	return min + ( static_cast<size_t>((max - min) * static_cast<double>(rand())/static_cast<double>(RAND_MAX + 1.0) - 0.5 ) );
}

double randomDouble( double min, double max )
{
	return min + ( (max - min) * static_cast<double>(rand())/static_cast<double>(RAND_MAX) );
}

/// melee attack

class AttackAction : public CAction
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target )
		{
			std::auto_ptr<AttackAction> newAction( new AttackAction() );
			newAction->creator = creator;
			newAction->target = target;

			return newAction.release();
		}

		virtual uint16_t getCastTime() const {
			return 0;
		}

		virtual uint16_t getManaCost() const {
			return 0;
		}

		virtual std::string getName() const {
			return "Melee Attack";
		}

		virtual std::string getInfo() const {
			return "Causes 20 points of damage to the target.\n";
		}

		virtual EffectType::EffectType getEffectType() const
		{
			return EffectType::SingleTargetSpell;
		}

		static CTexture *actionTexture;
		static CTexture *actionSymbol;

		static void init() {
			actionTexture = new CTexture();
			actionTexture->texture.reserve(1);
			//actionTexture->LoadIMG( "data/actions/attack/attack.tga", 0 );
			actionTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );

			actionSymbol = new CTexture();
			actionSymbol->texture.reserve(1);
			//actionSymbol->LoadIMG( "data/actions/attack/symbol.tga", 0 );
			actionTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );
		}

		static CTexture* getStaticSymbol() {
			return actionSymbol;
		}

		CTexture* getSymbol() const {
			return getStaticSymbol();
		}

		AttackAction()
				: damageCaused( true ) {
		}

		virtual double getProgress() const
		{
			uint32_t curTime = SDL_GetTicks();
			return ((curTime - effectStart) / 5.0)/90.0;
		}

		virtual void startEffect() {
			effectStart = SDL_GetTicks();
			curArc = -45.0;
			damageCaused = false;
		}

		virtual void inEffect() {
			uint32_t curTime = SDL_GetTicks();
			curArc = -45.0 + (curTime - effectStart) / 5;


			if ( curArc > 45.0 ) {
				curArc = 45.0;
				finishEffect();
			}
		}

		void finishEffect() {
			double distance = sqrt( pow(creator->getXPos() - target->getXPos(),2) + pow(creator->getYPos() - target->getYPos(),2) );
			if ( distance <= 120 ) {
				const StatsSystem *statsSystem = StatsSystem::getStatsSystem();

				double minDamage = creator->getModifiedMinDamage() * statsSystem->complexGetDamageModifier( creator->getLevel(), creator->getModifiedDamageModifierPoints(), target->getLevel() );
				double maxDamage = creator->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier( creator->getLevel(), creator->getModifiedDamageModifierPoints(), target->getLevel() );
				int damage = randomSizeT( minDamage, maxDamage );

				double hitChance = statsSystem->complexGetHitChance( creator->getLevel(), creator->getModifiedHitModifierPoints(), target->getLevel() );
				double criticalHitChance = statsSystem->complexGetMeleeCriticalStrikeChance( creator->getLevel(), creator->getModifiedMeleeCriticalModifierPoints(), target->getLevel() );
				double targetEvadeChance = statsSystem->complexGetEvadeChance( target->getLevel(), target->getModifiedEvadeModifierPoints(), creator->getLevel() );
				double targetBlockChance = statsSystem->complexGetBlockChance( target->getLevel(), target->getModifiedBlockModifierPoints(), creator->getLevel() );
				double damageReduction = statsSystem->complexGetDamageReductionModifier( target->getLevel(), target->getModifiedArmor(), creator->getLevel() );

				bool hasHit = randomSizeT( 0, 10000 ) <= hitChance * 10000;
				bool criticalHit = randomSizeT( 0, 10000 ) <= criticalHitChance * 10000;
				int criticalHitFactor = 2;
				bool targetEvaded = randomSizeT( 0, 10000 ) <= targetEvadeChance * 10000;
				bool targetBlocked = randomSizeT( 0, 10000 ) <= targetBlockChance * 10000;
				double blockFactor = 0.5;

				if ( hasHit && !targetEvaded ) {
					int damageDone = damage * (1.0-damageReduction) * (targetBlocked ? blockFactor : 1.0) * (criticalHit ? criticalHitFactor : 1);
					if ( damageDone < 1 ) {
						damageDone = 1;
					}
					target->Damage( damageDone, criticalHit );
					if ( ! target->isAlive() ) {
						creator->gainExperience( target->getModifiedMaxHealth() / 10 );
					}
				}
			}

			markSpellActionAsFinished();
		}

		virtual void drawEffect() {
		}

	private:
		CCharacter *target;
		uint32_t effectStart;
		bool damageCaused;
		double curArc;
};

CTexture *AttackAction::actionTexture = NULL;
CTexture *AttackAction::actionSymbol = NULL;


namespace ActionCreation
{
	void initActions()
	{
		AttackAction::init();
	}

	CTexture* getActionSymbolByName( std::string name )
	{
		{
			std::cerr << "Interface no longer supported. Action \"" << name << "\" not implemented yet" << std::endl;
			abort();
		}
	}

	CAction* createAttackAction( CCharacter *attacker, CCharacter *target )
	{
		AttackAction attackAction;
		return dynamic_cast<CAction*>(attackAction.cast( attacker, target ));
	}
}
