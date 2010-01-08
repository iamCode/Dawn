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


GeneralDamageSpell::GeneralDamageSpell()
{
	spellSymbol = NULL;
	
	castTime = 0;
	manaCost = 0;
	minDirectDamage = 0;
	maxDirectDamage = 0;
	elementDirect = ElementType::Air;
	
	minContinuousDamagePerSecond = 0.0;
	maxContinuousDamagePerSecond = 0.0;
	elementContinuous = ElementType::Air;
	
	name = "";
	info = "";
}

GeneralDamageSpell::GeneralDamageSpell( GeneralDamageSpell *other )
{
	spellSymbol = other->spellSymbol;

	castTime = other->castTime;
	manaCost = other->manaCost;
	minDirectDamage = other->minDirectDamage; // This should be a list of effects
	maxDirectDamage = other->maxDirectDamage;
	elementDirect = other->elementDirect;

	minContinuousDamagePerSecond = other->minContinuousDamagePerSecond;
	maxContinuousDamagePerSecond = other->maxContinuousDamagePerSecond;
	elementContinuous = other->elementContinuous;
	continuousDamageTime = other->continuousDamageTime;

	name = other->name;
	info = other->info;
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

CTexture* GeneralDamageSpell::getSymbol() const {
	return spellSymbol;
}

EffectType::EffectType GeneralDamageSpell::getEffectType() const
{
	return EffectType::SingleTargetSpell;
}

void GeneralDamageSpell::dealDirectDamage()
{
	int damage = minDirectDamage + rand() % (maxDirectDamage - minDirectDamage);
	
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
}

double GeneralDamageSpell::calculateContinuousDamage( uint64_t timePassed )
{
	double secondsPassed = (timePassed) / 1000.0;
	
	double curRandDamage = randomDouble( minContinuousDamagePerSecond * secondsPassed, maxContinuousDamagePerSecond * secondsPassed );

	double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( elementContinuous ), target->getLevel() );
	double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( elementContinuous ), creator->getLevel() );
	double realDamage = curRandDamage * damageFactor * (1-resist);
	return realDamage;
}

/// class GeneralBarDamageSpell

GeneralBarDamageSpell::GeneralBarDamageSpell()
{
	remainingEffect = 0;

	numTextures = 0;
	spellTexture = NULL;
}

GeneralBarDamageSpell::GeneralBarDamageSpell( GeneralBarDamageSpell *other )
	: GeneralDamageSpell( other )
{
	remainingEffect = 0;

	numTextures = other->numTextures;
	spellTexture = other->spellTexture;
}

CSpellActionBase* GeneralBarDamageSpell::cast( CCharacter *creator, CCharacter *target )
{
	GeneralBarDamageSpell* newSpell = new GeneralBarDamageSpell( this );
	newSpell->creator = creator;
	newSpell->target = target;
	
	return newSpell;
}

void GeneralBarDamageSpell::setNumAnimations( int count )
{
	assert( spellTexture == NULL );
	spellTexture = new CTexture();
	numTextures = count;
	spellTexture->texture.reserve( count );
}

void GeneralBarDamageSpell::setAnimationTexture( int num, std::string filename )
{
	assert( spellTexture != NULL );
	assert( numTextures > num && num >= 0 );
	spellTexture->LoadIMG( filename, num );
}

void GeneralBarDamageSpell::startEffect()
{
	remainingEffect = 0.0;
	frameCount = 0;

	dealDirectDamage();

	effectStart = SDL_GetTicks();
	animationTimerStart = effectStart;
	lastEffect = effectStart;
	unbindFromCreator();
}

void GeneralBarDamageSpell::inEffect()
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

	remainingEffect += calculateContinuousDamage( elapsedSinceLast );
	// no critical damage in this phase so far

	bool callFinish = false;
	if ( elapsedSinceStart >= continuousDamageTime ) {
		callFinish = true;
	}

	if ( floor(remainingEffect) > 0 ) {
		target->Damage( floor(remainingEffect), false );
		remainingEffect = remainingEffect - floor( remainingEffect );
		if ( ! target->isAlive() ) {
			creator->gainExperience( target->getModifiedMaxHealth() / 10 );
		}
		lastEffect = curTime;
	}

	if ( callFinish || ! target->isAlive() ) {
		finishEffect();
	}
}

void GeneralBarDamageSpell::finishEffect()
{
	markSpellActionAsFinished();
}

