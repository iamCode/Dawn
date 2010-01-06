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

#include "CSpell.h"

#include <iostream>
#include <cstdlib>
#include <memory>
#include "CCharacter.h"
#include "CTexture.h"
#include "StatsSystem.h"

#include <cassert>

size_t randomSizeT( size_t min, size_t max );
double randomDouble( double min, double max );

/// Implementation of class CSpellActionBase

CSpellActionBase::CSpellActionBase()
		: boundToCreator( false ),
		  finished( false )
{
}

CSpellActionBase::~CSpellActionBase()
{
	if ( boundToCreator ) {
		creator->curSpellAction = NULL;
		creator->isPreparing = false;
	}
}

void CSpellActionBase::unbindFromCreator()
{
	if ( boundToCreator ) {
		creator->curSpellAction = NULL;
		creator->isPreparing = false;
		boundToCreator = false;
		creator->modifyCurrentMana(-getManaCost());
	}
}

bool CSpellActionBase::isBoundToCreator() const
{
	return boundToCreator;
}

void CSpellActionBase::beginPreparationOfSpellAction()
{
	boundToCreator = true;
}

void CSpellActionBase::markSpellActionAsFinished()
{
	unbindFromCreator();
	finished = true;
}

bool CSpellActionBase::isEffectComplete() const
{
	return finished;
}

void CSpellActionBase::drawSymbol( int left, int width, int bottom, int height ) const
{
	CTexture *texture = getSymbol();
	DrawingHelpers::mapTextureToRect( texture->texture[0].texture,
	                                  left, width, bottom, height );
}

/// Magic Missile

class MagicMissileSpell : public CSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target )
		{
			std::auto_ptr<MagicMissileSpell> newSpell( new MagicMissileSpell() );
			newSpell->creator = creator;
			newSpell->target = target;
			
			return newSpell.release();
		}
		
		virtual uint16_t getCastTime() const
		{
			return 1000;
		}

		virtual uint16_t getManaCost() const
		{
			return 10;
		}

		virtual std::string getName() const
		{
			return "Magic Missile";
		}

		virtual std::string getInfo() const
		{
			return "Causes 5 + (1 to 5) points of lightning damage to the target.";
		}

		static CTexture *spellTexture;
		static CTexture *spellSymbol;

		static void init() {
			spellTexture = new CTexture();
			spellTexture->texture.reserve( 1 );
			spellTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );

			spellSymbol = new CTexture();
			spellSymbol->texture.reserve( 1 );
			spellSymbol->LoadIMG( "data/spells/magicmissile/symbol.tga", 0 );
		}

		virtual CTexture* getSymbol() const
		{
			return spellSymbol;
		}

		virtual EffectType::EffectType getEffectType() const
		{
			return EffectType::SingleTargetSpell;
		}

		MagicMissileSpell()
		{
		}

		virtual void startEffect() {
			effectStart = SDL_GetTicks();
			lastEffect = effectStart;
			posx = creator->getXPos() + (creator->getWidth() / 2);
			posy = creator->getYPos() + (creator->getHeight() / 2);
			unbindFromCreator();
		}

		virtual void inEffect() {
			uint32_t curTicks = SDL_GetTicks();
			int move = (curTicks - lastEffect);
			int targetx = target->getXPos() + (target->getWidth() / 2);
			int targety = target->getYPos() + (target->getHeight() / 2);
			int dx = targetx - posx;
			int dy = targety - posy;
			double dist = sqrt( (dx * dx) + (dy * dy) );
			double percdist = (move / dist);
			int movex;
			int movey;

			if ( percdist >= 1.0 ) {
				movex = dx;
				movey = dy;
			} else {
				movex = dx * percdist;
				movey = dy * percdist;
			}

			double movedDist = sqrt(movex * movex + movey * movey);
			lastEffect += movedDist;
			if ( lastEffect > curTicks )
				lastEffect = curTicks;

			posx += movex;
			posy += movey;

			if ( posx == targetx && posy == targety )
				finishEffect();
		}

		void finishEffect() {
			int damage = 1 + rand() % 5 + 5;
			// element type is Air
			double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( ElementType::Air ), target->getLevel() );
			double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( ElementType::Air ), creator->getLevel() );
			double realDamage = damage * damageFactor * (1-resist);
			double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), target->getLevel() );
			bool criticalHit = randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000;
			if ( criticalHit == true ) {
				int criticalDamageMultiplier = 2;
				realDamage *= criticalDamageMultiplier;
			}

			target->Damage( round( realDamage ),criticalHit );
			if ( ! target->isAlive() ) {
				creator->gainExperience( target->getModifiedMaxHealth() / 10 );
			}

			markSpellActionAsFinished();
		}

		virtual void drawEffect() {
			DrawingHelpers::mapTextureToRect(
			    spellTexture->texture[0].texture,
			    posx - 16, 32,
			    posy - 16, 32 );
		}

	private:
		CCharacter *target;
		uint32_t effectStart;
		uint32_t lastEffect;
		int posx, posy;
};

