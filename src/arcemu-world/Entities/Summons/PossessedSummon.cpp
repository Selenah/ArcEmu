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


