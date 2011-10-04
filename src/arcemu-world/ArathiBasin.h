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

#define AB_BUFF_RESPAWN_TIME 90000

enum ABBuffs
{
    AB_BUFF_STABLES						= 0,
    AB_BUFF_BLACKSMITH					= 1,
    AB_BUFF_FARM						= 2,
    AB_BUFF_LUMBERMILL					= 3,
    AB_BUFF_MINE						= 4,
    AB_NUM_BUFFS						= 5,
};

enum ABControlPoints
{
    AB_CONTROL_POINT_STABLE				= 0,
    AB_CONTROL_POINT_FARM				= 1,
    AB_CONTROL_POINT_BLACKSMITH			= 2,
    AB_CONTROL_POINT_MINE				= 3,
    AB_CONTROL_POINT_LUMBERMILL			= 4,
    AB_NUM_CONTROL_POINTS				= 5,
};

enum ABSpawnTypes
{
    AB_SPAWN_TYPE_NEUTRAL				= 0,
    AB_SPAWN_TYPE_ALLIANCE_ASSAULT		= 1,
    AB_SPAWN_TYPE_HORDE_ASSAULT			= 2,
    AB_SPAWN_TYPE_ALLIANCE_CONTROLLED	= 3,
    AB_SPAWN_TYPE_HORDE_CONTROLLED		= 4,
    AB_NUM_SPAWN_TYPES					= 5,
};

class ArathiBasin : public CBattleground
{
	public:
		GameObject* m_buffs[AB_NUM_BUFFS];
		GameObject* m_controlPoints[AB_NUM_CONTROL_POINTS];
		GameObject* m_controlPointAuras[AB_NUM_CONTROL_POINTS];

	protected:
		list<GameObject*> m_gates;

		uint32 m_resources[2];
		uint32 m_capturedBases[2];
		uint32 m_lastHonorGainResources[2];
		uint32 m_lastRepGainResources[2];
		int32 m_basesOwnedBy[AB_NUM_CONTROL_POINTS];
		int32 m_basesLastOwnedBy[AB_NUM_CONTROL_POINTS];
		int32 m_basesAssaultedBy[AB_NUM_CONTROL_POINTS];
		Creature* m_spiritGuides[AB_NUM_CONTROL_POINTS];
		bool m_nearingVictory[2];
		uint32 m_lgroup;
		bool DefFlag[AB_NUM_CONTROL_POINTS][2];

	public:
		ArathiBasin(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
		~ArathiBasin();

		void HookOnPlayerDeath(Player* plr);
		void HookFlagDrop(Player* plr, GameObject* obj);
		void HookFlagStand(Player* plr, GameObject* obj);
		void HookOnMount(Player* plr);
		void HookOnAreaTrigger(Player* plr, uint32 id);
		bool HookHandleRepop(Player* plr);
		void OnAddPlayer(Player* plr);
		void OnRemovePlayer(Player* plr);
		void OnCreate();
		void HookOnPlayerKill(Player* plr, Player* pVictim);
		void HookOnUnitKill(Player* plr, Unit* pVictim);
		void HookOnHK(Player* plr);
		void HookOnShadowSight();
		void HookGenerateLoot(Player* plr, Object* pCorpse);
		void SpawnBuff(uint32 x);
		LocationVector GetStartingCoords(uint32 Team);
		void HookOnFlagDrop(Player* plr);

		static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new ArathiBasin(m, i, l, t); }

		uint32 GetNameID() { return 40; }
		void OnStart();

		void EventUpdateResources(uint32 Team);
		bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

		/* AB Game Mechanics */
		void SpawnControlPoint(uint32 Id, uint32 Type);
		void CaptureControlPoint(uint32 Id, uint32 Team);
		void AssaultControlPoint(Player* pPlayer, uint32 Id);

		void SetIsWeekend(bool isweekend);
};
