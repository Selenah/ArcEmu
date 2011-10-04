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

#ifndef OBJECT_STORAGE_H
#define OBJECT_STORAGE_H

extern SERVER_DECL SQLStorage<ItemPrototype, ArrayStorageContainer<ItemPrototype> >				ItemPrototypeStorage;
extern SERVER_DECL SQLStorage<ItemName, ArrayStorageContainer<ItemName> > ItemNameStorage;
extern SERVER_DECL SQLStorage<CreatureInfo, HashMapStorageContainer<CreatureInfo> >				CreatureNameStorage;
extern SERVER_DECL SQLStorage<GameObjectInfo, HashMapStorageContainer<GameObjectInfo> >			GameObjectNameStorage;
extern SERVER_DECL SQLStorage<CreatureProto, HashMapStorageContainer<CreatureProto> >			CreatureProtoStorage;
extern SERVER_DECL SQLStorage<DisplayBounding, HashMapStorageContainer<DisplayBounding> >		DisplayBoundingStorage;
extern SERVER_DECL SQLStorage<VendorRestrictionEntry, ArrayStorageContainer<VendorRestrictionEntry> > VendorRestrictionEntryStorage;
extern SERVER_DECL SQLStorage<AreaTrigger, HashMapStorageContainer<AreaTrigger> >				AreaTriggerStorage;
extern SERVER_DECL SQLStorage<ItemPage, HashMapStorageContainer<ItemPage> >						ItemPageStorage;
extern SERVER_DECL SQLStorage<Quest, HashMapStorageContainer<Quest> >							QuestStorage;
extern SERVER_DECL SQLStorage<GossipText, HashMapStorageContainer<GossipText> >					NpcTextStorage;
extern SERVER_DECL SQLStorage<GraveyardTeleport, HashMapStorageContainer<GraveyardTeleport> >	GraveyardStorage;
extern SERVER_DECL SQLStorage<TeleportCoords, HashMapStorageContainer<TeleportCoords> >			TeleportCoordStorage;
extern SERVER_DECL SQLStorage<FishingZoneEntry, HashMapStorageContainer<FishingZoneEntry> >		FishingZoneStorage;
extern SERVER_DECL SQLStorage<MapInfo, ArrayStorageContainer<MapInfo> >							WorldMapInfoStorage;
extern SERVER_DECL SQLStorage<ZoneGuardEntry, HashMapStorageContainer<ZoneGuardEntry> >			ZoneGuardStorage;
extern SERVER_DECL SQLStorage<UnitModelSizeEntry, HashMapStorageContainer<UnitModelSizeEntry> >	UnitModelSizeStorage;
extern SERVER_DECL SQLStorage<WorldStringTable, HashMapStorageContainer<WorldStringTable> >	WorldStringTableStorage;
extern SERVER_DECL SQLStorage<WorldBroadCast, HashMapStorageContainer<WorldBroadCast> >	WorldBroadCastStorage;
extern SERVER_DECL SQLStorage<BGMaster, HashMapStorageContainer<BGMaster> >						BGMasterStorage;
extern SERVER_DECL SQLStorage< SpellClickSpell, HashMapStorageContainer< SpellClickSpell > >		SpellClickSpellStorage;
extern SERVER_DECL SQLStorage< TotemDisplayIdEntry, HashMapStorageContainer< TotemDisplayIdEntry > > TotemDisplayIdStorage;

void Storage_FillTaskList(TaskList & tl);
void Storage_Cleanup();
bool Storage_ReloadTable(const char* TableName);
void Storage_LoadAdditionalTables();

extern SERVER_DECL set<string> ExtraMapCreatureTables;
extern SERVER_DECL set<string> ExtraMapGameObjectTables;

#endif


