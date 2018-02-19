#pragma once

#include <map>
#include <ctype.h>
#include "singleton.hpp"
#include "fnv.hpp"
#include "../sdk/classes/clientclass.hpp"

class netvar_manager : public singleton<netvar_manager> {
private:
	std::map<unsigned int, recv_prop*> netvars_map;
	void dump_table_recursive( recv_table* table ) {
		for ( auto i = 0; i < table->props_count; ++i ) {
			auto prop = &table->props [ i ];

			if ( !prop || isdigit( prop->prop_name [ 0 ] ) )
				continue;
			if ( strcmp( prop->prop_name, "baseclass" ) == 0 )
				continue;

			if ( prop->prop_type == send_prop_type::_data_table && prop->data_table != nullptr && prop->data_table->table_name [ 0 ] == 'D' ) {
				dump_table_recursive( prop->data_table );
			}

			std::string hash_string = table->table_name;
			hash_string.append( "->" );
			hash_string.append( prop->prop_name );

			netvars_map [ fnv_hash( hash_string.c_str( ) ) ] = prop;
		}
	}

public:
	void initialize( client_class* client_data ) {
		for ( auto data = client_data; data; data = data->next_ptr ) {
			if ( data->recvtable_ptr ) {
				dump_table_recursive( data->recvtable_ptr );
			}
		}
	}

	unsigned short get_offset( unsigned int hash ) {
		if ( !netvars_map [ hash ] ) return 0;
		return netvars_map [ hash ]->offset;
	}
	recv_prop* get_prop( unsigned int hash ) {
		return netvars_map [ hash ];
	}
};

#define offset_fn(type, var, offset) \
	type& var() { \
		return *(type*)(uintptr_t(this) + offset); \
	} \

#define netvar_fn(type, var, hash) \
	type& var() { \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return *(type*)(uintptr_t(this) + _offset); \
	} \

#define netvar_ptr_fn(type, var, hash) \
	type* var() { \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return (type*)(uintptr_t(this) + _offset); \
	} \

#define netvar_offset_fn(type, var, hash, offset) \
	type& var() { \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return *(type*)(uintptr_t(this) + _offset + offset); \
	} \