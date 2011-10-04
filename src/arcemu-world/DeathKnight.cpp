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

void DeathKnight::SendRuneUpdate(uint8 slot)
{
	WorldPacket data(SMSG_CONVERT_RUNE, 2);
	data << (uint8)slot;
	data << (uint8)m_runes[slot].type;
	GetSession()->SendPacket(&data);
}

uint8 DeathKnight::GetBaseRuneType(uint8 slot)
{
	return base_runes[slot];
}

uint8 DeathKnight::GetRuneType(uint8 slot)
{
	return m_runes[slot].type;
}

bool DeathKnight::GetRuneIsUsed(uint8 slot)
{
	return m_runes[slot].is_used;
}

void DeathKnight::ConvertRune(uint8 slot, uint8 type)
{
	if(m_runes[slot].type == type)
		return;

	m_runes[slot].type = type;
	SendRuneUpdate(slot);
}

uint32 DeathKnight::HasRunes(uint8 type, uint32 count)
{
	uint32 found = 0;
	for(uint8 i = 0; i < MAX_RUNES && count != found; ++i)
		if(m_runes[i].type == type && ! m_runes[i].is_used)
			found++;
	return (count - found);
}

uint32 DeathKnight::TakeRunes(uint8 type, uint32 count)
{
	uint8 found = 0;
	for(uint8 i = 0; i < MAX_RUNES && count != found; ++i)
		if(m_runes[i].type == type && ! m_runes[i].is_used)
		{
			m_runes[i].is_used = true;
			m_last_used_rune_slot = i;
			sEventMgr.AddEvent(this, &DeathKnight::ResetRune, i, EVENT_PLAYER_RUNE_REGEN + i, 10000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			found++;
		}
	return (count - found);
}

void DeathKnight::ResetRune(uint8 slot)
{
	m_runes[slot].is_used = false;
	sEventMgr.RemoveEvents(this, EVENT_PLAYER_RUNE_REGEN + slot);
}

uint8 DeathKnight::GetRuneFlags()
{
	uint8 result = 0;
	for(uint8 k = 0; k < MAX_RUNES; k++)
		if(! m_runes[k].is_used)
			result |= (1 << k);
	return result;
}

bool DeathKnight::IsAllRunesOfTypeInUse(uint8 type)
{
	for(uint8 i = 0; i < MAX_RUNES; ++i)
		if(m_runes[i].type == type && ! m_runes[i].is_used)
			return false;
	return true;
}