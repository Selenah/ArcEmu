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

#include "StdAfx.h"

#define MAX_MAP 800

CCollideInterface CollideInterface;
Mutex m_loadLock;
uint32 m_tilesLoaded[MAX_MAP][64][64];

#ifdef WIN32
#ifdef COLLISION_DEBUG

uint64 c_GetTimerValue()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return li.QuadPart;
}

uint32 c_GetNanoSeconds(uint64 t1, uint64 t2)
{
	LARGE_INTEGER li;
	double val;
	QueryPerformanceFrequency(&li);
	val = double(t1 - t2) * 1000000;
	val /= li.QuadPart;
	return long2int32(val);
}

#define COLLISION_BEGINTIMER uint64 v1 = c_GetTimerValue();

#endif	// COLLISION_DEBUG
#endif	// WIN32


// Debug functions
#ifdef COLLISION_DEBUG

void CCollideInterface::Init()
{
	Log.Notice("CollideInterface", "Init");
	COLLISION_BEGINTIMER;
	CollisionMgr = ((IVMapManager*)collision_init());
	LOG_DEBUG("[%u ns] collision_init", c_GetNanoSeconds(c_GetTimerValue(), v1));
}

void CCollideInterface::ActivateTile(uint32 mapId, uint32 tileX, uint32 tileY)
{
	m_loadLock.Acquire();
	if(m_tilesLoaded[mapId][tileX][tileY] == 0)
	{
		COLLISION_BEGINTIMER;
		CollisionMgr->loadMap(sWorld.vMapPath.c_str, mapId, tileY, tileX);
		LOG_DEBUG("[%u ns] collision_activate_cell %u %u %u", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, tileX, tileY);
	}

	++m_tilesLoaded[mapId][tileX][tileY];
	m_loadLock.Release();
}

void CCollideInterface::DeactivateTile(uint32 mapId, uint32 tileX, uint32 tileY)
{
	m_loadLock.Acquire();
	if(!(--m_tilesLoaded[mapId][tileX][tileY]))
	{
		COLLISION_BEGINTIMER;
		CollisionMgr->unloadMap(mapId, tileY, tileX);
		LOG_DEBUG("[%u ns] collision_deactivate_cell %u %u %u", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, tileX, tileY);
	}

	m_loadLock.Release();
}

void CCollideInterface::DeInit()
{
	Log.Notice("CollideInterface", "DeInit");
	COLLISION_BEGINTIMER;
	collision_shutdown();
	LOG_DEBUG("[%u ns] collision_shutdown", c_GetNanoSeconds(c_GetTimerValue(), v1));
}

