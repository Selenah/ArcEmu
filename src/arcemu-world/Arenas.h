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

class ArenaTeam;

class Arena : public CBattleground
{
		set<GameObject*> m_gates;
		GameObject* m_buffs[2];
		ArenaTeam* m_teams[2];
		uint32 m_arenateamtype;
		uint32 m_playersCount[2];
		set<uint32> m_players2[2];
		set<uint32> m_playersAlive;
	public:
		bool rated_match;
		Arena(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t, uint32 players_per_side);
		virtual ~Arena();

		bool HookHandleRepop(Player* plr);
		void OnAddPlayer(Player* plr);
		void OnRemovePlayer(Player* plr);
		void OnCreate();
		void HookOnPlayerDeath(Player* plr);
		void HookOnPlayerKill(Player* plr, Player* pVictim);
		void HookOnUnitKill(Player* plr, Unit* pVictim);
		void HookOnFlagDrop(Player* plr);
		void HookOnHK(Player* plr);
		void HookOnShadowSight();
		void HookGenerateLoot(Player* plr, Object* pCorpse);
		void UpdatePlayerCounts();
		LocationVector GetStartingCoords(uint32 Team);
		uint32 GetNameID() { return 50; }
		void OnStart();
		bool CanPlayerJoin(Player* plr, uint32 type)
		{
			if(m_started)
				return false;
			else
				return CBattleground::CanPlayerJoin(plr, type);
		}

		bool CreateCorpse(Player* plr) { return false; }

		/* dummy stuff */
		void HookOnMount(Player* plr) {}
		void HookFlagDrop(Player* plr, GameObject* obj) {}
		void HookFlagStand(Player* plr, GameObject* obj) {}
		void HookOnAreaTrigger(Player* plr, uint32 id);

		int32 GetFreeTeam()
		{
			size_t c0 = m_players[0].size() + m_pendPlayers[0].size();
			size_t c1 = m_players[1].size() + m_pendPlayers[1].size();
			if(m_started) return -1;

			// Check if there is free room, if yes, return team with less members
			return ((c0 + c1 >= m_playerCountPerTeam * 2) ? -1 : (c0 > c1));

			/* We shouldn't reach here. */
		}

		void Finish();
		ARCEMU_INLINE uint8 Rated() { return rated_match; }
		ARCEMU_INLINE uint32 GetArenaTeamType() { return m_arenateamtype; }
		ARCEMU_INLINE ArenaTeam** GetTeams() { return m_teams; }
		uint32 CalcDeltaRating(uint32 oldRating, uint32 opponentRating, bool outcome);
};
