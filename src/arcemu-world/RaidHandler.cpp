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

#include "StdAfx.h"

void WorldSession::HandleConvertGroupToRaidOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	// This is just soooo easy now
	Group* pGroup = _player->GetGroup();
	if(!pGroup) return;

	if(pGroup->GetLeader() != _player->m_playerInfo)      //access denied
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	pGroup->ExpandToRaid();
	SendPartyCommandResult(_player, 0, "", ERR_PARTY_NO_ERROR);
}

void WorldSession::HandleGroupChangeSubGroup(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	std::string name;
	uint8 subGroup;

	recv_data >> name;
	recv_data >> subGroup;

	PlayerInfo* inf = objmgr.GetPlayerInfoByName(name.c_str());
	if(inf == NULL || inf->m_Group == NULL || inf->m_Group != _player->m_playerInfo->m_Group)
		return;

	_player->GetGroup()->MovePlayer(inf, subGroup);
}

void WorldSession::HandleGroupAssistantLeader(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint64 guid;
	uint8 on;

	if(_player->GetGroup() == NULL)
		return;

	if(_player->GetGroup()->GetLeader() != _player->m_playerInfo)      //access denied
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	recv_data >> guid >> on;
	if(on == 0)
		_player->GetGroup()->SetAssistantLeader(NULL);
	else
	{
		PlayerInfo* np = objmgr.GetPlayerInfo((uint32)guid);
		if(np == NULL)
			_player->GetGroup()->SetAssistantLeader(NULL);
		else
		{
			if(_player->GetGroup()->HasMember(np))
				_player->GetGroup()->SetAssistantLeader(np);
		}
	}
}

void WorldSession::HandleGroupPromote(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint8 promotetype, on;
	uint64 guid;

	if(_player->GetGroup() == NULL)
		return;

	if(_player->GetGroup()->GetLeader() != _player->m_playerInfo)      //access denied
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	recv_data >> promotetype >> on;
	recv_data >> guid;

	void(Group::*function_to_call)(PlayerInfo*);
	function_to_call = 0;

	if(promotetype == 0)
		function_to_call = &Group::SetMainTank;
	else if(promotetype == 1)
		function_to_call = &Group::SetMainAssist;

	if(on == 0)
		(_player->GetGroup()->*function_to_call)(NULL);
	else
	{
		PlayerInfo* np = objmgr.GetPlayerInfo((uint32)guid);
		if(np == NULL)
			(_player->GetGroup()->*function_to_call)(NULL);
		else
		{
			if(_player->GetGroup()->HasMember(np))
				(_player->GetGroup()->*function_to_call)(np);
		}
	}
}

void WorldSession::HandleRequestRaidInfoOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	//		  SMSG_RAID_INSTANCE_INFO			 = 716,  //(0x2CC)
	//sInstanceSavingManager.BuildRaidSavedInstancesForPlayer(_player);
	sInstanceMgr.BuildRaidSavedInstancesForPlayer(_player);
}

void WorldSession::HandleReadyCheckOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	Group* pGroup  = _player->GetGroup();

	if(!pGroup)
		return;

	if(recv_data.size() == 0)
	{
		// only leader or leader assistant can perform the ready check
		if(pGroup->GetLeader() == _player->m_playerInfo || pGroup->GetAssistantLeader() == _player->m_playerInfo)
		{
			WorldPacket data(MSG_RAID_READY_CHECK, 8);
			data << GetPlayer()->GetGUID();
			/* send packet to group */
			pGroup->SendPacketToAll(&data);
		}
		else
		{
			SendNotification(NOTIFICATION_MESSAGE_NO_PERMISSION);
		}
	}
	else
	{
		uint8 ready;
		recv_data >> ready;

		WorldPacket data(MSG_RAID_READY_CHECK_CONFIRM, 9);
		data << _player->GetGUID();
		data << ready;

		if(pGroup->GetLeader() && pGroup->GetLeader()->m_loggedInPlayer)
			pGroup->GetLeader()->m_loggedInPlayer->GetSession()->SendPacket(&data);
		if(pGroup->GetAssistantLeader() && pGroup->GetAssistantLeader()->m_loggedInPlayer)
			pGroup->GetAssistantLeader()->m_loggedInPlayer->GetSession()->SendPacket(&data);
	}
}

