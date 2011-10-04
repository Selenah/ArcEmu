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

#ifndef WOWSERVER_DYNAMICOBJECT_H
#define WOWSERVER_DYNAMICOBJECT_H

struct SpellEntry;

typedef std::set<uint64>  DynamicObjectList;

class SERVER_DECL DynamicObject : public Object
{
	public:
		DynamicObject(uint32 high, uint32 low);
		~DynamicObject();

		void Create(Unit* caster, Spell* pSpell, float x, float y, float z, uint32 duration, float radius);
		void UpdateTargets();

		void AddInRangeObject(Object* pObj);
		void OnRemoveInRangeObject(Object* pObj);
		void Remove();

	protected:

		SpellEntry* m_spellProto;
		Unit* u_caster;
		Player* p_caster;
		Spell* m_parentSpell;
		DynamicObjectList targets;

		uint32 m_aliveDuration;
		uint32 _fields[DYNAMICOBJECT_END];
};

#endif

