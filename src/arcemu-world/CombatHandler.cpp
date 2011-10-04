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

void WorldSession::HandleAttackSwingOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	CHECK_PACKET_SIZE(recv_data, 8);
	uint64 guid;
	recv_data >> guid;

	if(!guid)
	{
		// does this mean cancel combat?
		HandleAttackStopOpcode(recv_data);
		return;
	}

	// AttackSwing
	Log.Debug("WORLD", "Recvd CMSG_ATTACKSWING Message");

	if(GetPlayer()->IsPacified() || GetPlayer()->IsStunned() || GetPlayer()->IsFeared())
		return;

//	printf("Got ATTACK SWING: %08X %08X\n", GUID_HIPART(guid), Arcemu::Util::GUID_LOPART( guid ));
	Unit* pEnemy = _player->GetMapMgr()->GetUnit(guid);
	//printf("Pointer: %08X\n", pEnemy);

	if(!pEnemy)
	{
		LOG_DEBUG("WORLD: "I64FMT" does not exist.", guid);
		return;
	}

	if(pEnemy->IsDead() || _player->IsDead() || !isAttackable(_player, pEnemy, false))		// haxors :(
		return;

	GetPlayer()->smsg_AttackStart(pEnemy);
	GetPlayer()->EventAttackStart();

}

void WorldSession::HandleAttackStopOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint64 guid = GetPlayer()->GetSelection();

	if(guid)
	{
		Unit* pEnemy = _player->GetMapMgr()->GetUnit(guid);
		if(pEnemy != NULL)
		{
			GetPlayer()->EventAttackStop();
			GetPlayer()->smsg_AttackStop(pEnemy);
		}
	}
}

