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

void WorldSession::HandleFriendListOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint32 flag;
	recv_data >> flag;
	_player->Social_SendFriendList(flag);
}

void WorldSession::HandleAddFriendOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	LOG_DEBUG("WORLD: Received CMSG_ADD_FRIEND");

	string name, note;
	recv_data >> name;
	recv_data >> note;

	_player->Social_AddFriend(name.c_str(), note.size() ? note.c_str() : NULL);
}

void WorldSession::HandleDelFriendOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	LOG_DEBUG("WORLD: Received CMSG_DEL_FRIEND");

	uint64 FriendGuid;
	recv_data >> FriendGuid;

	_player->Social_RemoveFriend((uint32)FriendGuid);
}

void WorldSession::HandleAddIgnoreOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	LOG_DEBUG("WORLD: Received CMSG_ADD_IGNORE");

	std::string ignoreName = "UNKNOWN";
	recv_data >> ignoreName;

	_player->Social_AddIgnore(ignoreName.c_str());
}

void WorldSession::HandleDelIgnoreOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	LOG_DEBUG("WORLD: Received CMSG_DEL_IGNORE");

	uint64 IgnoreGuid;
	recv_data >> IgnoreGuid;

	_player->Social_RemoveIgnore((uint32)IgnoreGuid);
}

void WorldSession::HandleSetFriendNote(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	uint64 guid;
	string note;

	recv_data >> guid >> note;
	_player->Social_SetNote((uint32)guid, note.size() ? note.c_str() : NULL);
}
