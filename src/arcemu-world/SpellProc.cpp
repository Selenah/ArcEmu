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

initialiseSingleton(SpellProcMgr);

uint32 SpellProc::CalcProcChance(Unit* victim, SpellEntry* CastingSpell)
{
	// Check if proc chance is based on combo points
	if(mTarget->IsPlayer() && mOrigSpell && mOrigSpell->AttributesEx & ATTRIBUTESEX_REQ_COMBO_POINTS1 && mOrigSpell->AttributesExD & FLAGS5_PROCCHANCE_COMBOBASED)
		return float2int32(TO_PLAYER(mTarget)->m_comboPoints * mOrigSpell->EffectPointsPerComboPoint[0]);
	else
		return mProcChance;
}

bool SpellProc::CanProcOnTriggered(Unit* victim, SpellEntry* CastingSpell)
{
	if(mOrigSpell != NULL && mOrigSpell->AttributesExC & FLAGS4_CAN_PROC_ON_TRIGGERED)
		return true;
	return false;
}

void SpellProc::CastSpell(Unit* victim, SpellEntry* CastingSpell, int* dmg_overwrite)
{
	SpellCastTargets targets;
	if(mProcFlags & PROC_TARGET_SELF)
		targets.m_unitTarget = mTarget->GetGUID();
	else
		targets.m_unitTarget = victim->GetGUID();

	Spell* spell = sSpellFactoryMgr.NewSpell(mTarget, mSpell, true, NULL);
	spell->forced_basepoints[0] = dmg_overwrite[0];
	spell->forced_basepoints[1] = dmg_overwrite[1];
	spell->forced_basepoints[2] = dmg_overwrite[2];
	spell->ProcedOnSpell = CastingSpell;

	if(mSpell->Id == 974 || mSpell->Id == 32593 || mSpell->Id == 32594 || mSpell->Id == 49283 || mSpell->Id == 49284)   // Earth Shield handler
	{
		spell->pSpellId = mSpell->Id;
		spell->SpellEffectDummy(0);
		delete spell;
		return;
	}

	if(mOrigSpell != NULL)
		spell->pSpellId = mOrigSpell->Id;

	spell->prepare(&targets);
}

SpellProc* SpellProcMgr::NewSpellProc(Unit* target, uint32 spell_id, uint32 orig_spell_id, uint64 caster, uint32 procChance, uint32 procFlags, uint32 procCharges, uint32* groupRelation, uint32* procClassMask, Object* obj)
{
	return NewSpellProc(target, dbcSpell.LookupEntryForced(spell_id), dbcSpell.LookupEntryForced(orig_spell_id), caster, procChance, procFlags, procCharges, groupRelation, procClassMask, obj);
}

SpellProc* SpellProcMgr::NewSpellProc(Unit* target, SpellEntry* spell, SpellEntry* orig_spell, uint64 caster, uint32 procChance, uint32 procFlags, uint32 procCharges, uint32* groupRelation, uint32* procClassMask, Object* obj)
{
	if(spell == NULL)
		return NULL;

	SpellProc* result;
	SpellProcMap::iterator itr;
	spell_proc_factory_function ptr = NULL;

	// Search for SpellProc in hash_map
	itr = mSpellProcNameHash.find(spell->NameHash);
	if(itr != mSpellProcNameHash.end())
		ptr = itr->second;
	else
	{
		itr = mSpellProc.find(spell->Id);
		if(itr != mSpellProc.end())
			ptr = itr->second;
	}

	if(ptr != NULL)
		result = (*ptr)();      // Found. Create a new object of this specific class
	else
		result = new SpellProc; // Not found. Create a new object of generic SpellProc

	result->mSpell            = spell;
	result->mOrigSpell        = orig_spell;
	result->mTarget           = target;
	result->mCaster           = caster;
	result->mProcChance       = procChance;
	result->mProcFlags        = procFlags;
	result->mProcCharges      = procCharges;
	result->mLastTrigger      = 0;
	result->mDeleted          = false;

	if(groupRelation != NULL)
	{
		result->mGroupRelation[0] = groupRelation[0];
		result->mGroupRelation[1] = groupRelation[1];
		result->mGroupRelation[2] = groupRelation[2];
	}
	else
	{
		result->mGroupRelation[0] = 0;
		result->mGroupRelation[1] = 0;
		result->mGroupRelation[2] = 0;
	}
	if(procClassMask != NULL)
	{
		result->mProcClassMask[0] = procClassMask[0];
		result->mProcClassMask[1] = procClassMask[1];
		result->mProcClassMask[2] = procClassMask[2];
	}
	else
	{
		result->mProcClassMask[0] = 0;
		result->mProcClassMask[1] = 0;
		result->mProcClassMask[2] = 0;
	}

	result->Init(obj);

	return result;
}

void SpellProcMgr::Setup()
{
	SetupItems();
	SetupDeathKnight();
	SetupDruid();
	SetupHunter();
	SetupMage();
	SetupPaladin();
	SetupPriest();
	SetupRogue();
	SetupShamman();
	SetupWarlock();
	SetupWarrior();
}