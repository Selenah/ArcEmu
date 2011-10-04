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

#ifndef _DAYWATCHERTHREAD_
#define _DAYWATCHERTHREAD_

enum DAYWATCHERSETTINGS
{
    WEEKLY		= 1,
    DAILY		= 2,
    MONTHLY		= 3,
    HOURLY		= 4,
};

class DayWatcherThread : public CThread
{
		Arcemu::Threading::ConditionVariable cond;

		bool m_running;
		bool m_busy;
		bool m_dirty;

		//static const time_t timeout = 120;		/* check every 2 minutes */
		time_t currenttime;
		tm local_currenttime;
		time_t last_arena_time;
		tm local_last_arena_time;

		time_t last_daily_time;
		tm local_last_daily_time;

		uint32 arena_period;
		uint32 daily_period;

	public:
		DayWatcherThread();
		~DayWatcherThread();

		bool run();
		void terminate();
		void maintenence();
		void dupe_tm_pointer(tm* returnvalue, tm* mypointer);
		void load_settings();
		void update_settings();
		void set_tm_pointers();
		uint32 get_timeout_from_string(const char* string, uint32 def);
		bool has_timeout_expired(tm* now_time, tm* last_time, uint32 timeoutval);
		void update_arena();
		void update_daily();
};

#endif
