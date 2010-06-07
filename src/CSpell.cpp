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

size_t randomSizeT( size_t min, size_t max )
{
	return min + ( static_cast<size_t>((max - min) * static_cast<double>(rand())/static_cast<double>(RAND_MAX + 1.0) - 0.5 ) );
}

double randomDouble( double min, double max )
{
	return min + ( (max - min) * static_cast<double>(rand())/static_cast<double>(RAND_MAX) );
}

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
		if ( creator->getArchType() == CharacterArchType::Fighter ) {
	        creator->modifyCurrentFatigue( -getSpellCost() );
	    } else {
	        creator->modifyCurrentMana( -getSpellCost() );
	    }
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

std::string CSpellActionBase::getID() const
{
	std::string name = getName();
	std::ostringstream idstream;
	for ( size_t curChar=0; curChar<name.size(); ++curChar ) {
		if ( isspace( name[curChar] ) ) {
			// ignore
		} else if ( isupper( name[curChar] ) ) {
			idstream << char( tolower( name[curChar] ) );
		} else {
			idstream << char( name[curChar] );
		}
	}
	return idstream.str();
}

void CSpellActionBase::addAdditionalSpell( CSpellActionBase *spell, double chanceToExecute )
{
    additionalSpells.push_back( std::pair<CSpellActionBase*,double>( spell, chanceToExecute ) );
}

/// ConfigurableSpell

ConfigurableSpell::ConfigurableSpell()
{
	spellSymbol = NULL;

	castTime = 0;
	cooldown = 0;
	spellCost = 0;
	duration = 0;
	minRange = 0;
	maxRange = 460; // default maxrange for spells. Can be overridden with setRange().

	name = "";
	info = "";
}

