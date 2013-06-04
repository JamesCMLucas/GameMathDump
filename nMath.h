#ifndef __JL_nMath_HG_20130314__
#define __JL_nMath_HG_20130314__

// handy constants, definitions, and inline functions

#include <limits>
#include <cmath>
#include <cstddef>
#include <cfloat>


namespace nMath
{
	/// pi
	const float PI = 3.141592653589793f;

	/// pi multiplied by 2
	const float PI_MUL_2 = 6.283185307179586f;

	/// square root of pi
	const float PI_SQRT = 1.7724538509055159f;

	/// pi divided by 2
	const float PI_DIV_2 = 1.5707963267948966f;

	/// pi divided by 3
	const float PI_DIV_3 = 1.0471975511965976f;

	/// pi divided by 4
	const float PI_DIV_4 = 0.7853981633974483f;

	/// pi divided by 6
	const float PI_DIV_6 = 0.5235987755982988f;

	/// Euler's constant
	const float E = 2.718281828459045f;

	/// golden ratio
	const float GOLDEN_RATIO = 1.61803398875f;

	/// goldent ratio inverse = 1 / GOLDEN_RATIO
	const float GOLDEN_RATIO_INVERSE = 0.6180339887f;

	/// maximum floating point number
	const float MAX_FLOAT = FLT_MAX;
	/// minimum floating point number
	const float MIN_FLOAT = FLT_MIN;
	/// smallest floating point increment
	const float EPSILON = FLT_EPSILON;

	
	/// Returns the larger of a and b
	template <typename A>
	inline A MaxT( A a, A b ) { return a > b ? a : b; }
	/// Returns the larger of a and b
	inline float Max( float a, float b ) { return MaxT<float>( a, b ); }
	/// Returns the larger of a and b
	inline int Max( int a, int b ) { return MaxT<int>( a, b ); }
	/// Returns the larger of a and b
	inline unsigned int Max( unsigned int a, unsigned int b ) { return MaxT<unsigned int>( a, b ); }

	/// Returns the smaller of a and b
	template <typename A>
	inline A MinT( A a, A b ) { return a < b ? a : b; }
	/// Returns the smaller of a and b
	inline float Min( float a, float b ) { return MinT<float>( a, b ); }
	/// Returns the smaller of a and b
	inline int Min( int a, int b ) { return MinT<int>( a, b ); }
	/// Returns the smaller of a and b
	inline unsigned int Min( unsigned int a, unsigned int b ) { return MinT<unsigned int>( a, b ); }

	/// Clamps a value between low and high
	template <typename T>
	inline T ClampT( T a, T low, T high ) { return MaxT<T>( low, Min( a, high ) ); }
	/// Clamps a float between low and high
	inline float Clamp( float a, float low, float high ) { return ClampT<float>( a, low, high ); }
	/// Clamps an int between low and high
	inline int Clamp( int a, int low, int high ) { return ClampT<int>( a, low, high ); }
	/// Clamps an unsigned int between low and high
	inline unsigned int Clamp( unsigned int a, unsigned int low, unsigned int high ) { return ClampT<unsigned int>( a, low, high ); }
	/// Clamps a float between 0 and 1
	inline float Clamp( float a ) { return Clamp( a, 0.f, 1.f ); }

	/// check if a float is NaN
	inline bool IsNaN( float x )
	{
		return ( x != x );
	}

	/// checks if a float is infinity
	inline bool IsInfinity( float x )
	{
		float inf = std::numeric_limits<float>::infinity();
		return ( ( -inf < x ) && ( x < inf ) );
	}

	/// check validity (NaN and Infinity fails)
	inline bool IsValid( float x )
	{
		// check if it's NaN
		if ( IsNaN( x ) )
		{
			return false;
		}

		// check infinites
		if ( IsInfinity( x ) )
		{
			return false;
		}
		return true;
	}

	/// fast inverse square root approximation function
	inline float InverseSqrt( float x )
	{
		long i;
		float y, r;

		y = x * 0.5f;
		i = *(long*)( &x );
		i = 0x5f3759df - ( i >> 1 );
		r = *(float*)( &i );
		r = r * ( 1.5f - r*r*y );
		return r;
	}

	/// Gets the quadrant given a point
	inline int GetQuadrant( float x, float y )
	{
		if ( x >= 0.f )
		{
			if ( y >= 0.f )
			{
				return 1;
			}
			else
			{
				return 4;
			}
		}
		if ( y >= 0.f )
		{
			return 2;
		}
		return 3;
	}

	/// Gets the angle (in radians) from a point
	inline float AngleFromXY( float x, float y )
	{
		float theta = 0.f;
		// Quadrant I or IV
		if( x >= 0.f ) 
		{
			// If x = 0, then atanf(y/x) = +pi/2 if y > 0
			//                atanf(y/x) = -pi/2 if y < 0
			theta = atanf( y / x ); // in [-pi/2, +pi/2]

			if( theta < 0.0f )
			{
				theta += 2.0f * PI; // in [0, 2*pi)
			}
		}
		else
		{	// Quadrant II or III
			theta = atanf( y / x ) + PI;  // in [0, 2*PI)
		}
		return theta;
	}
};


#endif