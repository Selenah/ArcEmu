/*
 * Servidor ArcEmu MMORPG
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

#include "StdAfx.h"

namespace Arcemu
{

	EquipmentSetMgr::~EquipmentSetMgr()
	{
		for(EquipmentSetStorage::iterator itr = EquipmentSets.begin(); itr != EquipmentSets.end(); ++itr)
			delete itr->second;

		EquipmentSets.clear();
	}

	EquipmentSet* EquipmentSetMgr::GetEquipmentSet(uint32 id)
	{
		EquipmentSetStorage::iterator itr;

		itr = EquipmentSets.find(id);

		if(itr != EquipmentSets.end())
			return itr->second;
		else
			return NULL;
	}



	bool EquipmentSetMgr::AddEquipmentSet(uint32 setGUID, EquipmentSet* set)
	{
		std::pair< EquipmentSetStorage::iterator, bool > retval;

		retval = EquipmentSets.insert(std::pair< uint32, EquipmentSet* >(setGUID, set));

		return retval.second;
	}


	bool EquipmentSetMgr::DeleteEquipmentSet(uint32 setGUID)
	{
		EquipmentSetStorage::iterator itr;

		itr = EquipmentSets.find(setGUID);

		if(itr != EquipmentSets.end())
		{
			EquipmentSet* set = itr->second;

			EquipmentSets.erase(itr);
			delete set;
			set = NULL;

			return true;
		}
		else
			return false;
	}


	bool EquipmentSetMgr::LoadfromDB(QueryResult* result)
	{
		if(result == NULL)
			return false;

		uint32 setcount = 0;
		EquipmentSet* set = NULL;
		Field* fields = NULL;

		do
		{

			if(setcount >= 10)
			{
				LOG_ERROR("There were more than 10 equipment sets for GUID: %u", ownerGUID);
				return true;
			}

			fields = result->Fetch();

			set = new EquipmentSet();
			if(set == NULL)
				return false;

			set->SetGUID = fields[ 1 ].GetUInt32();
			set->SetID = fields[ 2 ].GetUInt32();
			set->SetName = fields[ 3 ].GetString();
			set->IconName = fields[ 4 ].GetString();

			for(uint32 i = 0; i < set->ItemGUID.size(); ++i)
				set->ItemGUID[ i ] = fields[ 5 + i ].GetUInt32();

			EquipmentSets.insert(std::pair< uint32, EquipmentSet* >(set->SetGUID, set));
			set = NULL;
			setcount++;

		}
		while(result->NextRow());


		return true;
	}


	bool EquipmentSetMgr::SavetoDB(QueryBuffer* buf)
	{
		if(buf == NULL)
			return false;

		std::stringstream ds;
		ds << "DELETE FROM equipmentsets WHERE ownerguid = ";
		ds << ownerGUID;

		buf->AddQueryNA(ds.str().c_str());

		for(EquipmentSetStorage::iterator itr = EquipmentSets.begin(); itr != EquipmentSets.end(); ++itr)
		{

			EquipmentSet* set = itr->second;

			std::stringstream ss;

			ss << "INSERT INTO equipmentsets VALUES('";
			ss << ownerGUID << "','";
			ss << set->SetGUID << "','";
			ss << set->SetID << "','";
			ss << CharacterDatabase.EscapeString(set->SetName) << "','";
			ss << set->IconName << "'";

			for(uint32 j = 0; j < set->ItemGUID.size(); ++j)
			{
				ss << ",'";
				ss << set->ItemGUID[ j ];
				ss << "'";
			}

			ss << ")";

			buf->AddQueryNA(ss.str().c_str());
		}

		return true;
	}

	void EquipmentSetMgr::FillEquipmentSetListPacket(WorldPacket & data)
	{

		data << uint32(EquipmentSets.size());

		for(EquipmentSetStorage::iterator itr = EquipmentSets.begin(); itr != EquipmentSets.end(); ++itr)
		{
			EquipmentSet* set = itr->second;

			data << WoWGuid(uint64(set->SetGUID));
			data << uint32(set->SetID);
			data << std::string(set->SetName);
			data << std::string(set->IconName);

			for(uint32 i = 0; i < set->ItemGUID.size(); ++i)
			{
				data << WoWGuid(uint64(Arcemu::Util::MAKE_ITEM_GUID(set->ItemGUID[ i ])));
			}
		}
	}
}