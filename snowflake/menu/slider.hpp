#pragma once
#include "base_control.hpp"

template <typename t>
inline t clamp( t number, t min, t max ) {
	if ( number < min ) {
		return min;
	}
	else if ( number > max ) {
		return max;
	}
	else {
		return number;
	}
}

class slider : public control {
private:
	float min, max;
	void init( int x, int y, std::wstring label, std::string var_name, float min, float max, float default_value = 0.f ) {
		this->x = x + 16;
		this->y = y + 16;
		this->label = label;
		this->var_name = var_name;
		this->min = min;
		this->max = max;
		options [ var_name ].set<float>( default_value );
	}

public:
	slider( ) {
		init( 0, 0, L"", nullptr, 0.f, 0.f );
	}
	slider( int x, int y, std::wstring label, std::string var_name, float min, float max ) {
		init( x, y, label, var_name, min, max );
	}
	slider( int x, int y, std::wstring label, std::string var_name, float min, float max, float default_value ) {
		init( x, y, label, var_name, min, max, default_value );
	}

	void draw( ) override {
		auto value = options [ var_name ].get<float>( );
		auto ratio = ( value - min ) / ( max - min );

		interfaces::get( ).vgui_surface->set_drawing_color( 180, 30, 30 );
		interfaces::get( ).vgui_surface->draw_filled_rect( this->x, this->y, static_cast< int >( 150 * ( ratio ) ), 12 );

		interfaces::get( ).vgui_surface->set_drawing_color( 255, 255, 255 );
		interfaces::get( ).vgui_surface->draw_outlined_rect( this->x - 1, this->y - 1, 152, 14 );

		char buf [ 16 ];
		sprintf_s( buf, " = %.1f", options [ var_name ].get<float>( ) );

		wchar_t buf_wc [ 128 ];
		if ( MultiByteToWideChar( CP_UTF8, 0, buf, -1, buf_wc, 128 ) > 0 ) {
			std::wstring label_wc( label );
			label_wc.append( buf_wc );

			interfaces::get( ).vgui_surface->set_text_color( 255, 255, 255 );
			interfaces::get( ).vgui_surface->set_text_position( x + 4, y );
			interfaces::get( ).vgui_surface->draw_string( label_wc.c_str( ), wcslen( label_wc.c_str( ) ) );
		}
	}
	void update( ) override {
		menu_blocked = false;
		if ( utilities::get( ).is_in_bounds<int>( x - 10, x + 160, input_system::get( ).get_mouse_pos( ).x ) && utilities::get( ).is_in_bounds<int>( y, y + 12, input_system::get( ).get_mouse_pos( ).y ) && !menu_blocked ) {
			if ( input_system::get( ).get_key_state( VK_LBUTTON ) == key_state::held ) {
				auto relative_x = clamp( ( int ) ( input_system::get( ).get_mouse_pos( ).x - x ), 0, ( int ) ( 150 ) );
				auto ratio = ( relative_x / ( float ) 150 );

				if ( ratio < 0.f ) ratio = 0.f;
				if ( ratio > 1.f ) ratio = 1.f;

				auto value = min + ( ( max - min ) * ratio );

				options [ var_name ].set<float>( value );
				menu_blocked = true;
			}
		}
	}
};