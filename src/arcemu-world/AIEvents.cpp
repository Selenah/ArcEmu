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