CTexture *MagicMissileSpell::spellTexture = NULL;
CTexture *MagicMissileSpell::spellSymbol = NULL;

/// Lightning spell

class LightningSpell : public CSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target )
		{
			std::auto_ptr<LightningSpell> newSpell( new LightningSpell() );
			newSpell->creator = creator;
			newSpell->target = target;
			
			return newSpell.release();
		}

		virtual uint16_t getCastTime() const
		{
			return 3000;
		}

		virtual uint16_t getManaCost() const
		{
			return 20;
		}

		virtual std::string getName() const
		{
			return "Lightning";
		}

		virtual std::string getInfo() const
		{
			return "Causes 30 + (1 to 60) points of lightning damage to the target.";
		}

		static CTexture *spellTexture;
		static CTexture *spellSymbol;

		static void init() {
			spellTexture = new CTexture();
			spellTexture->texture.reserve( 5 );
			spellTexture->LoadIMG( "data/spells/lightning/1.tga", 0 );
			spellTexture->LoadIMG( "data/spells/lightning/2.tga", 1 );
			spellTexture->LoadIMG( "data/spells/lightning/3.tga", 2 );
			spellTexture->LoadIMG( "data/spells/lightning/4.tga", 3 );
			spellTexture->LoadIMG( "data/spells/lightning/5.tga", 4 );

			spellSymbol = new CTexture();
			spellSymbol->texture.reserve(1);
			spellSymbol->LoadIMG( "data/spells/lightning/symbol.tga", 0 );
		}

		CTexture* getSymbol() const {
			return spellSymbol;
		}

		virtual EffectType::EffectType getEffectType() const
		{
			return EffectType::SingleTargetSpell;
		}

		LightningSpell()
				: continuousDamageCaused( 0 ),
				  remainingEffect( 0.0 ) {
		}

		virtual void startEffect() {
			remainingEffect = 0.0;
			int damage = 1 + rand() % 60;
			// element type is Air
			double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( ElementType::Air ), target->getLevel() );
			double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( ElementType::Air ), creator->getLevel() );
			double realDamage = damage * damageFactor * (1-resist);
			double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), target->getLevel() );
			bool criticalHit = randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000;
			if ( criticalHit == true ) {
				int criticalDamageMultiplier = 2;
				realDamage *= criticalDamageMultiplier;
			}

			target->Damage( round(realDamage), criticalHit );
			if ( ! target->isAlive() ) {
				creator->gainExperience( target->getModifiedMaxHealth() / 10 );
			}
			effectStart = SDL_GetTicks();
			lastEffect = effectStart;
			unbindFromCreator();
		}

		virtual void inEffect() {
			uint32_t curTime = SDL_GetTicks();
			int curDamage = static_cast<int>( (curTime - lastEffect) / 50 );
            // element type is Air
			double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( ElementType::Air ), target->getLevel() );
			double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( ElementType::Air ), creator->getLevel() );
			double realDamage = curDamage * damageFactor * (1-resist) + remainingEffect;
			// no critical damage in this phase so far

			bool callFinish = false;
			double topLimit = 30.0 * damageFactor * (1-resist);

			if ( continuousDamageCaused + realDamage >= topLimit ) {
				realDamage = topLimit - continuousDamageCaused;
				callFinish = true;
			}

			if ( floor(realDamage) > 0 && ( curTime - lastEffect > 500 || callFinish ) ) {
				target->Damage( floor(realDamage), false );
				remainingEffect = realDamage - floor( realDamage );
				if ( ! target->isAlive() ) {
					creator->gainExperience( target->getModifiedMaxHealth() / 10 );
				}
				lastEffect += curDamage * 50;
				continuousDamageCaused += floor(realDamage);
			}

			if ( callFinish || ! target->isAlive() ) {
				finishEffect();
			}
		}

		void finishEffect() {
			markSpellActionAsFinished();
		}

		virtual void drawEffect() {
			float degrees;
			degrees = asin((creator->y_pos - target->y_pos)/sqrt((pow(creator->x_pos - target->x_pos,2)+pow(creator->y_pos - target->y_pos,2)))) * 57.296;
			degrees += 90;

			animationTimerStop = SDL_GetTicks();
			if (animationTimerStop - animationTimerStart > 50) {
				frameCount = rand() % 4;
			}

			if (creator->x_pos < target->x_pos) {
				degrees = -degrees;
			}


			glPushMatrix();
			glBindTexture( GL_TEXTURE_2D, spellTexture->texture[frameCount].texture);

			glTranslatef(creator->x_pos+32, creator->y_pos+32, 0.0f);
			glRotatef(degrees,0.0f,0.0f,1.0f);
			glTranslatef(-160-creator->x_pos,-creator->y_pos-32,0.0);

			glBegin( GL_QUADS );
			// Bottom-left vertex (corner)
			glTexCoord2f( 0.0f, 0.0f );
			glVertex3f( creator->x_pos+32, creator->y_pos+64, 0.0f );
			// Bottom-right vertex (corner)
			glTexCoord2f( 1.0f, 0.0f );
			glVertex3f( creator->x_pos+256+32, creator->y_pos+64, 0.0f );
			// Top-right vertex (corner)
			glTexCoord2f( 1.0f, 1.0f );
			glVertex3f( creator->x_pos+256+32, creator->y_pos+400+64, 0.0f );
			// Top-left vertex (corner)
			glTexCoord2f( 0.0f, 1.0f );
			glVertex3f( creator->x_pos+32, creator->y_pos+400+64, 0.0f );
			glEnd();
			glPopMatrix();
		}

	private:
		CCharacter *target;
		uint8_t frameCount;
		uint32_t effectStart;
		uint32_t lastEffect;
		uint32_t animationTimerStart;
		uint32_t animationTimerStop;
		double continuousDamageCaused;
		double remainingEffect;
};

