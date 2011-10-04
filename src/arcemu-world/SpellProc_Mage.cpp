/*
 * Servidor ArcEmu MMORPG
 *
 * Copyright (C) 2011 <http://www.ArcEmu.es/> 
 *
 * Este programa es software libre: usted puede redistribuirlo y modificarlo
 * Bajo los t�rminos de la licencia GNU Affero General Public License publicada por
 * La Fundacion del Software gratuito, ya sea la versi�n 3 de la Licencia, o
 * Cualquier versi�n posterior.
 *
 * Este programa se distribuye con la esperanza de que sea �til, 
 * Pero SIN NINGUNA GARANT�A, incluso sin la garant�a impl�cita de
 * O IDONEIDAD PARA UN PROP�SITO PARTICULAR. Ver el 
 * GNU Affero General Public License para m�s detalles.
 *
 * Usted debe haber recibido una copia de la licencia GNU Affero General licencia publica
 * Junto con este programa. Si no es as�, consulte <http://www.gnu.org/licenses/>. 
 *
 */

#include "StdAfx.h"

class HotStreakSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(HotStreakSpellProc);

		void Init(Object* obj)
		{
			mCritsInARow = 0;
		}

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			// Check for classmask. Should proc only if CastingSpell is one listed in http://www.wowhead.com/spell=44448
			if(! CheckClassMask(victim, CastingSpell))
				return true;

			// If was not a crit, reset counter and don't proc
			if(!(flag & PROC_ON_SPELL_CRIT_HIT))
			{
				mCritsInARow = 0;
				return true;
			}

			// If was not at least 2nd crit in a row, don't proc
			if(++mCritsInARow < 2)
				return true;

			return false;
		}

	private:
		int mCritsInARow;
};

void SpellProcMgr::SetupMage()
{
	AddById(48108, &HotStreakSpellProc::Create);
}