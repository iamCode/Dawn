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

#include "CSpell.h"

#include <iostream>
#include <cstdlib>
#include <memory>
#include "CCharacter.h"
#include "CTexture.h"
#include "StatsSystem.h"
#include "CDrawingHelpers.h"

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

/// ConfigurableSpell

ConfigurableSpell::ConfigurableSpell()
{
	spellSymbol = NULL;

	castTime = 0;
	cooldown = 0;
	manaCost = 0;

	name = "";
	info = "";
}

ConfigurableSpell::ConfigurableSpell( ConfigurableSpell *other )
{
	spellSymbol = other->spellSymbol;

	castTime = other->castTime;
	cooldown = other->cooldown;
	manaCost = other->manaCost;

	name = other->name;
	info = other->info;
}

void ConfigurableSpell::setCastTime( uint16_t newCastTime )
{
	castTime = newCastTime;
}

uint16_t ConfigurableSpell::getCastTime() const
{
	return castTime;
}

void ConfigurableSpell::setCooldown( uint16_t newCooldown )
{
    cooldown = newCooldown;
}

uint16_t ConfigurableSpell::getCooldown() const
{
    return cooldown;
}

void ConfigurableSpell::setManaCost( uint16_t newManaCost )
{
	manaCost = newManaCost;
}

uint16_t ConfigurableSpell::getManaCost() const
{
	return manaCost;
}

void ConfigurableSpell::setName( std::string newName )
{
	name = newName;
}

std::string ConfigurableSpell::getName() const
{
	return name;
}

void ConfigurableSpell::setInfo( std::string newInfo )
{
	info = newInfo;
}

std::string ConfigurableSpell::getInfo() const
{
	return info;
}

void ConfigurableSpell::setSpellSymbol( std::string symbolFile )
{
	assert( spellSymbol == NULL );
	spellSymbol = new CTexture();
	spellSymbol->texture.resize(1);
	spellSymbol->LoadIMG( symbolFile, 0 );
}

CTexture* ConfigurableSpell::getSymbol() const {
	return spellSymbol;
}

/// GeneralDamageSpell


GeneralDamageSpell::GeneralDamageSpell()
{
	minDirectDamage = 0;
	maxDirectDamage = 0;
	elementDirect = ElementType::Air;

	minContinuousDamagePerSecond = 0.0;
	maxContinuousDamagePerSecond = 0.0;
	elementContinuous = ElementType::Air;
}

