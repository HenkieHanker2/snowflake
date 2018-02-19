#pragma once
#include "../classes/material.hpp"

class iv_model_render {
public:
	void override_material( i_material* material ) {
		using original_fn = void( __thiscall* )( iv_model_render*, i_material*, int, int );
		return utilities::get( ).get_vfunc<original_fn>( this, 1 )( this, material, 0, 0 );
	}
};