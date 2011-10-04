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

#include "StdAfx.h"

extern pAIEvent AIEventHandlers[NUM_AI_EVENTS] =
{
	&AIInterface::EventEnterCombat,
	&AIInterface::EventLeaveCombat,
	&AIInterface::EventDamageTaken,
	&AIInterface::EventFear,
	&AIInterface::EventUnfear,
	&AIInterface::EventFollowOwner,
	&AIInterface::EventWander,
	&AIInterface::EventUnwander,
	&AIInterface::EventUnitDied,
	&AIInterface::EventHostileAction,
	&AIInterface::EventForceRedirected,
};
