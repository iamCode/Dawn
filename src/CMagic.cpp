#include "CMagic.h"

#include <cmath>
#include "CZone.h"
#include "globals.h"

namespace DawnInterface {
	void addTextToLogWindow( GLfloat color[], const char *text, ... );
}

CMagic::CMagic( CSpellActionBase *spell )
{
	this->spell = spell;
	creator = NULL;
}

CSpellActionBase *CMagic::getSpell()
{
	return spell;
}

void CMagic::setCreator( CCharacter *c )
{
	creator = c;
}

void CMagic::process()
{
	int a = 0;

	std::vector<CNPC*> zoneNPCs = Globals::getCurrentZone()->getNPCs();
	for (unsigned int x=0; x<zoneNPCs.size(); x++)
	{
		CNPC *curNPC = zoneNPCs[x];

		// is the npc colliding with the spell and make sure it's alive
		if ( collision(curNPC) && curNPC->isAlive() )
		{
			// loop through the active spells on the npc if it has any and make sure the effect isn't cast twice
			std::vector<std::pair<CSpellActionBase*, uint32_t> > activeSpells = curNPC->getActiveSpells();
			if( activeSpells.size() > 0 )
			{
				for ( size_t curSpell = 0; curSpell < activeSpells.size(); curSpell++ )
				{
					if ( activeSpells[curSpell].first->getID() == spell->getID() ) // there is no active spell matching this one, cast it
					{
						a++;
					}
				}

				if( a == 0 )
				{
					CSpellActionBase *s = spell->cast( creator, curNPC, true );
					s->startEffect();
					curNPC->addActiveSpell( s );
				}
			}
			else // cast the spell
			{
				CSpellActionBase *s = spell->cast( creator, curNPC, true );
				s->startEffect();
				curNPC->addActiveSpell( s );
			}
		}
	}
}

bool CMagic::isDone()
{
	if ( spell->isEffectComplete() )
		return true;
	else
		return false;
}

bool CMagic::collision(CNPC *npc)
{
	RECT rec;
	rec.left				= npc->getXPos();
	rec.right				= npc->getWidth();
	rec.top					= npc->getYPos();
	rec.bottom			= npc->getHeight();

	int recCenterX 	= rec.left + rec.right/2;
	int recCenterY 	= rec.top + rec.bottom/2;
	int w						= rec.right/2;
	int h						= rec.bottom/2;
	int dx					= abs(spell->getX() - recCenterX);
	int dy					= abs(spell->getY() - recCenterY);

	if ( dx > (spell->getRadius() + w) || dy > (spell->getRadius() + h))
		return false;

	int cirDistX = abs(spell->getX() - rec.left - w);
	int cirDistY = abs(spell->getY() - rec.top - h);

	if ( cirDistX <= w)
		return true;

	if ( cirDistY <= h)
		return true;

	return ( (pow(cirDistX - w, 2) + pow(cirDistY - h, 2)) <= pow(spell->getRadius(), 2));
}
