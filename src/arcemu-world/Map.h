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

//
// Map.h
//

#ifndef __MAP_H
#define __MAP_H

class MapMgr;
struct MapInfo;
class TerrainMgr;

#include "TerrainMgr.h"

struct Formation;

typedef struct
{
	uint32	id;//spawn ID
	uint32	entry;
	float	x;
	float	y;
	float	z;
	float	o;
	Formation* form;
	uint8 movetype;
	uint32 displayid;
	uint32 factionid;
	uint32 flags;
	uint32 bytes0;
	uint32 bytes1;
	uint32 bytes2;
	uint32 emote_state;
	//uint32 respawnNpcLink;
	uint16 channel_spell;
	uint32 channel_target_go;
	uint32 channel_target_creature;
	uint16 stand_state;
	uint32 death_state;
	uint32 MountedDisplayID;
	uint32 Item1SlotDisplay;
	uint32 Item2SlotDisplay;
	uint32 Item3SlotDisplay;
	uint32 CanFly;
	uint32 phase;

	/* sets one of the bytes of an uint32 */
	uint32 setbyte(uint32 buffer, uint8 index, uint32 byte)
	{

		/* We don't want a segfault, now do we? */
		if(index >= 4)
			return buffer;

		byte = byte << index * 8;
		buffer = buffer | byte;

		return buffer;
	}
} CreatureSpawn;

typedef struct
{
	uint32	id;//spawn ID
	uint32	entry;
	float	x;
	float	y;
	float	z;
	float	o;
	float	o1;
	float	o2;
	float	o3;
	float	facing;
	uint32	flags;
	uint32	state;
	uint32	faction;
	//uint32 level;
	float scale;
	//uint32 stateNpcLink;
	uint32 phase;
	uint32 overrides;
} GOSpawn;

typedef std::vector<CreatureSpawn*> CreatureSpawnList;
typedef std::vector<GOSpawn*> GOSpawnList;

typedef struct
{
	CreatureSpawnList CreatureSpawns;
	GOSpawnList GOSpawns;
} CellSpawns;

class SERVER_DECL Map
{
	public:
		Map(uint32 mapid, MapInfo* inf);
		~Map();

		ARCEMU_INLINE string GetNameString() { return name; }
		ARCEMU_INLINE const char* GetName() { return name.c_str(); }
		ARCEMU_INLINE MapEntry* GetDBCEntry() { return me; }

		ARCEMU_INLINE CellSpawns* GetSpawnsList(uint32 cellx, uint32 celly)
		{
			ARCEMU_ASSERT(cellx < _sizeX);
			ARCEMU_ASSERT(celly < _sizeY);
			if(spawns[cellx] == NULL) return NULL;

			return spawns[cellx][celly];
		}
		ARCEMU_INLINE CellSpawns* GetSpawnsListAndCreate(uint32 cellx, uint32 celly)
		{
			ARCEMU_ASSERT(cellx < _sizeX);
			ARCEMU_ASSERT(celly < _sizeY);
			if(spawns[cellx] == NULL)
			{
				spawns[cellx] = new CellSpawns*[_sizeY];
				memset(spawns[cellx], 0, sizeof(CellSpawns*)*_sizeY);
			}

			if(spawns[cellx][celly] == 0)
				spawns[cellx][celly] = new CellSpawns;
			return spawns[cellx][celly];
		}

		void LoadSpawns(bool reload);//set to true to make clean up
		uint32 CreatureSpawnCount;
		uint32 GameObjectSpawnCount;

		ARCEMU_INLINE void CellGoneActive(uint32 x, uint32 y)
		{
		}

		ARCEMU_INLINE void CellGoneIdle(uint32 x, uint32 y)
		{
		}

	private:
		MapInfo* 	   _mapInfo;
		uint32 _mapId;
		string name;
		MapEntry* me;

		//new stuff
		CellSpawns** spawns[_sizeX];
	public:
		CellSpawns staticSpawns;
};

#endif
