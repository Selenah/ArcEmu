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

#ifndef __MAIL_H
#define __MAIL_H

enum MailCMD
{
    MAIL_RES_MAIL_SENT = 0,
    MAIL_RES_MONEY_TAKEN = 1,
    MAIL_RES_ITEM_TAKEN = 2,
    MAIL_RES_RETURNED_TO_SENDER = 3,
    MAIL_RES_DELETED = 4,
    MAIL_RES_MADE_PERMANENT = 5
};

enum MailFlags
{
    MAIL_FLAG_NO_COST_FOR_GM					= 1,
    MAIL_FLAG_CAN_SEND_TO_OPPOSITE_FACTION	  = 2,
    MAIL_FLAG_CAN_SEND_TO_OPPOSITE_FACTION_GM   = 4,
    MAIL_FLAG_DISABLE_POSTAGE_COSTS			 = 8,
    MAIL_FLAG_DISABLE_HOUR_DELAY_FOR_ITEMS	  = 16,
    MAIL_FLAG_NO_EXPIRY						 = 32,
};

enum MailTypes
{
    NORMAL,
    COD,
    AUCTION,
    CREATURE,
    GAMEOBJECT,
    ITEM
};

enum MailError
{
    MAIL_OK = 0,
    MAIL_ERR_BAG_FULL = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND = 4,
    MAIL_ERR_NOT_YOUR_ALLIANCE = 5,
    MAIL_ERR_INTERNAL_ERROR = 6
};

// see Stationery.dbc
enum MailStationery
{
    // item:
    MAIL_STATIONERY_TEST1		= 1,	// 8164
    MAIL_STATIONERY_TEST2		= 41,	// 9311
    MAIL_STATIONERY_GM			= 61,	// 18154
    MAIL_STATIONERY_AUCTION		= 62,	// 21140
    MAIL_STATIONERY_VAL			= 64,	// 22058, Valentines day
    MAIL_STATIONERY_CHR			= 65	// 34171, Winter
};

struct MailMessage
{
	uint32 message_id;
	uint32 message_type;
	uint64 player_guid;
	uint64 sender_guid;
	string subject;
	string body;
	uint32 money;
	vector<uint32> items;
	uint32 cod;
	uint32 stationery;
	uint32 expire_time;
	uint32 delivery_time;
	uint32 copy_made;
	bool read_flag;
	bool deleted_flag;

	bool AddMessageDataToPacket(WorldPacket & data);
};

typedef map<uint32, MailMessage> MessageMap;

class Mailbox
{
	protected:
		uint64 owner;
		MessageMap Messages;

	public:
		Mailbox(uint64 owner_) : owner(owner_) {}

		void AddMessage(MailMessage* Message);
		void DeleteMessage(uint32 MessageId, bool sql);
		MailMessage* GetMessage(uint32 message_id)
		{
			MessageMap::iterator iter = Messages.find(message_id);
			if(iter == Messages.end())
				return NULL;
			return &(iter->second);
		}

		WorldPacket* BuildMailboxListingPacket();
		void CleanupExpiredMessages();
		ARCEMU_INLINE size_t MessageCount() { return Messages.size(); }
		void FillTimePacket(WorldPacket & data);
		ARCEMU_INLINE uint64 GetOwner() { return owner; }
		void Load(QueryResult* result);
};


class SERVER_DECL MailSystem : public Singleton<MailSystem>, public EventableObject
{
	public:

		void StartMailSystem();
		MailError DeliverMessage(uint64 recipent, MailMessage* message);
		void RemoveMessageIfDeleted(uint32 message_id, Player* plr);
		void SaveMessageToSQL(MailMessage* message);
		void SendAutomatedMessage(uint32 type, uint64 sender, uint64 receiver, string subject, string body, uint32 money,
		                          uint32 cod, uint64 item_guid, uint32 stationery);

		ARCEMU_INLINE bool MailOption(uint32 flag)
		{
			return (config_flags & flag) ? true : false;
		}
		uint32 config_flags;

};

#define sMailSystem MailSystem::getSingleton()
#define MAIL_DEFAULT_EXPIRATION_TIME 30

#endif
