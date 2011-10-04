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

SummonHandler::SummonHandler()
{
	std::fill(summonslots.begin(), summonslots.end(), reinterpret_cast< Unit* >(NULL));
}

SummonHandler::~SummonHandler()
{
	RemoveAllSummons();
}

void SummonHandler::AddSummon(Unit* summon)
{
	guardians.insert(summon);
}

void SummonHandler::AddSummonToSlot(Unit* summon, uint8 slot)
{
	if(summonslots[ slot ] != NULL)
		summonslots[ slot ]->Delete();

	summonslots[ slot ] = summon;
}

void SummonHandler::RemoveSummon(Unit* summon)
{
	std::set< Unit* >::iterator itr = guardians.find(summon);
	if(itr != guardians.end())
		guardians.erase(itr);
}

void SummonHandler::RemoveSummonFromSlot(uint8 slot, bool del)
{
	if(summonslots[ slot ] != NULL)
	{
		if(del)
			summonslots[ slot ]->Delete();

		summonslots[ slot ] = NULL;
	}
}

void SummonHandler::ExpireSummonsInSlot()
{
	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = *itr;

		if(u != NULL)
			u->Delete();
	}
	std::fill(summonslots.begin(), summonslots.end(), reinterpret_cast< Unit* >(NULL));
}

void SummonHandler::RemoveAllSummons()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end();)
	{
		Unit* g = *itr;
		++itr;
		g->Delete();
	}
	guardians.clear();

	ExpireSummonsInSlot();
}

void SummonHandler::GetSummonSlotSpellIDs(std::vector< uint32 > &spellids)
{
	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);

		if(u != NULL)
			if(u->GetCreatedBySpell() != 0)
				spellids.push_back(u->GetCreatedBySpell());
	}
}

bool SummonHandler::HasSummonInSlot(uint8 slot)
{
	if(summonslots[ slot ] != 0)
		return true;
	else
		return false;
}

void SummonHandler::SetPvPFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->SetPvPFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->SetPvPFlag();
	}
}

void SummonHandler::SetFFAPvPFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->SetFFAPvPFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->SetFFAPvPFlag();
	}
}

void SummonHandler::SetSanctuaryFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->SetSanctuaryFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->SetSanctuaryFlag();
	}
}

void SummonHandler::RemovePvPFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->RemovePvPFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->RemovePvPFlag();
	}
}


void SummonHandler::RemoveFFAPvPFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->RemoveFFAPvPFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->RemoveFFAPvPFlag();
	}
}

void SummonHandler::RemoveSanctuaryFlags()
{
	for(std::set< Unit* >::iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
		(*itr)->RemoveSanctuaryFlag();

	for(std::tr1::array< Unit*, SUMMON_SLOTS >::iterator itr = summonslots.begin(); itr != summonslots.end(); ++itr)
	{
		Unit* u = (*itr);
		if(u != NULL)
			u->RemoveSanctuaryFlag();
	}
}


