#pragma once

class time_warp : public singleton<time_warp> {
private:
	struct backtrack_tick {
		float simulation_time;
		vector_3d hitbox_position;
	};
	backtrack_tick data [ 64 ] [ 12 ];

public:
	void handle( player_t* local, c_usercmd* user_cmd ) {
		int best_target = -1;
		float best_fov = 90.f;

		if ( local->health( ) <= 0 )
			return;

		for ( int i = 0; i < interfaces::get().globals->max_clients; i++ ) {
			auto entity = ( player_t* ) interfaces::get().entity_list->get_entity( i );

			if ( !entity )
				continue;

			if ( entity == local )
				continue;

			if ( entity->dormant( ) )
				continue;

			if ( entity->team( ) == local->team( ) )
				continue;

			if ( entity->health( ) > 0 ) {
				data [ i ] [ user_cmd->command_number % 13 ] = backtrack_tick { entity->simulation_time( ), entity->get_bone_position( 8 ) };
				vector_3d view_direction = utilities::get().angle_vector( user_cmd->view_angles );
				float fov = utilities::get( ).distance_point_to_line( entity->get_bone_position( 8 ), local->get_bone_position( 8 ), view_direction );

				if ( best_fov > fov ) {
					best_fov = fov;
					best_target = i;
				}
			}
		}

		float best_target_simulation_time = 0.f;

		if ( best_target != -1 ) {
			float temp = FLT_MAX;
			vector_3d view_direction = utilities::get().angle_vector( user_cmd->view_angles );

			for ( int t = 0; t < 12; ++t ) {
				float fov = utilities::get( ).distance_point_to_line( data [ best_target ] [ t ].hitbox_position, local->get_bone_position( 8 ), view_direction );
				if ( temp > fov && data [ best_target ] [ t ].simulation_time > local->simulation_time( ) - 1 ) {
					temp = fov;
					best_target_simulation_time = data [ best_target ] [ t ].simulation_time;
				}
			}

			if ( user_cmd->buttons & button_flags::in_attack ) {
				user_cmd->tick_count = ( int ) ( 0.5f + ( float ) ( best_target_simulation_time ) / interfaces::get().globals->interval_per_tick );
			}
		}
	}
};
