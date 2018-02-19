#pragma once

class i_surface {
public:
	void set_drawing_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 15 )( this, r, g, b, a );
	}
	void draw_filled_rect( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 16 )( this, x, y, x + w, y + h );
	}
	void draw_outlined_rect( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 18 )( this, x, y, x + w, y + h );
	}
	void draw_line( int x1, int y1, int x2, int y2 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 19 )( this, x1, y1, x2, y2 );
	}
	unsigned int create_font( ) {
		using original_fn = unsigned int( __thiscall* )( void* );
		return utilities::get( ).get_vfunc<original_fn>( this, 71 )( this );
	}
	bool set_font_glyph_set( unsigned int font, const char* name, int tall, int weight, int blur, int scan_lines, int flags, int range_min = 0, int range_max = 0 ) {
		using original_fn = bool( __thiscall* )( void*, unsigned int, const char*, int, int, int, int, int, int, int );
		return utilities::get( ).get_vfunc<original_fn>( this, 72 )( this, font, name, tall, weight, blur, scan_lines, flags, range_min, range_max );
	}
	void set_text_font( vgui::font font ) {
		using original_fn = void( __thiscall* )( i_surface*, vgui::font );
		utilities::get( ).get_vfunc<original_fn>( this, 23 )( this, font );
	}
	void set_text_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 25 )( this, r, g, b, a );
	}
	void set_text_position( int x, int y ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 26 )( this, x, y );
	}
	void draw_string( const wchar_t* text, int length, int draw_type = 0 ) {
		using original_fn = void( __thiscall* )( void*, wchar_t const*, int, int );
		utilities::get( ).get_vfunc<original_fn>( this, 28 )( this, text, length, draw_type );
	}
};