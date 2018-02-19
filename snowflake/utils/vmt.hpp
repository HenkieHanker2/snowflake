#pragma once

class vmt_hook {
private:
	uintptr_t * * table_pointer;
	uintptr_t* original_table;
	uintptr_t* new_table;
	size_t estimated_size;

public:
	void setup( void* class_pointer ) {
		this->table_pointer = reinterpret_cast< uintptr_t** >( class_pointer );
		this->original_table = *this->table_pointer;

		while ( this->original_table [ this->estimated_size ] )
			this->estimated_size++;

		this->new_table = new uintptr_t [ sizeof( uintptr_t ) * this->estimated_size ];
		memcpy( this->new_table, this->original_table, sizeof( uintptr_t ) * this->estimated_size );
	}

	template <typename t>
	void hook( size_t index, t function ) {
		this->new_table [ index ] = reinterpret_cast< uintptr_t >( function );
	}

	void apply( ) {
		*this->table_pointer = this->new_table;
	}
	void release( ) {
		*this->table_pointer = this->original_table;
	}

	template <typename t>
	t original( size_t index ) {
		return reinterpret_cast< t >( this->original_table [ index ] );
	}
};

class prop_hook {
private:
	recv_prop * prop;
	recv_var_proxy_fn original_fn;

public:
	void setup( recv_prop* prop ) {
		this->prop = prop;
		this->original_fn = prop->proxy_fn;
	}
	void swap_proxy( recv_var_proxy_fn fn ) {
		this->prop->proxy_fn = fn;
	}
	void release( ) {
		this->prop->proxy_fn = this->original_fn;
	}
	recv_var_proxy_fn original( ) {
		return this->original_fn;
	}
};