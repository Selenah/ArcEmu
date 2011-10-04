/*
 * Servidor ArcEmu MMORPG
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

void WorldSession::HandleDismissVehicle( WorldPacket &recv_data ){
	uint64 current_vehicle_guid = _player->GetCharmedUnitGUID();

	// wait what no vehicle
	if( current_vehicle_guid == 0 )
		return;

	Unit *v = _player->GetMapMgr()->GetUnit( current_vehicle_guid );
	if( v == NULL )
		return;

	if( v->GetVehicleComponent() == NULL )
		return;

	v->GetVehicleComponent()->EjectPassenger( _player );
}


void WorldSession::HandleChangeVehicleSeat( WorldPacket &recv_data ){
	if( _player->GetCurrentVehicle() == NULL )
		return;

	switch( recv_data.GetOpcode() ){
		case CMSG_REQUEST_VEHICLE_PREV_SEAT:
			_player->GetCurrentVehicle()->MovePassengerToPrevSeat( _player );
			break;

		case CMSG_REQUEST_VEHICLE_NEXT_SEAT:
			_player->GetCurrentVehicle()->MovePassengerToNextSeat( _player );
			break;

		case CMSG_REQUEST_VEHICLE_SWITCH_SEAT:{
			WoWGuid vehicle;
			uint8 seat = 0;
			
			recv_data >> vehicle;
			recv_data >> seat;

			if( vehicle.GetOldGuid() == _player->GetCurrentVehicle()->GetOwner()->GetGUID() ){
				_player->GetCurrentVehicle()->MovePassengerToSeat( _player, seat );
			}else{
				Unit *u = _player->GetMapMgr()->GetUnit( vehicle.GetOldGuid() );
				if( u == NULL )
					return;

				if( u->GetVehicleComponent() == NULL )
					return;

				// We can only switch to accessory or back to the parent vehicle
				if( !_player->GetCurrentVehicle()->HasAccessoryWithGUID( vehicle.GetOldGuid() ) && 
					!u->GetVehicleComponent()->HasAccessoryWithGUID( _player->GetCurrentVehicle()->GetOwner()->GetGUID() ) )
					return;

				_player->GetCurrentVehicle()->EjectPassenger( _player );
				u->GetVehicleComponent()->AddPassengerToSeat( _player, seat );
			}

			break;}


		case CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE:{
			WoWGuid src_guid;
			WoWGuid dst_guid;
			uint8 seat = 0;			
			MovementInfo mov;

			recv_data >> src_guid;
 			mov.init( recv_data );
			recv_data >> dst_guid;
			recv_data >> seat;
			
			Unit *src_vehicle = _player->GetMapMgr()->GetUnit( src_guid.GetOldGuid() );
			if( src_vehicle == NULL )
				return;
			
			if( src_vehicle->GetVehicleComponent() == NULL )
				return;
			
			if( src_vehicle->GetGUID() != _player->GetCurrentVehicle()->GetOwner()->GetGUID() )
				return;
			
			Unit *dst_vehicle = _player->GetMapMgr()->GetUnit( dst_guid.GetOldGuid() );
			if( dst_vehicle == NULL )
				return;
			
			if( dst_vehicle->GetVehicleComponent() == NULL )
				return;
			
			if( src_vehicle->GetGUID() == dst_vehicle->GetGUID() ){
				src_vehicle->GetVehicleComponent()->MovePassengerToSeat( _player, seat );
			}else{
				// We can only switch to accessory or back to parent vehicle
				if( !src_vehicle->GetVehicleComponent()->HasAccessoryWithGUID( dst_vehicle->GetGUID() ) && 
					!dst_vehicle->GetVehicleComponent()->HasAccessoryWithGUID( src_vehicle->GetGUID() ) )
					return;

				_player->GetCurrentVehicle()->EjectPassenger( _player );
				dst_vehicle->GetVehicleComponent()->AddPassengerToSeat( _player, seat );
			}

			break;}
	}
}


void WorldSession::HandleRemoveVehiclePassenger( WorldPacket &recv_data ){
	Vehicle *v = NULL;
	if( _player->IsVehicle() )
		v = _player->GetVehicleComponent();
	else
		v = _player->GetCurrentVehicle();

	if( v == NULL )
		return;

	uint64 guid = 0;
	recv_data >> guid;

	if( guid == 0 )
		return;

	Unit *passenger = _player->GetMapMgr()->GetUnit( guid );
	if( passenger == NULL )
		return;

	v->EjectPassenger( passenger );
}


void WorldSession::HandleLeaveVehicle( WorldPacket &recv_data ){
	if( _player->GetCurrentVehicle() == NULL )
		return;

	_player->GetCurrentVehicle()->EjectPassenger( _player );
}


void WorldSession::HandleEnterVehicle( WorldPacket &recv_data ){
	uint64 guid;

	recv_data >> guid;

	Unit *v = _player->GetMapMgr()->GetUnit( guid );
	if( v == NULL )
		return;

	if( !_player->isInRange( v, MAX_INTERACTION_RANGE ) )
		return;

	if( v->GetVehicleComponent() == NULL )
		return;

	v->GetVehicleComponent()->AddPassenger( _player );
}


