#include "cVector2.h"
#include "nMath.h"

float cVector2::Normalize( float tol /*= nMath::EPSILON */ )
{
	float mag2 = x*x + y*y;
	if ( mag2 < tol )
	{
		return mag2;
	}

	float magInv = nMath::InverseSqrt( mag2 );
	x *= magInv;
	y *= magInv;

	return mag2;
}

float cVector2::Length() const
{
	return sqrt( x*x + y*y );
}

float cVector2::Len2() const
{
	return ( ( x * x ) + ( y * y ) );
}

float cVector2::Dot( const cVector2& vec ) const
{
	return ( ( x * vec.x ) + ( y * vec.y ) );
}

cVector2 cVector2::ProjectedOn( const cVector2& vec )
{
	float mult = ( ( x * vec.x ) + ( y * vec.y ) ) / ( ( vec.x * vec.x ) + ( vec.y * vec.y ) );
	return cVector2( ( vec.x * mult ), ( vec.y * mult ) );
}
