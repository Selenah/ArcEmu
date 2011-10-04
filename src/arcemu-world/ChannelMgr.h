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
