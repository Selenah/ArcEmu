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
 
#ifndef _SPEED_DETECTOR_H_
#define _SPEED_DETECTOR_H_

#define SPDT_SAMPLINGRATE				1000	// there is no point flooding calculations	
#define SPDT_DETECTION_ERROR			0.70f	// ex: 10% for a speed=7 => 0.7 max speed cheat
#define CHEAT_ALARMS_TO_TRIGGER_CHEAT	5		// if x alarms stack up over time then it is time to kick the player

// problem : some players advance more then others by using speed cheat
// solution : check the amount of advance a player does over time to see if it is higher then should be
// situations :
//		- player plays with mouse triggering a setfacing packet every 16 ms would flood us with incorrect values
//		- client sends us every 500 ms a movement update
//		- server makes speed changes -> need to reset detector
//		- server uses scripts over character -> delay detector
// error recovery :
//		- speed change is detected then system resets state to start measuring again
//		- speed is measured over interval to avoid small value problems
//		- cheat detection has to stack up to trigger real cheat alarm
// problems :
//		- it takes SPDT_WINDOW_SIZE*SPDT_SAMPLINGRATE at each speed change until it gives relevant data
//		- moving in a small area is not considered cheating (it is hard to make that)

class Player;

class SpeedCheatDetector
{
	public:
		SpeedCheatDetector();
		void		AddSample(float x, float y, int stamp, float player_speed); // update the detector with new values
		inline char	IsCheatDetected() { return cheat_threat >= CHEAT_ALARMS_TO_TRIGGER_CHEAT; } // test cheater status
		void		SkipSamplingUntil(int stamp);	// delay then reset cheat detector
		void		ReportCheater(Player* _player);	// take actions against a cheater
		void		EventSpeedChange();				// reset internal values on speed change

	private:
		float			last_x, last_y;
		int				last_stamp;
		signed char		cheat_threat;		//don't draw quick conclusions. If player is suspicious over time then kill him
		float			last_used_speed;	//we reset if speed changed since our last measure
		float			bigest_hacked_speed_dif;
};

#endif
