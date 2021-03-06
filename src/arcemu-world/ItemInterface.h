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

#ifndef _ITEMINTERFACE_H
#define _ITEMINTERFACE_H

//In 1.8 client marked wrong slot like this
// #define INVALID_BACKPACK_SLOT ((int8)(0xFF))
const uint8 INVALID_BACKPACK_SLOT = 0xFF;

struct SlotResult
{
	SlotResult() { ContainerSlot = -1, Slot = -1, Result = false; }
	int8 ContainerSlot;
	int8 Slot;
	bool Result;
};

class Item;
class Container;
class Player;
class UpdateData;
class ByteBuffer;
class EquipmentSetMgr;

// sanity checking
enum AddItemResult
{
    ADD_ITEM_RESULT_ERROR			= 0,
    ADD_ITEM_RESULT_OK				= 1,
    ADD_ITEM_RESULT_DUPLICATED		= 2,
};

/////////////////////////////////////////////////////////////////
//
//RefundableMap
//
//Contains refundable item data.
//
//Key:
// uint64 GUID       - GUID of the item
//
//Value:
// time_t buytime    - time of purchase in Unixtime
// uint32 costid     - extendedcostID of the cost
/////////////////////////////////////////////////////////////////
typedef std::map< uint64, pair< time_t, uint32 > > RefundableMap;

class SERVER_DECL ItemInterface
{
	private:
		SlotResult result;
		Player* m_pOwner;
		Item* m_pItems[MAX_INVENTORY_SLOT];
		Item* m_pBuyBack[MAX_BUYBACK_SLOT];

		RefundableMap m_refundableitems;

		AddItemResult m_AddItem(Item* item, int8 ContainerSlot, int16 slot);

	public:
		Arcemu::EquipmentSetMgr m_EquipmentSets;
		friend class ItemIterator;
		ItemInterface(Player* pPlayer);
		~ItemInterface();

		Player* GetOwner() { return m_pOwner; }
		bool IsBagSlot(int16 slot);

		uint32 m_CreateForPlayer(ByteBuffer* data);
		void m_DestroyForPlayer();

		void mLoadItemsFromDatabase(QueryResult* result);
		void mSaveItemsToDatabase(bool first, QueryBuffer* buf);

		Item* GetInventoryItem(int16 slot);
		Item* GetInventoryItem(int8 ContainerSlot, int16 slot);
		int16 GetInventorySlotById(uint32 ID);
		int16 GetInventorySlotByGuid(uint64 guid);
		int16 GetBagSlotByGuid(uint64 guid);

		Item* SafeAddItem(uint32 ItemId, int8 ContainerSlot, int16 slot);
		AddItemResult SafeAddItem(Item* pItem, int8 ContainerSlot, int16 slot);
		Item* SafeRemoveAndRetreiveItemFromSlot(int8 ContainerSlot, int16 slot, bool destroy); //doesn't destroy item from memory
		Item* SafeRemoveAndRetreiveItemByGuid(uint64 guid, bool destroy);
		bool SafeFullRemoveItemFromSlot(int8 ContainerSlot, int16 slot); //destroys item fully
		bool SafeFullRemoveItemByGuid(uint64 guid); //destroys item fully
		AddItemResult AddItemToFreeSlot(Item* item);
		AddItemResult AddItemToFreeBankSlot(Item* item);

		Item* FindItemLessMax(uint32 itemid, uint32 cnt, bool IncBank);
		uint32 GetItemCount(uint32 itemid, bool IncBank = false);
		uint32 RemoveItemAmt(uint32 id, uint32 amt);
		uint32 RemoveItemAmt_ProtectPointer(uint32 id, uint32 amt, Item** pointer);
		uint32 RemoveItemAmtByGuid(uint64 guid, uint32 amt);
		void RemoveAllConjured();
		void BuyItem(ItemPrototype* item, uint32 total_amount, Creature* pVendor);

