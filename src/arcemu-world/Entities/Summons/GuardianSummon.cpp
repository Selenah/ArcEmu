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

GuardianSummon::GuardianSummon(uint64 GUID) : Summon(GUID)
{
}

GuardianSummon::~GuardianSummon()
{
}

void GuardianSummon::Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot)
{
	Summon::Load(proto, owner, position, spellid, summonslot);

	SetPowerType(POWER_TYPE_MANA);
	SetMaxPower(POWER_TYPE_MANA, GetMaxPower(POWER_TYPE_MANA) + 28 + 10 * getLevel());
	SetPower(POWER_TYPE_MANA, GetPower(POWER_TYPE_MANA) + 28 + 10 * getLevel());
	setLevel(owner->getLevel());
	SetMaxHealth(GetMaxHealth() + 28 + 30 * getLevel());
	SetHealth(GetMaxHealth());
	SetType(CREATURE_TYPE_GUARDIAN);

	m_aiInterface->Init(this, AITYPE_PET , MOVEMENTTYPE_NONE, owner);
	m_aiInterface->SetUnitToFollow(owner);
	m_aiInterface->SetFollowDistance(3.0f);

	m_noRespawn = true;
}

void GuardianSummon::OnPushToWorld()
{
	Summon::OnPushToWorld();
}

void GuardianSummon::OnPreRemoveFromWorld()
{
	Summon::OnPreRemoveFromWorld();
}


