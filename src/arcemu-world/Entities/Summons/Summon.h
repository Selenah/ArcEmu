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

#ifndef SUMMON_HPP_
#define SUMMON_HPP_

enum SummonType
{
    SUMMONTYPE_GUARDIAN       =  0,
    SUMMONTYPE_WILD           =  1,
    SUMMONTYPE_TOTEM          =  2,
    SUMMONTYPE_COMPANION      =  3,
    SUMMONTYPE_POSSESSED      =  4
};


/////////////////////////////////////////////////////////////////////////
//class Summon
//  Base class for Summoned creatures
//
/////////////////////////////////////////////////////////////////////////
class Summon : public Creature
{
	public:
		Summon(uint64 GUID);


		~Summon();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//virtual void Load( CreatureProto *proto, Unit *owner, LocationVector &position, uint32 spellid, int32 summonslot );
		//  Loads and sets up the basic properties of the summoned creature, like displayid, health, powers ( mana and co. )
		//
		//Parameter(s)
		//  CreatureProto *proto      -   Reference to the CreatureProto structure that belongs to this creature ( basically a template )
		//  Unit *owner               -   Owner unit of this Creature, usually the unit that summoned it, or the unit that summoned the summoner
		//  LocationVector &position  -   Position of the summoned creature in the game world
		//  uint32 spellid            -   The spell that summoned this creature
		//  int32 summonslot          -   The summon slot of the creature, -1 means no slot
		//
		//Return Value
		//  None
		//
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot);


		void OnPushToWorld();


		void OnPreRemoveFromWorld();


		bool SummonedToSlot()
		{
			if(summonslot != -1)
				return true;
			else
				return false;
		}


		bool IsSummon() { return true; }


		/////////////////////////////////////////////////////////
		//Unit* GetOwner()
		//  Returns the owner unit of this creature
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  Returns a pointer to the owner unit of this creature
		//
		//
		//
		/////////////////////////////////////////////////////////
		Unit* GetOwner() { return owner; }


		Object* GetPlayerOwner();


		void Die(Unit* pAttacker, uint32 damage, uint32 spellid);


		void OnRemoveInRangeObject(Object* object);


	private:
		int32 summonslot;  // Summon slot of the creature in the owner's summonhandler, -1 means no slot
		Unit* owner;       // Summoner of the creature
};

#endif
