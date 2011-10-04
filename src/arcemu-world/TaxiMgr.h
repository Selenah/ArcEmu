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

#ifndef __TAXIMGR_H
#define __TAXIMGR_H

#define TAXI_TRAVEL_SPEED 32

class Player;

struct TaxiNode
{
	uint32 id;
	float x, y, z;
	uint32 mapid;
	uint32 horde_mount;
	uint32 alliance_mount;
};

struct TaxiPathNode
{
	float x, y, z;
	uint32 mapid;
};

class TaxiPath
{
		friend class TaxiMgr;

	public:
		TaxiPath()
		{
			price = 0;
			id = 0;
		}

		~TaxiPath()
		{
			while(m_pathNodes.size())
			{
				TaxiPathNode* pn = m_pathNodes.begin()->second;
				m_pathNodes.erase(m_pathNodes.begin());
				delete pn;
			}
		}

		void ComputeLen();
		void SetPosForTime(float & x, float & y, float & z, uint32 time, uint32* lastnode, uint32 mapid);
		ARCEMU_INLINE uint32 GetID() { return id; }
		void SendMoveForTime(Player* riding, Player* to, uint32 time);
		void AddPathNode(uint32 index, TaxiPathNode* pn) { m_pathNodes[index] = pn; }
		ARCEMU_INLINE size_t GetNodeCount() { return m_pathNodes.size(); }
		TaxiPathNode* GetPathNode(uint32 i);
		ARCEMU_INLINE uint32 GetPrice() { return price; }
		ARCEMU_INLINE uint32 GetSourceNode() { return from; }

	protected:

		std::map<uint32, TaxiPathNode*> m_pathNodes;

		float m_length1;
		uint32 m_map1;

		float m_length2;
		uint32 m_map2;
		uint32 id, to, from, price;
};


class SERVER_DECL TaxiMgr :  public Singleton < TaxiMgr >
{
	public:
		TaxiMgr()
		{
			_LoadTaxiNodes();
			_LoadTaxiPaths();
		}

		~TaxiMgr()
		{
			while(m_taxiPaths.size())
			{
				TaxiPath* p = m_taxiPaths.begin()->second;
				m_taxiPaths.erase(m_taxiPaths.begin());
				delete p;
			}
			while(m_taxiNodes.size())
			{
				TaxiNode* n = m_taxiNodes.begin()->second;
				m_taxiNodes.erase(m_taxiNodes.begin());
				delete n;
			}
		}

		TaxiPath* GetTaxiPath(uint32 path);
		TaxiPath* GetTaxiPath(uint32 from, uint32 to);
		TaxiNode* GetTaxiNode(uint32 node);

		uint32 GetNearestTaxiNode(float x, float y, float z, uint32 mapid);
		bool GetGlobalTaxiNodeMask(uint32 curloc, uint32* Mask);


	private:
		void _LoadTaxiNodes();
		void _LoadTaxiPaths();

		HM_NAMESPACE::hash_map<uint32, TaxiNode*> m_taxiNodes;
		HM_NAMESPACE::hash_map<uint32, TaxiPath*> m_taxiPaths;
};

#define sTaxiMgr TaxiMgr::getSingleton()

#endif
