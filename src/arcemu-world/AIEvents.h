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

#ifndef __AIEVENTS_H
#define __AIEVENTS_H

class AIInterface;
typedef void(AIInterface::*pAIEvent)(Unit* punit, uint32 misc1);

enum AiEvents
{
    EVENT_ENTERCOMBAT,
    EVENT_LEAVECOMBAT,
    EVENT_DAMAGETAKEN,
    EVENT_FEAR,
    EVENT_UNFEAR,
    EVENT_FOLLOWOWNER,
    EVENT_WANDER,
    EVENT_UNWANDER,
    EVENT_UNITDIED,
    EVENT_HOSTILEACTION,
    EVENT_FORCEREDIRECTED,
    NUM_AI_EVENTS,
};

extern pAIEvent AIEventHandlers[NUM_AI_EVENTS];



#endif
