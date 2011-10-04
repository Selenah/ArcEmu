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

#ifndef _DEATH_KNIGHT_H
#define _DEATH_KNIGHT_H

#define TOTAL_NORMAL_RUNE_TYPES 3
#define TOTAL_USED_RUNES (TOTAL_NORMAL_RUNE_TYPES*2)
#define MAX_RUNES 6
#define TOTAL_RUNE_TYPES 4
#define MAX_RUNE_VALUE 1

enum SPELL_RUNE_TYPES
{
    RUNE_BLOOD		= 0,
    RUNE_FROST		= 1,
    RUNE_UNHOLY		= 2,
    RUNE_DEATH		= 3,
    RUNE_MAX_TYPES	= 4
};

const uint8 base_runes[MAX_RUNES] = {RUNE_BLOOD, RUNE_BLOOD, RUNE_FROST, RUNE_FROST, RUNE_UNHOLY, RUNE_UNHOLY};

struct Rune
{
	uint8 type;
	bool is_used;
};

class DeathKnight : public Player
{
		Rune m_runes[MAX_RUNES];

		// Holds last slot used
		uint8 m_last_used_rune_slot;

	protected:

		void SendRuneUpdate(uint8 slot);

	public:
		DeathKnight(uint32 guid) : Player(guid)
		{
			m_last_used_rune_slot = 0;
			for(uint8 i = 0; i < MAX_RUNES; ++i)
			{
				m_runes[i].type = base_runes[i];
				m_runes[i].is_used = false;
			}
		}

		bool IsDeathKnight() { return true; }

		//*************************************************************************************
		// RUNES
		//*************************************************************************************

		uint8 GetBaseRuneType(uint8 slot);
		uint8 GetRuneType(uint8 slot);
		bool GetRuneIsUsed(uint8 slot);
		void ConvertRune(uint8 slot, uint8 type);
		uint32 HasRunes(uint8 type, uint32 count);
		uint32 TakeRunes(uint8 type, uint32 count);
		void ResetRune(uint8 slot);
		uint8 GetRuneFlags();
		bool IsAllRunesOfTypeInUse(uint8 type);
		uint8 GetLastUsedUnitSlot() { return m_last_used_rune_slot; }
};

#endif