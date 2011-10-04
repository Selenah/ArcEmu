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

#ifndef __STATS_H
#define __STATS_H

#include "Unit.h"
#include "UpdateMask.h"
#include "ItemInterface.h"

enum Stats
{
    STAT_STRENGTH,
    STAT_AGILITY,
    STAT_STAMINA,
    STAT_INTELLECT,
    STAT_SPIRIT,
};

SERVER_DECL uint32 getConColor(uint16 AttackerLvl, uint16 VictimLvl);
SERVER_DECL uint32 CalculateXpToGive(Unit* pVictim, Unit* pAttacker);
SERVER_DECL uint32 CalculateStat(uint16 level, double a3, double a2, double a1, double a0);
SERVER_DECL uint32 CalculateDamage(Unit* pAttacker, Unit* pVictim, uint32 weapon_damage_type, uint32* spellgroup, SpellEntry* ability);
SERVER_DECL uint32 GainStat(uint16 level, uint8 playerclass, uint8 Stat);
SERVER_DECL bool isEven(int num);

#endif
