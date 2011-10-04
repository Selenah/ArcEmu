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

#ifndef __WORLDSTATE_H
#define __WORLDSTATE_H

class WorldStateHandler;
typedef std::map<uint32, WorldStateHandler*> WorldStateHandlerMap;
typedef std::map<uint32, uint32> WorldStateMap;

class WorldStateHandler
{
	public:
		WorldStateMap m_states;

		void SetState(uint32 index, uint32 value);

		ARCEMU_INLINE void EraseState(uint32 index) { m_states.erase(index); }
};

#endif
