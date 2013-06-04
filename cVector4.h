#ifndef __JL_cVector4_HG_20130314__
#define __JL_cVector4_HG_20130314__

#include "cVector3.h"

class cVector4
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
	union
	{
		float w;
		float a;
	};

	cVector4() : x(0.f), y(0.f), z(0.f), w(0.f) {};
	cVector4( float x_r, float y_g, float z_b, float w_a )
		: x(x_r), y(y_g), z(z_b), w(w_a) {}
	cVector4( const cVector2& v1, const cVector2& v2 ) : x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
	cVector4( const cVector3& v ) : x(v.x), y(v.y), z(v.z), w(1.f) {}
	cVector4( const cVector3& v, float w_a ) : x(v.x), y(v.y), z(v.z), w(w_a) {}
	cVector4( const cVector4& v ) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	~cVector4() {};

	cVector4& operator = ( const cVector4& vec );

	cVector4& operator += ( const cVector4& vec );
	cVector4& operator -= ( const cVector4& vec );
	cVector4& operator *= ( const cVector4& vec );
	cVector4& operator /= ( const cVector4& vec );

	cVector4& operator += ( float val );
	cVector4& operator -= ( float val );
	cVector4& operator *= ( float val );
	cVector4& operator /= ( float val );

	float& operator [] ( int i );
	const float& operator [] ( int i ) const;

	/// Normalizes this vector and returns the square length
	float Normalize( float tol = nMath::EPSILON );
	void Zeroes();
	void Ones();

	float Length() const;
	float Len2() const;
	float Dot( const cVector4& v ) const;
};

typedef cVector4 cColour4;


inline cVector4& cVector4::operator=( const cVector4& vec )
{
	if ( this != &vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}
	return *this;
}


inline cVector4& cVector4::operator+=( const cVector4& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.z;
	return *this;
}

inline cVector4& cVector4::operator-=( const cVector4& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

inline cVector4& cVector4::operator*=( const cVector4& v )
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

inline cVector4& cVector4::operator/=( const cVector4& v )
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}


inline cVector4& cVector4::operator+=( float val )
{
	x += val;
	y += val;
	z += val;
	w += val;
	return *this;
}

inline cVector4& cVector4::operator-=( float val )
{
	x -= val;
	y -= val;
	z -= val;
	w -= val;
	return *this;
}

inline cVector4& cVector4::operator*=( float val )
{
	x *= val;
	y *= val;
	z *= val;
	w *= val;
	return *this;
}

inline cVector4& cVector4::operator/=( float val )
{
	x /= val;
	y /= val;
	z /= val;
	w /= val;
	return *this;
}


inline float& cVector4::operator[]( int i )
{
	return ( &x )[i];
}

inline const float& cVector4::operator[]( int i ) const
{
	return ( &x )[i];
}


inline void cVector4::Zeroes()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

inline void cVector4::Ones()
{
	x = 1.f;
	y = 1.f;
	z = 1.f;
	w = 1.f;
}


inline cVector4 operator+( const cVector4& vL, const cVector4& vR )
{
	return cVector4( ( vL.x + vR.x ), ( vL.y + vR.y ), ( vL.z + vR.z ), ( vL.w + vR.w ) );
}

inline cVector4 operator+( const cVector4& vL, float val )
{
	return cVector4( ( vL.x + val ), ( vL.y + val ), ( vL.z + val ), ( vL.w + val ) );
}

inline cVector4 operator-( const cVector4& vL, const cVector4& vR )
{
	return cVector4( ( vL.x - vR.x ), ( vL.y - vR.y ), ( vL.z - vR.z ), ( vL.w - vR.w ) );
}

inline cVector4 operator-( const cVector4& vL, float val )
{
	return cVector4( ( vL.x - val ), ( vL.y - val ), ( vL.z - val ), ( vL.w - val ) );
}

inline cVector4 operator*( const cVector4& vL, const cVector4& vR )
{
	return cVector4( ( vL.x * vR.x ), ( vL.y * vR.y ), ( vL.z * vR.z ), ( vL.w * vR.w ) );
}

inline cVector4 operator*( const cVector4& vL, float val )
{
	return cVector4( ( vL.x * val ), ( vL.y * val ), ( vL.z * val ), ( vL.w * val ) );
}

inline cVector4 operator/( const cVector4& vL, const cVector4& vR )
{
	return cVector4( ( vL.x / vR.x ), ( vL.y / vR.y ), ( vL.z / vR.z ), ( vL.w / vR.w ) );
}

inline cVector4 operator/( const cVector4& vL, float val )
{
	return cVector4( ( vL.x / val ), ( vL.y / val ), ( vL.z / val ), ( vL.w / val ) );
}

/// Min Max stuff
namespace nMath
{
	/// Returns a vector containing the component-wise smaller values of either vector
	inline cVector4 Min( const cVector4& a, const cVector4& b )
	{
		return cVector4( Min( a.x, b.x ), Min( a.y, b.y ), Min( a.z, b.z ), Min( a.w, b.w ) );
	}

	/// Returns a vector containing the component-wise larger values of either vector
	inline cVector4 Max( const cVector4& a, const cVector4& b )
	{
		return cVector4( Max( a.x, b.x ), Max( a.y, b.y ), Max( a.z, b.z ), Max( a.w, b.w ) );
	}

	/// Returns a vector with each component's value clamped between 0 and 1
	inline cVector4 Clamp( const cVector4& a )
	{
		return cVector4( Clamp( a.x ), Clamp( a.y ), Clamp( a.z ), Clamp( a.w ) );
	}

	/// Returns a vector with each component's value clamped between the the values of the low and high vector
	inline cVector4 Clamp( const cVector4& a, const cVector4& low, const cVector4& high )
	{
		return Max( low, Min( a, high ) );
	}
};

#endif  // __JL_cVector4_HG_20130314__