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

#ifndef LOGONCOMMHANDLER_H
#define LOGONCOMMHANDLER_H

typedef struct
{
	uint32 ID;
	string Name;
	string Address;
	uint32 Port;
	uint32 ServerID;
	uint32 RetryTime;
	bool   Registered;
} LogonServer;

typedef struct
{
	string Name;
	string Address;
	uint32 flags;
	uint32 Icon;
	uint32 TimeZone;
	float Population;
	uint8 Lock;
} Realm;

enum RealmType
{
    REALMTYPE_NORMAL = 0,
    REALMTYPE_PVP	= 3,
    REALMTYPE_RP	 = 6,
    REALMTYPE_RPPVP  = 8,
};

class LogonCommHandler : public Singleton<LogonCommHandler>
{
#ifdef WIN32
		typedef HM_NAMESPACE::hash_map<string, string> ForcedPermissionMap;
#else
		typedef map<string, string> ForcedPermissionMap;
#endif

		ForcedPermissionMap forced_permissions;
		map<LogonServer*, LogonCommClientSocket*> logons;
		map<uint32, WorldSocket*> pending_logons;
		set<Realm*> realms;
		set<LogonServer*> servers;
		uint32 idhigh;
		uint32 next_request;
		Mutex mapLock;
		Mutex pendingLock;
		bool pings;
		uint32 _realmType;
		uint32 pLimit;
		float server_population;

	public:
		uint8 sql_passhash[20];

		LogonCommHandler();
		~LogonCommHandler();

		LogonCommClientSocket* ConnectToLogon(string Address, uint32 Port);
		void UpdateAccountCount(uint32 account_id, uint8 add);
		void RequestAddition(LogonCommClientSocket* Socket);
		void CheckAllServers();
		void Startup();
		void ConnectionDropped(uint32 ID);
		void AdditionAck(uint32 ID, uint32 ServID);
		void UpdateSockets();
		void Connect(LogonServer* server);
		void ConnectAll();
		//void LogonDatabaseSQLExecute(const char* str, ...);
		//void LogonDatabaseReloadAccounts();
		void RefreshRealmPop();

		void Account_SetBanned(const char* account, uint32 banned, const char* reason);
		void Account_SetGM(const char* account, const char* flags);
		void Account_SetMute(const char* account, uint32 muted);
		void IPBan_Add(const char* ip, uint32 duration, const char* reason);
		void IPBan_Remove(const char* ip);

		void LoadRealmConfiguration();
		void AddServer(string Name, string Address, uint32 Port);

		ARCEMU_INLINE uint32 GetRealmType() { return _realmType; }
		void SetRealmType(uint32 type) { _realmType = type; }
		float GetServerPopulation() { return server_population; }

		/////////////////////////////
		// Worldsocket stuff
		///////

		uint32 ClientConnected(string AccountName, WorldSocket* Socket);
		void UnauthedSocketClose(uint32 id);
		void RemoveUnauthedSocket(uint32 id);
		WorldSocket* GetSocketByRequest(uint32 id)
		{
			//pendingLock.Acquire();

			WorldSocket* sock;
			map<uint32, WorldSocket*>::iterator itr = pending_logons.find(id);
			sock = (itr == pending_logons.end()) ? 0 : itr->second;

			//pendingLock.Release();
			return sock;
		}
		ARCEMU_INLINE Mutex & GetPendingLock() { return pendingLock; }
		const string* GetForcedPermissions(string & username);

		void TestConsoleLogon(string & username, string & password, uint32 requestnum);
};

#define sLogonCommHandler LogonCommHandler::getSingleton()

#endif

