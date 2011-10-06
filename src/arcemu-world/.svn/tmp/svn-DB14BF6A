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


#ifndef _EOTS_H
#define _EOTS_H

#define EOTS_TOWER_COUNT 4

#define EOTS_BUFF_RESPAWN_TIME 90000

class EyeOfTheStorm : public CBattleground
{
	public:
		EyeOfTheStorm(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
		~EyeOfTheStorm();

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
		static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new EyeOfTheStorm(m, i, l, t); }
		uint32 GetFlagHolderGUID() { return m_flagHolder; }

		uint32 GetNameID() { return 44; }
		void OnStart();

		void UpdateCPs();
		void GeneratePoints();

		// returns true if that team won
		bool GivePoints(uint32 team, uint32 points);

		void RespawnCPFlag(uint32 i, uint32 id);		// 0 = Neutral, <0 = Leaning towards alliance, >0 Leaning towards horde

		bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);
		void DropFlag2(Player* plr, uint32 id);
		void HookOnFlagDrop(Player* plr);
		void EventResetFlag();
		void RepopPlayersOfTeam(int32 team, Creature* sh);

		void SetIsWeekend(bool isweekend);

	protected:
		int32 m_CPStatus[EOTS_TOWER_COUNT];
		uint32 m_flagHolder;

		GameObject* m_standFlag;
		GameObject* m_dropFlag;

		GameObject* m_CPStatusGO[EOTS_TOWER_COUNT];
		GameObject* m_CPBanner[EOTS_TOWER_COUNT];
		GameObject* m_CPBanner2[EOTS_TOWER_COUNT];
		GameObject* m_CPBanner3[EOTS_TOWER_COUNT];
		GameObject* m_bubbles[2];
		GameObject* EOTSm_buffs[4];

		typedef set<Player*> EOTSCaptureDisplayList;
		EOTSCaptureDisplayList m_CPDisplay[EOTS_TOWER_COUNT];

		uint32 m_lastHonorGainPoints[2];
		uint32 m_points[2];
		Creature* m_spiritGuides[EOTS_TOWER_COUNT];
};

#endif		// _EOTS_H
