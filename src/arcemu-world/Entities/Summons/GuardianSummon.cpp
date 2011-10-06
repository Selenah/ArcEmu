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


