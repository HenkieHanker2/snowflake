#pragma once

namespace vgui {
	using font = unsigned int;
	using panel = unsigned long;
}

class i_panel {
public:
	const char* get_name( vgui::panel panel ) {
		using get_name_t = const char*( __thiscall* )( void*, vgui::panel );
		return utilities::get( ).get_vfunc<get_name_t>( this, 36 )( this, panel );
	}
};