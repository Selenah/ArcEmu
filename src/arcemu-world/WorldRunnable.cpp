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

//
// WorldRunnable.cpp
//

#include "StdAfx.h"
#include <CrashHandler.h>

#define WORLD_UPDATE_DELAY 50

WorldRunnable::WorldRunnable() : CThread()
{

}

bool WorldRunnable::run()
{
	SetThreadName("WorldRunnable (non-instance/logon)");
	uint32 LastWorldUpdate = getMSTime();
	uint32 LastSessionsUpdate = getMSTime();

	THREAD_TRY_EXECUTION

	while(GetThreadState() != THREADSTATE_TERMINATE)
	{
		// Provision for pausing this thread.
		if(GetThreadState() == THREADSTATE_PAUSED)
		{
			while(GetThreadState() == THREADSTATE_PAUSED)
			{
				Arcemu::Sleep(200);
			}
		}
		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_BUSY);

		uint32 diff;
		//calc time passed
		uint32 now, execution_start;
		now = getMSTime();
		execution_start = now;

		if(now < LastWorldUpdate) //overrun
			diff = WORLD_UPDATE_DELAY;
		else
			diff = now - LastWorldUpdate;

		LastWorldUpdate = now;
		sWorld.Update(diff);

		now = getMSTime();

		if(now < LastSessionsUpdate) //overrun
			diff = WORLD_UPDATE_DELAY;
		else
			diff = now - LastSessionsUpdate;

		LastSessionsUpdate = now;
		sWorld.UpdateSessions(diff);

		now = getMSTime();
		//we have to wait now

		if(execution_start > now)//overrun
			diff = WORLD_UPDATE_DELAY - now;

		else
			diff = now - execution_start; //time used for updating

		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_SLEEPING);

		/*This is execution time compensating system
			if execution took more than default delay
			no need to make this sleep*/
		if(diff < WORLD_UPDATE_DELAY)
			Arcemu::Sleep(WORLD_UPDATE_DELAY - diff);
	}

	THREAD_HANDLE_CRASH
	return true;
}
