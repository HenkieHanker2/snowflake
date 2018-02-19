#pragma once
#include "base_control.hpp"

class selectable : public control {
private:
	std::vector<std::wstring> labels;
	void init( int x, int y, std::string var_name, std::vector<std::wstring> labels ) {
		this->x = x + 16;
		this->y = y + 16;
		this->var_name = var_name;
		this->labels = labels;
		options [ var_name ].set<int>( 0 );
	}

public:
	selectable( ) = default;
	selectable( int x, int y, std::string var_name, std::vector<std::wstring> labels ) {
		init( x, y, var_name, labels );
	}

	void draw( ) override {
		interfaces::get( ).vgui_surface->set_drawing_color( 30, 30, 30 );
		interfaces::get( ).vgui_surface->draw_filled_rect( this->x, this->y, 150, 20 );

		interfaces::get( ).vgui_surface->set_drawing_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->draw_outlined_rect( this->x - 1, this->y - 1, 150 + 2, 22 );

		interfaces::get( ).vgui_surface->set_text_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->set_text_position( x + 24, y + 4 );
		interfaces::get( ).vgui_surface->draw_string( this->labels.at( options [ var_name ].get<int>( ) ).c_str( ), wcslen( this->labels.at( options [ var_name ].get<int>( ) ).c_str( ) ) );

		interfaces::get( ).vgui_surface->set_text_position( x + 4, y + 4 );
		interfaces::get( ).vgui_surface->draw_string( L"<", wcslen( L"<" ) );

		interfaces::get( ).vgui_surface->set_text_position( x + 140, y + 4 );
		interfaces::get( ).vgui_surface->draw_string( L">", wcslen( L">" ) );
	}
	void update( ) override {
		menu_blocked = false;
		if ( utilities::get( ).is_in_bounds<int>( x, x + 16, input_system::get( ).get_mouse_pos( ).x ) && utilities::get( ).is_in_bounds<int>( y, y + 20, input_system::get( ).get_mouse_pos( ).y ) && !menu_blocked ) {
			if ( input_system::get( ).get_key_state( VK_LBUTTON ) == key_state::down ) {
				menu_blocked = true;

				if ( options [ var_name ].get<int>( ) < 1 )
					return;

				options [ var_name ].set<int>( options [ var_name ].get<int>( ) - 1 );
			}
		}
		if ( utilities::get( ).is_in_bounds<int>( x + 134, x + 150, input_system::get( ).get_mouse_pos( ).x ) && utilities::get( ).is_in_bounds<int>( y, y + 20, input_system::get( ).get_mouse_pos( ).y ) && !menu_blocked ) {
			if ( input_system::get( ).get_key_state( VK_LBUTTON ) == key_state::down ) {
				menu_blocked = true;

				if ( options [ var_name ].get<size_t>( ) > labels.size() - 2 )
					return;

				options [ var_name ].set<int>( options [ var_name ].get<int>( ) + 1 );
			}
		}
	}
};