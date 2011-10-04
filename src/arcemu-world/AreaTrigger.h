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
