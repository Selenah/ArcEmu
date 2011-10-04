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

class DamageShieldSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(DamageShieldSpellProc);

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			// Allow only proc for player unit
			if(! mTarget->IsPlayer())
				return false;
			return true;
		}

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			Player* plr = TO_PLAYER(mTarget);

			dmg_overwrite[0] = plr->GetBlockDamageReduction() * (mOrigSpell->EffectBasePoints[0] + 1) / 100;

			// plr->GetBlockDamageReduction() returns ZERO if player has no shield equipped
			if(dmg_overwrite[0] == 0)
				return true;

			return false;
		}
};

void SpellProcMgr::SetupWarrior()
{
	AddByNameHash(SPELL_HASH_DAMAGE_SHIELD, &DamageShieldSpellProc::Create);
}