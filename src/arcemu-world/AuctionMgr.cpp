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

initialiseSingleton(AuctionMgr);

void AuctionMgr::LoadAuctionHouses()
{
	Log.Notice("AuctionMgr", "Loading Auction Houses...");

	QueryResult* res = CharacterDatabase.Query("SELECT MAX(auctionId) FROM auctions");
	if(res)
	{
		maxId.SetVal(res->Fetch()[0].GetUInt32());
		delete res;
	}

	res = WorldDatabase.Query("SELECT DISTINCT ahgroup FROM auctionhouse");
	AuctionHouse* ah;
	map<uint32, AuctionHouse*> tempmap;
	if(res)
	{
		uint32 period = (res->GetRowCount() / 20) + 1;
		uint32 c = 0;
		do
		{
			ah = new AuctionHouse(res->Fetch()[0].GetUInt32());
			ah->LoadAuctions();
			auctionHouses.push_back(ah);
			tempmap.insert(make_pair(res->Fetch()[0].GetUInt32(), ah));
			if(!((++c) % period))
				Log.Notice("AuctionHouse", "Done %u/%u, %u%% complete.", c, res->GetRowCount(), c * 100 / res->GetRowCount());

		}
		while(res->NextRow());
		delete res;
	}

	res = WorldDatabase.Query("SELECT creature_entry, ahgroup FROM auctionhouse");
	if(res)
	{
		do
		{
			auctionHouseEntryMap.insert(make_pair(res->Fetch()[0].GetUInt32(), tempmap[res->Fetch()[1].GetUInt32()]));
		}
		while(res->NextRow());
		delete res;
	}
}

AuctionHouse* AuctionMgr::GetAuctionHouse(uint32 Entry)
{
	HM_NAMESPACE::hash_map<uint32, AuctionHouse*>::iterator itr = auctionHouseEntryMap.find(Entry);
	if(itr == auctionHouseEntryMap.end()) return NULL;
	return itr->second;
}

void AuctionMgr::Update()
{
	if((++loopcount % 100))
		return;

	vector<AuctionHouse*>::iterator itr = auctionHouses.begin();
	for(; itr != auctionHouses.end(); ++itr)
	{
		(*itr)->UpdateDeletionQueue();

		// Actual auction loop is on a separate timer.
		if(!(loopcount % 1200))
			(*itr)->UpdateAuctions();
	}
}
