#include "CMagic.h"

CMagic::CMagic( CSpellActionBase *spell )
{
	this->spell = spell;
	radius			= spell->getRadius();
	this->x			= spell->getX();
	this->y			= spell->getY();
}

CSpellActionBase *CMagic::getSpell()
{
	return spell;
}

void CMagic::process()
{
}

bool CMagic::isDone()
{
	if ( spell->isEffectComplete() )
		return true;
	else
		return false;
}
