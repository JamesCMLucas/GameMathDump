#include "cFrustum.h"


cFrustum::cFrustum()
{

}

cFrustum::~cFrustum()
{

}

void cFrustum::Build( const cVector3& pos, const cQuaternion& quat, float fovX, float fovY, float aspectWdivH, float zNear, float zFar )
{
	cVector3 localX = quat.GetLocalXAxis();
	cVector3 localY = quat.GetLocalYAxis();
	cVector3 localZ = quat.GetLocalZAxis();
	float halfDist = ( zFar + zNear )*0.5f;
	float tanHalfFovY = tan( fovY * 0.5f );
	//float fovX = atan( ( tanHalfFovY * aspectWdivH ) * 2.f );
	float tanHalfFovX = tan( fovX * 0.5f );

	LocalFrontUp = localY * ( tanHalfFovY * zNear );
	LocalFrontRight = localX * ( tanHalfFovX * zNear );

	cQuaternion qRot;	// rotation for left/right/top/bottom
	cVector3 point;		// a point on the plane


	// near plane:
	point = pos + ( localZ * zNear );
	Points[Z_NEAR] = point;
	Planes[Z_NEAR].vec = localZ;
	Planes[Z_NEAR].val = point.Dot( Planes[Z_NEAR].vec );


	// far plane:
	point = pos + ( localZ * zFar );
	Points[Z_FAR] = point;
	Planes[Z_FAR].vec = localZ*(-1.f);
	Planes[Z_FAR].val = point.Dot( Planes[Z_FAR].vec );


	// right plane
	qRot.FromAxisRotation( localY, ( fovX * 0.5f ) );
	point = ( localZ * halfDist );
	point = qRot.AppliedTo( point );
	point += pos;
	Points[X_RIGHT] = point;
	Planes[X_RIGHT].vec = qRot.AppliedTo( localX*(-1.f) );
	Planes[X_RIGHT].val = point.Dot( Planes[X_RIGHT].vec );

	// left plane
	qRot.FromAxisRotation( localY, -( fovX * 0.5f ) );
	point = ( localZ * halfDist );
	point = qRot.AppliedTo( point );
	point += pos;
	Points[X_LEFT] = point;
	Planes[X_LEFT].vec = qRot.AppliedTo( localX );
	Planes[X_LEFT].val = point.Dot( Planes[X_LEFT].vec );


	// top plane
	qRot.FromAxisRotation( localX, -( fovY * 0.5f ) );
	point = ( localZ * halfDist );
	point = qRot.AppliedTo( point );
	point += pos;
	Points[Y_TOP] = point;
	Planes[Y_TOP].vec = qRot.AppliedTo( localY*(-1.f) );
	Planes[Y_TOP].val = point.Dot( Planes[Y_TOP].vec );

	// bottom plane
	qRot.FromAxisRotation( localX, ( fovY * 0.5f ) );
	point = ( localZ * halfDist );
	point = qRot.AppliedTo( point );
	point += pos;
	Points[Y_BOTTOM] = point;

	Planes[Y_BOTTOM].vec = qRot.AppliedTo( localY );
	Planes[Y_BOTTOM].val = point.Dot( Planes[Y_BOTTOM].vec );
}

bool cFrustum::TestPoint( const cVector3& point )
{
	if ( point.x > -10.f && point.x < 10.f )
	{
		if ( point.z > 50.f )
		{
			bool imbreaking = true;
		}
	}
	float dist = 0.f;
	for ( int i = 0; i < NUM_PLANES; i++ )
	{
		dist = point.Dot( Planes[i].vec ) - Planes[i].val;
		if ( dist > - Planes[i].val )
		{
			bool what = true;
		}
		if ( dist < 0.f ) return false;
	}
	return true;
}

bool cFrustum::TestSphere( const cVector3& centre, float radius )
{
	for ( int i = 0; i < NUM_PLANES; i++ )
	{
		float dist = centre.Dot( Planes[i].vec ) - Planes[i].val;
		if ( dist < -radius ) return false;
	}
	return true;
}
