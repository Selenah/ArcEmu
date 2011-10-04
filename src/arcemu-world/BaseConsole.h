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

#ifndef _BASECONSOLE_H
#define _BASECONSOLE_H

class ConsoleSocket;

class BaseConsole
{
	public:
		virtual ~BaseConsole() {}
		virtual void Write(const char* Format, ...) = 0;
};

class RemoteConsole : public BaseConsole
{
		ConsoleSocket* m_pSocket;
	public:
		RemoteConsole(ConsoleSocket* pSocket);
		void Write(const char* Format, ...);
};

class LocalConsole : public BaseConsole
{
	public:
		void Write(const char* Format, ...);
};

void HandleConsoleInput(BaseConsole* pConsole, const char* szInput);

#endif