GeneralDamageSpell::GeneralDamageSpell( GeneralDamageSpell *other )
	: ConfigurableSpell( other )
{
	minDirectDamage = other->minDirectDamage; // This should be a list of effects
	maxDirectDamage = other->maxDirectDamage;
	elementDirect = other->elementDirect;

	minContinuousDamagePerSecond = other->minContinuousDamagePerSecond;
	maxContinuousDamagePerSecond = other->maxContinuousDamagePerSecond;
	elementContinuous = other->elementContinuous;
	continuousDamageTime = other->continuousDamageTime;
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

/// class GeneralRayDamageSpell

GeneralRayDamageSpell::GeneralRayDamageSpell()
{
	remainingEffect = 0;

	numTextures = 0;
	spellTexture = NULL;
}

GeneralRayDamageSpell::GeneralRayDamageSpell( GeneralRayDamageSpell *other )
	: GeneralDamageSpell( other )
{
	remainingEffect = 0;

	numTextures = other->numTextures;
	spellTexture = other->spellTexture;
}

CSpellActionBase* GeneralRayDamageSpell::cast( CCharacter *creator, CCharacter *target )
{
	GeneralRayDamageSpell* newSpell = new GeneralRayDamageSpell( this );
	newSpell->creator = creator;
	newSpell->target = target;

	return newSpell;
}

void GeneralRayDamageSpell::setNumAnimations( int count )
{
	assert( spellTexture == NULL );
	spellTexture = new CTexture();
	numTextures = count;
	spellTexture->texture.resize( count );
}

void GeneralRayDamageSpell::setAnimationTexture( int num, std::string filename )
{
	assert( spellTexture != NULL );
	assert( numTextures > num && num >= 0 );
	spellTexture->LoadIMG( filename, num );
}

void GeneralRayDamageSpell::startEffect()
{
	remainingEffect = 0.0;
	frameCount = 0;

	dealDirectDamage();

	effectStart = SDL_GetTicks();
	animationTimerStart = effectStart;
	lastEffect = effectStart;
	creator->addCooldownSpell( dynamic_cast<CSpell*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
}

void GeneralRayDamageSpell::inEffect()
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

void GeneralRayDamageSpell::finishEffect()
{
	markSpellActionAsFinished();
}

void GeneralRayDamageSpell::drawEffect()
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
	boltTexture->texture.resize( count );
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
	creator->addCooldownSpell( dynamic_cast<CSpell*> ( cast( NULL, NULL ) ) );
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

/// GeneralHealingSpell

GeneralHealingSpell::GeneralHealingSpell()
{
	effectType = EffectType::SelfAffectingSpell;
	healEffectMin = 0;
	healEffectMax = 0;
	healEffectElement = ElementType::Light;
}

GeneralHealingSpell::GeneralHealingSpell( GeneralHealingSpell *other )
	: ConfigurableSpell( other )
{
	effectType = other->effectType;
	healEffectMin = other->healEffectMin;
	healEffectMax = other->healEffectMax;
	healEffectElement = other->healEffectElement;
}

CSpellActionBase* GeneralHealingSpell::cast( CCharacter *creator, CCharacter *target )
{
	assert( effectType != EffectType::SelfAffectingSpell || creator == target );
	std::auto_ptr<GeneralHealingSpell> newSpell( new GeneralHealingSpell( this ) );
	newSpell->creator = creator;
	newSpell->target = target;

	return newSpell.release();
}

void GeneralHealingSpell::setEffectType( EffectType::EffectType newEffectType )
{
	assert( newEffectType == EffectType::SingleTargetSpell || newEffectType == EffectType::SelfAffectingSpell );
	effectType = newEffectType;
}

EffectType::EffectType GeneralHealingSpell::getEffectType() const
{
	return effectType;
}

void GeneralHealingSpell::setHealEffect( int healEffectMin, int healEffectMax, ElementType::ElementType healEffectElement )
{
	this->healEffectMin = healEffectMin;
	this->healEffectMax = healEffectMax;
	this->healEffectElement = healEffectElement;
}

int GeneralHealingSpell::getHealEffectMin() const
{
	return healEffectMin;
}

int GeneralHealingSpell::getHealEffectMax() const
{
	return healEffectMax;
}

ElementType::ElementType GeneralHealingSpell::getElementType() const
{
	return healEffectElement;
}

void GeneralHealingSpell::startEffect()
{
	int healing = randomSizeT( healEffectMin, healEffectMax );

	double effectFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( healEffectElement ), creator->getLevel() );
	double realEffect = healing * effectFactor;
	double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), creator->getLevel() );
	if ( randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000 ) {
		int criticalEffectMultiplier = 2;
		realEffect *= criticalEffectMultiplier;
	}
	int healEffectCaused = round( realEffect );


	target->Heal( healEffectCaused );
    creator->addCooldownSpell( dynamic_cast<CSpell*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
	markSpellActionAsFinished();
}

void GeneralHealingSpell::inEffect()
{
}

void GeneralHealingSpell::drawEffect()
{
}

/// GeneralBuffSpell

GeneralBuffSpell::GeneralBuffSpell()
{
	effectType = EffectType::SelfAffectingSpell;
	duration = 0;

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
}

GeneralBuffSpell::GeneralBuffSpell( GeneralBuffSpell *other )
	: ConfigurableSpell( other )
{
	effectType = other->effectType;
	duration = other->duration;
    statsModifier = other->statsModifier;
    resistElementModifier = other->resistElementModifier;
    spellEffectElementModifier = other->spellEffectElementModifier;
}

CSpellActionBase* GeneralBuffSpell::cast( CCharacter *creator, CCharacter *target )
{
	assert( effectType != EffectType::SelfAffectingSpell || creator == target );
	std::auto_ptr<GeneralBuffSpell> newSpell( new GeneralBuffSpell( this ) );
	newSpell->creator = creator;
	newSpell->target = target;

	return newSpell.release();
}

