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

class FrostBrandAttackSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(FrostBrandAttackSpellProc);

		void Init(Object* obj)
		{
			if(obj == NULL)
			{
				mDeleted = true;
				return;
			}

			mProcChance = TO_ITEM(obj)->GetProto()->Delay * 9 / 600;
		}
};

class FlametongueWeaponSpellProc : public SpellProc
{
		SPELL_PROC_FACTORY_FUNCTION(FlametongueWeaponSpellProc);

		void Init(Object* obj)
		{
			if(obj == NULL)
			{
				mDeleted = true;
				//initializing anyway all fields.
				mItemGUID = 0;
				damage = 0;
				return;
			}

			mItemGUID = obj->GetGUID();
			damage = 0;
			uint32 wp_speed;
			Item* item = TO_ITEM(obj);
			EnchantmentInstance* enchant = item->GetEnchantment(TEMP_ENCHANTMENT_SLOT);
			if(enchant != NULL)
			{
				SpellEntry* sp = dbcSpell.LookupEntryForced(enchant->Enchantment->spell[0]);
				if(sp != NULL && sp->NameHash == SPELL_HASH_FLAMETONGUE_WEAPON__PASSIVE_)
				{
					wp_speed = item->GetProto()->Delay;
					damage = (sp->EffectBasePoints[0] + 1) * wp_speed / 100000;
				}
			}
		}

		bool CanDelete(uint32 spellId, uint64 casterGuid = 0, uint64 misc = 0)//in this case misc is the item guid.
		{
			if(mSpell->Id == spellId && mCaster == casterGuid && misc == mItemGUID && !mDeleted)
				return true;

			return false;
		}

		bool CanProc(Unit* victim, SpellEntry* CastingSpell)
		{
			if(mTarget->IsPlayer())
				return true;
			return false;
		}

		bool DoEffect(Unit* victim, SpellEntry* CastingSpell, uint32 flag, uint32 dmg, uint32 abs, int* dmg_overwrite, uint32 weapon_damage_type)
		{
			Item* item;

			if(weapon_damage_type == OFFHAND)
				item = TO_PLAYER(mTarget)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
			else
				item = TO_PLAYER(mTarget)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);

			if(item != NULL && item->GetGUID() == mItemGUID)
			{
				dmg_overwrite[0] = damage;
				return false;
			}

			return true;
		}

	private:
		uint64 mItemGUID;
		int damage;
};

void SpellProcMgr::SetupShamman()
{
	AddByNameHash(SPELL_HASH_FROSTBRAND_ATTACK, &FrostBrandAttackSpellProc::Create);

	AddById(10444, &FlametongueWeaponSpellProc::Create);
}
