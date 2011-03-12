#ifndef __CMAGIC_H__
#define __CMAGIC_H__

#include "CSpell.h"
#include "CNPC.h"

class CMagic
{
	public:
		CMagic( CSpellActionBase *spell );
		CSpellActionBase *getSpell();
		void setCreator( CCharacter *c );

		void process();
		bool isDone();
		bool collision(CNPC *npc);

	private:
		CSpellActionBase *spell;
		CCharacter *creator;
};

#endif
