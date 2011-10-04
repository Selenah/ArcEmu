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

#ifndef __LOGON_COMM_CLIENT_H
#define __LOGON_COMM_CLIENT_H

#include "../arcemu-logonserver/LogonOpcodes.h"
#include <RC4Engine.h>

class LogonCommClientSocket : public Socket
{
		uint32 remaining;
		uint16 opcode;
		RC4Engine _sendCrypto;
		RC4Engine _recvCrypto;
	public:
		LogonCommClientSocket(SOCKET fd);
		~LogonCommClientSocket();

		void OnRead();
		void SendPacket(WorldPacket* data, bool no_crypto);
		void HandlePacket(WorldPacket & recvData);
		void SendPing();
		void SendChallenge();
		void HandleAuthResponse(WorldPacket & recvData);

		void HandleRegister(WorldPacket & recvData);
		void HandlePong(WorldPacket & recvData);
		void HandleSessionInfo(WorldPacket & recvData);
		void HandleRequestAccountMapping(WorldPacket & recvData);
		void UpdateAccountCount(uint32 account_id, uint8 add);
		void HandleDisconnectAccount(WorldPacket & recvData);
		void HandleConsoleAuthResult(WorldPacket & recvData);
		void HandlePopulationRequest(WorldPacket & recvData);

		void OnDisconnect();
		void CompressAndSend(ByteBuffer & uncompressed);
		uint32 last_ping;
		uint32 last_pong;

		uint32 pingtime;
		uint32 latency;
		uint32 _id;
		uint32 authenticated;
		bool use_crypto;
		set<uint32> realm_ids;
};

typedef void (LogonCommClientSocket::*logonpacket_handler)(WorldPacket &);

#endif

