#pragma once
#include "base_control.hpp"

class checkbox : public control {
private:
	void init( int x, int y, std::wstring label, std::string var_name, bool default_value = false ) {
		this->x = x + 16;
		this->y = y + 16;
		this->label = label;
		this->var_name = var_name;
		options [ var_name ].set<float>( default_value );
	}

public:
	checkbox( ) {
		init( 0, 0, L"", nullptr );
	}
	checkbox( int x, int y, std::wstring label, std::string var_name ) {
		init( x, y, label, var_name );
	}
	checkbox( int x, int y, std::wstring label, std::string var_name, bool default_value ) {
		init( x, y, label, var_name, default_value );
	}

	void draw( ) override {
		if ( options [ var_name ].get<bool>() ) {
			interfaces::get( ).vgui_surface->set_drawing_color( 180, 30, 30 );
			interfaces::get( ).vgui_surface->draw_filled_rect( this->x, this->y, 12, 12 );
		}

		interfaces::get( ).vgui_surface->set_drawing_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->draw_outlined_rect( this->x - 1, this->y - 1, 14, 14 );

		interfaces::get( ).vgui_surface->set_text_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->set_text_position( x + 18, y );
		interfaces::get( ).vgui_surface->draw_string( this->label.c_str( ), wcslen( this->label.c_str( ) ) );
	}
	void update( ) override {
		menu_blocked = false;
		if ( utilities::get( ).is_in_bounds<int>( x, x + 12, input_system::get( ).get_mouse_pos( ).x ) && utilities::get( ).is_in_bounds<int>( y, y + 12, input_system::get( ).get_mouse_pos( ).y ) && !menu_blocked ) {
			if ( input_system::get( ).get_key_state( VK_LBUTTON ) == key_state::down ) {
				options [ var_name ].set<bool>( !options [ var_name ].get<bool>( ) );
				menu_blocked = true;
			}
		}
	}
};