CTexture *LightningSpell::spellTexture = NULL;
CTexture *LightningSpell::spellSymbol = NULL;

/// Heal Other spell

class HealOtherSpell : public CSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target )
		{
			std::auto_ptr<HealOtherSpell> newSpell( new HealOtherSpell() );
			newSpell->creator = creator;
			newSpell->target = target;
			
			return newSpell.release();
		}
		
		virtual uint16_t getCastTime() const
		{
			return 4000;
		}

		virtual uint16_t getManaCost() const
		{
			return 40;
		}

		virtual std::string getName() const
		{
			return "Heal Other";
		}

		virtual std::string getInfo() const
		{
			return "Heals 50 points of damage on the target.";
		}

		static CTexture *spellSymbol;

		static void init() {
			spellSymbol = new CTexture();
			spellSymbol->texture.reserve(1);
			spellSymbol->LoadIMG( "data/spells/healother/symbol.tga", 0 );
		}

		CTexture* getSymbol() const {
			return spellSymbol;
		}

		virtual EffectType::EffectType getEffectType() const
		{
			return EffectType::SingleTargetSpell;
		}

		HealOtherSpell()
		{
		}

		virtual void startEffect() {
			int healEffect = 50;
			// element type is Light
			double effectFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( ElementType::Light ), creator->getLevel() );
			double realEffect = healEffect * effectFactor;
			double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), creator->getLevel() );
			if ( randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000 ) {
				int criticalEffectMultiplier = 2;
				realEffect *= criticalEffectMultiplier;
			}
			int healEffectCaused = round( realEffect );

			target->Heal( healEffectCaused );
			unbindFromCreator();
			markSpellActionAsFinished();
		}

		virtual void inEffect() {
		}

		virtual void drawEffect() {
		}

	private:
		CCharacter *target;
};

