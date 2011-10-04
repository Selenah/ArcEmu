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

#ifndef _LOOTMGR_H
#define _LOOTMGR_H


enum LOOTTYPE
{
    LOOT_NORMAL10,		// normal dungeon / old raid  (10/25/40 men) / normal 10 raid
    LOOT_NORMAL25,		// heroic dungeon / normal 25 raid
    LOOT_HEROIC10,		// heroic 10 men raid
    LOOT_HEROIC25,		// heroic 25 men raid
    NUM_LOOT_TYPES
};

struct ItemPrototype;
class MapMgr;
class LootRoll : public EventableObject
{
	public:
		LootRoll(uint32 timer, uint32 groupcount, uint64 guid, uint32 slotid, uint32 itemid, uint32 itemunk1, uint32 itemunk2, MapMgr* mgr);
		~LootRoll();
		void PlayerRolled(Player* player, uint8 choice);
		void Finalize();

		int32 event_GetInstanceID();

	private:
		std::map<uint32, uint32> m_NeedRolls;
		std::map<uint32, uint32> m_GreedRolls;
		set<uint32> m_passRolls;
		uint32 _groupcount;
		uint32 _slotid;
		uint32 _itemid;
		uint32 _randomsuffixid;
		uint32 _randompropertyid;
		uint32 _remaining;
		uint64 _guid;
		MapMgr* _mgr;
};

typedef vector<pair<RandomProps*, float> > RandomPropertyVector;
typedef vector<pair<ItemRandomSuffixEntry*, float> > RandomSuffixVector;

typedef struct
{
	ItemPrototype* itemproto;
	uint32 displayid;
} _LootItem;

typedef std::set<uint32> LooterSet;

typedef struct
{
	_LootItem item;
	uint32 iItemsCount;
	RandomProps* iRandomProperty;
	ItemRandomSuffixEntry* iRandomSuffix;
	LootRoll* roll;
	bool passed;
	LooterSet has_looted;
	uint32 ffa_loot;
} __LootItem;


typedef struct
{
	_LootItem item;		// the item that drops
	float chance;		// normal dungeon / normal 10men raid / old raid (10,25, or 40 men )
	float chance2;		// heroic dungeon / normal 25men raid
	float chance3;		// heroic 10men raid
	float chance4;		// heroic 25men raid
	uint32 mincount;	// minimum quantity to drop
	uint32 maxcount;	// maximum quantity to drop
	uint32 ffa_loot;	// can everyone from the group loot the item?
} StoreLootItem;


typedef struct
{
	uint32 count;
	StoreLootItem* items;
} StoreLootList;

typedef struct
{
	std::vector<__LootItem> items;
	uint32 gold;
	LooterSet looters;
} Loot;

struct tempy
{
	uint32 itemid;
	float chance;
	float chance_2;
	float chance3;
	float chance4;
	uint32 mincount;
	uint32 maxcount;
	uint32 ffa_loot;
};


//////////////////////////////////////////////////////////////////////////////////////////


typedef HM_NAMESPACE::hash_map<uint32, StoreLootList > LootStore;

#define PARTY_LOOT_FFA	  0
#define PARTY_LOOT_MASTER   2
#define PARTY_LOOT_RR	   1
#define PARTY_LOOT_NBG	  4
#define PARTY_LOOT_GROUP	3



class SERVER_DECL LootMgr : public Singleton < LootMgr >
{
	public:
		LootMgr();
		~LootMgr();

		void AddLoot(Loot* loot, uint32 itemid, uint32 mincount, uint32 maxcount, uint32 ffa_loot);

		void FillCreatureLoot(Loot* loot, uint32 loot_id, uint32 type);
		void FillGOLoot(Loot* loot, uint32 loot_id, uint32 type);
		void FillItemLoot(Loot* loot, uint32 loot_id);
		void FillFishingLoot(Loot* loot, uint32 loot_id);
		void FillSkinningLoot(Loot* loot, uint32 loot_id);
		void FillPickpocketingLoot(Loot* loot, uint32 loot_id);

		bool CanGODrop(uint32 LootId, uint32 itemid);
		bool IsPickpocketable(uint32 creatureId);
		bool IsSkinnable(uint32 creatureId);
		bool IsFishable(uint32 zoneid);

		void LoadLoot();
		void LoadLootProp();

		LootStore	CreatureLoot;
		LootStore	FishingLoot;
		LootStore	SkinningLoot;
		LootStore	GOLoot;
		LootStore	ItemLoot;
		LootStore	PickpocketingLoot;
		std::map<uint32, std::set<uint32> > quest_loot_go;

		RandomProps* GetRandomProperties(ItemPrototype* proto);
		ItemRandomSuffixEntry* GetRandomSuffix(ItemPrototype* proto);

		bool is_loading;

	private:
		void LoadLootTables(const char* szTableName, LootStore* LootTable);
		void PushLoot(StoreLootList* list, Loot* loot, uint32 type);

		map<uint32, RandomPropertyVector> _randomprops;
		map<uint32, RandomSuffixVector> _randomsuffix;
};

#define lootmgr LootMgr::getSingleton()

#endif
