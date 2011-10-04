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

#ifndef _MASTER_H
#define _MASTER_H

#include "Common.h"
//#include "Singleton.h"
#include "Config/ConfigEnv.h"
#include "Database/DatabaseEnv.h"
#include "MainServerDefines.h"

#ifndef _VERSION
# define _VERSION "3.3.5a"
#endif

#if PLATFORM == PLATFORM_WIN32
# define _FULLVERSION _VERSION "-SVN (Win32)"
#else
# define _FULLVERSION _VERSION "-SVN (Unix)"
#endif

#ifdef _DEBUG
#define BUILDTYPE "Debug"
#else
#define BUILDTYPE "Release"
#endif

#define REQUIRED_WORLD_DB_VERSION 4606
#define REQUIRED_CHAR_DB_VERSION 4479

#define DEFAULT_LOOP_TIME 0 /* 0 milliseconds - instant */
#define DEFAULT_LOG_LEVEL 0
#define DEFAULT_PLAYER_LIMIT 100
#define DEFAULT_WORLDSERVER_PORT 8129
#define DEFAULT_REALMSERVER_PORT 3724
#define DEFAULT_HOST "0.0.0.0"
#define DEFAULT_REGEN_RATE 0.15
#define DEFAULT_XP_RATE 1
#define DEFAULT_DROP_RATE 1
#define DEFAULT_REST_XP_RATE 1
#define DEFAULT_QUEST_XP_RATE 1
#define DEFAULT_SAVE_RATE 300000	// 5mins

class Master : public Singleton<Master>
{
	public:
		Master();
		~Master();
		bool Run(int argc, char** argv);
		bool m_ShutdownEvent;
		uint32 m_ShutdownTimer;

		static volatile bool m_stopEvent;
		bool m_restartEvent;

	private:
		bool _StartDB();
		void _StopDB();
		bool CheckDBVersion();

		void _HookSignals();
		void _UnhookSignals();

		static void _OnSignal(int s);
};

#define sMaster Master::getSingleton()

#endif
