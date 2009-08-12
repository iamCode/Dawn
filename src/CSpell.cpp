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

/// Implementation of class CSpellActionBase

CSpellActionBase::CSpellActionBase( uint16_t castTime_, uint16_t manaCost_, std::string name_, std::string info_ )
    : castTime( castTime_ ),
      manaCost( manaCost_ ),
      name( name_ ),
      info( info_ )
{
}

uint16_t CSpellActionBase::getCastTime() const
{
    return castTime;
}

uint16_t CSpellActionBase::getManaCost() const
{
    return manaCost;
}

std::string CSpellActionBase::getName() const
{
    return name;
}

std::string CSpellActionBase::getInfo() const
{
    return info;
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

    static CTexture *spellTexture;
    static CTexture *spellSymbol;

    static void init()
    {
        spellTexture = new CTexture();
        spellTexture->texture.reserve( 1 );
        spellTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );

        spellSymbol = new CTexture();
        spellSymbol->texture.reserve( 1 );
        spellSymbol->LoadIMG( "data/spells/magicmissile/symbol.tga", 0 );
    }

    static CTexture* getStaticSymbol()
    {
        return spellSymbol;
    }

    MagicMissileSpell( CCharacter *caster_, CCharacter *target_ )
        : CSpell( getStaticCastTime(),
                  getStaticManaCost(),
                  getStaticName(),
                  getStaticSpellInfo() ),
          caster( caster_ ),
          target( target_ ),
          finished( false )
    {
    }

    virtual void startEffect()
    {
        effectStart = SDL_GetTicks();
        lastEffect = effectStart;
        posx = caster->getXPos() + (caster->getWidth() / 2);
        posy = caster->getYPos() + (caster->getHeight() / 2);
    }

    virtual void inEffect()
    {
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
        
        if ( percdist >= 1.0 )
        {
            movex = dx;
            movey = dy;
        }
        else
        {
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

    void finishEffect()
    {
        int damage = 1 + rand() % 5 + 5;

        target->Damage( damage );
        finished = true;
    }

    virtual void drawEffect()
    {
        DrawingHelpers::mapTextureToRect( 
                spellTexture->texture[0].texture, 
                posx - 16, 32,
                posy - 16, 32 );
    }

    virtual bool isEffectComplete()
    {
        return finished;
    }

  private:
    CCharacter *caster;
    CCharacter *target;
    uint32_t effectStart;
    uint32_t lastEffect;
    bool finished;
    int posx, posy;
};

CTexture *MagicMissileSpell::spellTexture = NULL;
CTexture *MagicMissileSpell::spellSymbol = NULL;

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
    static CTexture *spellSymbol;

    static void init()
    {
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

    static CTexture* getStaticSymbol()
    {
        return spellSymbol;
    }

    LightningSpell( CCharacter *caster_, CCharacter *target_ )
        : CSpell( getStaticCastTime(),
                  getStaticManaCost(),
                  getStaticName(),
                  getStaticSpellInfo() ),
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

    virtual void drawEffect()
    {
        double percentageTodo = static_cast<double>(continuousDamageCaused)/30;
        float degrees;
        degrees = asin((caster->y_pos - target->y_pos)/sqrt((pow(caster->x_pos - target->x_pos,2)+pow(caster->y_pos - target->y_pos,2)))) * 57,296;
        degrees += 90;

        animationTimerStop = SDL_GetTicks();
        if (animationTimerStop - animationTimerStart > 50)
        {
            frameCount = rand() % 4;
        }

        if (caster->x_pos < target->x_pos) { degrees = -degrees; }


        glPushMatrix();
            glBindTexture( GL_TEXTURE_2D, spellTexture->texture[frameCount].texture);

            glTranslatef(caster->x_pos+32, caster->y_pos+32, 0.0f);
            glRotatef(degrees,0.0f,0.0f,1.0f);
            glTranslatef(-160-caster->x_pos,-caster->y_pos-32,0.0);

            glBegin( GL_QUADS );
            // Bottom-left vertex (corner)
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( caster->x_pos+32, caster->y_pos+64, 0.0f );
                // Bottom-right vertex (corner)
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f( caster->x_pos+256+32, caster->y_pos+64, 0.0f );
                // Top-right vertex (corner)
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f( caster->x_pos+256+32, caster->y_pos+400+64, 0.0f );
                // Top-left vertex (corner)
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( caster->x_pos+32, caster->y_pos+400+64, 0.0f );
            glEnd();
        glPopMatrix();
    }

    virtual bool isEffectComplete()
    {
        return finished;
    }

  private:
    CCharacter *caster;
    CCharacter *target;
    uint8_t frameCount;
    uint32_t effectStart;
    uint32_t lastEffect;
    uint32_t animationTimerStart;
    uint32_t animationTimerStop;
    bool finished;
    int continuousDamageCaused;
};

CTexture *LightningSpell::spellTexture = NULL;
CTexture *LightningSpell::spellSymbol = NULL;

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

    HealOtherSpell( CCharacter *caster_, CCharacter *target_ )
        : CSpell( getStaticCastTime(),
                  getStaticManaCost(),
                  getStaticName(),
                  getStaticSpellInfo() ),
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

    virtual void drawEffect()
    {
    }

    virtual bool isEffectComplete()
    {
        return true;
    }

  private:
    CCharacter *caster;
    CCharacter *target;
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
        : CSpell( getStaticCastTime(),
                  getStaticManaCost(),
                  getStaticName(),
                  getStaticSpellInfo() ),
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

    virtual void drawEffect()
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
    MagicMissileSpell::init();
    LightningSpell::init();
}

CTexture* getSpellSymbolByName( std::string name )
{
    if ( name == LightningSpell::getStaticName() )
    {
        return LightningSpell::getStaticSymbol();
    }
    else if ( name == MagicMissileSpell::getStaticName() )
    {
        return MagicMissileSpell::getStaticSymbol();
    }
    else
    {
        std::cerr << "symbol for spell \"" << name << "\" not implemented yet" << std::endl;
        abort();
    }
} 

CSpell* createSingleTargetSpellByName( std::string name, CCharacter *caster, CCharacter *target )
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



