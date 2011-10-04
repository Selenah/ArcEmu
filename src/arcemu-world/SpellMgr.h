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

#ifndef __SPELL_MGR_H
#define __SPELL_MGR_H

#include "StdAfx.h"

class Aura;

#define SPELL_FACTORY_FUNCTION(T) \
  public: \
  static Spell* Create(Object* Caster, SpellEntry *info, bool triggered, Aura* aur) { return new T(Caster, info, triggered, aur); } \
  T(Object* Caster, SpellEntry *info, bool triggered, Aura* aur) : Spell(Caster, info, triggered, aur) {}

#define AURA_FACTORY_FUNCTION(T) \
  public: \
  static Aura* Create(SpellEntry *proto, int32 duration, Object* caster, Unit *target, bool temporary = false, Item* i_caster = NULL) { return new T(proto, duration, caster, target, temporary, i_caster); } \
  T(SpellEntry *proto, int32 duration, Object* caster, Unit *target, bool temporary = false, Item* i_caster = NULL) : Aura(proto, duration, caster, target, temporary, i_caster) {}

typedef Spell* (*spell_factory_function)(Object* Caster, SpellEntry* info, bool triggered, Aura* aur);
typedef Aura* (*aura_factory_function)(SpellEntry* proto, int32 duration, Object* caster, Unit* target, bool temporary, Item* i_caster);

class SERVER_DECL SpellFactoryMgr: public Singleton < SpellFactoryMgr >
{
	public:
		SpellFactoryMgr()
		{
			Setup();
		}

		~SpellFactoryMgr()
		{
		}

		Spell* NewSpell(Object* Caster, SpellEntry* info, bool triggered, Aura* aur);
		Aura* NewAura(SpellEntry* proto, int32 duration, Object* caster, Unit* target, bool temporary = false, Item* i_caster = NULL);

	private:

		void AddSpellByEntry(SpellEntry* info, spell_factory_function spell_func);
		void AddSpellById(uint32 spellId, spell_factory_function spell_func);
		void AddSpellByNameHash(uint32 name_hash, spell_factory_function spell_func);

		void AddAuraByEntry(SpellEntry* info, aura_factory_function aura_func);
		void AddAuraById(uint32 spellId, aura_factory_function aura_func);
		void AddAuraByNameHash(uint32 name_hash, aura_factory_function aura_func);

		void Setup();

		void SetupDeathKnight();
		void SetupDruid();
		void SetupHunter();
		void SetupMage();
		void SetupPaladin();
		void SetupPriest();
		void SetupRogue();
		void SetupShaman();
		void SetupWarlock();
		void SetupWarrior();
};

#define sSpellFactoryMgr SpellFactoryMgr::getSingleton()

#endif