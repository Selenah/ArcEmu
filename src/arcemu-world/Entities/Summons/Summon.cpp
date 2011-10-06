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
 
#include "../../StdAfx.h"

Summon::Summon(uint64 GUID) : Creature(GUID)
{
	summonslot = -1;
}

Summon::~Summon()
{
}

void Summon::Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot)
{
	ARCEMU_ASSERT(owner != NULL);

	Creature::Load(proto, position.x, position.y, position.z, position.o);

	SetFaction(owner->GetFaction());
	Phase(PHASE_SET, owner->GetPhase());
	SetZoneId(owner->GetZoneId());
	SetCreatedBySpell(spellid);
	this->summonslot = summonslot;

	if(owner->IsPvPFlagged())
		SetPvPFlag();
	else
		RemovePvPFlag();

	if(owner->IsFFAPvPFlagged())
		SetFFAPvPFlag();
	else
		RemoveFFAPvPFlag();

	if(owner->IsSanctuaryFlagged())
		SetSanctuaryFlag();
	else
		RemoveSanctuaryFlag();

	SetCreatedByGUID(owner->GetGUID());

	if(owner->GetSummonedByGUID() == 0)
		SetSummonedByGUID(owner->GetGUID());
	else
		SetSummonedByGUID(owner->GetSummonedByGUID());

	this->owner = owner;

	if(owner->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE))
		SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);

}

void Summon::OnPushToWorld()
{
	if(summonslot != -1)
		owner->summonhandler.AddSummonToSlot(this, summonslot);
	else
		owner->summonhandler.AddSummon(this);

	Creature::OnPushToWorld();

}

void Summon::OnPreRemoveFromWorld()
{
	if(owner == NULL)
		return;

	if(GetCreatedBySpell() != 0)
		owner->RemoveAura(GetCreatedBySpell());

	if(summonslot != -1)
		owner->summonhandler.RemoveSummonFromSlot(summonslot, false);
	else
		owner->summonhandler.RemoveSummon(this);

	summonslot = -1;
	owner = NULL;

	SendDestroyObject();

}

Object* Summon::GetPlayerOwner()
{
	// owner is nulled on death
	if(owner == NULL)
		return NULL;

	if(owner->IsPlayer())
		return owner;
	else
		return NULL;
}

void Summon::Die(Unit* pAttacker, uint32 damage, uint32 spellid)
{
	if(owner->IsTotem())
		owner->Die(pAttacker, damage, spellid);

	Creature::Die(pAttacker, damage, spellid);

	if(summonslot != -1)
		owner->summonhandler.RemoveSummonFromSlot(summonslot, false);
	else
		owner->summonhandler.RemoveSummon(this);

	summonslot = -1;
	owner = NULL;
}

void Summon::OnRemoveInRangeObject(Object* object)
{

	if((owner != NULL) && (object->GetGUID() == owner->GetGUID()))
		Despawn(1, 0);

	Creature::OnRemoveInRangeObject(object);
}