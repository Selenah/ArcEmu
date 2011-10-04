/*
 * Servidor ArcEmu MMORPG
 *
 * Copyright (C) 2011 <http://www.ArcEmu.es/> 
 * cebernic@gmail.com
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
/*
  Cebernic : This thread watching global schedule and execute it.
*/

#ifndef _COMMONSCHEDULETHREAD_
#define _COMMONSCHEDULETHREAD_

class CommonScheduleThread : public CThread
{
		bool m_running;
		bool m_busy;
		std::multimap<uint32, uint32>::iterator itOrderMSGEntry;

		uint32 BCTimerCount;

		Arcemu::Threading::ConditionVariable cond;

	public:
		CommonScheduleThread();
		~CommonScheduleThread();

		bool run();
		void terminate();

		void BroadCastExec();
};

#endif