float CCollideInterface::GetHeight(uint32 mapId, float x, float y, float z)
{
	COLLISION_BEGINTIMER;
	float v = CollisionMgr->getHeight(mapId, x, y, z);
	LOG_DEBUG("[%u ns] GetHeight Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, x, y, z);
	return v;
}

float CCollideInterface::GetHeight(uint32 mapId, LocationVector & pos)
{
	COLLISION_BEGINTIMER;
	float v = CollisionMgr->getHeight(mapId, pos);
	LOG_DEBUG("[%u ns] GetHeight Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, pos.x, pos.y, pos.z);
	return v;
}

bool CCollideInterface::IsIndoor(uint32 mapId, LocationVector & pos)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isInDoors(mapId, pos);
	LOG_DEBUG("[%u ns] IsIndoor Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, pos.x, pos.y, pos.z);
	return r;
}

bool CCollideInterface::IsOutdoor(uint32 mapId, LocationVector & pos)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isOutDoors(mapId, pos);
	LOG_DEBUG("[%u ns] IsOutdoor Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, pos.x, pos.y, pos.z);
	return r;
}

bool CCollideInterface::IsIndoor(uint32 mapId, float x, float y, float z)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isInDoors(mapId, x, y, z);
	LOG_DEBUG("[%u ns] IsIndoor Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, x, y, z);
	return r;
}

bool CCollideInterface::IsOutdoor(uint32 mapId, float x, float y, float z)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isOutDoors(mapId, x, y, z);
	LOG_DEBUG("[%u ns] IsOutdoor Map:%u %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, x, y, z);
	return r;
}

bool CCollideInterface::CheckLOS(uint32 mapId, LocationVector & pos1, LocationVector & pos2)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isInLineOfSight(mapId, pos1, pos2);
	LOG_DEBUG("[%u ns] CheckLOS Map:%u %f %f %f -> %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z);
	return r;
}

bool CCollideInterface::CheckLOS(uint32 mapId, float x1, float y1, float z1, float x2, float y2, float z2)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->isInLineOfSight(mapId, x1, y1, z1, x2, y2, z2);
	LOG_DEBUG("[%u ns] CheckLOS Map:%u %f %f %f -> %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, x1, y1, z1, x2, y2, z2);
	return r;
}

bool CCollideInterface::GetFirstPoint(uint32 mapId, LocationVector & pos1, LocationVector & pos2, LocationVector & outvec, float distmod)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->getObjectHitPos(mapId, pos1, pos2, outvec, distmod);
	LOG_DEBUG("[%u ns] GetFirstPoint Map:%u %f %f %f -> %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z);
	return r;
}

bool CCollideInterface::GetFirstPoint(uint32 mapId, float x1, float y1, float z1, float x2, float y2, float z2, float & outx, float & outy, float & outz, float distmod)
{
	bool r;
	COLLISION_BEGINTIMER;
	r = CollisionMgr->getObjectHitPos(mapId, x1, y1, z1, x2, y2, z2, outx, outy, outz, distmod);
	LOG_DEBUG("[%u ns] GetFirstPoint Map:%u %f %f %f -> %f %f %f", c_GetNanoSeconds(c_GetTimerValue(), v1), mapId, x1, y1, z1, x2, y2, z2);
	return r;
}

#else

void CCollideInterface::Init()
{
	Log.Notice("CollideInterface", "Init");
	//CollisionMgr = ((IVMapManager*)collision_init());
}

void CCollideInterface::ActivateTile(uint32 mapId, uint32 tileX, uint32 tileY)
{
	VMAP::IVMapManager* mgr = VMAP::VMapFactory::createOrGetVMapManager();
	m_loadLock.Acquire();
	if(m_tilesLoaded[mapId][tileX][tileY] == 0)
	{
		mgr->loadMap(sWorld.vMapPath.c_str(), mapId, tileX, tileY);
		LoadNavMeshTile(mapId, tileX, tileY);
	}
	++m_tilesLoaded[mapId][tileX][tileY];
	m_loadLock.Release();
}

void CCollideInterface::DeactivateTile(uint32 mapId, uint32 tileX, uint32 tileY)
{
	VMAP::IVMapManager* mgr = VMAP::VMapFactory::createOrGetVMapManager();
	m_loadLock.Acquire();
	if(!(--m_tilesLoaded[mapId][tileX][tileY]))
	{
		mgr->unloadMap(mapId, tileX, tileY);

		NavMeshData* nav = GetNavMesh(mapId);

		if(nav != NULL)
		{
			uint32 key = tileX | (tileY << 16);
			nav->tilelock.Acquire();
			std::map<uint32, dtTileRef>::iterator itr = nav->tilerefs.find(key);

			if(itr != nav->tilerefs.end())
			{
				nav->mesh->removeTile(itr->second, NULL, NULL);
				nav->tilerefs.erase(itr);
			}

			nav->tilelock.Release();
		}
	}

	m_loadLock.Release();
}

void CCollideInterface::DeInit()
{
	Log.Notice("CollideInterface", "DeInit");
	//collision_shutdown();
}

void CCollideInterface::ActivateMap(uint32 mapid)
{
	m_navmaplock.Acquire();
	std::map<uint32, NavMeshData*>::iterator itr = m_navdata.find(mapid);

	if(itr != m_navdata.end())
		++itr->second->refs;
	else
	{

		//load params
		char filename[1024];
		sprintf(filename, "mmaps/%03i.mmap", mapid);
		FILE* f = fopen(filename, "rb");

		if(f == NULL)
		{
			m_navmaplock.Release();
			return;
		}

		dtNavMeshParams params;
		fread(&params, sizeof(params), 1, f);
		fclose(f);

		NavMeshData* d = new NavMeshData;
		d->mesh = dtAllocNavMesh();
		d->query = dtAllocNavMeshQuery();
		d->mesh->init(&params);
		d->query->init(d->mesh, 1024);
		d->AddRef();
		m_navdata.insert(std::make_pair(mapid, d));
	}
	m_navmaplock.Release();
}

void CCollideInterface::DeactiveMap(uint32 mapid)
{
	m_navmaplock.Acquire();

	std::map<uint32, NavMeshData*>::iterator itr = m_navdata.find(mapid);

	if(itr != m_navdata.end())
	{
		if(itr->second->DecRef())
			m_navdata.erase(itr);
	}

	m_navmaplock.Release();
}

NavMeshData* CCollideInterface::GetNavMesh(uint32 mapId)
{
#ifndef TEST_PATHFINDING
	return NULL;
#endif
	NavMeshData* retval = NULL;
	m_navmaplock.Acquire();
	std::map<uint32, NavMeshData*>::iterator itr = m_navdata.find(mapId);

	if(itr != m_navdata.end())
		retval = itr->second;

	m_navmaplock.Release();
	return retval;
}

void CCollideInterface::LoadNavMeshTile(uint32 mapId, uint32 tileX, uint32 tileY)
{
	NavMeshData* nav = GetNavMesh(mapId);

	if(nav == NULL)
		return;

	char filename[1024];
	sprintf(filename, "mmaps/%03i%02i%02i.mmtile", mapId, tileX, tileY);
	FILE* f = fopen(filename, "rb");

	if(f == NULL)
		return;

	MmapTileHeader header;

	fread(&header, sizeof(MmapTileHeader), 1, f);

	if(header.mmapMagic != MMAP_MAGIC || header.mmapVersion != MMAP_VERSION)
	{
		sLog.Debug("NavMesh", "Load failed (%u %u %u): tile headers incorrect", mapId, tileX, tileY);
		fclose(f);
		return;
	}

	uint8* data = (uint8*)dtAlloc(header.size, DT_ALLOC_PERM);

	if(data == NULL)
	{
		fclose(f);
		return;
	}

	fread(data, 1, header.size, f);

	fclose(f);

	dtTileRef dtref;
	nav->mesh->addTile(data, header.size, DT_TILE_FREE_DATA, 0, &dtref);

	nav->tilelock.Acquire();
	nav->tilerefs.insert(std::make_pair(tileX | (tileY << 16), dtref));
	nav->tilelock.Release();
}

#endif		// COLLISION_DEBUG

