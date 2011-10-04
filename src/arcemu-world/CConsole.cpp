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
LocalConsole g_localConsole;

#ifndef WIN32
#include <poll.h>
#endif

void ConsoleThread::terminate()
{
	m_killSwitch = true;
#ifdef WIN32
	/* write the return keydown/keyup event */
	DWORD dwTmp;
	INPUT_RECORD ir[2];
	ir[0].EventType = KEY_EVENT;
	ir[0].Event.KeyEvent.bKeyDown = TRUE;
	ir[0].Event.KeyEvent.dwControlKeyState = 288;
	ir[0].Event.KeyEvent.uChar.AsciiChar = 13;
	ir[0].Event.KeyEvent.wRepeatCount = 1;
	ir[0].Event.KeyEvent.wVirtualKeyCode = 13;
	ir[0].Event.KeyEvent.wVirtualScanCode = 28;
	ir[1].EventType = KEY_EVENT;
	ir[1].Event.KeyEvent.bKeyDown = FALSE;
	ir[1].Event.KeyEvent.dwControlKeyState = 288;
	ir[1].Event.KeyEvent.uChar.AsciiChar = 13;
	ir[1].Event.KeyEvent.wRepeatCount = 1;
	ir[1].Event.KeyEvent.wVirtualKeyCode = 13;
	ir[1].Event.KeyEvent.wVirtualScanCode = 28;
	WriteConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ir, 2, & dwTmp);
#endif
	LOG_BASIC("Waiting for console thread to terminate....");
	while(m_isRunning)
	{
		Arcemu::Sleep(100);
	}
	LOG_BASIC("Console shut down.");
}

bool ConsoleThread::run()
{
	SetThreadName("Console Interpreter");
	size_t i = 0;
	size_t len;
	char cmd[300];
#ifndef WIN32
	struct pollfd input;

	input.fd      = 0;
	input.events  = POLLIN | POLLPRI;
	input.revents = 0;
#endif

	m_killSwitch = false;
	m_isRunning = true;
	while(m_killSwitch != true)
	{
#ifdef WIN32

		// Read in single line from "stdin"
		memset(cmd, 0, sizeof(cmd));
		if(fgets(cmd, 300, stdin) == NULL)
			continue;

		if(m_killSwitch)
			break;

#else
		int ret = poll(&input, 1, 1000);
		if(ret < 0)
		{
			break;
		}
		else if(ret == 0)
		{
			if(!m_killSwitch)	// timeout
				continue;
			else
				break;
		}

		ret = read(0, cmd, sizeof(cmd));
		if(ret <= 0)
		{
			break;
		}
#endif

		len = strlen(cmd);
		for(i = 0; i < len; ++i)
		{
			if(cmd[i] == '\n' || cmd[i] == '\r')
				cmd[i] = '\0';
		}

		HandleConsoleInput(&g_localConsole, cmd);
	}
	m_isRunning = false;
	return false;
}
