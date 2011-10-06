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

#ifndef TOTEMSUMMON_HPP_
#define TOTEMSUMMON_HPP_

///////////////////////////////////////////////////////////
//class TotemSummon
//  Class that implements Totems
//  Totems are stationary, and don't attack with melee,
//  however they can cast spells
//
//
///////////////////////////////////////////////////////////
class TotemSummon : public Summon
{
	public:
		TotemSummon(uint64 GUID);


		~TotemSummon();


		void Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot);


		void OnPushToWorld();


		void OnPreRemoveFromWorld();


		bool IsTotem() { return true; }


		Group* GetGroup();


		//////////////////////////////////////////////////////
		//void SetupSpells()
		//  Sets up the spells the totem will cast
		//  This code was almost directly copied from SpellEffects.cpp,
		//  it requires further refactoring!
		//  For example totems should cast like other units..
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		//////////////////////////////////////////////////////
		void SetupSpells();


		void Die(Unit* pAttacker, uint32 damage, uint32 spellid);


	private:
};

#endif
