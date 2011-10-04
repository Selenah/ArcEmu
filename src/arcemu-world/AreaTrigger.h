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

#ifndef __AREATRIGGERHANDLER_H
#define __AREATRIGGERHANDLER_H


enum AreaTriggerType
{
    ATTYPE_NULL		 = 0,
    ATTYPE_INSTANCE	 = 1,
    ATTYPE_QUESTTRIGGER = 2,
    ATTYPE_INN		  = 3,
    ATTYPE_TELEPORT	 = 4,
    ATTYPE_SPELL		= 5,
    ATTYPE_BATTLEGROUND = 6,
};

#pragma pack(push,1)
typedef struct AreaTrigger
{
	uint32 AreaTriggerID;
	uint8 Type;
	uint32 Mapid;
	uint32 PendingScreen;
	char* Name;
	float x;
	float y;
	float z;
	float o;
	uint32 required_honor_rank;
	uint32 required_level;
} AreaTrigger;
#pragma pack(pop)



#endif
