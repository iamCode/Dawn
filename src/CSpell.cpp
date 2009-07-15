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
#include "CCharacter.h"
#include "CTexture.h"

/// Implementation of class CSpell

CSpell::CSpell( uint16_t castTime_, uint16_t manaCost_, std::string name_, std::string spellInfo_ )
    : castTime( castTime_ ),
      manaCost( manaCost_ ),
      name( name_ ),
      spellInfo( spellInfo_ )
{
}

uint16_t CSpell::getCastTime() const
{
    return castTime;
}

uint16_t CSpell::getManaCost() const
{
    return manaCost;
}

std::string CSpell::getName() const
{
    return name;
}

std::string CSpell::getSpellInfo() const
{
    return spellInfo;
}

/// Magic Missile

class MagicMissileSpell : public CSpell
{
  public:
    static uint16_t getStaticCastTime()
    {
        return 1000;
    }

    static uint16_t getStaticManaCost()
    {
        return 10;
    }

    static std::string getStaticName()
    {
        return "Magic Missile";
    }

    static std::string getStaticSpellInfo()
    {
        return "Causes 5 + (1 to 5) points of lightning damage to the target.\n";
    }

    MagicMissileSpell( CCharacter *caster_, CNPC *target_ )
        : CSpell( MagicMissileSpell::getStaticCastTime(),
                  MagicMissileSpell::getStaticManaCost(),
                  MagicMissileSpell::getStaticName(),
                  MagicMissileSpell::getStaticSpellInfo() ),
          caster( caster_ ),
          target( target_ )
    {
    }

    virtual void startEffect()
    {
        int damage = 1 + rand() % 5 + 5;

        target->Damage( damage );
    }

    virtual void inEffect()
    {
    }

    virtual void drawSpellEffect()
    {
    }

    virtual bool isEffectComplete()
    {
        return true;
    }

  private:
    CCharacter *caster;
    CNPC *target;
};

/// Lightning spell

class LightningSpell : public CSpell
{
  public:
    static uint16_t getStaticCastTime()
    {
        return 3000;
    }

    static uint16_t getStaticManaCost()
    {
        return 20;
    }

    static std::string getStaticName()
    {
        return "Lightning";
    }

    static std::string getStaticSpellInfo()
    {
        return "Causes 30 + (1 to 60) points of lightning damage to the target.\n";
    }

    static CTexture *spellTexture;

    static void init()
    {
        LightningSpell::spellTexture = new CTexture();
        LightningSpell::spellTexture->texture.reserve( 1 );
        LightningSpell::spellTexture->LoadIMG( "data/lightning.tga", 0 );
    }

    LightningSpell( CCharacter *caster_, CNPC *target_ )
        : CSpell( LightningSpell::getStaticCastTime(),
                  LightningSpell::getStaticManaCost(),
                  LightningSpell::getStaticName(),
                  LightningSpell::getStaticSpellInfo() ),
          caster( caster_ ),
          target( target_ ),
          finished( false ),
          continuousDamageCaused( 0 )
    {
    }

    virtual void startEffect()
    {
        int damage = 1 + rand() % 60;

        target->Damage( damage );
        effectStart = SDL_GetTicks();
        lastEffect = effectStart;
    }

    virtual void inEffect()
    {
        uint32_t curTime = SDL_GetTicks();
        int curDamage = static_cast<int>( (curTime - lastEffect) / 50 );
        bool callFinish = false;

        if ( continuousDamageCaused + curDamage >= 30 )
        {
            curDamage = 30 - continuousDamageCaused;
            callFinish = true;
        }

        if ( curDamage > 0 )
        {
            target->Damage( curDamage );
            lastEffect += curDamage * 50;
            continuousDamageCaused += curDamage;
        }

        if ( callFinish || ! target->isAlive() )
        {
            finishEffect();
        }
    }

    void finishEffect()
    {
        finished = true;
    }

