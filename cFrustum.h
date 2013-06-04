#ifndef __cFrustum_HG_20130412__
#define __cFrustum_HG_20130412__

#include "cVector3.h"
#include "cQuaternion.h"
#include "Geometry_Primitives.h"

class cFrustum
{
public:
	cFrustum();
	virtual ~cFrustum();

	void Build( const cVector3& pos, const cQuaternion& quat, float fovX, float fovY, float aspectWdivH, float zNear, float zFar );

	bool TestPoint( const cVector3& point );

	bool TestSphere( const cVector3& centre, float radius );

	static const int Z_NEAR = 0;
	static const int Z_FAR = 1;
	static const int X_LEFT = 2;
	static const int X_RIGHT = 3;
	static const int Y_TOP = 4;
	static const int Y_BOTTOM = 5;
	static const int NUM_PLANES = 6;
	sPlane Planes[6];
	cVector3 LocalFrontUp;
	cVector3 LocalFrontRight;

	cVector3 Points[6];
};

#endif  //  __cFrustum_HG_20130412__