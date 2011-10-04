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

#ifndef WIN32
#include <sys/resource.h>
#endif
#include "CrashHandler.h"

uint8 loglevel = DEFAULT_LOG_LEVEL;

#ifndef WIN32
int unix_main(int argc, char** argv)
{
	rlimit rl;
	if(getrlimit(RLIMIT_CORE, &rl) == -1)
		printf("getrlimit failed. This could be problem.\n");
	else
	{
		rl.rlim_cur = rl.rlim_max;
		if(setrlimit(RLIMIT_CORE, &rl) == -1)
			printf("setrlimit failed. Server may not save core.dump files.\n");
	}

	if(!sMaster.Run(argc, argv))
		exit(-1);
	else
		exit(0);

	return 0;// shouldn't be reached
}

#else

int win32_main(int argc, char** argv)
{
	SetThreadName("Main Thread");

	StartCrashHandler();

	//Andy: windows only, helps fight heap allocation on allocations lower then 16KB
	unsigned long arg = 2;
	HeapSetInformation(GetProcessHeap(), HeapCompatibilityInformation, &arg, sizeof(arg));

	THREAD_TRY_EXECUTION
	sMaster.Run(argc, argv);
	THREAD_HANDLE_CRASH

	exit(0);
}

#endif

int main(int argc, char** argv)
{
#ifdef WIN32
	win32_main(argc, argv);
#else
	unix_main(argc, argv);
#endif
}

