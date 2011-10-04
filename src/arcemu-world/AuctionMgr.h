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

#ifndef __AUCTIONMGR_H
#define __AUCTIONMGR_H

class AuctionHouse;
class AuctionMgr : public Singleton <AuctionMgr>
{
	public:
		AuctionMgr()
		{
			loopcount = 0;
			maxId.SetVal(1);
		}

		~AuctionMgr()
		{
			vector<AuctionHouse*>::iterator itr = auctionHouses.begin();
			for(; itr != auctionHouses.end(); ++itr)
				delete(*itr);
		}

		void LoadAuctionHouses();
		void Update();

		AuctionHouse* GetAuctionHouse(uint32 Entry);

		uint32 GenerateAuctionId()
		{
			uint32 id = ++maxId;

			return id;
		}

	private:
		HM_NAMESPACE::hash_map<uint32, AuctionHouse*> auctionHouseEntryMap;
		vector<AuctionHouse*> auctionHouses;

		Arcemu::Threading::AtomicCounter maxId;

		uint32 loopcount;
};

#define sAuctionMgr AuctionMgr::getSingleton()

#endif
