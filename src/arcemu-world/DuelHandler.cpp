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

void WorldSession::HandleDuelAccepted(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	if(_player->DuelingWith == NULL)
		return;

	if(_player->m_duelState != DUEL_STATE_FINISHED)
		return;

	if(_player->m_duelCountdownTimer > 0)
		return;

	_player->m_duelStatus = DUEL_STATUS_INBOUNDS;
	_player->DuelingWith->m_duelStatus = DUEL_STATUS_INBOUNDS;

	_player->m_duelState = DUEL_STATE_STARTED;
	_player->DuelingWith->m_duelState = DUEL_STATE_STARTED;

	WorldPacket data(SMSG_DUEL_COUNTDOWN, 4);
	data << uint32(3000);

	SendPacket(&data);
	_player->DuelingWith->m_session->SendPacket(&data);

	_player->m_duelCountdownTimer = 3000;

	sEventMgr.AddEvent(_player, &Player::DuelCountdown, EVENT_PLAYER_DUEL_COUNTDOWN, 1000, 3, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void WorldSession::HandleDuelCancelled(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	if(_player->DuelingWith ==  NULL)
		return;

	if(_player->m_duelState == DUEL_STATE_STARTED)
	{
		_player->DuelingWith->EndDuel(DUEL_WINNER_KNOCKOUT);
		return;
	}

	WorldPacket data(SMSG_DUEL_COMPLETE, 1);
	data << uint8(1);

	SendPacket(&data);
	_player->DuelingWith->m_session->SendPacket(&data);

	GameObject* arbiter = _player->GetMapMgr() ? _player->GetMapMgr()->GetGameObject(GET_LOWGUID_PART(_player->GetDuelArbiter())) : NULL;
	if(arbiter != NULL)
	{
		arbiter->RemoveFromWorld(true);
		delete arbiter;
	}

	_player->DuelingWith->SetDuelArbiter(0);
	_player->DuelingWith->SetDuelTeam(0);
	_player->DuelingWith->m_duelState = DUEL_STATE_FINISHED;
	_player->DuelingWith->m_duelCountdownTimer = 0;
	_player->DuelingWith->DuelingWith = NULL;

	_player->SetDuelArbiter(0);
	_player->SetDuelTeam(0);
	_player->m_duelState = DUEL_STATE_FINISHED;
	_player->m_duelCountdownTimer = 0;
	_player->DuelingWith = NULL;

	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; x++)
	{
		if(_player->m_auras[x])
		{
			_player->m_auras[x]->Remove();
		}
	}
	std::list<Pet*> summons = _player->GetSummons();
	for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
	{
		if((*itr)->isAlive())
		{
			(*itr)->SetPetAction(PET_ACTION_STAY);
			(*itr)->SetPetAction(PET_ACTION_FOLLOW);
		}
	}
}