void GeneralBarDamageSpell::drawEffect()
{
	float degrees;
	degrees = asin((creator->y_pos - target->y_pos)/sqrt((pow(creator->x_pos - target->x_pos,2)+pow(creator->y_pos - target->y_pos,2)))) * 57.296;
	degrees += 90;

	animationTimerStop = SDL_GetTicks();
	frameCount = static_cast<size_t>((animationTimerStop - animationTimerStart) / 50) % numTextures;

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

/// class GeneralBoltDamageSpell


GeneralBoltDamageSpell::GeneralBoltDamageSpell()
{
	numBoltTextures = 0;
	boltTexture = NULL;
	moveSpeed = 1;
	expireTime = 10000;
}

GeneralBoltDamageSpell::GeneralBoltDamageSpell( GeneralBoltDamageSpell *other )
	: GeneralDamageSpell( other )
{
	numBoltTextures = other->numBoltTextures;
	boltTexture = other->boltTexture;
	moveSpeed = other->moveSpeed;
	expireTime = other->expireTime;
}

CSpellActionBase* GeneralBoltDamageSpell::cast( CCharacter *creator, CCharacter *target )
{
	GeneralBoltDamageSpell* newSpell = new GeneralBoltDamageSpell( this );
	newSpell->creator = creator;
	newSpell->target = target;
	
	return newSpell;
}

void GeneralBoltDamageSpell::setMoveSpeed( int newMoveSpeed )
{
	moveSpeed = newMoveSpeed;
}

void GeneralBoltDamageSpell::setExpireTime( int newExpireTime )
{
	expireTime = newExpireTime;
}

void GeneralBoltDamageSpell::setNumAnimations( int count )
{
	assert( boltTexture == NULL );
	boltTexture = new CTexture();
	numBoltTextures = count;
	boltTexture->texture.reserve( count );
}

void GeneralBoltDamageSpell::setAnimationTexture( int num, std::string filename )
{
	assert( boltTexture != NULL );
	assert( numBoltTextures > num && num >= 0 );
	boltTexture->LoadIMG( filename, num );
}

void GeneralBoltDamageSpell::startEffect()
{
	frameCount = 0;
	moveRemaining = 0.0;
	effectStart = SDL_GetTicks();
	animationTimerStart = effectStart;
	lastEffect = effectStart;
	posx = creator->getXPos() + (creator->getWidth() / 2);
	posy = creator->getYPos() + (creator->getHeight() / 2);
	unbindFromCreator();
}

void GeneralBoltDamageSpell::inEffect()
{
	uint32_t curTicks = SDL_GetTicks();
	moveRemaining += moveSpeed * (curTicks - lastEffect) / 1000.0;
	int targetx = target->getXPos() + (target->getWidth() / 2);
	int targety = target->getYPos() + (target->getHeight() / 2);
	int dx = targetx - posx;
	int dy = targety - posy;
	double dist = sqrt( (dx * dx) + (dy * dy) );
	double percdist = (moveRemaining / dist);
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
	moveRemaining -= movedDist;
	lastEffect = curTicks;

	posx += movex;
	posy += movey;

	if ( (posx == targetx && posy == targety) ) {
		finishEffect();
	} else if ( (curTicks - effectStart) > expireTime ) {
		markSpellActionAsFinished();
	}
}

void GeneralBoltDamageSpell::finishEffect()
{
	dealDirectDamage();
	markSpellActionAsFinished();
}

void GeneralBoltDamageSpell::drawEffect()
{
	int targetx = target->getXPos() + (target->getWidth() / 2);
	int targety = target->getYPos() + (target->getHeight() / 2);
	float degrees;
	degrees = asin((posy - targety)/sqrt((pow(posx - targetx,2)+pow(posy - targety,2)))) * 57.296;
	degrees += 90;

	animationTimerStop = SDL_GetTicks();
	frameCount = static_cast<size_t>((animationTimerStop - animationTimerStart) / 50) % numBoltTextures;

	if (posx < targetx) {
		degrees = -degrees;
	}

	int textureWidth = target->getWidth()/2;
	int textureHeight = target->getWidth()/2;
	glPushMatrix();
	glTranslatef(posx, posy, 0.0f);
	glRotatef(degrees,0.0f,0.0f,1.0f);
	glTranslatef(-textureWidth/2, -textureHeight/2, 0.0f);

	DrawingHelpers::mapTextureToRect(
			    boltTexture->texture[frameCount].texture,
			    0, textureWidth,
			    0, textureHeight );
	glPopMatrix();
}

/// SpellCreation factory methods

namespace SpellCreation
{

	void initSpells()
	{
		HealOtherSpell::init();
		HealingSpell::init();
	}
	
	CSpellActionBase* getHealingSpell()
	{
		return new HealingSpell();
	}
	
	CSpellActionBase* getHealOtherSpell()
	{
		return new HealOtherSpell();
	}
	
	CSpellActionBase* getGeneralBarDamageSpell()
	{
		return new GeneralBarDamageSpell();
	}
	
	CSpellActionBase* getGeneralBoltDamageSpell()
	{
		return new GeneralBoltDamageSpell();
	}

} // namespace SpellCreation

namespace DawnInterface
{
	GeneralBarDamageSpell* createGeneralBarDamageSpell()
	{
		 std::auto_ptr<GeneralBarDamageSpell> newSpell( dynamic_cast<GeneralBarDamageSpell*>( SpellCreation::getGeneralBarDamageSpell() ) );
		 return newSpell.release();
	}
	
	GeneralBoltDamageSpell* createGeneralBoltDamageSpell()
	{
		 std::auto_ptr<GeneralBoltDamageSpell> newSpell( dynamic_cast<GeneralBoltDamageSpell*>( SpellCreation::getGeneralBoltDamageSpell() ) );
		 return newSpell.release();
	}
}



