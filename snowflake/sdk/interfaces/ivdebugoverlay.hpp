#pragma once

class iv_debug_overlay {
public:
	bool world_to_screen( const vector_3d& in, vector_3d& out ) {
		using original_fn = int( __thiscall* )( iv_debug_overlay*, const vector_3d&, vector_3d& );
		int return_value = utilities::get( ).get_vfunc<original_fn>( this, 13 )( this, in, out );
		return static_cast< bool >( return_value != 1 );
	}
};