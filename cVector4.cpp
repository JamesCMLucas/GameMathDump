#include "cVector4.h"

float cVector4::Normalize( float tol /*= nMath::EPSILON */ )
{
	float mag2 = x*x + y*y + z*z + w*w;
	if ( mag2 < tol )
	{
		return mag2;
	}

	float magInv = nMath::InverseSqrt( mag2 );
	x *= magInv;
	y *= magInv;
	z *= magInv;
	w *= magInv;

	return mag2;
}

float cVector4::Length() const
{
	return sqrt( x*x + y*y + z*z + w*w );
}

float cVector4::Len2() const
{
	return x*x + y*y + z*z + w*w;
}

float cVector4::Dot( const cVector4& v ) const
{
	return x*v.x + y*v.y + z*v.z + w*v.w;
}

