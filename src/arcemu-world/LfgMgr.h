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

enum LFGTypes
{
    LFG_NONE = 0,
    LFG_INSTANCE = 1,
    LFG_RAID = 2,
    LFG_QUEST = 3,
    LFG_ZONE = 4,
    LFG_HEROIC_DUNGEON = 5, // from client
    LFG_ANY_DUNGEON = 6,
    LFG_ANY_HEROIC_DUNGEON = 7,
    LFG_DAILY_DUNGEON = 8,
    LFG_DAILY_HEROIC_DUNGEON = 9,
};

#define MAX_DUNGEONS 294+1 // check max entry's +1 on lfgdungeons.dbc
#define MAX_LFG_QUEUE_ID 3
#define LFG_MATCH_TIMEOUT 30		// in seconds

class LfgMatch;
class LfgMgr : public Singleton < LfgMgr >, EventableObject
{
	public:

		typedef list<Player*> LfgPlayerList;

		LfgMgr();
		~LfgMgr();

		bool AttemptLfgJoin(Player* pl, uint32 LfgDungeonId);
		void SetPlayerInLFGqueue(Player* pl, uint32 LfgDungeonId);
		void SetPlayerInLfmList(Player* pl, uint32 LfgDungeonId);
		void RemovePlayerFromLfgQueue(Player* pl, uint32 LfgDungeonId);
		void RemovePlayerFromLfgQueues(Player* pl);
		void RemovePlayerFromLfmList(Player* pl, uint32 LfmDungeonId);
		void UpdateLfgQueue(uint32 LfgDungeonId);
		void SendLfgList(Player* plr, uint32 Dungeon);

		int32 event_GetInstanceId() { return -1; }

	protected:

		LfgPlayerList m_lookingForGroup[MAX_DUNGEONS];
		LfgPlayerList m_lookingForMore[MAX_DUNGEONS];
		Mutex m_lock;


};

class LfgMatch
{
	public:
		set<Player*> PendingPlayers;
		set<Player*> AcceptedPlayers;
		Mutex lock;
		uint32 DungeonId;
		Group* pGroup;

		LfgMatch(uint32 did) : DungeonId(did), pGroup(NULL) { }
};

extern uint32 LfgDungeonTypes[MAX_DUNGEONS];

#define sLfgMgr LfgMgr::getSingleton()
