// 
// 
// 

#include "MissionMonitor.h"
#include "EnumHelper.h"

MissionMonitor::MissionMonitor()
{}

void MissionMonitor::onHeatbeat( mavlink_heartbeat_t mavlink_heartbeat )
{
	if ( mavlink_heartbeat.type == (uint8_t)MAV_TYPE_GROUND_ROVER )
		if ( mavlink_heartbeat.custom_mode != (uint32_t)_roverMode )
		{
			ROVER_MODE roverMode = (ROVER_MODE)mavlink_heartbeat.custom_mode;
			 Log.trace( "Rover mode changed from %s to %s", EnumHelper::convert( _roverMode), EnumHelper::convert( roverMode) );

			_roverMode = roverMode;
		}
}

void MissionMonitor::onMissionItemReached( mavlink_mission_item_reached_t mavlink_mission_item_reached )
{

	Log.trace( "Destination reached: %d", mavlink_mission_item_reached.seq );
}

void MissionMonitor::onNavControllerOutput( mavlink_nav_controller_output_t mavlink_nav_controller )
{
	Log.trace( "Distance to waypont is %d", mavlink_nav_controller.wp_dist );
}

void MissionMonitor::tick()
{
	evaluateMission();
}

/**
 * @brief 
 * This method will monitor the current state of the flight controller. When the flight controller 
 * is in AUTO mode, the logic will ensure progress is being made between waypoints. If it detects a problem, this 
 * method will call fail mission.
*/
void MissionMonitor::evaluateMission()
{}

void MissionMonitor::failMission()
{}




