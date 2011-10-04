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

// Class WorldSocket - Main network code functions, handles
// reading/writing of all packets.

#ifndef __WORLDSOCKET_H
#define __WORLDSOCKET_H

#define WORLDSOCKET_SENDBUF_SIZE 131078
#define WORLDSOCKET_RECVBUF_SIZE 16384

class WorldPacket;
class SocketHandler;
class WorldSession;

enum OUTPACKET_RESULT
{
    OUTPACKET_RESULT_SUCCESS = 1,
    OUTPACKET_RESULT_NO_ROOM_IN_BUFFER = 2,
    OUTPACKET_RESULT_NOT_CONNECTED = 3,
    OUTPACKET_RESULT_SOCKET_ERROR = 4,
};

class SERVER_DECL WorldSocket : public Socket
{
	public:
		WorldSocket(SOCKET fd);
		~WorldSocket();

		// vs8 fix - send null on empty buffer
		ARCEMU_INLINE void SendPacket(WorldPacket* packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->size(), (packet->size() ? (const void*)packet->contents() : NULL)); }
		ARCEMU_INLINE void SendPacket(StackBufferBase* packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->GetSize(), (packet->GetSize() ? (const void*)packet->GetBufferPointer() : NULL)); }

		void  OutPacket(uint16 opcode, size_t len, const void* data);
		OUTPACKET_RESULT  _OutPacket(uint16 opcode, size_t len, const void* data);

		ARCEMU_INLINE uint32 GetLatency() { return _latency; }

		void Authenticate();
		void InformationRetreiveCallback(WorldPacket & recvData, uint32 requestid);

		void  UpdateQueuePosition(uint32 Position);

		void OnRead();
		void OnConnect();
		void OnDisconnect();

		ARCEMU_INLINE void SetSession(WorldSession* session) { mSession = session; }
		ARCEMU_INLINE WorldSession* GetSession() { return mSession; }
		bool Authed;

		void UpdateQueuedPackets();

	protected:

		void _HandleAuthSession(WorldPacket* recvPacket);
		void _HandlePing(WorldPacket* recvPacket);

	private:

		uint32 mOpcode;
		uint32 mRemaining;
		uint32 mSize;
		uint32 mSeed;
		uint32 mClientSeed;
		uint32 mClientBuild;
		uint32 mRequestID;

		WorldSession* mSession;
		WorldPacket* pAuthenticationPacket;
		FastQueue<WorldPacket*, DummyLock> _queue;
		Mutex queueLock;

		WowCrypt _crypt;
		uint32 _latency;
		bool mQueued;
		bool m_nagleEanbled;
		string* m_fullAccountName;
};


static inline void FastGUIDPack(ByteBuffer & buf, const uint64 & oldguid)
{
	// hehe speed freaks
	uint8 guidmask = 0;
	uint8 guidfields[9] = {0, 0, 0, 0, 0, 0, 0, 0};

	int j = 1;
	uint8* test = (uint8*)&oldguid;

	if(*test)  //7*8
	{
		guidfields[j] = *test;
		guidmask |= 1;
		j++;
	}
	if(*(test + 1)) //6*8
	{
		guidfields[j] = *(test + 1);
		guidmask |= 2;
		j++;
	}
	if(*(test + 2)) //5*8
	{
		guidfields[j] = *(test + 2);
		guidmask |= 4;
		j++;
	}
	if(*(test + 3)) //4*8
	{
		guidfields[j] = *(test + 3);
		guidmask |= 8;
		j++;
	}
	if(*(test + 4)) //3*8
	{
		guidfields[j] = *(test + 4);
		guidmask |= 16;
		j++;
	}
	if(*(test + 5)) //2*8
	{
		guidfields[j] = *(test + 5);
		guidmask |= 32;
		j++;
	}
	if(*(test + 6)) //1*8
	{
		guidfields[j] = *(test + 6);
		guidmask |= 64;
		j++;
	}
	if(*(test + 7)) //0*8
	{
		guidfields[j] = *(test + 7);
		guidmask |= 128;
		j++;
	}
	guidfields[0] = guidmask;

	buf.append(guidfields, j);
}

//!!! warning. This presumes that all guids can be compressed at least 1 byte
//make sure you choose highguids accordingly
static inline unsigned int FastGUIDPack(const uint64 & oldguid, unsigned char* buffer, uint32 pos)
{
	// hehe speed freaks
	uint8 guidmask = 0;

	int j = 1 + pos;

	uint8* test = (uint8*)&oldguid;

	if(*test)  //7*8
	{
		buffer[j] = *test;
		guidmask |= 1;
		j++;
	}
	if(*(test + 1)) //6*8
	{
		buffer[j] = *(test + 1);
		guidmask |= 2;
		j++;
	}
	if(*(test + 2)) //5*8
	{
		buffer[j] = *(test + 2);
		guidmask |= 4;
		j++;
	}
	if(*(test + 3)) //4*8
	{
		buffer[j] = *(test + 3);
		guidmask |= 8;
		j++;
	}
	if(*(test + 4)) //3*8
	{
		buffer[j] = *(test + 4);
		guidmask |= 16;
		j++;
	}
	if(*(test + 5)) //2*8
	{
		buffer[j] = *(test + 5);
		guidmask |= 32;
		j++;
	}
	if(*(test + 6)) //1*8
	{
		buffer[j] = *(test + 6);
		guidmask |= 64;
		j++;
	}
	if(*(test + 7)) //0*8
	{
		buffer[j] = *(test + 7);
		guidmask |= 128;
		j++;
	}
	buffer[pos] = guidmask;
	return (j - pos);
}

#endif
