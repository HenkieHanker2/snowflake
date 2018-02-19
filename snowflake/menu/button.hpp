#pragma once
#include "base_control.hpp"

class button : public control {
private:
	std::function<void( )> callback;
	int width;

	void init( int x, int y, std::wstring label, std::function<void( )> callback ) {
		this->x = x + 16;
		this->y = y + 16;
		this->label = label;
		this->callback = callback;
		this->width = 100;
	}
	void init( int x, int y, int width, std::wstring label, std::function<void( )> callback ) {
		this->x = x + 16;
		this->y = y + 16;
		this->label = label;
		this->callback = callback;
		this->width = width;
	}

public:
	button( ) {
		init( 0, 0, L"", nullptr );
	}
	button( int x, int y, std::wstring label, std::function<void( )> callback ) {
		init( x, y, label, callback );
	}
	button( int x, int y, int width, std::wstring label, std::function<void( )> callback ) {
		init( x, y, width, label, callback );
	}

	void draw( ) override {
		interfaces::get( ).vgui_surface->set_drawing_color( 30, 30, 30 );
		interfaces::get( ).vgui_surface->draw_filled_rect( this->x, this->y, width, 20 );

		interfaces::get( ).vgui_surface->set_drawing_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->draw_outlined_rect( this->x - 1, this->y - 1, width + 2, 22 );

		interfaces::get( ).vgui_surface->set_text_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->set_text_position( x + 18, y + 4 );
		interfaces::get( ).vgui_surface->draw_string( this->label.c_str( ), wcslen( this->label.c_str( ) ) );
	}
	void update( ) override {
		menu_blocked = false;
		if ( utilities::get( ).is_in_bounds<int>( x, x + width, input_system::get( ).get_mouse_pos( ).x ) && utilities::get( ).is_in_bounds<int>( y, y + 20, input_system::get( ).get_mouse_pos( ).y ) && !menu_blocked ) {
			if ( input_system::get( ).get_key_state( VK_LBUTTON ) == key_state::down ) {
				if ( this->callback ) {
					callback( );
					menu_blocked = true;
				}
			}
		}
	}
};