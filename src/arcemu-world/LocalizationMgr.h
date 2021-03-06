/*
 * Servidor ArcEmu MMORPG
 * String Localization Manager
 * Copyright (C) 2007 Burlex <burlex@gmail.com>
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

#ifndef __LOCALIZATIONMGR_H
#define __LOCALIZATIONMGR_H

struct LocalizedCreatureName
{
	char* Name;
	char* SubName;
};

struct LocalizedGameObjectName
{
	char* Name;
};

struct LocalizedNpcText
{
	char* Texts[8][2];
};

struct LocalizedItemPage
{
	char* Text;
};

struct LocalizedItem
{
	char* Name;
	char* Description;
};

struct LocalizedQuest
{
	char* Title;
	char* Details;
	char* Objectives;
	char* CompletionText;
	char* IncompleteText;
	char* EndText;
	char* ObjectiveText[4];
};

struct LocalizedWorldBroadCast
{
	char* Text;
};

struct LocalizedWorldStringTable
{
	char* Text;
};

struct LocalizedWorldMapInfo
{
	char* Text;
};

class LocalizationMgr
{
	public:
		void Shutdown();

		void Reload(bool first);
		void Lower(string & conv);
		uint32 GetLanguageId(uint32 full);
		uint32 GetLanguageId(string langstr)
		{
			string ns = langstr;
			Lower(ns);

			uint32 lid = *(uint32*)ns.c_str();
			return GetLanguageId(lid);
		}

		void GetDistinctLanguages(set<string>& dest, const char* table);

		LocalizedQuest* 			GetLocalizedQuest(uint32 id, uint32 language);
		LocalizedItem* 				GetLocalizedItem(uint32 id, uint32 language);
		LocalizedNpcText* 			GetLocalizedNpcText(uint32 id, uint32 language);
		LocalizedCreatureName* 		GetLocalizedCreatureName(uint32 id, uint32 language);
		LocalizedGameObjectName* 	GetLocalizedGameObjectName(uint32 id, uint32 language);
		LocalizedItemPage* 			GetLocalizedItemPage(uint32 id, uint32 language);
		LocalizedWorldStringTable* 	GetLocalizedWorldStringTable(uint32 id, uint32 language);
		LocalizedWorldBroadCast* 	GetLocalizedWorldBroadCast(uint32 id, uint32 language);
		LocalizedWorldMapInfo* 	GetLocalizedWorldMapInfo(uint32 id, uint32 language);

		template<typename T>
		void CopyHashMap(HM_NAMESPACE::hash_map<uint32, T> * src, HM_NAMESPACE::hash_map<uint32, T> * dest)
		{
			for(typename HM_NAMESPACE::hash_map<uint32, T>::iterator itr = src->begin(); itr != src->end(); ++itr)
				dest->insert(make_pair(itr->first, itr->second));
		}

	private:
		HM_NAMESPACE::hash_map<uint32, LocalizedQuest>				* m_Quests;
		HM_NAMESPACE::hash_map<uint32, LocalizedItem>				* m_Items;
		HM_NAMESPACE::hash_map<uint32, LocalizedNpcText>			* m_NpcTexts;
		HM_NAMESPACE::hash_map<uint32, LocalizedCreatureName>		* m_CreatureNames;
		HM_NAMESPACE::hash_map<uint32, LocalizedGameObjectName>		* m_GameObjectNames;
		HM_NAMESPACE::hash_map<uint32, LocalizedItemPage>			* m_ItemPages;
		HM_NAMESPACE::hash_map<uint32, LocalizedWorldStringTable>			* m_WorldStrings;
		HM_NAMESPACE::hash_map<uint32, LocalizedWorldBroadCast>			* m_WorldBroadCast;
		HM_NAMESPACE::hash_map<uint32, LocalizedWorldMapInfo>			* m_WorldMapInfo;

		vector<pair<uint32, uint32> >								  m_languages;
		bool														  m_disabled;
};

extern LocalizationMgr sLocalizationMgr;

#endif
