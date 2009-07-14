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
#include "CNPC.h"

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

    virtual void applyEffect()
    {
        int damage = 1 + rand() % 5 + 5;

        target->modifyCurHealth( -damage );
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

    LightningSpell( CCharacter *caster_, CNPC *target_ )
        : CSpell( LightningSpell::getStaticCastTime(),
                  LightningSpell::getStaticManaCost(),
                  LightningSpell::getStaticName(),
                  LightningSpell::getStaticSpellInfo() ),
          caster( caster_ ),
          target( target_ )
    {
    }

    virtual void applyEffect()
    {
        int damage = 1 + rand() % 60 + 30;

        target->modifyCurHealth( -damage );
    }

  private:
    CCharacter *caster;
    CNPC *target;
};

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

    virtual void applyEffect()
    {
        int healEffect = 50;

        target->modifyCurHealth( healEffect );
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

    virtual void applyEffect()
    {
        int healing = 100;

        caster->modifyCurHealth( healing );
    }

  private:
    CCharacter *caster;
};

/// SpellCreation factory methods

namespace SpellCreation
{

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



