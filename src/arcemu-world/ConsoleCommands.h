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

#ifndef _CONSOLECOMMANDS_H
#define _CONSOLECOMMANDS_H

bool HandleAnnounceCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleBanAccountCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleCancelCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleInfoCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleNetworkStatusCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleGMsCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleKickCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleMOTDCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleOnlinePlayersCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandlePlayerInfoCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleRehashCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleShutDownCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleUnbanAccountCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleWAnnounceCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleWhisperCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleNameHashCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleRevivePlayer(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleClearConsoleCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleReloadConsoleCommand(BaseConsole* pConsole, int argc, const char* argv[]);
bool HandleScriptEngineReloadCommand(BaseConsole*, int argc, const char * []);
#endif