    virtual void drawSpellEffect()
    {
        double percentageTodo = static_cast<double>(continuousDamageCaused)/30;
        DrawingHelpers::mapTextureToRect( 
                LightningSpell::spellTexture->texture[0].texture, 
                target->x_pos + percentageTodo * 0.5 * target->texture->texture[1].width, target->texture->texture[1].width * (1-percentageTodo),
                target->y_pos + percentageTodo * 0.5 * target->texture->texture[1].height, target->texture->texture[1].height * (1-percentageTodo) );
    }

    virtual bool isEffectComplete()
    {
        return finished;
    }

  private:
    CCharacter *caster;
    CNPC *target;
    uint32_t effectStart;
    uint32_t lastEffect;
    bool finished;
    int continuousDamageCaused;
};

CTexture *LightningSpell::spellTexture = NULL;

/// Heal Other spell

class HealOtherSpell : public CSpell
{
  public:
    static uint16_t getStaticCastTime()
    {
        return 4000;
    }

    static uint16_t getStaticManaCost()
    {
        return 40;
    }

    static std::string getStaticName()
    {
        return "Heal Other";
    }

    static std::string getStaticSpellInfo()
    {
        return "Heals 50 points of damage on the target.\n";
    }

    HealOtherSpell( CCharacter *caster_, CNPC *target_ )
        : CSpell( HealOtherSpell::getStaticCastTime(),
                  HealOtherSpell::getStaticManaCost(),
                  HealOtherSpell::getStaticName(),
                  HealOtherSpell::getStaticSpellInfo() ),
          caster( caster_ ),
          target( target_ )
    {
    }

    virtual void startEffect()
    {
        int healEffect = 50;

        target->Heal( healEffect );
    }

    virtual void inEffect()
    {
    }

    virtual void drawSpellEffect()
    {
    }

    virtual bool isEffectComplete()
    {
        return true;
    }

  private:
    CCharacter *caster;
    CNPC *target;
};

/// Healing spell

class HealingSpell : public CSpell
{
  public:
    static uint16_t getStaticCastTime()
    {
        return 5000;
    }

    static uint16_t getStaticManaCost()
    {
        return 50;
    }

    static std::string getStaticName()
    {
        return "Healing";
    }

    static std::string getStaticSpellInfo()
    {
        return "Heals 100 points of damage on self.\n";
    }

    HealingSpell( CCharacter *caster_ )
        : CSpell( HealingSpell::getStaticCastTime(),
                  HealingSpell::getStaticManaCost(),
                  HealingSpell::getStaticName(),
                  HealingSpell::getStaticSpellInfo() ),
          caster( caster_ )
    {
    }

    virtual void startEffect()
    {
        int healing = 100;

        caster->Heal( healing );
    }

    virtual void inEffect()
    {
    }

    virtual void drawSpellEffect()
    {
    }

    virtual bool isEffectComplete()
    {
        return true;
    }

  private:
    CCharacter *caster;
};

/// SpellCreation factory methods

namespace SpellCreation
{

void initSpells()
{
    LightningSpell::init();
}

/// TODO: as soon as CCharacter is the base and CNPC derived from it, make the target a CCharacter to allow
///       mobs to cast as well. This must be added to the spells as well.
CSpell* createSingleTargetSpellByName( std::string name, CCharacter *caster, CNPC *target )
{
    if ( name == LightningSpell::getStaticName() )
    {
        return new LightningSpell( caster, target );
    }
    else if ( name == MagicMissileSpell::getStaticName() )
    {
        return new MagicMissileSpell( caster, target );
    }
    else if ( name == HealOtherSpell::getStaticName() )
    {
        return new HealOtherSpell( caster, target );
    }
    else
    {
        std::cerr << "unknown single target spell \"" << name << "\"" << std::endl;
        abort();
    }
}

CSpell* createSelfAffectingSpellByName( std::string name, CCharacter *caster )
{
    if ( name == HealingSpell::getStaticName() )
    {
        return new HealingSpell( caster );
    }
    else
    {
        std::cerr << "unknown self affecting spell \"" << name << "\"" << std::endl;
        abort();
    }
}

} // namespace SpellCreation



