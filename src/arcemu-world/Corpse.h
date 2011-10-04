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

#ifndef WOWSERVER_CORPSE_H
#define WOWSERVER_CORPSE_H

enum CORPSE_STATE
{
    CORPSE_STATE_BODY = 0,
    CORPSE_STATE_BONES = 1,
};

struct CorpseData
{
	uint32 LowGuid;
	uint32 mapid;
	uint64 owner;
	uint32 instancemapid;
	float x;
	float y;
	float z;
	void DeleteFromDB();
};

#define CORPSE_RECLAIM_TIME 30
#define CORPSE_RECLAIM_TIME_MS CORPSE_RECLAIM_TIME * 1000
#define CORPSE_MINIMUM_RECLAIM_RADIUS 39
#define CORPSE_MINIMUM_RECLAIM_RADIUS_SQ CORPSE_MINIMUM_RECLAIM_RADIUS * CORPSE_MINIMUM_RECLAIM_RADIUS

class SERVER_DECL Corpse : public Object
{
	public:
		Corpse(uint32 high, uint32 low);
		~Corpse();

		// void Create();
		void Create(Player* owner, uint32 mapid, float x, float y, float z, float ang);

		void SaveToDB();
		void DeleteFromDB();
		ARCEMU_INLINE void SetCorpseState(uint32 state) { m_state = state; }
		ARCEMU_INLINE uint32 GetCorpseState() { return m_state; }
		void Despawn();

		ARCEMU_INLINE void SetLoadedFromDB(bool value) { _loadedfromdb = value; }
		ARCEMU_INLINE bool GetLoadedFromDB(void) { return _loadedfromdb; }
		Loot loot;
		void generateLoot();

		void SpawnBones();
		void Delink();

		void ResetDeathClock() { m_time = time(NULL); }
		time_t GetDeathClock() { return m_time; }

		//Easy functions
		void SetOwner(uint64 guid);
		uint64 GetOwner() { return GetUInt64Value(CORPSE_FIELD_OWNER); }

		void SetDisplayId(uint32 id) { SetUInt32Value(CORPSE_FIELD_DISPLAY_ID, id); }
		uint32 GetDisplayId() { return GetUInt32Value(CORPSE_FIELD_DISPLAY_ID); }

	private:
		uint32 m_state;
		time_t m_time;
		uint32 _fields[CORPSE_END];
		bool _loadedfromdb;
};

#endif

