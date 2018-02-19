#pragma once

enum key_state {
	undefined = -1,
	inactive,
	down,
	held,
	released
};

class input_system : public singleton<input_system> {
private:
	bool key_states [ 256 ];
	bool previous_states [ 256 ];
	std::unordered_map<int, std::function<void( )>> key_binds;
	POINT mouse;

public:
	void poll( ) {
		memcpy( this->previous_states, this->key_states, 256 );

		for ( int i = 0; i < 256; i++ ) {
			this->key_states [ i ] = GetAsyncKeyState( i );
			if ( this->get_key_state( i ) == key_state::down ) {
				if ( this->key_binds [ i ] ) {
					this->key_binds [ i ]( );
				}
			}
		}

		GetCursorPos( &this->mouse );
	}
	key_state get_key_state( int key ) {
		if ( key_states [ key ] ) {
			if ( previous_states [ key ] ) {
				return key_state::held;
			}
			else {
				return key_state::down;
			}
		}
		else {
			if ( previous_states [ key ] ) {
				return key_state::released;
			}
			else {
				return key_state::inactive;
			}
		}
		return key_state::undefined;
	}

	void bind_key( int key, std::function<void( )> function ) {
		this->key_binds [ key ] = function;
	}
	void unbind_key( int key ) {
		this->key_binds [ key ] = 0;
	}

	POINT get_mouse_pos( ) {
		return this->mouse;
	}
};