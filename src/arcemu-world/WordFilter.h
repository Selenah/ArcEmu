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

#ifndef _WORDFILTER_H
#define _WORDFILTER_H

struct WordFilterMatch
{
	char* szMatch;
	char* szIgnoreMatch;
	void* pCompiledExpression;
	void* pCompiledIgnoreExpression;
	void* pCompiledExpressionOptions;
	void* pCompiledIgnoreExpressionOptions;
	int iType;
};

class WordFilter
{
		WordFilterMatch** m_filters;
		size_t m_filterCount;

		bool CompileExpression(const char* szExpression, void** pOutput, void** pExtraOutput);

	public:
		WordFilter() : m_filters(NULL), m_filterCount(0) {}
		~WordFilter();

		void Load(const char* szTableName);
		bool Parse(string & sMessage, bool bAllowReplace = true);
		bool ParseEscapeCodes(char* sMessage, bool bAllowLinks);
};

extern WordFilter* g_characterNameFilter;
extern WordFilter* g_chatFilter;

#endif		// _WORDFILTER_H
