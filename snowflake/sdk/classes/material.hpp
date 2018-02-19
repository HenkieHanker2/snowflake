#pragma once

using material_handle_t = unsigned short;

enum material_flags {
	material_var_debug = ( 1 << 0 ),
	material_var_no_debug_override = ( 1 << 1 ),
	material_var_no_draw = ( 1 << 2 ),
	material_var_use_in_fillrate_mode = ( 1 << 3 ),
	material_var_vertexcolor = ( 1 << 4 ),
	material_var_vertexalpha = ( 1 << 5 ),
	material_var_selfillum = ( 1 << 6 ),
	material_var_additive = ( 1 << 7 ),
	material_var_alphatest = ( 1 << 8 ),
	material_var_multipass = ( 1 << 9 ),
	material_var_znearer = ( 1 << 10 ),
	material_var_model = ( 1 << 11 ),
	material_var_flat = ( 1 << 12 ),
	material_var_nocull = ( 1 << 13 ),
	material_var_nofog = ( 1 << 14 ),
	material_var_ignorez = ( 1 << 15 ),
	material_var_decal = ( 1 << 16 ),
	material_var_envmapsphere = ( 1 << 17 ),
	material_var_noalphamod = ( 1 << 18 ),
	material_var_envmapcameraspace = ( 1 << 19 ),
	material_var_basealphaenvmapmask = ( 1 << 20 ),
	material_var_translucent = ( 1 << 21 ),
	material_var_normalmapalphaenvmapmask = ( 1 << 22 ),
	material_var_needs_software_skinning = ( 1 << 23 ),
	material_var_opaquetexture = ( 1 << 24 ),
	material_var_envmapmode = ( 1 << 25 ),
	material_var_suppress_decals = ( 1 << 26 ),
	material_var_halflambert = ( 1 << 27 ),
	material_var_wireframe = ( 1 << 28 ),
	material_var_allowalphatocoverage = ( 1 << 29 ),
	material_var_ignore_alpha_modulation = ( 1 << 30 ),
	material_var_vertexfog = ( 1 << 31 )
};

class i_material {
public:
	const char* get_name( ) {
		using original_fn = const char*( __thiscall* )( i_material* );
		return utilities::get( ).get_vfunc<original_fn>( this, 0 )( this );
	}
	const char* get_group_name( ) {
		using original_fn = const char*( __thiscall* )( i_material* );
		return utilities::get( ).get_vfunc<original_fn>( this, 1 )( this );
	}
	void set_alpha( int alpha ) {
		using original_fn = void( __thiscall* )( i_material*, float );
		return utilities::get( ).get_vfunc<original_fn>( this, 27 )( this, static_cast< float >( alpha ) / 255.f );
	}
	void set_color( int r, int g, int b ) {
		using original_fn = void( __thiscall* )( i_material*, float, float, float );
		return utilities::get( ).get_vfunc<original_fn>( this, 28 )( this, r / 255.f, g / 255.f, b / 255.f );
	}
	void set_flag( int flag, bool on ) {
		using original_fn = void( __thiscall* )( i_material*, int, bool );
		return utilities::get( ).get_vfunc<original_fn>( this, 29 )( this, flag, on );
	}
};