void GeneralBuffSpell::setEffectType( EffectType::EffectType newEffectType )
{
	assert( newEffectType == EffectType::SingleTargetSpell || newEffectType == EffectType::SelfAffectingSpell );
	effectType = newEffectType;
}

EffectType::EffectType GeneralBuffSpell::getEffectType() const
{
	return effectType;
}

void GeneralBuffSpell::setDuration( uint16_t newDuration )
{
    duration = newDuration;
}

uint16_t GeneralBuffSpell::getDuration() const
{
    return duration;
}

int16_t GeneralBuffSpell::getStats( StatsType::StatsType statsType ) const
{
    return statsModifier[ static_cast<size_t>( statsType ) ];
}

int16_t GeneralBuffSpell::getResistElementModifierPoints( ElementType::ElementType elementType ) const
{
	return resistElementModifier[ static_cast<size_t>(elementType) ];
}

int16_t GeneralBuffSpell::getSpellEffectElementModifierPoints( ElementType::ElementType elementType ) const
{
	return spellEffectElementModifier[ static_cast<size_t>(elementType) ];
}

void GeneralBuffSpell::setStats( StatsType::StatsType statsType, int16_t amount )
{
    statsModifier[ static_cast<size_t>( statsType ) ] = amount;
}

void GeneralBuffSpell::setResistElementModifierPoints( ElementType::ElementType elementType, int16_t resistModifierPoints )
{
	resistElementModifier[ static_cast<size_t>( elementType ) ] = resistModifierPoints;
}

void GeneralBuffSpell::setSpellEffectElementModifierPoints( ElementType::ElementType elementType, int16_t spellEffectElementModifierPoints )
{
	spellEffectElementModifier[ static_cast<size_t>( elementType ) ] = spellEffectElementModifierPoints;
}

void GeneralBuffSpell::startEffect()
{
	creator->addActiveSpell( cast( NULL, NULL ) );
	creator->addCooldownSpell( dynamic_cast<CSpell*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
	markSpellActionAsFinished();
}

void GeneralBuffSpell::inEffect()
{
}

void GeneralBuffSpell::drawEffect()
{
}

/// SpellCreation factory methods

namespace SpellCreation
{
	CSpellActionBase* getGeneralRayDamageSpell()
	{
		return new GeneralRayDamageSpell();
	}

	CSpellActionBase* getGeneralBoltDamageSpell()
	{
		return new GeneralBoltDamageSpell();
	}

	CSpellActionBase* getGeneralHealingSpell()
	{
		return new GeneralHealingSpell();
	}

	CSpellActionBase* getGeneralBuffSpell()
	{
		return new GeneralBuffSpell();
	}

} // namespace SpellCreation

namespace DawnInterface
{
	GeneralRayDamageSpell* createGeneralRayDamageSpell()
	{
		 std::auto_ptr<GeneralRayDamageSpell> newSpell( dynamic_cast<GeneralRayDamageSpell*>( SpellCreation::getGeneralRayDamageSpell() ) );
		 return newSpell.release();
	}

	GeneralBoltDamageSpell* createGeneralBoltDamageSpell()
	{
		 std::auto_ptr<GeneralBoltDamageSpell> newSpell( dynamic_cast<GeneralBoltDamageSpell*>( SpellCreation::getGeneralBoltDamageSpell() ) );
		 return newSpell.release();
	}

	GeneralHealingSpell* createGeneralHealingSpell()
	{
		std::auto_ptr<GeneralHealingSpell> newSpell( dynamic_cast<GeneralHealingSpell*>( SpellCreation::getGeneralHealingSpell() ) );
		return newSpell.release();
	}

	GeneralBuffSpell* createGeneralBuffSpell()
	{
		std::auto_ptr<GeneralBuffSpell> newSpell( dynamic_cast<GeneralBuffSpell*>( SpellCreation::getGeneralBuffSpell() ) );
		return newSpell.release();
	}
}



