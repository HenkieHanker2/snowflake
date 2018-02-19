#pragma once

class chams : public singleton<chams> {
private:
	i_material * chams_mat;

public:
	void setup( ) {
		std::ofstream( "csgo\\materials\\chams_snowflake.vmt" ) << R"#("VertexLitGeneric" {
            "$basetexture" "vgui/white_additive"
            "$ignorez"      "0"
            "$envmap"       ""
            "$nofog"        "1"
            "$model"        "1"
            "$nocull"       "0"
            "$selfillum"    "1"
            "$halflambert"  "1"
            "$znearer"      "0"
            "$flat"         "0"
        })#";

		chams_mat = interfaces::get( ).material_system->find_material( "chams_snowflake", "Model textures", true, NULL );
	}
	void scene_end( ) {
		static bool once = false;
		if ( !once ) {
			this->setup( );
			once = true;
		}

		if ( interfaces::get( ).engine->is_sane( ) && options [ "var.chams" ].get<bool>( ) ) {
			player_t* local = ( player_t* ) interfaces::get( ).entity_list->get_entity( interfaces::get( ).engine->get_local_player( ) );
			if ( local ) {
				for ( int i = 1; i <= interfaces::get( ).globals->max_clients; i++ ) {
					player_t* entity = ( player_t* ) interfaces::get( ).entity_list->get_entity( i );

					if ( i == interfaces::get( ).engine->get_local_player( ) )
						continue;
					if ( !entity )
						continue;
					if ( !entity->is_player( ) )
						continue;
					if ( entity->health( ) <= 0 )
						continue;
					if ( entity->team( ) == local->team( ) && options [ "var.chamsteamcheck" ].get<bool>( ) )
						continue;

					if ( options [ "var.chamshealthbased" ].get<bool>( ) ) {
						const float multiplier = 2.55f;

						int red, green, blue;
						int health = entity->health( );

						red = static_cast< int >( 255 - ( health * multiplier ) );
						green = static_cast< int >( health * multiplier );
						blue = 0;

						chams_mat->set_color( red, green, blue );
					}
					else {
						switch ( entity->team( ) ) {
							case 2:
								chams_mat->set_color( 255, 0, 0 );
								break;
							case 3:
								chams_mat->set_color( 0, 0, 255 );
								break;
							default:
								chams_mat->set_color( 170, 170, 170 );
								break;
						}
					}

					chams_mat->set_flag( material_flags::material_var_ignorez, options [ "var.chamsxqz" ].get<bool>( ) );

					interfaces::get( ).model_render->override_material( chams_mat );
					entity->draw_model( 1, 255 );
					interfaces::get( ).model_render->override_material( nullptr );
				}
			}
		}
	}
};