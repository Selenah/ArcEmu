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

#ifndef __ADDONMGR_H
#define __ADDONMGR_H

struct AddonEntry
{
	std::string name;
	uint64 crc;
	bool banned;
	bool isNew;
	bool showinlist;
};

typedef std::map<std::string, AddonEntry*> KnownAddons;
typedef KnownAddons::iterator KnownAddonsItr;

typedef std::map<std::string, ByteBuffer> AddonData;
typedef AddonData::iterator AddonDataItr;

class AddonMgr : public Singleton < AddonMgr >
{
	public:
		AddonMgr();
		~AddonMgr();

		void					LoadFromDB();
		void					SaveToDB();

		void					SendAddonInfoPacket(WorldPacket* source, uint32 pos, WorldSession* m_session);
		bool					AppendPublicKey(WorldPacket & data, std::string & AddonName, uint32 CRC);

	private:
		bool					IsAddonBanned(uint64 crc, std::string name = "");
		bool					IsAddonBanned(std::string name, uint64 crc = 0);
		bool					ShouldShowInList(std::string name);

		KnownAddons				mKnownAddons;
		AddonData				mAddonData;
};

#define sAddonMgr AddonMgr::getSingleton()

#endif
