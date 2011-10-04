/*
 * Servidor ArcEmu MMORPG
 *
 * Copyright (C) 2011 <http://www.ArcEmu.es/> 
 * cebernic@gmail.com
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

#define THREAD_LOOP_INTERVAL 10 // cebernic: don't modify it

CommonScheduleThread::CommonScheduleThread()
{
	m_running = true;
	BCTimerCount = 0;
}

CommonScheduleThread::~CommonScheduleThread()
{

}

void CommonScheduleThread::terminate()
{
	BCTimerCount = 0;
	m_running = false;

	cond.Signal();
}

bool CommonScheduleThread::run()
{
	Log.Success("CommonScheduleThread", "Started.");
	m_busy = false;

	if(sWorld.BCSystemEnable && sWorld.BCOrderMode == 1)
		itOrderMSGEntry = objmgr.GetBCTotalItemBegin();
	// cebernic nothing in storage
	if(objmgr.IsBCEntryStorageEmpty()) sWorld.BCSystemEnable = 0;

	BCTimerCount = getMSTime() + ((uint32)sWorld.BCInterval * 1000);

	while(GetThreadState() != THREADSTATE_TERMINATE)
	{
		m_busy = true;
		// do job -------------------
		BroadCastExec();
		// -----------------------
		m_busy = false;
		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		cond.Wait(THREAD_LOOP_INTERVAL * 1000);

		if(!m_running)
			break;
	}

	return true;
}
/*
cebernic: AutoBroadCast System
*/
void CommonScheduleThread::BroadCastExec()
{
	if(!sWorld.BCSystemEnable) return;

	if((uint32)sWorld.BCInterval > THREAD_LOOP_INTERVAL)
	{
		if(getMSTime() <= BCTimerCount)
		{
			return;
		}
		else	BCTimerCount = getMSTime() + ((uint32)sWorld.BCInterval * 1000);
	}

	switch(sWorld.BCOrderMode)
	{
		case 0:
			{
				int entry =	objmgr.CalcCurrentBCEntry();
				if(entry < 0)
				{
					sWorld.BCSystemEnable = false;
					Log.Notice("BCSystem", "table worldbroadcast loads failed,so BCSystem disabled already.");
					return;
				}

				if(entry == 0) return;    // no anymessagez hitted.
				else sWorld.SendBCMessageByID(entry);
				//printf("random entry: %u\n",entry);
			}
			break;
		case 1:
			{
				// re-assign
				if(itOrderMSGEntry ==  objmgr.GetBCTotalItemEnd()) itOrderMSGEntry = objmgr.GetBCTotalItemBegin();
				sWorld.SendBCMessageByID((uint32)itOrderMSGEntry->second);
				//printf("serial entry: %u\n",(uint32)itOrderMSGEntry->second);
				itOrderMSGEntry++;
			}
			break;
		default:
			return;
	}
}
