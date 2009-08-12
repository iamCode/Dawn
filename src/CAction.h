#ifndef __C_ACTION_H_
#define __C_ACTION_H_

#include "CSpell.h" // only for CSpellActionBase which should be moved to a separate file...

class CAction : public CSpellActionBase
{
  public:
    CAction( uint16_t castTime, uint16_t manaCost, std::string name, std::string info )
        : CSpellActionBase( castTime, manaCost, name, info )
    {}
};

namespace ActionCreation
{
    void initActions();
    CTexture* getActionSymbolByName( std::string name );
    CAction* createAttackAction( CCharacter *attacker, CCharacter *target );
}

#endif // __C_ACTION_H_
