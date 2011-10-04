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

#ifndef WOWSERVER_DEFINITION_H
#define WOWSERVER_DEFINITION_H


const unsigned NUM_MAPS = 800;
const unsigned NUM_INSTANCE_MODES = 4;


// Sorry...need this enumeration in Player.*
enum INSTANCE_MODE
{
    MODE_NORMAL = 0,
    MODE_HEROIC = 1
};

enum RAID_MODE
{
    MODE_NORMAL_10MEN	=	0,
    MODE_NORMAL_25MEN	=	1,
    MODE_HEROIC_10MEN	=	2,
    MODE_HEROIC_25MEN	=	3,
    TOTAL_RAID_MODES    =   4
};


#endif
