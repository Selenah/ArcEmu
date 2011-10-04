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

initialiseSingleton(SpellFactoryMgr);

void SpellFactoryMgr::AddSpellByEntry(SpellEntry* info, spell_factory_function spell_func)
{
	if(info != NULL)
		info->SpellFactoryFunc = (void * (*)) spell_func;
}

void SpellFactoryMgr::AddSpellById(uint32 spellId, spell_factory_function spell_func)
{
	AddSpellByEntry(dbcSpell.LookupEntryForced(spellId), spell_func);
}

void SpellFactoryMgr::AddSpellByNameHash(uint32 name_hash, spell_factory_function spell_func)
{
	uint32 cnt = dbcSpell.GetNumRows();
	SpellEntry* sp;

	for(uint32 x = 0; x < cnt; x++)
	{
		sp = dbcSpell.LookupRow(x);

		if(sp->NameHash != name_hash)
			continue;

		AddSpellByEntry(sp, spell_func);
	}
}

void SpellFactoryMgr::AddAuraByEntry(SpellEntry* info, aura_factory_function aura_func)
{
	if(info != NULL)
		info->AuraFactoryFunc = (void * (*)) aura_func;
}

void SpellFactoryMgr::AddAuraById(uint32 spellId, aura_factory_function aura_func)
{
	AddAuraByEntry(dbcSpell.LookupEntryForced(spellId), aura_func);
}

void SpellFactoryMgr::AddAuraByNameHash(uint32 name_hash, aura_factory_function aura_func)
{
	uint32 cnt = dbcSpell.GetNumRows();
	SpellEntry* sp;

	for(uint32 x = 0; x < cnt; x++)
	{
		sp = dbcSpell.LookupRow(x);

		if(sp->NameHash != name_hash)
			continue;

		AddAuraByEntry(sp, aura_func);
	}
}

Spell* SpellFactoryMgr::NewSpell(Object* Caster, SpellEntry* info, bool triggered, Aura* aur)
{
	if(info->SpellFactoryFunc == NULL)
		return new Spell(Caster, info, triggered, aur);
	else
	{
		spell_factory_function ptr;
		ptr = *spell_factory_function(info->SpellFactoryFunc);
		return (*ptr)(Caster, info, triggered, aur);
	}
}

Aura* SpellFactoryMgr::NewAura(SpellEntry* proto, int32 duration, Object* caster, Unit* target, bool temporary, Item* i_caster)
{
	if(proto->AuraFactoryFunc == NULL)
		return new Aura(proto, duration, caster, target, temporary, i_caster);
	else
	{
		aura_factory_function ptr;
		ptr = *aura_factory_function(proto->AuraFactoryFunc);
		return (*ptr)(proto, duration, caster, target, temporary, i_caster);
	}
}

void SpellFactoryMgr::Setup()
{
	SetupDeathKnight();
	SetupDruid();
	SetupHunter();
	SetupMage();
	SetupPaladin();
	SetupPriest();
	SetupRogue();
	SetupShaman();
	SetupWarlock();
	SetupWarrior();
}
