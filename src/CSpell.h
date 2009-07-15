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

#ifndef __C_SPELL_H_
#define __C_SPELL_H_

#include <string>

class CCharacter;
class CNPC;

namespace EffectType
{
    enum EffectType
    {
        SingleTargetSpell,
        SelfAffectingSpell
    };
}

class CSpell
{
  public:
    CSpell( uint16_t castTime, uint16_t manaCost, std::string name, std::string spellInfo );

    /// \brief Returns the time needed to cast a spell in ms.
    uint16_t getCastTime() const;
    uint16_t getManaCost() const;

    std::string getName() const;
    std::string getSpellInfo() const;

    virtual void drawSpellEffect() = 0;
    virtual void startEffect() = 0;
    virtual void inEffect() = 0;
    virtual bool isEffectComplete() = 0;

  private:
    uint16_t castTime;
    uint16_t manaCost;
    std::string name;
    std::string spellInfo;
};

namespace SpellCreation
{
    void initSpells();
    CSpell* createSingleTargetSpellByName( std::string name, CCharacter *caster, CNPC *target );
    CSpell* createSelfAffectingSpellByName( std::string name, CCharacter *caster );
}

#endif // __C_SPELL_H_
