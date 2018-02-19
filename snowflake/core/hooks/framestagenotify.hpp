#pragma once
#include "../../menu/menu.hpp"

void __stdcall frame_stage_notify( client_frame_stage_t frame_stage ) {
	using original_fn = void( __thiscall* )( void*, client_frame_stage_t );
	hooks::get( ).client_hook.original<original_fn>( 36 )( interfaces::get( ).client, frame_stage );

	interfaces::get( ).console->get_convar( "viewmodel_fov" )->set_value( options [ "var.viewmodelfov" ].get<float>( ) );
}