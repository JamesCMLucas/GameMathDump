#ifndef __JL_cVector2_HG_20130314__
#define __JL_cVector2_HG_20130314__

#include "nMath.h"

class cVector2
{
public:
	union
	{
		struct 
		{
			float x, y;
		};
		struct
		{
			float u, v;
		};
	};

	cVector2() : x(0.f), y(0.f) {};
	cVector2( const cVector2& v ) : x(v.x), y(v.y) {};
	cVector2( float x_u, float y_v ) : x(x_u), y(y_v) {}
	~cVector2() {};
	
	cVector2& operator = ( const cVector2& vec );

	cVector2& operator += ( const cVector2& vec );
	cVector2& operator -= ( const cVector2& vec );
	cVector2& operator *= ( const cVector2& vec );
	cVector2& operator /= ( const cVector2& vec );

	cVector2& operator += ( float val );
	cVector2& operator -= ( float val );
	cVector2& operator *= ( float val );
	cVector2& operator /= ( float val );

	float& operator [] ( int i );
	const float& operator [] ( int i ) const;

	/// Normalizes this vector and returns the square length
	float Normalize( float tol = nMath::EPSILON );
	void Zeroes();
	void Ones();

	float Length() const;
	float Len2() const;
	float Dot( const cVector2& vec ) const;

	cVector2 ProjectedOn( const cVector2& vec );
};

typedef cVector2 cUVCoord;
typedef cVector2 cTexCoord;

inline cVector2& cVector2::operator=( const cVector2& vec )
{
	if ( this != &vec )
	{
		x = vec.x;
		y = vec.y;
	}
	return *this;
}


inline cVector2& cVector2::operator+=( const cVector2& v )
{
	x += v.x;
	y += v.y;
	return *this;
}

inline cVector2& cVector2::operator-=( const cVector2& v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline cVector2& cVector2::operator*=( const cVector2& v )
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline cVector2& cVector2::operator/=( const cVector2& v )
{
	x /= v.x;
	y /= v.y;
	return *this;
}


inline cVector2& cVector2::operator+=( float val )
{
	x += val;
	y += val;
	return *this;
}

inline cVector2& cVector2::operator-=( float val )
{
	x -= val;
	y -= val;
	return *this;
}

inline cVector2& cVector2::operator*=( float val )
{
	x *= val;
	y *= val;
	return *this;
}

inline cVector2& cVector2::operator/=( float val )
{
	x /= val;
	y /= val;
	return *this;
}


inline float& cVector2::operator[]( int i )
{
	return ( &x )[i];
}

inline const float& cVector2::operator[]( int i ) const
{
	return ( &x )[i];
}

inline void cVector2::Zeroes()
{
	x = 0.f;
	y = 0.f;
}

inline void cVector2::Ones()
{
	x = 1.f;
	y = 1.f;
}


inline cVector2 operator+( const cVector2& vL, const cVector2& vR )
{
	return cVector2( ( vL.x + vR.x ), ( vL.y + vR.y ) );
}

inline cVector2 operator-( const cVector2& vL, const cVector2& vR )
{
	return cVector2( ( vL.x - vR.x ), ( vL.y - vR.y ) );
}

inline cVector2 operator*( const cVector2& vL, const cVector2& vR )
{
	return cVector2( ( vL.x * vR.x ), ( vL.y * vR.y ) );
}

inline cVector2 operator*( const cVector2& vL, float val )
{
	return cVector2( ( vL.x * val ), ( vL.y * val) );
}

inline cVector2 operator/( const cVector2& vL, const cVector2& vR )
{
	return cVector2( ( vL.x / vR.x ), ( vL.y / vR.y ) );
}

inline cVector2 operator/( const cVector2& vL, float val )
{
	return cVector2( ( vL.x / val ), ( vL.y / val) );
}

// Max Min stuff
namespace nMath
{
	/// Returns a vector containing the component-wise smaller values of either vector
	inline cVector2 Min( const cVector2& a, const cVector2& b )
	{
		return cVector2( Min( a.x, b.x ), Min( a.y, b.y ) );
	}

	/// Returns a vector containing the component-wise larger values of either vector
	inline cVector2 Max( const cVector2& a, const cVector2& b )
	{
		return cVector2( Max( a.x, b.x ), Max( a.y, b.y ) );
	}

	/// Returns a vector with each component's value clamped between 0 and 1
	inline cVector2 Clamp( const cVector2& a )
	{
		return cVector2( Clamp( a.x ), Clamp( a.y ) );
	}

	/// Returns a vector with each component's value clamped between the the values of the low and high vector
	inline cVector2 Clamp( const cVector2& a, const cVector2& low, const cVector2& high )
	{
		return Max( low, Min( a, high ) );
	}
};


#endif // __JL_cVector2_HG_20130314__