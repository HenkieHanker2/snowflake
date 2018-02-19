#include "../sdk/sdk.hpp"
#include "hooks.hpp"
#include "../menu/menu.hpp"

bool test = false;

void initialize( void* dll_instance ) {
	utilities::get( ).create_console( );

	interfaces::get( ).initialize( );
	netvar_manager::get( ).initialize( interfaces::get( ).client->get_client_class_head( ) );
	hooks::get( ).initialize( );

	input_system::get( ).bind_key( VK_INSERT, [ ] ( ) {
		options [ "global.menu" ].set<bool>( !options [ "global.menu" ].get<bool>( ) );
		interfaces::get( ).console->get_convar( "cl_mouseenable" )->set_value( !options [ "global.menu" ].get<bool>( ) );
	} );
	input_system::get( ).bind_key( VK_DELETE, [ ] ( ) {
		options [ "global.unload" ].set<bool>( true );
		interfaces::get( ).console->get_convar( "cl_mouseenable" )->set_value( true );
	} );

	do {
		input_system::get( ).poll( );
		menu::get( ).update( );
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
	}
	while ( !options [ "global.unload" ].get<bool>( ) );

	hooks::get( ).destroy( );
	utilities::get( ).destroy_console( );

	FreeLibraryAndExitThread( ( HMODULE ) dll_instance, 0 );
}

bool __stdcall DllMain( void* dll_instance, unsigned long reason_to_call, void* reserved ) {
	switch ( reason_to_call ) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls( ( HMODULE ) dll_instance );
			CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) initialize, dll_instance, 0, 0 );
			break;
	}

	return true;
}