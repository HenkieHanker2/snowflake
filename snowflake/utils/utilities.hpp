#pragma once
#include "vector.hpp"
#define M_PI 3.14159265358979323846

class utilities : public singleton<utilities> {
public:
	void create_console( ) {
		AllocConsole( );
		freopen_s( ( FILE** ) stdin, "CONIN$", "r", stdin );
		freopen_s( ( FILE** ) stdout, "CONOUT$", "w", stdout );
		freopen_s( ( FILE** ) stderr, "CONERR$", "w", stderr );
	}
	void destroy_console( ) {
		fclose( stdin );
		fclose( stdout );
		fclose( stderr );
		FreeConsole( );
	}
	void print_to_console( const char* fmt, ... ) {

	}

	template <typename t>
	t get_vfunc( void* class_pointer, size_t index ) {
		return ( *( t** ) class_pointer ) [ index ];
	}

	template <typename t>
	bool is_in_bounds( t min, t max, t value ) {
		return ( value > min && value < max );
	}

	vector_3d angle_vector( vector_3d to_convert ) {
		auto y_sin = sin( to_convert.y / 180.f * static_cast< float >( M_PI ) );
		auto y_cos = cos( to_convert.y / 180.f * static_cast< float >( M_PI ) );

		auto x_sin = sin( to_convert.x / 180.f * static_cast< float >( M_PI ) );
		auto x_cos = cos( to_convert.x / 180.f * static_cast< float >( M_PI ) );

		return vector_3d( x_cos * y_cos, x_cos * y_sin, -x_sin );
	}
	float distance_point_to_line( vector_3d point, vector_3d origin, vector_3d direction ) {
		auto delta = point - origin;

		auto temp = delta.dot( direction ) / ( direction.x * direction.x + direction.y * direction.y + direction.z * direction.z );
		if ( temp < 0.000001f )
			return FLT_MAX;

		auto temp_meme = origin + ( direction * temp );
		return ( point - temp_meme ).length( );
	}
};