CTexture *HealOtherSpell::spellSymbol = NULL;

/// Healing spell

class HealingSpell : public CSpell
{
	public:
		virtual CSpellActionBase* cast( CCharacter *creator, CCharacter *target )
		{
			assert( creator == target );
			std::auto_ptr<HealingSpell> newSpell( new HealingSpell() );
			newSpell->creator = creator;
			
			return newSpell.release();
		}
		
		virtual uint16_t getCastTime() const
		{
			return 5000;
		}

		virtual uint16_t getManaCost() const
		{
			return 50;
		}

		virtual std::string getName() const
		{
			return "Healing";
		}

		virtual std::string getInfo() const
		{
			return "Heals 100 points of damage on self.";
		}

		static CTexture *spellSymbol;

		static void init() {
			spellSymbol = new CTexture();
			spellSymbol->texture.reserve(1);
			spellSymbol->LoadIMG( "data/spells/healing/symbol.tga", 0 );
		}

		CTexture* getSymbol() const {
			return spellSymbol;
		}

		virtual EffectType::EffectType getEffectType() const
		{
			return EffectType::SelfAffectingSpell;
		}

		HealingSpell()
		{
		}

		virtual void startEffect() {
			int healing = 100;

			// element type is Light
			double effectFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( ElementType::Light ), creator->getLevel() );
			double realEffect = healing * effectFactor;
			double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), creator->getLevel() );
			if ( randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000 ) {
				int criticalEffectMultiplier = 2;
				realEffect *= criticalEffectMultiplier;
			}
			int healEffectCaused = round( realEffect );


			creator->Heal( healEffectCaused );
			unbindFromCreator();
			markSpellActionAsFinished();
		}

		virtual void inEffect() {
		}

		virtual void drawEffect() {
		}

};

CTexture *HealingSpell::spellSymbol = NULL;

/// GeneralDamageSpell

CSpellActionBase* GeneralDamageSpell::cast( CCharacter *creator, CCharacter *target )
{
	std::auto_ptr<GeneralDamageSpell> newSpell( new GeneralDamageSpell() );
	newSpell->creator = creator;
	newSpell->target = target;
	
	newSpell->castTime = castTime;
	newSpell->manaCost = manaCost;
	newSpell->delayTime = delayTime;
	newSpell->moveToTarget = moveToTarget;
	newSpell->minDirectDamage = minDirectDamage; // This should be a list of effects
	newSpell->maxDirectDamage = maxDirectDamage;
	newSpell->elementDirect = elementDirect;

	newSpell->minContinuousDamagePerSecond = minContinuousDamagePerSecond;
	newSpell->maxContinuousDamagePerSecond = maxContinuousDamagePerSecond;
	newSpell->elementContinuous = elementContinuous;
	newSpell->continuousDamageTime = continuousDamageTime;

	newSpell->name = name;
	newSpell->info = info;
	
	newSpell->numTextures  = numTextures;
	newSpell->spellTexture = spellTexture;
	newSpell->spellSymbol  = spellSymbol;
	
	return newSpell.release();
}

void GeneralDamageSpell::setCastTime( uint16_t newCastTime )
{
	castTime = newCastTime;
}

uint16_t GeneralDamageSpell::getCastTime() const
{
	return castTime;
}

void GeneralDamageSpell::setManaCost( uint16_t newManaCost )
{
	manaCost = newManaCost;
}

uint16_t GeneralDamageSpell::getManaCost() const
{
	return manaCost;
}

void GeneralDamageSpell::setName( std::string newName )
{
	name = newName;
}

std::string GeneralDamageSpell::getName() const
{
	return name;
}

void GeneralDamageSpell::setInfo( std::string newInfo )
{
	info = newInfo;
}

std::string GeneralDamageSpell::getInfo() const
{
	return info;
}

void GeneralDamageSpell::setDirectDamage( uint16_t newMinDirectDamage, uint16_t newMaxDirectDamage, ElementType::ElementType newElementDirect )
{
	minDirectDamage = newMinDirectDamage; // This should be a list of effects
	maxDirectDamage = newMaxDirectDamage;
	elementDirect = newElementDirect;
}

