#pragma once

class esp : public singleton<esp> {
private:
	struct box {
		int x, y, w, h;
		box( ) = default;
		box( int x, int y, int w, int h ) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};
	bool get_playerbox( entity_t* ent, box& in ) {
		vector_3d origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
		float left, top, right, bottom;

		origin = ent->origin( );
		min = ent->collideable( )->mins( ) + origin;
		max = ent->collideable( )->maxs( ) + origin;

		vector_3d points [ ] = {
			vector_3d( min.x, min.y, min.z ),
			vector_3d( min.x, max.y, min.z ),
			vector_3d( max.x, max.y, min.z ),
			vector_3d( max.x, min.y, min.z ),
			vector_3d( max.x, max.y, max.z ),
			vector_3d( min.x, max.y, max.z ),
			vector_3d( min.x, min.y, max.z ),
			vector_3d( max.x, min.y, max.z )
		};

		if ( !interfaces::get().debug_overlay->world_to_screen( points [ 3 ], flb ) || !interfaces::get( ).debug_overlay->world_to_screen( points [ 5 ], brt )
			|| !interfaces::get( ).debug_overlay->world_to_screen( points [ 0 ], blb ) || !interfaces::get( ).debug_overlay->world_to_screen( points [ 4 ], frt )
			|| !interfaces::get( ).debug_overlay->world_to_screen( points [ 2 ], frb ) || !interfaces::get( ).debug_overlay->world_to_screen( points [ 1 ], brb )
			|| !interfaces::get( ).debug_overlay->world_to_screen( points [ 6 ], blt ) || !interfaces::get( ).debug_overlay->world_to_screen( points [ 7 ], flt ) )
			return false;

		vector_3d arr [ ] = { flb, brt, blb, frt, frb, brb, blt, flt };

		left = flb.x;
		top = flb.y;
		right = flb.x;
		bottom = flb.y;

		for ( int i = 1; i < 8; i++ ) {
			if ( left > arr [ i ].x )
				left = arr [ i ].x;
			if ( bottom < arr [ i ].y )
				bottom = arr [ i ].y;
			if ( right < arr [ i ].x )
				right = arr [ i ].x;
			if ( top > arr [ i ].y )
				top = arr [ i ].y;
		}

		in.x = ( int ) left;
		in.y = ( int ) top;
		in.w = int( right - left );
		in.h = int( bottom - top );

		return true;
	}

public:
	void paint( ) {
		if ( !interfaces::get( ).engine->is_sane( ) )
			return;

		player_t* me = ( player_t* ) interfaces::get( ).entity_list->get_entity( interfaces::get( ).engine->get_local_player( ) );
		if ( !me )
			return;

		for ( int i = 0; i < interfaces::get( ).globals->max_clients; i++ ) {
			player_t* entity = ( player_t* ) interfaces::get( ).entity_list->get_entity( i );

			if ( i == interfaces::get( ).engine->get_local_player( ) )
				continue;
			if ( !entity )
				continue;
			if ( !entity->is_player( ) )
				continue;
			if ( entity->health( ) <= 0 )
				continue;
			if ( entity->team( ) == me->team( ) && options [ "var.teamcheck" ].get<bool>( ) )
				continue;

			box player_box;
			if ( !this->get_playerbox( entity, player_box ) )
				continue;

			if ( options [ "var.boxesp" ].get<bool>( ) ) {
				interfaces::get( ).vgui_surface->set_drawing_color( 0, 0, 0 );
				interfaces::get( ).vgui_surface->draw_outlined_rect( player_box.x - 1, player_box.y - 1, player_box.w + 2, player_box.h + 2 );
				interfaces::get( ).vgui_surface->draw_outlined_rect( player_box.x + 1, player_box.y + 1, player_box.w - 2, player_box.h - 2 );

				if ( options [ "var.healthbased" ].get<bool>( ) ) {
					const float multiplier = 2.55f;

					int red, green, blue;
					int health = entity->health( );

					red = static_cast< int >( 255 - ( health * multiplier ) );
					green = static_cast< int >( health * multiplier );
					blue = 0;

					interfaces::get( ).vgui_surface->set_drawing_color( red, green, blue );
				}
				else {
					switch ( entity->team( ) ) {
						case 2:
							interfaces::get( ).vgui_surface->set_drawing_color( 255, 0, 0 );
							break;
						case 3:
							interfaces::get( ).vgui_surface->set_drawing_color( 0, 0, 255 );
							break;
						default:
							interfaces::get( ).vgui_surface->set_drawing_color( 170, 170, 170 );
							break;
					}
				}
				interfaces::get( ).vgui_surface->draw_outlined_rect( player_box.x, player_box.y, player_box.w, player_box.h );
			}
			if ( options [ "var.healthbar" ].get<bool>( ) ) {
				// s/o to @worldgamer123
				// https://www.unknowncheats.me/forum/counterstrike-global-offensive/222175-edgy-healthbars.html

				float flBoxes = std::ceil( entity->health( ) / 10.f );
				float flX = ( float ) player_box.x - 9;
				float flY = ( float ) player_box.y - 1;
				float flHeight = player_box.h / 10.f;
				float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;

				const float multiplier = 2.55f;
				int red, green, blue;
				int health = entity->health( );

				red = static_cast< int >( 255 - ( health * multiplier ) );
				green = static_cast< int >( health * multiplier );
				blue = 0;

				interfaces::get( ).vgui_surface->set_drawing_color( 80, 80, 80, 125 );
				interfaces::get( ).vgui_surface->draw_filled_rect( (int)flX, ( int ) flY, 4, player_box.h + 2 );

				interfaces::get( ).vgui_surface->set_drawing_color( 0, 0, 0 );
				interfaces::get( ).vgui_surface->draw_outlined_rect( ( int ) flX, ( int ) flY, 4, player_box.h + 2 );

				interfaces::get( ).vgui_surface->set_drawing_color( red, green, blue );
				interfaces::get( ).vgui_surface->draw_filled_rect( ( int ) flX + 1, ( int ) flY, 2, static_cast< int >( flHeight * flBoxes + 1 ) );

				interfaces::get( ).vgui_surface->set_drawing_color( 0, 0, 0 );
				for ( int i = 0; i < 10; i++ ) {
					interfaces::get( ).vgui_surface->draw_line( ( int ) flX, static_cast< int >( flY + i * flHeight ), ( int ) flX + 4, static_cast< int >( flY + i * flHeight ) );
				}
			}
			if ( options [ "var.skeletonesp" ].get<bool>( ) ) {
				studio_hdr_t* hdr = interfaces::get( ).model_info->get_studio_model( entity->model( ) );
				if ( hdr ) {
					static matrix_t bone_matrix [ 128 ];

					if ( entity->setup_bones( bone_matrix, 128, bone_flags::bone_used_by_hitbox, interfaces::get( ).globals->cur_time ) ) {
						interfaces::get( ).vgui_surface->set_drawing_color( 255, 255, 255 );

						for ( int b = 0; b < hdr->bones_count; b++ ) {
							studio_bone_t *bone = hdr->bone( b );
							if ( !bone || !( bone->flags & bone_flags::bone_used_by_hitbox ) || bone->parent == -1 )
								continue;

							vector_3d bone_start_screen, bone_end_screen;;
							if ( !interfaces::get().debug_overlay->world_to_screen( vector_3d( bone_matrix [ b ] [ 0 ] [ 3 ], bone_matrix [ b ] [ 1 ] [ 3 ], bone_matrix [ b ] [ 2 ] [ 3 ] ), bone_start_screen ) ||
								!interfaces::get( ).debug_overlay->world_to_screen( vector_3d( bone_matrix [ bone->parent ] [ 0 ] [ 3 ], bone_matrix [ bone->parent ] [ 1 ] [ 3 ], bone_matrix [ bone->parent ] [ 2 ] [ 3 ] ), bone_end_screen ) )
								continue;

							interfaces::get().vgui_surface->draw_line( ( int ) bone_start_screen.x, ( int ) bone_start_screen.y, ( int ) bone_end_screen.x, ( int ) bone_end_screen.y );
						}
					}
				}
			}
		}
	}
};