#ifndef __JL_Geometry_Primitives_HG_20130314__
#define __JL_Geometry_Primitives_HG_20130314__

#include "cVector3.h"

// a line from defined by two points
struct sLineSegment
{
	sLineSegment() : A(), B() {}
	sLineSegment( const cVector3& a, const cVector3& b ) : A(a), B(b) {}
	cVector3 A, B;
};

// a triangle defined by three points ccw orientation
struct sTriangle
{
	sTriangle() : A(), B(), C() {}
	sTriangle( const cVector3& a, const cVector3& b, const cVector3& c )
		: A(a), B(b), C(c) {}
	cVector3 A, B, C;
};

// a rectangle defined by a centre position, local axes, and halfwidths
struct sRectangle
{
	cVector3 Centre;
	cVector3 LocalXAxis;
	cVector3 LocalYAxis;
	float HalfWidthX;
	float HalfWidthY;
};

// a quad definied by 4 points
struct sQuad 
{
	sQuad() : A(), B(), C(), D() {}
	sQuad( const cVector3& a, const cVector3& b, const cVector3& c, const cVector3& d )
		: A(a), B(b), C(c), D(d) {}
	cVector3 A, B, C, D;
};

inline sQuad RectangleToQuad( const sRectangle& r )
{
	cVector3 x = r.LocalXAxis * r.HalfWidthX;
	cVector3 y = r.LocalYAxis * r.HalfWidthY;

	sQuad q;
	
	q.A = r.Centre - x - y;
	q.B = r.Centre + x - y;
	q.C = r.Centre + x + y;
	q.D = r.Centre - x + y;
	
	return q;
}

/// a plane
/// use of the vector and float values vary
struct sPlane
{
	sPlane() : vec(), val(0) {}
	sPlane( const cVector3& v, float f ) : vec(v), val(f) {}
	
	cVector3 vec;
	float val;
};


/// a ray defined by a point and a direction
struct sRay
{
	sRay() : Direction(0.f,1.f,0.f) {}
	sRay( const cVector3& p, const cVector3& d ) : Position(p), Direction(d) {}
	
	cVector3 Position;
	cVector3 Direction;
};

/// a sphere defined by a centre point and a radius
struct sSphere
{
	sSphere() : Centre(), Radius(1.f) {}
	sSphere( const cVector3& c, float r ) : Centre(c), Radius(r) {}
	cVector3 Centre;
	float Radius;
};

/// a sphere-swept line defined by two points and a radius
struct sSphereSweptLine
{
	sSphereSweptLine() : Radius(1.f) {}
	sSphereSweptLine( const cVector3& a, const cVector3& b, float r )
		: A(a), B(b), Radius(r) {}
	cVector3 A;
	cVector3 B;
	/// Radius of the sweeping sphere
	float Radius;
};

/// an axis aligned box defined by max and min values
struct sAxisAlignedBox 
{
	sAxisAlignedBox() : Max(), Min() {}
	sAxisAlignedBox( const cVector3& max, const cVector3& min ) : Max(max), Min(min) {}
	/// Maximum values
	cVector3 Max;
	/// Minimum values
	cVector3 Min;
};

/// an oriented box defined by a centre point, local axes, and half-widths
struct sOrientedBox 
{
	sOrientedBox() 
		: Centre()
		, LocalXAxis(1.f,0.f,0.f)
		, LocalYAxis(0.f,1.f,0.f)
		, LocalZAxis(0.f,0.f,1.f)
		, HalfWidths(0.5f,0.5f,0.5f) {}
	sOrientedBox( const cVector3& c, const cVector3& xAxis, const cVector3& yAxis, const cVector3& zAxis, const cVector3& hw )
		: Centre(c), LocalXAxis(xAxis), LocalYAxis(yAxis), LocalZAxis(zAxis), HalfWidths(hw) {}
	/// The centre position of the cuboid
	cVector3 Centre;
	/// Local x-axis
	cVector3 LocalXAxis;
	/// Local y-axis
	cVector3 LocalYAxis;
	/// Local z-axis
	cVector3 LocalZAxis;
	/// Half-widths
	cVector3 HalfWidths;
};



#endif  //  __JL_Geometry_Primitives_HG_20130314__