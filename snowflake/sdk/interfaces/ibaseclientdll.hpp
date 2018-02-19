#pragma once

class i_base_client_dll {
public:
	client_class * get_client_class_head( ) {
		using get_client_class_head_t = client_class * ( __thiscall* )( void* );
		return utilities::get( ).get_vfunc<get_client_class_head_t>( this, 8 )( this );
	}
};