		uint32 CalculateFreeSlots(ItemPrototype* proto);
		void ReduceItemDurability();

		uint8 LastSearchItemBagSlot() {return result.ContainerSlot;}
		uint8 LastSearchItemSlot() {return result.Slot;}
		SlotResult* LastSearchResult() {return &result;}

		//Searching functions
		SlotResult FindFreeInventorySlot(ItemPrototype* proto);
		SlotResult FindFreeBankSlot(ItemPrototype* proto);
		SlotResult FindAmmoBag();
		int8 FindFreeBackPackSlot();
		uint8 FindFreeBackPackSlotMax();
		int8 FindFreeKeyringSlot();
		int16 FindFreeCurrencySlot();
		int8 FindSpecialBag(Item* item);


		int8 CanEquipItemInSlot(int8 DstInvSlot, int8 slot, ItemPrototype* item, bool ignore_combat = false, bool skip_2h_check = false);
		int8 CanEquipItemInSlot2(int8 DstInvSlot, int8 slot, Item* item, bool ignore_combat = false, bool skip_2h_check = false);
		int8 CanReceiveItem(ItemPrototype* item, uint32 amount);
		int8 CanAffordItem(ItemPrototype* item, uint32 amount, Creature* pVendor);
		int8 GetItemSlotByType(uint32 type);
		Item* GetItemByGUID(uint64 itemGuid);

		void BuildInventoryChangeError(Item* SrcItem, Item* DstItem, uint8 Error);
		void SwapItemSlots(int8 srcslot, int8 dstslot);

		int8 GetInternalBankSlotFromPlayer(int8 islot); //converts inventory slots into 0-x numbers

		//buyback stuff
		ARCEMU_INLINE Item* GetBuyBack(int32 slot)
		{
			if(slot >= 0 && slot < MAX_BUYBACK_SLOT)
				return m_pBuyBack[slot];
			else
				return NULL;
		}
		void AddBuyBackItem(Item* it, uint32 price);
		void RemoveBuyBackItem(uint32 index);
		void EmptyBuyBack();
		bool IsEquipped(uint32 itemid);

		void CheckAreaItems();

		uint32 GetItemCountByLimitId(uint32 LimitId, bool IncBank);
		uint32 GetEquippedCountByItemLimit(uint32 LimitId);

		void HandleItemDurations();

/////////////////////////////////////////////// Refundable item stuff ////////////////////////////////////
		void AddRefundable(uint64 GUID,  uint32 extendedcost);
		void AddRefundable(uint64 GUID,  uint32 extendedcost, time_t buytime);
		void AddRefundable(Item* item, uint32 extendedcost, time_t buytime);
		void RemoveRefundable(uint64 GUID);
		std::pair< time_t, uint32 > LookupRefundable(uint64 GUID);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:
		ARCEMU_INLINE bool VerifyBagSlots(int8 ContainerSlot, int8 Slot)
		{
			if(ContainerSlot < -1 || Slot < 0)
				return false;

			if(ContainerSlot > 0 && (ContainerSlot < INVENTORY_SLOT_BAG_START || ContainerSlot >= INVENTORY_SLOT_BAG_END))
				return false;

			if(ContainerSlot == -1 && (Slot >= INVENTORY_SLOT_ITEM_END  || Slot <= EQUIPMENT_SLOT_END))
				return false;

			return true;
		}

		////////////////////////////////////////////////////////////////////////////////
		//bool AddItemById( uint32 itemid, uint32 count, int32 randomprop )
		//  Adds item(s) to a Player
		//
		//Parameters
		//  uint32 itemid     -  ID of the item(s) to add
		//  uint32 count      -  Amount of items to add
		//  int32 randomprop  -  Random prop or suffix id for the items to add.
		//                       If positive it's prop, If negative it's suffix,
		//                       If 0 it's autogenerated.
		//
		//Return Value
		//  Returns true on success.
		//  Returns false on failure.
		//
		//
		////////////////////////////////////////////////////////////////////////////////
		bool AddItemById(uint32 itemid, uint32 count, int32 randomprop);

