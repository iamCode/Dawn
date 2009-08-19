#include "CAction.h"

#include "CDrawingHelpers.h"
#include "CTexture.h"
#include "CCharacter.h"

/// melee attack

class AttackAction : public CAction
{
  public:
    static uint16_t getStaticCastTime()
    {
        return 0;
    }

    static uint16_t getStaticManaCost()
    {
        return 0;
    }

    static std::string getStaticName()
    {
        return "Melee Attack";
    }

    static std::string getStaticActionInfo()
    {
        return "Causes 20 points of damage to the target.\n";
    }

    static CTexture *actionTexture;
    static CTexture *actionSymbol;

    static void init()
    {
        actionTexture = new CTexture();
        actionTexture->texture.reserve(1);
        //actionTexture->LoadIMG( "data/actions/attack/attack.tga", 0 );
        actionTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );
        
        actionSymbol = new CTexture();
        actionSymbol->texture.reserve(1);
        //actionSymbol->LoadIMG( "data/actions/attack/symbol.tga", 0 );
        actionTexture->LoadIMG( "data/spells/magicmissile/magicmissile.tga", 0 );
    }

    static CTexture* getStaticSymbol()
    {
        return actionSymbol;
    }

    CTexture* getSymbol() const
    {
        return getStaticSymbol();
    }

    AttackAction( CCharacter *creator_, CCharacter *target_ )
        : CAction( creator_,
                  getStaticCastTime(),
                  getStaticManaCost(),
                  getStaticName(),
                  getStaticActionInfo() ),
          target( target_ ),
          damageCaused( true )
    {
    }

    virtual void startEffect()
    {
        effectStart = SDL_GetTicks();
        curArc = -45.0;
        damageCaused = false;
    }

    virtual void inEffect()
    {
        uint32_t curTime = SDL_GetTicks();
        curArc = -45.0 + (curTime - effectStart) / 5;
        

        if ( curArc > 45.0 )
        {
            curArc = 45.0;
        }

        if ( curArc >= 0 && !damageCaused )
        {
            double distance = sqrt( pow(creator->getXPos() - target->getXPos(),2) + pow(creator->getYPos() - target->getYPos(),2) );
            if ( distance <= 120 )
            {
                target->Damage( 20 );
            }
            damageCaused = true;
        }

        if ( curArc >= 45 )
        {
            finishEffect();
        }
    }

    void finishEffect()
    {
        markSpellActionAsFinished();
    }

    virtual void drawEffect()
    {
        float degrees;
        degrees = asin((creator->getYPos() - target->getYPos())/sqrt((pow(creator->getXPos() - target->getXPos(),2)+pow(creator->getYPos() - target->getYPos(),2)))) * 57,296;

        degrees += 90;        

        if (creator->getXPos() < target->x_pos) { degrees = -degrees; }

        degrees += curArc + 90;

        glPushMatrix();
            glTranslatef(creator->getXPos() + (creator->getWidth() / 2), creator->getYPos() + (creator->getHeight() / 2), 0.0f);
            glRotatef(degrees,0.0f,0.0f,1.0f);
            
            DrawingHelpers::mapTextureToRect( actionTexture->texture[0].texture,
                                              creator->getWidth() / 2, 50,
                                              0, 10 );
        glPopMatrix();
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
        if ( name == AttackAction::getStaticName() )
        {
            return AttackAction::getStaticSymbol();
        }
        else
        {
            std::cerr << "symbol for action \"" << name << "\" not implemented yet" << std::endl;
            abort();
        }
    }

    CAction* createAttackAction( CCharacter *attacker, CCharacter *target )
    {
        return new AttackAction( attacker, target );
    }
}
