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
