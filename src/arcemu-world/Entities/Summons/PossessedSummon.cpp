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

PossessedSummon::PossessedSummon(uint64 GUID) : Summon(GUID)
{
}

PossessedSummon::~PossessedSummon()
{
}

void PossessedSummon::Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot)
{
	Summon::Load(proto, owner, position, spellid, summonslot);

	setLevel(owner->getLevel());
	setAItoUse(false);
	m_aiInterface->StopMovement(0);
}

void PossessedSummon::OnPushToWorld()
{
	Summon::OnPushToWorld();
}

void PossessedSummon::OnPreRemoveFromWorld()
{
	Summon::OnPreRemoveFromWorld();
}


