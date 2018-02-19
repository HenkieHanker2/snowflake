#pragma once
extern bool menu_blocked;

#include "checkbox.hpp"
#include "slider.hpp"
#include "button.hpp"
#include "selectable.hpp"

class menu : public singleton<menu> {
private:
	std::vector<control*> controls;

public:
	void init( ) {
		controls.push_back( new checkbox( 0, ( 18 * 0 ),  L"bunny hop", "var.bunnyhop" ) );
		controls.push_back( new checkbox( 0, ( 18 * 1 ),  L"backtracking", "var.backtrack" ) );
		controls.push_back( new checkbox( 0, ( 18 * 3 ),  L"box esp", "var.boxesp" ) );
		controls.push_back( new checkbox( 0, ( 18 * 4 ),  L"health based", "var.healthbased" ) );
		controls.push_back( new checkbox( 0, ( 18 * 5 ),  L"health bar", "var.healthbar" ) );
		controls.push_back( new checkbox( 0, ( 18 * 6 ),  L"skeleton esp", "var.skeletonesp" ) );
		controls.push_back( new checkbox( 0, ( 18 * 7 ),  L"esp team check", "var.teamcheck" ) );
		controls.push_back( new checkbox( 0, ( 18 * 9 ),  L"chams", "var.chams" ) );
		controls.push_back( new checkbox( 0, ( 18 * 10 ), L"chams xqz", "var.chamsxqz" ) );
		controls.push_back( new checkbox( 0, ( 18 * 11 ), L"chams team check", "var.chamsteamcheck" ) );
		controls.push_back( new checkbox( 0, ( 18 * 12 ), L"chams health based", "var.chamshealthbased" ) );
		controls.push_back( new slider  ( 0, ( 18 * 14 ), L"viewmodel fov", "var.viewmodelfov", 68.f, 150.f, 68.f ) );
		controls.push_back( new button  ( 0,  ( 18 * 15 ), 70, L"load cfg", [ ] ( ) {
			static char path [ MAX_PATH ];
			std::string folder, file;

			if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 0, path ) ) ) {
				folder = std::string( path ) + ( "\\snowflake\\" );
				file = std::string( path ) + ( "\\snowflake\\config.ini" );
			}

			CreateDirectory( folder.c_str( ), NULL );

			for ( auto &e : options ) {
				char value [ 64 ] = { '\0' };

				GetPrivateProfileStringA( "snowflake", e.first.c_str( ), "", value, 64, file.c_str( ) );

				e.second.set<double>( atof( value ) );
			}
		} ) );
		controls.push_back( new button  ( 80, ( 18 * 15 ), 70, L"save cfg", [ ] ( ) {
			static char path [ MAX_PATH ];
			std::string folder, file;

			if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 0, path ) ) ) {
				folder = std::string( path ) + ( "\\snowflake\\" );
				file = std::string( path ) + ( "\\snowflake\\config.ini" );
			}

			CreateDirectory( folder.c_str( ), NULL );

			for ( auto &e : options ) {
				WritePrivateProfileStringA( "snowflake", e.first.c_str( ), std::to_string( e.second.get<double>( ) ).c_str( ), file.c_str( ) );
			}
		} ) );
	}

	void paint( ) {
		if ( options [ "global.menu" ].get<bool>( ) ) {
			for ( auto i : controls ) {
				i->draw( );
			}
			this->draw_cursor( );
		}
	}
	void update( ) {
		if ( options [ "global.menu" ].get<bool>( ) ) {
			for ( auto i : controls ) {
				i->update( );
			}
		}
	}

	void draw_cursor( ) {
		POINT cursor = input_system::get( ).get_mouse_pos( );
		interfaces::get( ).vgui_surface->set_drawing_color( 30, 30, 30 );

		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 1, cursor.y, 1, 17 );

		for ( int i = 0; i < 11; i++ ) {
			interfaces::get( ).vgui_surface->draw_filled_rect( cursor.x + 2 + i, cursor.y + 1 + i, 1, 1 );
		}

		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 8, cursor.y + 12, 5, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 8, cursor.y + 13, 1, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 9, cursor.y + 14, 1, 2 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 10, cursor.y + 16, 1, 2 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 8, cursor.y + 18, 2, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 7, cursor.y + 16, 1, 2 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 6, cursor.y + 14, 1, 2 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 5, cursor.y + 13, 1, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 4, cursor.y + 14, 1, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 3, cursor.y + 15, 1, 1 );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 2, cursor.y + 16, 1, 1 );

		interfaces::get( ).vgui_surface->set_drawing_color( 255, 48, 48 );

		for ( int i = 0; i < 4; i++ ) {
			interfaces::get( ).vgui_surface->draw_filled_rect( cursor.x + 2 + i, cursor.y + 2 + i, 1, 14 - ( i * 2 ) );
		}

		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 6, cursor.y + 6, 1, 8  );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 7, cursor.y + 7, 1, 9  );

		for ( int i = 0; i < 4; i++ ) {
			interfaces::get( ).vgui_surface->draw_filled_rect( cursor.x + 8 + i, cursor.y + 8 + i, 1, 4 - i );
		}

		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 8, cursor.y + 14, 1, 4  );
		interfaces::get().vgui_surface->draw_filled_rect( cursor.x + 9, cursor.y + 16, 1, 2  );
	}
};