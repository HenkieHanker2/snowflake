#include "hooks.hpp"

#include "hooks/framestagenotify.hpp"
#include "hooks/createmove.hpp"
#include "hooks/painttraverse.hpp"
#include "hooks/sceneend.hpp"

void hooks::initialize( ) {
	this->client_hook.setup( interfaces::get( ).client );
	this->client_mode_hook.setup( interfaces::get( ).client_mode );
	this->panel_hook.setup( interfaces::get( ).vgui_panel );
	this->render_view_hook.setup( interfaces::get( ).render_view );

	this->client_hook.hook( 36, frame_stage_notify );
	this->client_mode_hook.hook( 24, create_move );
	this->panel_hook.hook( 41, paint_traverse );
	this->render_view_hook.hook( 9, scene_end );

	this->client_hook.apply( );
	this->client_mode_hook.apply( );
	this->panel_hook.apply( );
	this->render_view_hook.apply( );

	interfaces::get( ).console->get_convar( "viewmodel_fov" )->callbacks.SetSize( 0 );
}

void hooks::destroy( ) {
	this->client_hook.release( );
	this->client_mode_hook.release( );
	this->panel_hook.release( );
	this->render_view_hook.release( );

	std::this_thread::sleep_for( std::chrono::milliseconds( 150 ) );
}