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

#ifndef AUCTIONHOUSE_H
#define AUCTIONHOUSE_H

enum AuctionRemoveType
{
    AUCTION_REMOVE_EXPIRED,
    AUCTION_REMOVE_WON,
    AUCTION_REMOVE_CANCELLED,
};
enum AUCTIONRESULT
{
    AUCTION_CREATE,
    AUCTION_CANCEL,
    AUCTION_BID,
    AUCTION_BUYOUT,
};
enum AUCTIONRESULTERROR
{
    AUCTION_ERROR_NONE = 0,
    AUCTION_ERROR_INTERNAL = 2,
    AUCTION_ERROR_MONEY = 3,
    AUCTION_ERROR_ITEM = 4,
    AUCTION_ERROR_BID_OWN_AUCTION = 10
};
enum AuctionMailResult
{
    AUCTION_OUTBID,
    AUCTION_WON,
    AUCTION_SOLD,
    AUCTION_EXPIRED,
    AUCTION_EXPIRED2,
    AUCTION_CANCELLED,
};

struct Auction
{
	uint32 Id;

	uint32 Owner;
	uint32 HighestBidder;
	uint32 HighestBid;
	uint32 StartingPrice;
	uint32 BuyoutPrice;
	uint32 DepositAmount;

	uint32 ExpiryTime;
	Item* pItem;

	void DeleteFromDB();
	void SaveToDB(uint32 AuctionHouseId);
	void UpdateInDB();
	void AddToPacket(WorldPacket & data);
	bool Deleted;
	uint32 DeletedReason;
};

class AuctionHouse
{
	public:
		AuctionHouse(uint32 ID);
		~AuctionHouse();

		ARCEMU_INLINE uint32 GetID() { return dbc->id; }
		void LoadAuctions();

		void UpdateAuctions();
		void UpdateDeletionQueue();

		void RemoveAuction(Auction* auct);
		void AddAuction(Auction* auct);
		Auction* GetAuction(uint32 Id);
		void QueueDeletion(Auction* auct, uint32 Reason);

		void SendOwnerListPacket(Player* plr, WorldPacket* packet);
		void UpdateOwner(uint32 oldGuid, uint32 newGuid);
		void SendBidListPacket(Player* plr, WorldPacket* packet);
		void SendAuctionBuyOutNotificationPacket(Auction* auct);
		void SendAuctionOutBidNotificationPacket(Auction* auct, uint64 newBidder, uint32 newHighestBid);
		void SendAuctionExpiredNotificationPacket(Auction* auct);
		void SendAuctionList(Player* plr, WorldPacket* packet);

	private:
		RWLock auctionLock;
		HM_NAMESPACE::hash_map<uint32, Auction*> auctions;

		Mutex removalLock;
		list<Auction*> removalList;

		AuctionHouseDBC* dbc;

	public:
		float cut_percent;
		float deposit_percent;

		bool enabled;
};
#endif

