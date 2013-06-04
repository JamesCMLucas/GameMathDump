#ifndef __JL_cVector3_HG_20130314__
#define __JL_cVector3_HG_20130314__

#include "cVector2.h"

class cVector3
{
public:
	union
	{
		float x;
		float r;
	};
	union
	{
		float y;
		float g;
	};
	union
	{
		float z;
		float b;
	};

	cVector3() : x(0.f), y(0.f), z(0.f) {}
	cVector3( const cVector2& v ) : x(v.x), y(v.y), z(0.f) {}
	cVector3( const cVector2& v, float z_b ) : x(v.x), y(v.y), z(z_b) {}
	cVector3( const cVector3& v ) : x(v.x), y(v.y), z(v.z) {}
	cVector3( float x_r, float y_g, float z_b ) : x(x_r), y(y_g), z(z_b) {}

	~cVector3() {};
	
	cVector3& operator = ( const cVector3& vec );

	cVector3& operator += ( const cVector3& vec );
	cVector3& operator -= ( const cVector3& vec );
	cVector3& operator *= ( const cVector3& vec );
	cVector3& operator /= ( const cVector3& vec );

	cVector3& operator += ( float val );
	cVector3& operator -= ( float val );
	cVector3& operator *= ( float val );
	cVector3& operator /= ( float val );

	float& operator [] ( int i );
	const float& operator [] ( int i ) const;
	
	/// Normalizes this vector and returns the square length
	float Normalize( float tol = nMath::EPSILON );
	void Zeroes();
	void Ones();

	float Length() const;
	float Len2() const;
	float Dot( const cVector3& vec ) const;

	cVector3 Cross( const cVector3& v ) const;

	cVector3 ProjectedOn( const cVector3& vec ) const;
	cVector3 ProjectedOn( const cVector3& v1, const cVector3& v2 ) const;
};

typedef cVector3 cColour3;

inline cVector3& cVector3::operator=( const cVector3& vec )
{
	if ( this != &vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	return *this;
}


inline cVector3& cVector3::operator+=( const cVector3& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline cVector3& cVector3::operator-=( const cVector3& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline cVector3& cVector3::operator*=( const cVector3& v )
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline cVector3& cVector3::operator/=( const cVector3& v )
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}


inline cVector3& cVector3::operator+=( float val )
{
	x += val;
	y += val;
	z += val;
	return *this;
}

inline cVector3& cVector3::operator-=( float val )
{
	x -= val;
	y -= val;
	z -= val;
	return *this;
}

inline cVector3& cVector3::operator*=( float val )
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

inline cVector3& cVector3::operator/=( float val )
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}


inline float& cVector3::operator[]( int i )
{
	return ( &x )[i];
}

inline const float& cVector3::operator[]( int i ) const
{
	return ( &x )[i];
}

inline void cVector3::Zeroes()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

inline void cVector3::Ones()
{
	x = 1.f;
	y = 1.f;
	z = 1.f;
}



inline cVector3 operator+( const cVector3& vL, const cVector3& vR )
{
	return cVector3( ( vL.x + vR.x ), ( vL.y + vR.y ), ( vL.z + vR.z ) );
}

inline cVector3 operator-( const cVector3& vL, const cVector3& vR )
{
	return cVector3( ( vL.x - vR.x ), ( vL.y - vR.y ), ( vL.z - vR.z ) );
}

inline cVector3 operator*( const cVector3& vL, const cVector3& vR )
{
	return cVector3( ( vL.x * vR.x ), ( vL.y * vR.y ), ( vL.z * vR.z ) );
}

inline cVector3 operator/( const cVector3& vL, const cVector3& vR )
{
	return cVector3( ( vL.x / vR.x ), ( vL.y / vR.y ), ( vL.z / vR.z ) );
}

inline cVector3 operator+( const cVector3& v, float f )
{
	return cVector3( ( v.x + f ), ( v.y + f ), ( v.z + f ) );
}

inline cVector3 operator-( const cVector3& v, float f )
{
	return cVector3( ( v.x - f ), ( v.y - f ), ( v.z - f ) );
}

inline cVector3 operator*( const cVector3& v, float f )
{
	return cVector3( ( v.x * f ), ( v.y * f ), ( v.z * f ) );
}

inline cVector3 operator/( const cVector3& v, float f )
{
	return cVector3( ( v.x / f ), ( v.y / f ), ( v.z / f ) );
}

/// Min Max stuff
namespace nMath
{
	/// Returns a vector containing the component-wise smaller values of either vector
	inline cVector3 Min( const cVector3& a, const cVector3& b )
	{
		return cVector3( Min( a.x, b.x ), Min( a.y, b.y ), Min( a.z, b.z ) );
	}

	/// Returns a vector containing the component-wise larger values of either vector
	inline cVector3 Max( const cVector3& a, const cVector3& b )
	{
		return cVector3( Max( a.x, b.x ), Max( a.y, b.y ), Max( a.z, b.z ) );
	}

	/// Returns a vector with each component's value clamped between 0 and 1
	inline cVector3 Clamp( const cVector3& a )
	{
		return cVector3( Clamp( a.x ), Clamp( a.y ), Clamp( a.z ) );
	}

	/// Returns a vector with each component's value clamped between the the values of the low and high vector
	inline cVector3 Clamp( const cVector3& a, const cVector3& low, const cVector3& high )
	{
		return Max( low, Min( a, high ) );
	}
};

#endif  // __JL_cVector3_HG_20130314__