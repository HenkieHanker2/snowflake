#pragma once

class i_client_entity_list {
public:
	void* get_entity( int index ) {
		using get_entity_t = void*( __thiscall* )( void*, int );
		return utilities::get( ).get_vfunc<get_entity_t>( this, 3 )( this, index );
	}
	void* get_entity( uintptr_t handle ) {
		using get_entity_t = void*( __thiscall* )( void*, uintptr_t );
		return utilities::get( ).get_vfunc<get_entity_t>( this, 4 )( this, handle );
	}
};