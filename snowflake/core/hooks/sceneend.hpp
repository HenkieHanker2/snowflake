#pragma once
#include "../../hacks/chams.hpp"

void __stdcall scene_end( ) {
	using original_fn = void( __thiscall* )( iv_render_view* );
	hooks::get( ).render_view_hook.original<original_fn>( 9 )( interfaces::get( ).render_view );

	chams::get( ).scene_end( );
}