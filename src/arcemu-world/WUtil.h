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

#ifndef ARCWORLDUTILS__H
#define ARCWORLDUTILS__H

namespace Arcemu
{

	// Common Arcemu world stuff
	class Util
	{
		public:
			SERVER_DECL static uint32 GUID_LOPART(uint64 GUID);
			SERVER_DECL static uint32 GUID_HIPART(uint64 GUID);
			SERVER_DECL static uint32 GET_CREATURE_ENTRY_FROM_GUID(uint64 guid);
			static void ArcemuAssert(bool condition);
			static uint64 MAKE_PET_GUID(uint32 entry, uint32 lowGUID);
			static uint64 MAKE_ITEM_GUID(uint32 lowGUID);
	};
}
#define ARCEMU_ASSERT( EXPR ) Arcemu::Util::ArcemuAssert( EXPR ); ANALYSIS_ASSUME( EXPR )

#endif
