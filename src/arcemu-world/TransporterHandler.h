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

#ifndef __TRANSPORTERHANDLER_H
#define __TRANSPORTERHANDLER_H

class TransportPath
{
	public:
		struct PathNode
		{
			uint32 mapid;
			float x, y, z;
			uint32 actionFlag;
			uint32 delay;
		};

		ARCEMU_INLINE void SetLength(const unsigned int sz)
		{
			i_nodes.resize(sz);
		}

		ARCEMU_INLINE size_t Size(void) const { return i_nodes.size(); }
		ARCEMU_INLINE void Resize(unsigned int sz) { i_nodes.resize(sz); }
		ARCEMU_INLINE void Clear(void) { i_nodes.clear(); }
		ARCEMU_INLINE PathNode* GetNodes(void) { return TO< PathNode* >(&i_nodes[0]); }
		float GetTotalLength(void)
		{
			float len = 0, xd, yd, zd;
			for(unsigned int idx = 1; idx < i_nodes.size(); ++idx)
			{
				xd = i_nodes[ idx ].x - i_nodes[ idx - 1 ].x;
				yd = i_nodes[ idx ].y - i_nodes[ idx - 1 ].y;
				zd = i_nodes[ idx ].z - i_nodes[ idx - 1 ].z;
				len += (float)sqrt(xd * xd + yd * yd + zd * zd);
			}
			return len;
		}

		PathNode & operator[](const unsigned int idx) { return i_nodes[idx]; }
		const PathNode & operator()(const unsigned int idx) const { return i_nodes[idx]; }

	protected:
		std::vector<PathNode> i_nodes;
};

struct keyFrame
{
	keyFrame(float _x, float _y, float _z, uint32 _mapid, int _actionflag, int _delay)
	{
		x = _x;
		y = _y;
		z = _z;
		mapid = _mapid;
		actionflag = _actionflag;
		delay = _delay;
		distFromPrev = -1;
		distSinceStop = -1;
		distUntilStop = -1;
		tFrom = 0;
		tTo = 0;
	}

	float x;
	float y;
	float z;
	uint32 mapid;
	int actionflag;
	int delay;
	float distSinceStop;
	float distUntilStop;
	float distFromPrev;
	float tFrom, tTo;
};

struct TWayPoint
{
	TWayPoint() : mapid(0), x(0), y(0), z(0), o(0), teleport(0), delayed(false) {}
	TWayPoint(uint32 _mapid, float _x, float _y, float _z, bool _teleport) :
		mapid(_mapid), x(_x), y(_y), z(_z), o(0), teleport(_teleport), delayed(false) {}
	uint32 mapid;
	float x;
	float y;
	float z;
	float o;
	bool teleport;
	bool delayed;
};

typedef std::map<uint32, TWayPoint> WaypointMap;
typedef std::map<uint32, TWayPoint>::iterator WaypointIterator;
typedef std::map<uint32, Player*> PassengerMap;
typedef std::map<uint32, Player*>::iterator PassengerIterator;
typedef std::map<uint32, Object*> TransportNPCMap;

bool FillTransporterPathVector(uint32 PathID, TransportPath & Path);

extern Mutex m_transportGuidGen;
extern uint32 m_transportGuidMax;

class Transporter : public GameObject
{
	public:
		Transporter(uint64 guid);
		~Transporter();

		bool CreateAsTransporter(uint32 EntryID, const char* Name, int32 Time);
		void UpdatePosition();
		void TransportPassengers(uint32 mapid, uint32 oldmap, float x, float y, float z);
		void TransportGossip(uint32 route);
		bool GenerateWaypoints();

		ARCEMU_INLINE void AddPlayer(Player* pPlayer) { mPassengers[pPlayer->GetLowGUID()] = pPlayer; }
		ARCEMU_INLINE void RemovePlayer(Player* pPlayer) {mPassengers.erase(pPlayer->GetLowGUID()); }
		ARCEMU_INLINE bool HasPlayer(Player* pPlayer) { return mPassengers.find(pPlayer->GetLowGUID()) != mPassengers.end(); }
		ARCEMU_INLINE void SetPeriod(uint32 val) { m_period = val; }

		uint32 m_pathTime;
		uint32 m_timer;

		WaypointIterator mCurrentWaypoint;
		WaypointIterator mNextWaypoint;

		void OnPushToWorld();
		uint32  BuildCreateUpdateBlockForPlayer(ByteBuffer* data, Player* target);
		void DestroyTransportNPCs(Player* target);
		void AddNPC(uint32 Entry, float offsetX, float offsetY, float offsetZ, float offsetO);
		Creature* GetCreature(uint32 Guid);
		GameObject* GetGameObject(uint32 Guid);

		void AddPassenger( Object *o );
		void RemovePassenger( Object *o );

		void MovePassengers( float x, float y, float z, float o );

	private:

		TransportNPCMap m_npcs;
		WaypointMap m_WayPoints;
		PassengerMap mPassengers;
		std::map< uint64, Object* > passengers;

		int32 m_period;

		WaypointIterator GetNextWaypoint();
};

#endif
