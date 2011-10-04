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

class SealOfCommandSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(SealOfCommandSpellProc);

		void Init(Object* obj)
		{
			// default chance of proc
			mProcChance = 25;

			mProcFlags = PROC_ON_MELEE_ATTACK;

			/* The formula for SoC proc rate is: [ 7 / ( 60 / Weapon Speed ) - from wowwiki */
			if(! mTarget->IsPlayer())
				return;

			uint32 weapspeed = 1;
			Item* itm = TO_PLAYER(mTarget)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			if(itm != NULL)
				weapspeed = itm->GetProto()->Delay;
			mProcChance = 7 * weapspeed / 600;
			if(mProcChance >= 50)
				mProcChance = 50;
		}
};

class EyeForAnEyeSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(EyeForAnEyeSpellProc);

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			// If this player died by crit damage, don't do dmg back
			if(! mTarget->isAlive())
				return true;

			// Prevent proc on healing criticals
			if(CastingSpell != NULL && !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
				return true;

			dmg_overwrite[0] = dmg * (mOrigSpell->EffectBasePoints[0] + 1) / 100;

			int max_dmg = mTarget->GetMaxHealth() / 2;

			if(dmg_overwrite[0] > max_dmg)
				dmg_overwrite[0] = max_dmg;

			return false;
		}
};

class GraceOfTheNaaruSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(GraceOfTheNaaruSpellProc);

		void Init(Object* obj)
		{
			this->mProcClassMask[0] = 0x80000000;
		}
};

class SpiritualAttunementSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(SpiritualAttunementSpellProc);

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			if(CastingSpell == NULL || ! IsHealingSpell(CastingSpell))
				return false;

			return true;
		}
};

class PaladinSealsSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(PaladinSealsSpellProc);

		void Init(Object* obj)
		{
			this->mProcFlags = PROC_ON_MELEE_ATTACK;
		}
};

class SealOfCorruptionSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(SealOfCorruptionSpellProc);

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			if(victim == NULL || victim->FindAuraCountByHash(SPELL_HASH_BLOOD_CORRUPTION) < 5)
				return false;

			return true;
		}
};

class SealOfVengeanceSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(SealOfVengeanceSpellProc);

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			if(victim == NULL || victim->FindAuraCountByHash(SPELL_HASH_HOLY_VENGEANCE) < 5)
				return false;

			return true;
		}
};

void SpellProcMgr::SetupPaladin()
{
	AddByNameHash(SPELL_HASH_SEAL_OF_COMMAND, &SealOfCommandSpellProc::Create);

	AddByNameHash(SPELL_HASH_EYE_FOR_AN_EYE, &EyeForAnEyeSpellProc::Create);

	AddByNameHash(SPELL_HASH_GRACE_OF_THE_NAARU, &GraceOfTheNaaruSpellProc::Create);

	AddByNameHash(SPELL_HASH_SPIRITUAL_ATTUNEMENT, &SpiritualAttunementSpellProc::Create);

	AddById(20167, &PaladinSealsSpellProc::Create);
	AddById(20168, &PaladinSealsSpellProc::Create);
	AddById(20170, &PaladinSealsSpellProc::Create);
	AddById(53739, &SealOfCorruptionSpellProc::Create);
	AddById(42463, &SealOfVengeanceSpellProc::Create);
}