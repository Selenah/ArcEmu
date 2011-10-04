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

#ifndef _CONTAINER_H
#define _CONTAINER_H

class SERVER_DECL Container : public Item
{
	public:
		friend class WorldSession;
		Container(uint32 high, uint32 low);
		~Container();

		void Create(uint32 itemid, Player* owner);
		void LoadFromDB(Field* fields);

		bool AddItem(int16 slot, Item* item);
		bool AddItemToFreeSlot(Item* pItem, uint32* r_slot);
		Item* GetItem(int16 slot)
		{
			if(slot >= 0 && (uint16)slot < GetProto()->ContainerSlots)
				return m_Slot[slot];
			else
				return 0;
		}

		int8 FindFreeSlot();
		bool HasItems();

		void SwapItems(int8 SrcSlot, int8 DstSlot);
		Item* SafeRemoveAndRetreiveItemFromSlot(int16 slot, bool destroy); //doesn't destroy item from memory
		bool SafeFullRemoveItemFromSlot(int16 slot); //destroys item fully

		void SaveBagToDB(int8 slot, bool first, QueryBuffer* buf);
		void SetNumSlots(uint32 num) { SetUInt32Value(CONTAINER_FIELD_NUM_SLOTS, num); }
		uint32 GetNumSlots() { return GetUInt32Value(CONTAINER_FIELD_NUM_SLOTS); }
		void SetSlot(uint16 slot, uint64 guid) { SetUInt64Value(CONTAINER_FIELD_SLOT_1 + (slot * 2), guid); }
		uint64 GetSlot(uint16 slot) { return GetUInt64Value(CONTAINER_FIELD_SLOT_1 + (slot * 2)); }

	protected:
		Item** m_Slot;
		uint32 __fields[CONTAINER_END];
};

#endif