ConfigurableSpell::ConfigurableSpell( ConfigurableSpell *other )
{
	spellSymbol = other->spellSymbol;

	castTime = other->castTime;
	cooldown = other->cooldown;
	spellCost = other->spellCost;
	duration = other->duration;
    minRange = other->minRange;
    maxRange = other->maxRange;

    additionalSpells = other->additionalSpells;

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

void ConfigurableSpell::setSpellCost( uint16_t spellCost )
{
	this->spellCost = spellCost;
}

uint16_t ConfigurableSpell::getSpellCost() const
{
	return spellCost;
}

void ConfigurableSpell::setRange( uint16_t minRange, uint16_t maxRange )
{
	this->minRange = minRange;
	this->maxRange = maxRange;
}

bool ConfigurableSpell::isInRange( uint16_t distance ) const
{
    if ( distance >= minRange && distance <= maxRange )
    {
        return true;
    }
    return false;
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

void ConfigurableSpell::setDuration( uint16_t newDuration )
{
    duration = newDuration;
}

uint16_t ConfigurableSpell::getDuration() const
{
    return duration;
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


/// ConfigurableAction

ConfigurableAction::ConfigurableAction()
{
	spellSymbol = NULL;

	castTime = 0;
	cooldown = 0;
	spellCost = 0;
	duration = 0;
    minRange = 0;
    maxRange = 100; // default maxrange for melee actions. Can be overridden with setRange().

	name = "";
	info = "";
}

ConfigurableAction::ConfigurableAction( ConfigurableAction *other )
{
	spellSymbol = other->spellSymbol;

	castTime = other->castTime;
	cooldown = other->cooldown;
	spellCost = other->spellCost;
	duration = other->duration;
    minRange = other->minRange;
    maxRange = other->maxRange;

    additionalSpells = other->additionalSpells;

	name = other->name;
	info = other->info;
}

void ConfigurableAction::setCastTime( uint16_t newCastTime )
{
	castTime = newCastTime;
}

uint16_t ConfigurableAction::getCastTime() const
{
	return castTime;
}

void ConfigurableAction::setCooldown( uint16_t newCooldown )
{
    cooldown = newCooldown;
}

uint16_t ConfigurableAction::getCooldown() const
{
    return cooldown;
}

void ConfigurableAction::setSpellCost( uint16_t spellCost )
{
	this->spellCost = spellCost;
}

uint16_t ConfigurableAction::getSpellCost() const
{
	return spellCost;
}

void ConfigurableAction::setRange( uint16_t minRange, uint16_t maxRange )
{
	this->minRange = minRange;
	this->maxRange = maxRange;
}

bool ConfigurableAction::isInRange( uint16_t distance ) const
{
    if ( distance >= minRange && distance <= maxRange )
    {
        return true;
    }
    return false;
}

void ConfigurableAction::setName( std::string newName )
{
	name = newName;
}

std::string ConfigurableAction::getName() const
{
	return name;
}

void ConfigurableAction::setInfo( std::string newInfo )
{
	info = newInfo;
}

std::string ConfigurableAction::getInfo() const
{
	return info;
}

void ConfigurableAction::setDuration( uint16_t newDuration )
{
    duration = newDuration;
}

uint16_t ConfigurableAction::getDuration() const
{
    return duration;
}

void ConfigurableAction::setSpellSymbol( std::string symbolFile )
{
	assert( spellSymbol == NULL );
	spellSymbol = new CTexture();
	spellSymbol->texture.resize(1);
	spellSymbol->LoadIMG( symbolFile, 0 );
}

CTexture* ConfigurableAction::getSymbol() const {
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

	// setting a continous damage also sets a duration of the spell (so we can see it in the buffwindow)
	setDuration( static_cast<uint16_t> ( floor( continuousDamageTime / 1000 ) ) );
}

EffectType::EffectType GeneralDamageSpell::getEffectType() const
{
	return EffectType::SingleTargetSpell;
}

uint16_t GeneralDamageSpell::getDirectDamageMin() const
{
    return minDirectDamage;
}

uint16_t GeneralDamageSpell::getDirectDamageMax() const
{
    return maxDirectDamage;
}

ElementType::ElementType GeneralDamageSpell::getDirectDamageElement() const
{
    return elementDirect;
}

uint16_t GeneralDamageSpell::getContinuousDamageMin() const
{
    return minContinuousDamagePerSecond;
}

uint16_t GeneralDamageSpell::getContinuousDamageMax() const
{
    return maxContinuousDamagePerSecond;
}

ElementType::ElementType GeneralDamageSpell::getContinuousDamageElement() const
{
    return elementContinuous;
}

void GeneralDamageSpell::dealDirectDamage()
{
	if ( getDirectDamageMax() > 0 ) {
	    int damage = getDirectDamageMin() + rand() % ( getDirectDamageMax() - getDirectDamageMin() );

        double damageFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( getDirectDamageElement() ), target->getLevel() );
        double resist = StatsSystem::getStatsSystem()->complexGetResistElementChance( target->getLevel(), target->getModifiedResistElementModifierPoints( getDirectDamageElement() ), creator->getLevel() );
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
	creator->addCooldownSpell( dynamic_cast<CSpellActionBase*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
}

void GeneralRayDamageSpell::inEffect()
{
	uint32_t curTime = SDL_GetTicks();
	uint32_t elapsedSinceLast  = curTime - lastEffect;
	uint32_t elapsedSinceStart = curTime - effectStart;
	if ( curTime - lastEffect < 1000 ) {
		// do damage at most every 1 seconds unless effect is done
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

    // do we have an additional spell that perhaps should be cast?
    for ( size_t additionalSpell = 0; additionalSpell < additionalSpells.size(); additionalSpell++ ) {
        if ( randomSizeT( 0, 10000 ) <= additionalSpells[ additionalSpell ].second * 10000 ) {
            creator->executeSpellWithoutCasting( additionalSpells[ additionalSpell ].first );
        }
    }
}

void GeneralRayDamageSpell::drawEffect()
{
	if ( numTextures > 0 ) {
	    float degrees;
        degrees = asin((creator->getYPos() - target->getYPos())/sqrt((pow(creator->getXPos() - target->getXPos(),2)+pow(creator->getXPos() - target->getYPos(),2)))) * 57.296;
        degrees += 90;

        animationTimerStop = SDL_GetTicks();
        frameCount = static_cast<size_t>((animationTimerStop - animationTimerStart) / 50) % numTextures;

        if (creator->getXPos() < target->getXPos()) {
            degrees = -degrees;
        }


        glPushMatrix();
        glBindTexture( GL_TEXTURE_2D, spellTexture->texture[frameCount].texture);

        glTranslatef(creator->getXPos()+32, creator->getYPos()+32, 0.0f);
        glRotatef(degrees,0.0f,0.0f,1.0f);
        glTranslatef(-160-creator->getXPos(),-creator->getYPos()-32,0.0);

        glBegin( GL_QUADS );
        // Bottom-left vertex (corner)
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( creator->getXPos()+32, creator->getYPos()+64, 0.0f );
        // Bottom-right vertex (corner)
        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( creator->getXPos()+256+32, creator->getYPos()+64, 0.0f );
        // Top-right vertex (corner)
        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( creator->getXPos()+256+32, creator->getYPos()+400+64, 0.0f );
        // Top-left vertex (corner)
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( creator->getXPos()+32, creator->getYPos()+400+64, 0.0f );
        glEnd();
        glPopMatrix();
	}
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

	creator->addCooldownSpell( dynamic_cast<CSpellActionBase*> ( cast( NULL, NULL ) ) );
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

    // do we have an additional spell that perhaps should be cast?
    for ( size_t additionalSpell = 0; additionalSpell < additionalSpells.size(); additionalSpell++ ) {
        if ( randomSizeT( 0, 10000 ) <= additionalSpells[ additionalSpell ].second * 10000 ) {
            creator->executeSpellWithoutCasting( additionalSpells[ additionalSpell ].first );
        }
    }
}

void GeneralBoltDamageSpell::drawEffect()
{
	if ( numBoltTextures > 0 ) {
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
}

/// GeneralHealingSpell

GeneralHealingSpell::GeneralHealingSpell()
{
	effectType = EffectType::SelfAffectingSpell;
	healEffectMin = 0;
	healEffectMax = 0;
	healEffectElement = ElementType::Light;
	minContinuousHealingPerSecond = 0.0;
	maxContinuousHealingPerSecond = 0.0;
	elementContinuous = ElementType::Light;
	remainingEffect = 0.0;
    lastEffect = effectStart;
    continuousHealingTime = 0;
}

GeneralHealingSpell::GeneralHealingSpell( GeneralHealingSpell *other )
	: ConfigurableSpell( other )
{
	effectType = other->effectType;
	healEffectMin = other->healEffectMin;
	healEffectMax = other->healEffectMax;
	healEffectElement = other->healEffectElement;
	minContinuousHealingPerSecond = other->minContinuousHealingPerSecond;
	maxContinuousHealingPerSecond = other->maxContinuousHealingPerSecond;
	elementContinuous = other->elementContinuous;
	remainingEffect = other->remainingEffect;
    continuousHealingTime = other->continuousHealingTime;
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

ElementType::ElementType GeneralHealingSpell::getDirectElementType() const
{
    return healEffectElement;
}

uint16_t GeneralHealingSpell::getDirectHealingMin() const
{
    return healEffectMin;
}

uint16_t GeneralHealingSpell::getDirectHealingMax() const
{
    return healEffectMax;
}

ElementType::ElementType GeneralHealingSpell::getContinuousElementType() const
{
    return elementContinuous;
}

uint16_t GeneralHealingSpell::getContinuousHealingMin() const
{
    return minContinuousHealingPerSecond;
}

uint16_t GeneralHealingSpell::getContinuousHealingMax() const
{
    return maxContinuousHealingPerSecond;
}

void GeneralHealingSpell::setDirectHealing( int healEffectMin, int healEffectMax, ElementType::ElementType healEffectElement )
{
	this->healEffectMin = healEffectMin;
	this->healEffectMax = healEffectMax;
	this->healEffectElement = healEffectElement;
}

void GeneralHealingSpell::setContinuousHealing( double minContinuousHealingPerSecond, double maxContinuousHealingPerSecond, uint16_t continuousHealingTime, ElementType::ElementType elementContinuous )
{
	this->minContinuousHealingPerSecond = minContinuousHealingPerSecond;
	this->maxContinuousHealingPerSecond = maxContinuousHealingPerSecond;
	this->continuousHealingTime = continuousHealingTime;
	this->elementContinuous = elementContinuous;

	// setting a continous heal also sets a duration of the spell (so we can see it in the buffwindow)
	setDuration( static_cast<uint16_t> ( floor( continuousHealingTime / 1000 ) ) );
}

double GeneralHealingSpell::calculateContinuousHealing( uint64_t timePassed )
{
	double secondsPassed = (timePassed) / 1000.0;

	double curRandHealing = randomDouble( minContinuousHealingPerSecond * secondsPassed, maxContinuousHealingPerSecond * secondsPassed );

	double healingFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( elementContinuous ), target->getLevel() );
	double realHealing = curRandHealing * healingFactor;
	return realHealing;
}

void GeneralHealingSpell::startEffect()
{
	remainingEffect = 0.0;
    effectStart = SDL_GetTicks();
	lastEffect = effectStart;

	int healing = randomSizeT( healEffectMin, healEffectMax );

    // only do a heal if we've set a healing value to the spell.
	if ( ( healEffectMin + healEffectMax ) > 0 )
	{
	    double healingFactor = StatsSystem::getStatsSystem()->complexGetSpellEffectElementModifier( creator->getLevel(), creator->getModifiedSpellEffectElementModifierPoints( healEffectElement ), creator->getLevel() );
        double realHealing = healing * healingFactor;
        double spellCriticalChance = StatsSystem::getStatsSystem()->complexGetSpellCriticalStrikeChance( creator->getLevel(), creator->getModifiedSpellCriticalModifierPoints(), creator->getLevel() );
        if ( randomSizeT( 0, 10000 ) <= spellCriticalChance * 10000 ) {
            int criticalEffectMultiplier = 2;
            realHealing *= criticalEffectMultiplier;
        }
        int healingCaused = round( realHealing );

        target->Heal( healingCaused );
	}

    creator->addActiveSpell( cast( NULL, NULL ) );
    creator->addCooldownSpell( dynamic_cast<CSpellActionBase*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
}

void GeneralHealingSpell::inEffect()
{
    uint32_t curTime = SDL_GetTicks();
	uint32_t elapsedSinceLast  = curTime - lastEffect;
	uint32_t elapsedSinceStart = curTime - effectStart;
	if ( curTime - lastEffect < 1000 ) {
		// heal every second
		if ( elapsedSinceStart >= continuousHealingTime )
		{
			elapsedSinceLast = continuousHealingTime - (lastEffect - effectStart);
		}
		return;
	}

	remainingEffect += calculateContinuousHealing( elapsedSinceLast );

	bool callFinish = false;
	if ( elapsedSinceStart >= continuousHealingTime ) {
		callFinish = true;
	}

	if ( floor(remainingEffect) > 0 ) {
		target->Heal( floor(remainingEffect ) );
		remainingEffect = remainingEffect - floor( remainingEffect );
		lastEffect = curTime;
	}

	if ( callFinish ) {
		finishEffect();
	}
}

void GeneralHealingSpell::finishEffect()
{
	markSpellActionAsFinished();

    // do we have an additional spell that perhaps should be cast?
    for ( size_t additionalSpell = 0; additionalSpell < additionalSpells.size(); additionalSpell++ ) {
        if ( randomSizeT( 0, 10000 ) <= additionalSpells[ additionalSpell ].second * 10000 ) {
            creator->executeSpellWithoutCasting( additionalSpells[ additionalSpell ].first );
        }
    }
}

void GeneralHealingSpell::drawEffect()
{
}

/// GeneralBuffSpell

GeneralBuffSpell::GeneralBuffSpell()
{
	effectType = EffectType::SelfAffectingSpell;

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
	creator->addCooldownSpell( dynamic_cast<CSpellActionBase*> ( cast( NULL, NULL ) ) );
	unbindFromCreator();
	markSpellActionAsFinished();
}

void GeneralBuffSpell::inEffect()
{
}

void GeneralBuffSpell::drawEffect()
{
}

void GeneralBuffSpell::finishEffect()
{
    // do we have an additional spell that perhaps should be cast?
    for ( size_t additionalSpell = 0; additionalSpell < additionalSpells.size(); additionalSpell++ ) {
        if ( randomSizeT( 0, 10000 ) <= additionalSpells[ additionalSpell ].second * 10000 ) {
            creator->executeSpellWithoutCasting( additionalSpells[ additionalSpell ].first );
        }
    }
}

/// MeleeDamageAction

MeleeDamageAction::MeleeDamageAction()
{
	damageBonus = 1.0;
}

MeleeDamageAction::MeleeDamageAction( MeleeDamageAction *other )
	: ConfigurableAction( other )
{
    damageBonus = other->damageBonus;
}

CSpellActionBase* MeleeDamageAction::cast( CCharacter *creator, CCharacter *target )
{
	std::auto_ptr<MeleeDamageAction> newAction( new MeleeDamageAction( this ) );
	newAction->creator = creator;
	newAction->target = target;

	return newAction.release();
}

void MeleeDamageAction::setDamageBonus( double damageBonus )
{
    this->damageBonus = damageBonus;
}

double MeleeDamageAction::getDamageBonus() const
{
    return damageBonus;
}

void MeleeDamageAction::dealDamage()
{
    assert ( target != NULL );
    const StatsSystem *statsSystem = StatsSystem::getStatsSystem();

    double minDamage = creator->getModifiedMinDamage() * statsSystem->complexGetDamageModifier( creator->getLevel(), creator->getModifiedDamageModifierPoints(), target->getLevel() );
    double maxDamage = creator->getModifiedMaxDamage() * statsSystem->complexGetDamageModifier( creator->getLevel(), creator->getModifiedDamageModifierPoints(), target->getLevel() );
    int damage = randomSizeT( minDamage, maxDamage ) * damageBonus;

    double hitChance = statsSystem->complexGetHitChance( creator->getLevel(), creator->getModifiedHitModifierPoints(), target->getLevel() );
    double criticalHitChance = statsSystem->complexGetMeleeCriticalStrikeChance( creator->getLevel(), creator->getModifiedMeleeCriticalModifierPoints(), target->getLevel() );
    double targetEvadeChance = statsSystem->complexGetEvadeChance( target->getLevel(), target->getModifiedEvadeModifierPoints(), creator->getLevel() );
    double targetParryChance = statsSystem->complexGetParryChance( target->getLevel(), target->getModifiedParryModifierPoints(), creator->getLevel() );
    double targetBlockChance = statsSystem->complexGetBlockChance( target->getLevel(), target->getModifiedBlockModifierPoints(), creator->getLevel() );
    double damageReduction = statsSystem->complexGetDamageReductionModifier( target->getLevel(), target->getModifiedArmor(), creator->getLevel() );

    bool hasHit = randomSizeT( 0, 10000 ) <= hitChance * 10000;
    bool criticalHit = randomSizeT( 0, 10000 ) <= criticalHitChance * 10000;
    int criticalHitFactor = 2;
    bool targetEvaded = randomSizeT( 0, 10000 ) <= targetEvadeChance * 10000;
    bool targetParried = randomSizeT( 0, 10000 ) <= targetParryChance * 10000;
    bool targetBlocked = randomSizeT( 0, 10000 ) <= targetBlockChance * 10000;
    double blockFactor = 0.5;

    if ( hasHit && !targetEvaded && !targetParried ) {
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

double MeleeDamageAction::getProgress() const
{
    int32_t curTime = SDL_GetTicks();
    return ( ( curTime - effectStart ) / 650.0 );
}

EffectType::EffectType MeleeDamageAction::getEffectType() const
{
	return EffectType::SingleTargetSpell;
}

void MeleeDamageAction::startEffect()
{
	effectStart = SDL_GetTicks();
	creator->addCooldownSpell( dynamic_cast<CSpellActionBase*> ( cast( NULL, NULL ) ) );
}

void MeleeDamageAction::inEffect()
{
    if ( getProgress() >= 1.0 )
    {
        finishEffect();
    }
}

void MeleeDamageAction::drawEffect()
{
}

void MeleeDamageAction::finishEffect()
{
    dealDamage();
    markSpellActionAsFinished();

    // do we have an additional spell that perhaps should be cast?
    for ( size_t additionalSpell = 0; additionalSpell < additionalSpells.size(); additionalSpell++ ) {
        if ( randomSizeT( 0, 10000 ) <= additionalSpells[ additionalSpell ].second * 10000 ) {
            creator->executeSpellWithoutCasting( additionalSpells[ additionalSpell ].first );
        }
    }
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

	CSpellActionBase* getMeleeDamageAction()
	{
	    return new MeleeDamageAction();
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

	MeleeDamageAction* createMeleeDamageAction()
	{
	    std::auto_ptr<MeleeDamageAction> newAction( dynamic_cast<MeleeDamageAction*>( SpellCreation::getMeleeDamageAction() ) );
	    return newAction.release();
	}
}



