/*
 * Servidor ArcEmu MMORPG
 *
 * Copyright (C) 2011 <http://www.ArcEmu.es/> 
 *
 * Este programa es software libre: usted puede redistribuirlo y modificarlo
 * Bajo los términos de la licencia GNU Affero General Public License publicada por
 * La Fundacion del Software gratuito, ya sea la versión 3 de la Licencia, o
 * Cualquier versión posterior.
 *
 * Este programa se distribuye con la esperanza de que sea útil, 
 * Pero SIN NINGUNA GARANTÍA, incluso sin la garantía implícita de
 * O IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Ver el 
 * GNU Affero General Public License para más detalles.
 *
 * Usted debe haber recibido una copia de la licencia GNU Affero General licencia publica
 * Junto con este programa. Si no es así, consulte <http://www.gnu.org/licenses/>. 
 *
 */

#include "StdAfx.h"

class TwinBladesOfAzzinothSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(TwinBladesOfAzzinothSpellProc);

		void Init(Object* obj)
		{
			if(! mTarget->IsPlayer())
				return;

			/* The Twin Blades of Azzinoth.
				* According to comments on wowhead, this proc has ~0.75ppm (procs-per-minute). */
			Item* mh = TO_PLAYER(mTarget)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			Item* of = TO_PLAYER(mTarget)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
			if(mh != NULL && of != NULL)
			{
				uint32 mhs = mh->GetProto()->Delay;
				uint32 ohs = of->GetProto()->Delay;
				mProcChance = mhs * ohs / (800 * (mhs + ohs));     // 0.75 ppm
			}
		}
};

void SpellProcMgr::SetupItems()
{
	AddByNameHash(SPELL_HASH_THE_TWIN_BLADES_OF_AZZINOTH, &TwinBladesOfAzzinothSpellProc::Create);
}