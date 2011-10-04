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

#ifndef __WEATHERMGR_H
#define __WEATHERMGR_H

#define WEATHER_DENSITY_UPDATE 0.05f

class WeatherInfo;
class WeatherMgr;

void   BuildWeatherPacket(WorldPacket* data, uint32 Effect, float Density);
uint32 GetSound(uint32 Effect, float Density);

class WeatherMgr :  public Singleton < WeatherMgr >
{
	public:
		WeatherMgr();
		~WeatherMgr();

		void LoadFromDB();
		void SendWeather(Player* plr);

	private:
		std::map<uint32, WeatherInfo*> m_zoneWeathers;
};

class WeatherInfo : public EventableObject
{
		friend class WeatherMgr;
	public:
		WeatherInfo();
		~WeatherInfo();

		void BuildUp();
		void Update();
		void SendUpdate();
		void SendUpdate(Player* plr);

	protected:
		void _GenerateWeather();

		uint32 m_zoneId;

		uint32 m_totalTime;
		uint32 m_currentTime;

		float m_maxDensity;
		float m_currentDensity;

		uint32 m_currentEffect;
		std::map<uint32, uint32> m_effectValues;
};

#define sWeatherMgr WeatherMgr::getSingleton()

#endif
