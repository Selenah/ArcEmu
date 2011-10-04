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

#ifndef SUMMONHANDLER_HPP
#define SUMMONHANDLER_HPP

#define SUMMON_SLOTS 6

class Unit;

///////////////////////////////////////////////
//class SummonHandler
//  Manages the summons for Units.
//
//////////////////////////////////////////////
class SERVER_DECL SummonHandler
{
	public:
		SummonHandler();
		~SummonHandler();

		///////////////////////////////////////////////////////////////////////////
		//void AddSummon( Unit *summon )
		//  Adds a summon that doesn't have a summon slot
		//
		//Parameter(s)
		//  Unit *summon  -  pointer to the summon to add
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void AddSummon(Unit* summon);


		///////////////////////////////////////////////////////////////////////////
		//void AddSummonToSlot( Unit *summon, uint8 slot )
		//  Adds a summon to a summon slot.
		//  If something is already there, it's despawned.
		//
		//Parameter(s)
		//  Unit *summon  -  pointer to the summon to add
		//  uint8 slot    -  slot number where we want to
		//                   add the summon to
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void AddSummonToSlot(Unit* summon, uint8 slot);


		///////////////////////////////////////////////////////////////////////////
		//void RemoveSummon( Unit *summon )
		//  Removes a summon that was not summoned to a slot
		//
		//Parameter(s)
		//  Unit *summon  -  summon to remove
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemoveSummon(Unit* summon);


		///////////////////////////////////////////////////////////////////////////
		//void RemoveSummonFromSlot( uint8 slot, bool del = true )
		//  Removes a summon that was summoned to a slot
		//
		//Parameter(s)
		//  uint8 slot  -  the slot to remove a summon from
		//  bool del    -  decides if the summon should also be deleted
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemoveSummonFromSlot(uint8 slot, bool del = true);


		///////////////////////////////////////////////////////////////////////////
		//void ExpireSummonsInSlot()
		//  Expires all summons that were summoned to a slot
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void ExpireSummonsInSlot();


		///////////////////////////////////////////////////////////////////////////
		//void RemoveAllSummons()
		//  Removes and despawns all summons both from slots or otherwise
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemoveAllSummons();


		///////////////////////////////////////////////////////////////////////////
		//void GetSummonSlotSpellIDs( std::vector< uint32 > &spellids )
		//  Retrieves the spellids the summons in slots were created by
		//
		//Parameter(s)
		//  std::vector< uint32 > &spellids - reference to a vector where the
		//                                    spellids will be put
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void GetSummonSlotSpellIDs(std::vector< uint32 > &spellids);


		///////////////////////////////////////////////////////////////////////////
		//bool HasSummonInSlot( uint8 slot )
		//  Tells if there is a summon in the specified slot
		//
		//Parameter(s)
		//  uint8 slot  -  the slot we are querying
		//
		//Return Value
		//  Returns true if there is a summon in that slot
		//  Return false otherwise
		//
		//
		///////////////////////////////////////////////////////////////////////////
		bool HasSummonInSlot(uint8 slot);



		///////////////////////////////////////////////////////////////////////////
		//void SetPvPFlags()
		//  Flags all summons for PvP
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void SetPvPFlags();


		///////////////////////////////////////////////////////////////////////////
		//void SetFFAPvPFlags()
		//  Flags all summons for FFA PvP
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void SetFFAPvPFlags();


		///////////////////////////////////////////////////////////////////////////
		//void SetSanctuaryFlags()
		//  Sets the sanctuary flag on all summons
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void SetSanctuaryFlags();


		///////////////////////////////////////////////////////////////////////////
		//void RemovePvPFlags()
		//  Removes the PvP flag from all summons
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemovePvPFlags();


		///////////////////////////////////////////////////////////////////////////
		//void RemoveFFAPvPFlags()
		//  Removes the FFA PvP flag from all summons
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemoveFFAPvPFlags();


		///////////////////////////////////////////////////////////////////////////
		//void RemoveSanctuaryFlags()
		//  Removes the sanctuary flag from all summons
		//
		//Parameter(s)
		//  None
		//
		//Return Value
		//  None
		//
		//
		///////////////////////////////////////////////////////////////////////////
		void RemoveSanctuaryFlags();

	private:
		std::tr1::array< Unit*, SUMMON_SLOTS > summonslots;
		std::set< Unit* > guardians;
};

#endif
