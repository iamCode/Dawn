#ifndef __CMAGIC_H__
#define __CMAGIC_H__

#include "CSpell.h"

class CMagic
{
	public:
		CMagic( CSpellActionBase *spell );
		CSpellActionBase *getSpell();
		void process();
		bool isDone();

	private:
		CSpellActionBase *spell;
		int radius;
		int duration;
		int x;
		int y;
};

#endif
