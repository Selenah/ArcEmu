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

bool ChatHandler::HandleInitializeAllQueuedBattlegroundsCommand(const char* args, WorldSession* m_session)
{
	SystemMessage(m_session, "Forcing initialization of all battlegrounds...");
	BattlegroundManager.EventQueueUpdate(true);
	SystemMessage(m_session, "...done");
	return true;
}

bool ChatHandler::HandleGetBattlegroundQueueCommand(const char* args, WorldSession* m_session)
{
	SystemMessage(m_session, "Getting battleground queues...");
	BattlegroundManager.HandleGetBattlegroundQueueCommand(m_session);
	SystemMessage(m_session, "...done");
	return true;
}

bool ChatHandler::HandleSetBGScoreCommand(const char* args, WorldSession* m_session)
{
	return true;
}

bool ChatHandler::HandleStartBGCommand(const char* args, WorldSession* m_session)
{
	if(!m_session->GetPlayer()->m_bg)
	{
		SystemMessage(m_session, "You're not in a battleground!");
		return true;
	}
	m_session->GetPlayer()->m_bg->SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, m_session->LocalizedWorldSrv(49), m_session->LocalizedWorldSrv(m_session->GetPlayer()->m_bg->GetNameID()));
	sEventMgr.RemoveEvents(m_session->GetPlayer()->m_bg, EVENT_BATTLEGROUND_COUNTDOWN);
	m_session->GetPlayer()->m_bg->Start();
	return true;
}

bool ChatHandler::HandlePauseBGCommand(const char* args, WorldSession* m_session)
{
	return true;
}

bool ChatHandler::HandleBGInfoCommnad(const char* args, WorldSession* m_session)
{
	return true;
}

bool ChatHandler::HandleBattlegroundCommand(const char* args, WorldSession* m_session)
{
	uint32 type = atoi(args);
	if(type >= BATTLEGROUND_NUM_TYPES)
		return false;

	Player* plr = getSelectedChar(m_session, true);
	if(plr == NULL)
		return true;
	BattlegroundManager.HandleBattlegroundListPacket(plr->GetSession(), type);
	return true;
}

bool ChatHandler::HandleSetWorldStateCommand(const char* args, WorldSession* m_session)
{
	uint32 id, val;
	if(sscanf(args, "%u %u", &id, &val) != 2)
		return false;

	if(m_session->GetPlayer()->m_bg)
		m_session->GetPlayer()->m_bg->SetWorldState(id, val);

	return true;
}

bool ChatHandler::HandleSetWorldStatesCommand(const char* args, WorldSession* m_session)
{
	uint32 first, last, val;
	if(sscanf(args, "%u %u %u", &first, &last, &val) != 3)
		return false;

	if(m_session->GetPlayer()->m_bg)
	{
		for(uint32 i = first; i < last; i++)
		{
			m_session->GetPlayer()->m_bg->SetWorldState(i, val);
		}
	}

	return true;
}

bool ChatHandler::HandlePlaySoundCommand(const char* args, WorldSession* m_session)
{
	if(!m_session->GetPlayer()->m_bg)
	{
		SystemMessage(m_session, "You're not in a battleground!");
		return true;
	}
	m_session->GetPlayer()->m_bg->PlaySoundToAll(atoi(args));
	return true;
}

bool ChatHandler::HandleSetBattlefieldStatusCommand(const char* args, WorldSession* m_session)
{
	uint32 type = atoi(args);
	BattlegroundManager.SendBattlefieldStatus(m_session->GetPlayer(), BGSTATUS_INQUEUE, type, 0 , 0, m_session->GetPlayer()->GetMapId(), 0);
	return true;
}

bool ChatHandler::HandleBattlegroundExitCommand(const char* args, WorldSession* m_session)
{
	if(!m_session->GetPlayer()->m_bg)
	{
		SystemMessage(m_session, "You're not in a battleground!");
		return true;
	}
	m_session->GetPlayer()->m_bg->Close();
	return true;
}