void GeneralDamageSpell::setContinuousDamage( double newMinContDamagePerSec, double newMaxContDamagePerSec, uint16_t newContDamageTime, ElementType::ElementType newContDamageElement )
{
	minContinuousDamagePerSecond = newMinContDamagePerSec;
	maxContinuousDamagePerSecond = newMaxContDamagePerSec;
	elementContinuous = newContDamageElement;
	continuousDamageTime = newContDamageTime;
}

void GeneralDamageSpell::setSpellSymbol( std::string symbolFile )
{
	assert( spellSymbol == NULL );
	spellSymbol = new CTexture();
	spellSymbol->texture.reserve(1);
	spellSymbol->LoadIMG( symbolFile, 0 );
}

void GeneralDamageSpell::setNumAnimations( int count )
{
	assert( spellTexture == NULL );
	spellTexture = new CTexture();
	numTextures = count;
	spellTexture->texture.reserve( count );
}

void GeneralDamageSpell::setAnimationTexture( int num, std::string filename )
{
	assert( spellTexture != NULL );
	assert( numTextures > num && num >= 0 );
	spellTexture->LoadIMG( filename, num );
}

CTexture* GeneralDamageSpell::getSymbol() const {
	return spellSymbol;
}

EffectType::EffectType GeneralDamageSpell::getEffectType() const
{
	return EffectType::SingleTargetSpell;
}

GeneralDamageSpell::GeneralDamageSpell()
	: remainingEffect( 0.0 ),
	  numTextures( 0 ),
	  spellTexture( NULL ),
	  spellSymbol( NULL )
{
}

void GeneralDamageSpell::startEffect()
{
	remainingEffect = 0.0;
	int damage = minDirectDamage + rand() % (maxDirectDamage - minDirectDamage);
	// element type is Air
	double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( elementDirect ), target->getLevel() );
	double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( elementDirect ), creator->getLevel() );
	double realDamage = damage * damageFactor * (1-resist);
	double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), target->getLevel() );
	bool criticalHit = randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000;
	if ( criticalHit == true ) {
		int criticalDamageMultiplier = 2;
		realDamage *= criticalDamageMultiplier;
	}

	target->Damage( round(realDamage), criticalHit );
	if ( ! target->isAlive() ) {
		creator->gainExperience( target->getModifiedMaxHealth() / 10 );
	}
	effectStart = SDL_GetTicks();
	lastEffect = effectStart;
	unbindFromCreator();
}

void GeneralDamageSpell::inEffect()
{
	uint32_t curTime = SDL_GetTicks();
	uint32_t elapsedSinceLast  = curTime - lastEffect;
	uint32_t elapsedSinceStart = curTime - effectStart;
	if ( curTime - lastEffect < 500 ) {
		// do damage at most every 0.5 seconds unless effect is done
		if ( elapsedSinceStart >= continuousDamageTime )
		{
			elapsedSinceLast = continuousDamageTime - (lastEffect - effectStart);
		}
		return;
	}

	double secondsPassed = (elapsedSinceLast) / 1000.0;
	
	double curRandDamage = randomDouble( minContinuousDamagePerSecond * secondsPassed, maxContinuousDamagePerSecond * secondsPassed );

	double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( elementContinuous ), target->getLevel() );
	double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( elementContinuous ), creator->getLevel() );
	double realDamage = curRandDamage * damageFactor * (1-resist) + remainingEffect;
	remainingEffect += realDamage;
	// no critical damage in this phase so far

	bool callFinish = false;
	if ( elapsedSinceStart >= continuousDamageTime ) {
		callFinish = true;
	}

	if ( floor(remainingEffect) > 0 ) {
		target->Damage( floor(realDamage), false );
		remainingEffect = realDamage - floor( realDamage );
		if ( ! target->isAlive() ) {
			creator->gainExperience( target->getModifiedMaxHealth() / 10 );
		}
		lastEffect = curTime;
	}

	if ( callFinish || ! target->isAlive() ) {
		finishEffect();
	}
}

void GeneralDamageSpell::finishEffect()
{
	markSpellActionAsFinished();
}

