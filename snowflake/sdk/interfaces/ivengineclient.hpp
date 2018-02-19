#pragma once

struct player_info_t {
	long __pad0;
	union {
		long xuid;
		struct {
			int xuid_low;
			int xuid_high;
		};
	};
	char player_name [ 128 ];
	int user_id;
	char steam_id_string [ 20 ];
	char __pad0x0ab [ 0x10 ];
	unsigned long steam_id;
	char friends_name [ 128 ];
	bool is_fake_player;
	bool is_hltv;
	unsigned int custom_files [ 4 ];
	unsigned char files_downloaded;
};

class iv_engine_client {
public:
	int get_local_player( ) {
		using original_fn = int( __thiscall* )( iv_engine_client* );
		return utilities::get( ).get_vfunc<original_fn>( this, 12 )( this );
	}
	int get_player_for_user_id( int user_id ) {
		using original_fn = int( __thiscall* )( iv_engine_client*, int );
		return utilities::get( ).get_vfunc<original_fn>( this, 9 )( this, user_id );
	}
	bool get_player_info( int index, player_info_t* info ) {
		using original_fn = bool( __thiscall* )( iv_engine_client*, int, player_info_t* );
		return utilities::get( ).get_vfunc<original_fn>( this, 8 )( this, index, info );
	}
	void get_screen_size( int& width, int& height ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, int&, int& );
		utilities::get( ).get_vfunc<original_fn>( this, 5 )( this, width, height );
	}
	bool is_in_game( ) {
		using original_fn = bool( __thiscall* )( iv_engine_client* );
		return utilities::get( ).get_vfunc<original_fn>( this, 26 )( this );
	}
	bool is_connected( ) {
		using original_fn = bool( __thiscall* )( iv_engine_client* );
		return utilities::get( ).get_vfunc<original_fn>( this, 27 )( this );
	}
	void execute_cmd( const char* cmd ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, const char* );
		utilities::get( ).get_vfunc<original_fn>( this, 108 )( this, cmd );
	}
	void set_view_angles( vector_3d& angles ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, vector_3d& );
		utilities::get( ).get_vfunc<original_fn>( this, 19 )( this, angles );
	}
	vector_3d get_view_angles( ) {
		vector_3d temp;
		using original_fn = void( __thiscall* )( iv_engine_client*, vector_3d& );
		utilities::get( ).get_vfunc<original_fn>( this, 18 )( this, temp );
		return temp;
	}
	bool is_sane( ) {
		return ( this->is_in_game( ) && this->is_connected( ) );
	}
};