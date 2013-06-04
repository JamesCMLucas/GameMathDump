#include "cVector3.h"
#include "nMath.h"

float cVector3::Normalize( float tol /*= nMath::EPSILON */ )
{
	float mag2 = x*x + y*y + z*z;
	if ( mag2 < tol )
	{
		return mag2;
	}

	float magInv = nMath::InverseSqrt( mag2 );
	x *= magInv;
	y *= magInv;
	z *= magInv;

	return mag2;
}

float cVector3::Length() const
{
	return sqrt( x*x + y*y + z*z );
}

float cVector3::Len2() const
{
	return ( ( x * x ) + ( y * y ) + ( z * z ) );
}

float cVector3::Dot( const cVector3& vec ) const
{
	return ( ( x * vec.x ) + ( y * vec.y ) + ( z * vec.z ) );
}

cVector3 cVector3::ProjectedOn( const cVector3& vec ) const
{
	float mult = ( ( x * vec.x ) + ( y * vec.y ) + ( z * vec.z ) ) / ( ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) );
	return cVector3( ( vec.x * mult ), ( vec.y * mult), ( vec.z * mult) );
}

cVector3 cVector3::ProjectedOn( const cVector3& v1, const cVector3& v2 ) const
{
	float m1 = ( ( x * v1.x ) + ( y * v1.y ) + ( z * v1.z ) ) / ( ( v1.x * v1.x ) + ( v1.y * v1.y ) + ( v1.z * v1.z ) );
	float m2 = ( ( x * v2.x ) + ( y * v2.y ) + ( z * v2.z ) ) / ( ( v2.x * v2.x ) + ( v2.y * v2.y ) + ( v2.z * v2.z ) );

	return cVector3( (( v1.x * m1 ) + ( v2.x * m2 )), (( v1.y * m1 ) + ( v2.y * m2 )), (( v1.z * m1 ) + ( v2.z * m2 )) );
}

cVector3 cVector3::Cross( const cVector3& v ) const
{
	return cVector3( 
		y*v.z - z*v.y, 
		z*v.x - x*v.z, 
		x*v.y - y*v.x );
}