		///////////////////////////////////////////////////////////////////////////////
		//void SwapItems( int8 DstInvSlot, int8 DstSlot, int8 SrcInvSlot, int8 SrcSlot )
		// Exchanges items A and B
		//
		//Parameter(s)
		// int8 DstInvSlot  -  Item A's bag inventory slot (-1 if it's an equipment slot)
		// int8 DstSlot     -  Item A's slotid within that bag
		// int8 SrcInvSlot  -  Item B's bag inventory slot (-1 if it's an equipment slot)
		// int8 SrcSlot     -  Item B's slotid within that bag
		//
		//Return Value(s)
		// Returns true on success.
		// Returns false on failure.
		//
		///////////////////////////////////////////////////////////////////////////////
		bool SwapItems(int8 DstInvSlot, int8 DstSlot, int8 SrcInvSlot, int8 SrcSlot);
};
class ItemIterator
{
		bool m_atEnd;
		bool m_searchInProgress;
		uint32 m_slot;
		uint32 m_containerSlot;
		Container* m_container;
		Item* m_currentItem;
		ItemInterface* m_target;
	public:
		ItemIterator(ItemInterface* target) : m_atEnd(false), m_searchInProgress(false), m_slot(0), m_containerSlot(0), m_container(NULL), m_target(target) {}
		~ItemIterator() { if(m_searchInProgress) { EndSearch(); } }

		void BeginSearch()
		{
			// iteminterface doesn't use mutexes, maybe it should :P
			ARCEMU_ASSERT(!m_searchInProgress);
			m_atEnd = false;
			m_searchInProgress = true;
			m_container = NULL;
			m_currentItem = NULL;
			m_slot = 0;
			Increment();
		}

		void EndSearch()
		{
			// nothing here either
			ARCEMU_ASSERT(m_searchInProgress);
			m_atEnd = true;
			m_searchInProgress = false;
		}

		Item* operator*() const
		{
			return m_currentItem;
		}

		Item* operator->() const
		{
			return m_currentItem;
		}

		void Increment()
		{
			if(!m_searchInProgress)
				BeginSearch();

			// are we currently inside a container?
			if(m_container != NULL)
			{
				// loop the container.
				for(; m_containerSlot < m_container->GetProto()->ContainerSlots; ++m_containerSlot)
				{
					m_currentItem = m_container->GetItem(static_cast<int16>(m_containerSlot));
					if(m_currentItem != NULL)
					{
						// increment the counter so we don't get the same item again
						++m_containerSlot;

						// exit
						return;
					}
				}

				// unset this
				m_container = NULL;
			}

			for(; m_slot < MAX_INVENTORY_SLOT; ++m_slot)
			{
				if(m_target->m_pItems[m_slot])
				{
					if(m_target->m_pItems[m_slot]->IsContainer())
					{
						// we are a container :O lets look inside the box!
						m_container = TO< Container* >(m_target->m_pItems[m_slot]);
						m_containerSlot = 0;

						// clear the pointer up. so we can tell if we found an item or not
						m_currentItem = NULL;

						// increment m_slot so we don't search this container again
						++m_slot;

						// call increment() recursively. this will search the container.
						Increment();

						// jump out so we're not wasting cycles and skipping items
						return;
					}

					// we're not a container, just a regular item
					// set the pointer
					m_currentItem = m_target->m_pItems[m_slot];

					// increment the slot counter so we don't do the same item again
					++m_slot;

					// jump out
					return;
				}
			}

			// if we're here we've searched all items.
			m_atEnd = true;
			m_currentItem = NULL;
		}

		ARCEMU_INLINE Item* Grab() { return m_currentItem; }
		ARCEMU_INLINE bool End() { return m_atEnd; }
};

#endif
