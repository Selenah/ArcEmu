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
#include <iostream>

uint32 Arcemu::Util::GUID_HIPART(uint64 GUID)
{
	uint32 higuid = *(reinterpret_cast< const uint32* >(&GUID) + 1);

	return higuid;
}

uint32 Arcemu::Util::GUID_LOPART(uint64 GUID)
{
	uint32 loguid = *(reinterpret_cast< const uint32* >(&GUID));

	return loguid;
}

void Arcemu::Util::ArcemuAssert(bool condition)
{
	if(!condition)
	{
		LOG_ERROR("Assertion failed. Please submit the callstack on ArcEmu IssueTracker (unless you are using a repack).");
		sLog.Close();

		// bogus null function call to make sure we stop and make a core dump / crash dump
		((void(*)())0)();
	}
}

uint64 Arcemu::Util::MAKE_PET_GUID(uint32 entry, uint32 lowGUID)
{
	uint64 val = 0;

	val = uint64(HIGHGUID_TYPE_PET) << 32;
	val = val | (uint64(entry) << 24);
	val = val | lowGUID;

	return val;
}

uint64 Arcemu::Util::MAKE_ITEM_GUID(uint32 lowguid)
{
	uint64 GUID = 0;

	uint32* u = reinterpret_cast< uint32* >(&GUID);

	u[ 0 ] = lowguid;
	u[ 1 ] = HIGHGUID_TYPE_ITEM;

	return GUID;
}

uint32 Arcemu::Util::GET_CREATURE_ENTRY_FROM_GUID(uint64 guid)
{
	return ( guid >> 24) & 0x0FFFFFFF;
}