void GeneralDamageSpell::drawEffect()
{
	float degrees;
	degrees = asin((creator->y_pos - target->y_pos)/sqrt((pow(creator->x_pos - target->x_pos,2)+pow(creator->y_pos - target->y_pos,2)))) * 57.296;
	degrees += 90;

	animationTimerStop = SDL_GetTicks();
	if (animationTimerStop - animationTimerStart > 50) {
		frameCount = randomSizeT( 0, numTextures-1 );
	}

	if (creator->x_pos < target->x_pos) {
		degrees = -degrees;
	}


	glPushMatrix();
	glBindTexture( GL_TEXTURE_2D, spellTexture->texture[frameCount].texture);

	glTranslatef(creator->x_pos+32, creator->y_pos+32, 0.0f);
	glRotatef(degrees,0.0f,0.0f,1.0f);
	glTranslatef(-160-creator->x_pos,-creator->y_pos-32,0.0);

	glBegin( GL_QUADS );
	// Bottom-left vertex (corner)
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( creator->x_pos+32, creator->y_pos+64, 0.0f );
	// Bottom-right vertex (corner)
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( creator->x_pos+256+32, creator->y_pos+64, 0.0f );
	// Top-right vertex (corner)
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( creator->x_pos+256+32, creator->y_pos+400+64, 0.0f );
	// Top-left vertex (corner)
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( creator->x_pos+32, creator->y_pos+400+64, 0.0f );
	glEnd();
	glPopMatrix();
}

/// SpellCreation factory methods

namespace SpellCreation
{

	void initSpells()
	{
		MagicMissileSpell::init();
		LightningSpell::init();
		HealOtherSpell::init();
		HealingSpell::init();
	}
	
	CSpellActionBase* getMagicMissileSpell()
	{
		return new MagicMissileSpell();
	}
	
	CSpellActionBase* getLightningSpell()
	{
		return new LightningSpell();
	}
	
	CSpellActionBase* getHealingSpell()
	{
		return new HealingSpell();
	}
	
	CSpellActionBase* getHealOtherSpell()
	{
		return new HealOtherSpell();
	}
	
	CSpellActionBase* getGeneralDamageSpell()
	{
		uint16_t castTime = 1500;
		uint16_t manaCost = 120;
		uint16_t delayTime = 0;
		bool moveToTarget = false;
		uint16_t minDirectDamage = 1; // This should be a list of effects
		uint16_t maxDirectDamage = 10;
		ElementType::ElementType elementDirect = ElementType::Air;
		
		double minContinuousDamagePerSecond = 5.5;
		double maxContinuousDamagePerSecond = 5.5;
		ElementType::ElementType elementContinuous = ElementType::Light;
		uint16_t continuousDamageTime = 4000;
		
		std::string name = "DUMMY - not set yet";
		std::string info = "DUMMY description";
	
		std::auto_ptr<GeneralDamageSpell> newSpell( new GeneralDamageSpell() );

		newSpell->castTime = castTime;
		newSpell->manaCost = manaCost;
		newSpell->delayTime = delayTime;
		newSpell->moveToTarget = moveToTarget;
		newSpell->minDirectDamage = minDirectDamage; // This should be a list of effects
		newSpell->maxDirectDamage = maxDirectDamage;
		newSpell->elementDirect = elementDirect;
		
		newSpell->minContinuousDamagePerSecond = minContinuousDamagePerSecond;
		newSpell->maxContinuousDamagePerSecond = maxContinuousDamagePerSecond;
		newSpell->elementContinuous = elementContinuous;
		newSpell->continuousDamageTime = continuousDamageTime;
		
		newSpell->name = name;
		newSpell->info = info;
		
		return newSpell.release();
	}

} // namespace SpellCreation

#include "ActionBar.h"
extern std::auto_ptr<ActionBar> actionBar;

namespace DawnInterface
{
	GeneralDamageSpell* createGeneralDamageSpell()
	{
		 std::auto_ptr<GeneralDamageSpell> newSpell( dynamic_cast<GeneralDamageSpell*>( SpellCreation::getGeneralDamageSpell() ) );
		 return newSpell.release();
	}
}



