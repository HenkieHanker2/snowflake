#pragma once
#include "../../menu/menu.hpp"
#include "../../hacks/esp.hpp"

void __stdcall paint_traverse( vgui::panel panel, bool force_repaint, bool allow_force ) {
	static vgui::font menu_font {};
	static bool once = false;

	if ( !once ) {
		menu_font = interfaces::get( ).vgui_surface->create_font( );
		interfaces::get( ).vgui_surface->set_font_glyph_set( menu_font, "Calibri", 13, 500, 0, 0, 512 );
		menu::get( ).init( );

		once = true;
	}
	
	using original_fn = void( __thiscall* )( void*, vgui::panel, bool, bool );
	hooks::get( ).panel_hook.original<original_fn>( 41 )( interfaces::get( ).vgui_panel, panel, force_repaint, allow_force );

	if ( strcmp( interfaces::get( ).vgui_panel->get_name( panel ), "FocusOverlayPanel" ) == 0 ) {
		interfaces::get( ).vgui_surface->set_text_font( menu_font );
		menu::get( ).paint( );

		esp::get( ).paint( );
	}
}