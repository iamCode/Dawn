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
		//zoneNPCs[x].
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
	if( npc == NULL ) return false;

	int left				= npc->getXPos();
	int right				= npc->getWidth();
	int top					= npc->getYPos();
	int bottom			= npc->getHeight();

	int recCenterX 	= left + right/2;
	int recCenterY 	= top + bottom/2;
	int w						= right/2;
	int h						= bottom/2;
	int dx					= abs(spell->getX() - recCenterX);
	int dy					= abs(spell->getY() - recCenterY);

	if ( dx > (spell->getRadius() + w) || dy > (spell->getRadius() + h))
		return false;

	int cirDistX = abs(spell->getX() - left - w);
	int cirDistY = abs(spell->getY() - top - h);

	if ( cirDistX <= w)
		return true;

	if ( cirDistY <= h)
		return true;

	return ( (pow(cirDistX - w, 2) + pow(cirDistY - h, 2)) <= pow(spell->getRadius(), 2));
}
