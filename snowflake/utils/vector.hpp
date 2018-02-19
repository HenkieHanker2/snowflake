#pragma once
#include <limits>

template <typename t>
t clip_number( const t& n, const t& lower, const t& upper ) {
	if ( n < lower ) return lower;
	if ( n > upper ) return upper;
	return n;
}

class vector_3d {
public:
	float x, y, z;

	vector_3d( void ) {
		x = y = z = 0.0f;
	}
	vector_3d( float fx, float fy, float fz ) {
		x = fx;
		y = fy;
		z = fz;
	}
	~vector_3d( void ) { };

	vector_3d& operator+=( const vector_3d& v ) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	vector_3d& operator-=( const vector_3d& v ) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	vector_3d& operator*=( float v ) {
		x *= v; y *= v; z *= v; return *this;
	}
	vector_3d operator+( const vector_3d& v ) {
		return vector_3d { x + v.x, y + v.y, z + v.z };
	}
	vector_3d operator-( const vector_3d& v ) {
		return vector_3d { x - v.x, y - v.y, z - v.z };
	}
	vector_3d operator*( float v ) const {
		return vector_3d { x * v, y * v, z * v };
	}

	float& operator[]( int i ) {
		return ( ( float* ) this ) [ i ];
	}
	float operator[]( int i ) const {
		return ( ( float* ) this ) [ i ];
	}

	void clamp( ) {
		x = clip_number( x, -89.0f, 89.0f );
		y = clip_number( std::remainder( y, 360.0f ), -180.0f, 180.0f );
		z = clip_number( z, -50.0f, 50.0f );
	}
	vector_3d normalized( ) {
		vector_3d vec( *this );
		vec.normalize( );

		return vec;
	}
	void normalize( ) {
		auto vec_normalize = [ & ] ( vector_3d& v ) {
			auto l = v.length( );

			if ( l != 0.0f ) {
				v.x /= l;
				v.y /= l;
				v.z /= l;
			}
			else {
				v.x = v.y = 0.0f; v.z = 1.0f;
			}

			return l;
		};

		vec_normalize( *this );
	}
	float length( ) {
		float root = 0.0f, sqsr = this->length_sqr( );

		__asm        sqrtss xmm0, sqsr
		__asm        movss root, xmm0

		return root;
	}
	float length_sqr( ) {
		auto sqr = [ ] ( float n ) {
			return static_cast< float >( n * n );
		};

		return ( sqr( x ) + sqr( y ) + sqr( z ) );
	}
	float dot( const vector_3d other ) {
		return ( x * other.x + y * other.y + z * other.z );
	}
};

class vector_aligned : public vector_3d {
public:
	vector_aligned( ) { }
	vector_aligned( const vector_3d& vec ) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};

typedef float matrix_t [ 3 ] [ 4 ];