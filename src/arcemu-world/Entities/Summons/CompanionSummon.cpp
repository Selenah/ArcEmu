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

CompanionSummon::CompanionSummon(uint64 GUID) : Summon(GUID)
{
}

CompanionSummon::~CompanionSummon()
{
}

void CompanionSummon::Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot)
{
	Summon::Load(proto, owner, position, spellid, summonslot);

	SetFaction(35);
	setLevel(1);
	m_aiInterface->Init(this, AITYPE_PET, MOVEMENTTYPE_NONE, owner);
	m_aiInterface->SetUnitToFollow(owner);
	m_aiInterface->SetUnitToFollowAngle(-M_PI_FLOAT / 2);
	m_aiInterface->SetFollowDistance(3.0f);
	m_aiInterface->disable_melee = true;
	bInvincible = true;

	RemovePvPFlag();
	RemoveFFAPvPFlag();
}

void CompanionSummon::OnPushToWorld()
{
	Summon::OnPushToWorld();
}

void CompanionSummon::OnPreRemoveFromWorld()
{
	Summon::OnPreRemoveFromWorld();
}

