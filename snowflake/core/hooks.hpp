#pragma once
#include "../sdk/sdk.hpp"

class hooks : public singleton<hooks> {
public:
	vmt_hook client_hook;
	vmt_hook client_mode_hook;
	vmt_hook panel_hook;
	vmt_hook render_view_hook;

	void initialize( );
	void destroy( );
};