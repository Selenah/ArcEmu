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

#ifndef __FACTION_H
#define __FACTION_H

#include "Unit.h"

SERVER_DECL bool isHostile(Object* objA, Object* objB); // B is hostile for A?
SERVER_DECL bool isAttackable(Object* objA, Object* objB, bool CheckStealth = true); // A can attack B?
SERVER_DECL bool isCombatSupport(Object* objA, Object* objB); // B combat supports A?;
SERVER_DECL bool isAlliance(Object* objA); // A is alliance?


//////////////////////////////////////////////////////////////////
//bool isNeutral( Object *a, Object *b )
//  Tells if 2 Objects are neutral to each others based on
//  their faction.
//
//Parameters
//  Object *a  -  Pointer to an Object
//  Object *b  -  Pointer to an Object
//
//Return Value
//  Returns true if they are neutral.
//  Returns false otherwise.
//
/////////////////////////////////////////////////////////////////
SERVER_DECL bool isNeutral(Object* a, Object* b);

ARCEMU_INLINE bool isFriendly(Object* objA, Object* objB)// B is friendly to A if its not hostile
{
	if(!(objA->m_phase & objB->m_phase))	//We have to return prematurely, because isHostile would return false (phase difference!!!), and it would result in a true return value here.
		return false;			//We must do this, as it affects AoE spell targets, thus required for them to function properly (so you won't heal out of phase friends...).
	return !isHostile(objA, objB);
}

ARCEMU_INLINE bool isSameFaction(Object* objA, Object* objB)
{
	if(!objB->m_faction || !objA->m_faction)
		return true; //we return true to not give any agro to this object since it might cause other problems later
	return (objB->m_faction->Faction == objA->m_faction->Faction);
}

#endif
