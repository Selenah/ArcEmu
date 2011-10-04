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

#ifndef _MAP_SCRIPT_INTERFACE_H
#define _MAP_SCRIPT_INTERFACE_H

/* * Class MapScriptInterface
   * Provides an interface to mapmgr for scripts, to obtain objects,
   * get players, etc.
*/

class GameObject;
class Object;
class Creature;
class Unit;
class Player;

class SERVER_DECL MapScriptInterface
{
	public:
		MapScriptInterface(MapMgr & mgr);
		~MapScriptInterface();

		template<class T, uint32 TypeId> T* GetObjectNearestCoords(uint32 Entry, float x, float y, float z = 0.0f)
		{
			MapCell* pCell = mapMgr.GetCell(mapMgr.GetPosX(x), mapMgr.GetPosY(y));
			if(pCell == 0)
				return 0;

			T* ClosestObject = NULL;
			float ClosestDist = 999999.0f;
			float CurrentDist = 0;

			ObjectSet::const_iterator iter = pCell->Begin();
			for(; iter != pCell->End(); ++iter)
			{
				CurrentDist = (*iter)->CalcDistance(x, y, (z != 0.0f ? z : (*iter)->GetPositionZ()));
				if(CurrentDist < ClosestDist && (*iter)->GetTypeId() == TypeId)
				{
					if((Entry && (*iter)->GetEntry() == Entry) || !Entry)
					{
						ClosestDist = CurrentDist;
						ClosestObject = ((T*)(*iter));
					}
				}
			}

			return ClosestObject;
		}

		ARCEMU_INLINE GameObject* GetGameObjectNearestCoords(float x, float y, float z = 0.0f, uint32 Entry = 0)
		{
			return GetObjectNearestCoords<GameObject, TYPEID_GAMEOBJECT>(Entry, x, y, z);
		}

		ARCEMU_INLINE Creature* GetCreatureNearestCoords(float x, float y, float z = 0.0f, uint32 Entry = 0)
		{
			return GetObjectNearestCoords<Creature, TYPEID_UNIT>(Entry, x, y, z);
		}

		ARCEMU_INLINE Player* GetPlayerNearestCoords(float x, float y, float z = 0.0f, uint32 Entry = 0)
		{
			return GetObjectNearestCoords<Player, TYPEID_PLAYER>(Entry, x, y, z);
		}

		uint32 GetPlayerCountInRadius(float x, float y, float z = 0.0f, float radius = 5.0f);

		GameObject* SpawnGameObject(uint32 Entry, float cX, float cY, float cZ, float cO, bool AddToWorld, uint32 Misc1, uint32 Misc2, uint32 phase = 0xFFFFFFF);
		GameObject* SpawnGameObject(GOSpawn* gs, bool AddToWorld);
		Creature* SpawnCreature(uint32 Entry, float cX, float cY, float cZ, float cO, bool AddToWorld, bool tmplate, uint32 Misc1, uint32 Misc2, uint32 phase = 0xFFFFFFF);
		Creature* SpawnCreature(CreatureSpawn* sp, bool AddToWorld);
		WayPoint* CreateWaypoint();

		void DeleteGameObject(GameObject* ptr);
		void DeleteCreature(Creature* ptr);

		MapScriptInterface & operator=(MapScriptInterface & msi)
		{
			if(this != &msi)
			{
				this->mapMgr = msi.mapMgr;
			}

			return *this;
		}

	private:
		MapMgr & mapMgr;
};

class SERVER_DECL StructFactory : public Singleton<StructFactory>
{
	public:
		StructFactory() {}
		WayPoint* CreateWaypoint();
};

#define sStructFactory StructFactory::getSingleton()

#endif

