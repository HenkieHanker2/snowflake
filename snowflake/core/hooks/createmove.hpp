#pragma once
#include "../../hacks/timewarp.hpp"

bool __stdcall create_move( float frame_time, c_usercmd* cmd ) {
	using original_fn = bool( __thiscall* )( void*, float, c_usercmd* );
	hooks::get( ).client_mode_hook.original<original_fn>( 24 )( interfaces::get( ).client_mode, frame_time, cmd );

	player_t* local = ( player_t* ) interfaces::get( ).entity_list->get_entity( 1 );
	if ( local ) {
		if ( !( local->flags( ) & entity_flags::fl_onground ) && cmd->buttons & button_flags::in_jump && options [ "var.bunnyhop" ].get<bool>( ) ) {
			cmd->buttons &= ~button_flags::in_jump;
		}
		if ( options [ "var.backtrack" ].get<bool>( ) ) {
			time_warp::get( ).handle( local, cmd );
		}
	}

	return false;
}