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

class SERVER_DECL ChannelMgr :  public Singleton < ChannelMgr >
{

	public:
		ChannelMgr();
		~ChannelMgr();

		Channel* GetCreateChannel(const char* name, Player* p, uint32 type_id);
		Channel* GetChannel(const char* name, Player* p);
		Channel* GetChannel(const char* name, uint32 team);
		void RemoveChannel(Channel* chn);
		bool seperatechannels;

	private:
		//team 0: alliance, team 1 horde
		typedef map<string, Channel*> ChannelList;
		ChannelList Channels[2];
		Mutex lock;
};

#define channelmgr ChannelMgr::getSingleton()
