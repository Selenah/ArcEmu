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

#ifndef arcemu_ARENATEAMS_H
#define arcemu_ARENATEAMS_H

struct ArenaTeamMember
{
	PlayerInfo* Info;
	uint32 Played_ThisWeek;
	uint32 Won_ThisWeek;
	uint32 Played_ThisSeason;
	uint32 Won_ThisSeason;
	uint32 PersonalRating;
};

class SERVER_DECL ArenaTeam
{
		void AllocateSlots(uint32 Type)
		{
			uint32 Slots = 0;
			if(Type == ARENA_TEAM_TYPE_2V2)
				Slots = 4;
			else if(Type == ARENA_TEAM_TYPE_3V3)
				Slots = 6;
			else if(Type == ARENA_TEAM_TYPE_5V5)
				Slots = 10;
			ARCEMU_ASSERT(Slots > 0);
			m_members = new ArenaTeamMember[Slots];
			memset(m_members, 0, sizeof(ArenaTeamMember)*Slots);
			m_slots = Slots;
			m_memberCount = 0;
		}

	public:

		uint32 m_id;
		uint32 m_type;
		uint32 m_leader;
		uint32 m_slots;
		string m_name;
		uint32 m_memberCount;
		ArenaTeamMember* m_members;

		uint32 m_emblemStyle;
		uint32 m_emblemColour;
		uint32 m_borderStyle;
		uint32 m_borderColour;
		uint32 m_backgroundColour;

		uint32 m_stat_rating;
		uint32 m_stat_gamesplayedweek;
		uint32 m_stat_gameswonweek;
		uint32 m_stat_gamesplayedseason;
		uint32 m_stat_gameswonseason;
		uint32 m_stat_ranking;

		ArenaTeam(uint32 Type, uint32 Id);
		ArenaTeam(Field* f);
		~ArenaTeam()
		{
			delete [] m_members;
		}

		void SendPacket(WorldPacket* data);
		void Query(WorldPacket & data);
		void Stat(WorldPacket & data);
		void Roster(WorldPacket & data);
		void Inspect(WorldPacket & data);
		void Destroy();
		void SaveToDB();

		bool AddMember(PlayerInfo* info);
		bool RemoveMember(PlayerInfo* info);
		bool HasMember(uint32 guid);
		void SetLeader(PlayerInfo* info);
		ArenaTeamMember* GetMember(PlayerInfo* info);
		ArenaTeamMember* GetMemberByGuid(uint32 guid);

		uint32 GetPlayersPerTeam()
		{
			switch(m_type)
			{
				case ARENA_TEAM_TYPE_2V2:
					return 2;

				case ARENA_TEAM_TYPE_3V3:
					return 3;

				case ARENA_TEAM_TYPE_5V5:
					return 5;
			}

			// never reached
			return 2;
		}
};

#endif		// arcemu_ARENATEAMS_H
