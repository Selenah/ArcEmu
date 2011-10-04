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

class ButcherySpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(ButcherySpellProc);

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			dmg_overwrite[0] = mOrigSpell->EffectBasePoints[0] + 1;

			return false;
		}
};

class BladeBarrierSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(BladeBarrierSpellProc);

		void Init(Object* obj)
		{
			mProcFlags = PROC_ON_CAST_SPELL;

			mProcClassMask[0] = mOrigSpell->EffectSpellClassMask[0][0];
			mProcClassMask[1] = mOrigSpell->EffectSpellClassMask[0][1];
			mProcClassMask[2] = mOrigSpell->EffectSpellClassMask[0][2];

			dk = TO_DK(mTarget);
		}

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			if(dk->IsAllRunesOfTypeInUse(RUNE_BLOOD))
				return true;
			return false;
		}

	private:
		DeathKnight* dk;
};

class DeathRuneMasterySpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(DeathRuneMasterySpellProc);

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			DeathKnight* dk = TO_DK(mTarget);

			if(dk->GetRuneType(dk->GetLastUsedUnitSlot()) == RUNE_DEATH)
				return true;

			uint8 count = 2;
			for(uint8 x = 0; x < MAX_RUNES && count; ++x)
				if((dk->GetRuneType(x) == RUNE_FROST || dk->GetRuneType(x) == RUNE_UNHOLY) && ! dk->GetRuneIsUsed(x))
				{
					dk->ConvertRune(x, RUNE_DEATH);
					--count;
				}

			return true;
		}
};

void SpellProcMgr::SetupDeathKnight()
{
	AddById(50163, &ButcherySpellProc::Create);
	AddById(50806, &DeathRuneMasterySpellProc::Create);

	AddByNameHash(SPELL_HASH_BLADE_BARRIER, &BladeBarrierSpellProc::Create);
}