#pragma once

class interfaces : public singleton<interfaces> {
private:
	template <typename t = void*>
	t get_interface( const char* module_name, const char* interface_name ) {
		using original_fn = void*( *)( const char*, int* );
		original_fn create_interface = ( original_fn ) GetProcAddress( GetModuleHandleA( module_name ), "CreateInterface" );
		return reinterpret_cast< t >( create_interface( interface_name, nullptr ) );
	}

public:
	void initialize( ) {
		this->client = this->get_interface<i_base_client_dll*>( "client.dll", "VClient018" );
		this->engine = this->get_interface<iv_engine_client*>( "engine.dll", "VEngineClient014" );
		this->entity_list = this->get_interface<i_client_entity_list*>( "client.dll", "VClientEntityList003" );
		this->client_mode = **reinterpret_cast< i_client_mode*** >( ( *reinterpret_cast< uintptr_t** >( this->client ) ) [ 10 ] + 5 );
		this->vgui_panel = this->get_interface<i_panel*>( "vgui2.dll", "VGUI_Panel009" );
		this->vgui_surface = this->get_interface<i_surface*>( "vguimatsurface.dll", "VGUI_Surface031" );
		this->trace = this->get_interface<i_engine_trace*>( "engine.dll", "EngineTraceClient004" );
		this->console = this->get_interface<i_console*>( "vstdlib.dll", "VEngineCvar007" );
		this->debug_overlay = this->get_interface<iv_debug_overlay*>( "engine.dll", "VDebugOverlay004" );
		this->globals = **reinterpret_cast< c_global_vars_base*** >( ( *reinterpret_cast< uintptr_t** >( this->client ) [ 0 ] + 27 ) );
		this->model_info = this->get_interface<iv_model_info*>( "engine.dll", "VModelInfoClient004" );
		this->render_view = this->get_interface<iv_render_view*>( "engine.dll", "VEngineRenderView014" );
		this->material_system = this->get_interface<i_material_system*>( "materialsystem.dll", "VMaterialSystem080" );
		this->model_render = this->get_interface<iv_model_render*>( "engine.dll", "VEngineModel016" );
	}

	i_base_client_dll* client;
	iv_engine_client* engine;
	i_client_entity_list* entity_list;
	i_client_mode* client_mode;
	i_panel* vgui_panel;
	i_surface* vgui_surface;
	i_engine_trace* trace;
	i_console* console;
	iv_debug_overlay* debug_overlay;
	c_global_vars_base* globals;
	iv_model_info* model_info;
	iv_render_view* render_view;
	i_material_system* material_system;
	iv_model_render* model_render;
};