#ifndef __JL_cMatrix4x4_HG_20130314__
#define __JL_cMatrix4x4_HG_20130314__

#include "cQuaternion.h"
#include "cMatrix3x3.h"
#include "Geometry_Primitives.h"

class cMatrix4x4
{
public:
	union
	{
		float mn[4][4];
		float m[16];
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
	};

	// initializes to identity
	cMatrix4x4()
		: m00(1.f), m01(0.f), m02(0.f), m03(0.f)
		, m10(0.f), m11(1.f), m12(0.f), m13(0.f)
		, m20(0.f), m21(0.f), m22(1.f), m23(0.f)
		, m30(0.f), m31(0.f), m32(0.f), m33(1.f) {}
	cMatrix4x4( float* mIn );
	cMatrix4x4( const cVector4& v0, const cVector4& v1, const cVector4& v2, const cVector4& v3 )
		: m00(v0.x), m01(v0.y), m02(v0.z), m03(v0.w)
		, m10(v1.x), m11(v1.y), m12(v1.z), m13(v1.w)
		, m20(v2.x), m21(v2.y), m22(v2.z), m23(v2.w)
		, m30(v3.x), m31(v3.y), m32(v3.z), m33(v3.w) {}
	cMatrix4x4( 
		float a00, float a01, float a02, float a03, 
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33 )
		: m00(a00), m01(a01), m02(a02), m03(a03)
		, m10(a10), m11(a11), m12(a12), m13(a13)
		, m20(a20), m21(a21), m22(a22), m23(a23)
		, m30(a30), m31(a31), m32(a32), m33(a33) {}
	cMatrix4x4( const cMatrix3x3& mat )
		: m00(mat.m00), m01(mat.m01), m02(mat.m02), m03(0.f)
		, m10(mat.m10), m11(mat.m11), m12(mat.m12), m13(0.f)
		, m20(mat.m20), m21(mat.m21), m22(mat.m22), m23(0.f)
		, m30(0.f), m31(0.f), m32(0.f), m33(1.f) {}
	cMatrix4x4( const cMatrix4x4& mat )
		: m00(mat.m00), m01(mat.m01), m02(mat.m02), m03(mat.m03)
		, m10(mat.m10), m11(mat.m11), m12(mat.m12), m13(mat.m13)
		, m20(mat.m20), m21(mat.m21), m22(mat.m22), m23(mat.m23)
		, m30(mat.m30), m31(mat.m31), m32(mat.m32), m33(mat.m33) {}
	~cMatrix4x4() {};

	float GetDeterminant() const;
	cMatrix4x4 Transpose() const;
	void Translate( const cVector3& vt );
	void Translate( float x, float y, float z );
	void SetTranslation( const cVector3& vt );
	void SetTranslation( float x, float y, float z );

	cMatrix4x4& operator = ( const cMatrix4x4& mat );
	cMatrix4x4& operator += ( const cMatrix4x4& mat );
	cMatrix4x4& operator -= ( const cMatrix4x4& mat );
	cMatrix4x4& operator *= ( const cMatrix4x4& mat );
	float& operator () ( int i, int j );
	const float& operator () ( int i, int j ) const;
	
	static cMatrix4x4 Ones();
	static cMatrix4x4 Zeroes();
	static cMatrix4x4 Identity();
	static cMatrix4x4 Inverse( const cMatrix4x4& mat );
	static cMatrix4x4 Transpose( const cMatrix4x4& mat );
	static cMatrix4x4 InverseTranspose( const cMatrix4x4& mat );

	static cMatrix4x4 Scaling( float scale );
	static cMatrix4x4 Scaling( float sx, float sy, float sz );
	static cMatrix4x4 Scaling( const cVector3& vs );

	static cMatrix4x4 RotationX( float rad );
	static cMatrix4x4 RotationY( float rad );
	static cMatrix4x4 RotationZ( float rad );
	static cMatrix4x4 Rotation( const cVector3& axis, float rad );
	static cMatrix4x4 Rotation( const cQuaternion& q );

	static cMatrix4x4 Translation( float x, float y, float z );
	static cMatrix4x4 Translation( const cVector3& vt );

	static cMatrix4x4 ViewLH( const cVector3& eye, const cVector3& at, const cVector3& up );
	static cMatrix4x4 ViewLH( const cVector3& pos, const cQuaternion& rot );
	static cMatrix4x4 ViewRH( const cVector3& eye, const cVector3& at, const cVector3& up );
	static cMatrix4x4 ViewRH( const cVector3& pos, const cQuaternion& rot );

	static cMatrix4x4 OrthogonalProjectionLH( float width, float height, float zNear, float zFar );
	static cMatrix4x4 OrthogonalProjectionRH( float width, float height, float zNear, float zFar );
	static cMatrix4x4 OrthogonalOffCentreProjectionLH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ );
	static cMatrix4x4 OrthogonalOffCentreProjectionRH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ );

	static cMatrix4x4 PerspectiveProjectionLH( float zFar, float zNear, float aspectWdivH, float fovH );
	static cMatrix4x4 PerspectiveProjectionRH( float zFar, float zNear, float aspectWdivH, float fovH );
	static cMatrix4x4 PerspectiveOffCentreProjectionLH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ );
	static cMatrix4x4 PerspectiveOffCentreProjectionRH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ );

	static cMatrix4x4 PerspectiveObliqueProjectionLH( float left, float right, float top, float bottom, float nearZ, float farZ );

	static cMatrix4x4 WorldLH( const cVector3& pos, const cQuaternion& rot );
	static cMatrix4x4 WorldLH( const cVector3& pos, const cQuaternion& rot, const cVector3& scale );

	static cMatrix4x4 ShadowTransform( const sPlane& plane, const cVector3& light, bool bIsDirectional );
	static cMatrix4x4 ShadowTransform( const cVector4& plane, const cVector3& light, bool bIsDirectional );

	static cMatrix4x4 ReflectionMatrix( const sPlane& plane );
	static cMatrix4x4 ReflectionMatrix( const cVector4& plane );
};

inline float& cMatrix4x4::operator () ( int i, int j )
{
	return mn[i][j];
}

inline const float& cMatrix4x4::operator () ( int i, int j ) const
{
	return mn[i][j];
}

inline cMatrix4x4& cMatrix4x4::operator = ( const cMatrix4x4& mat )
{
	if ( this != &mat )
	{
		m00 = mat.m00;  m01 = mat.m01;  m02 = mat.m02;  m03 = mat.m03;
		m10 = mat.m10;  m11 = mat.m11;  m12 = mat.m12;  m13 = mat.m13;
		m20 = mat.m20;  m21 = mat.m21;  m22 = mat.m22;  m23 = mat.m23;
		m30 = mat.m30;  m31 = mat.m31;  m32 = mat.m32;  m33 = mat.m33;
	}
	return *this;
}

inline cMatrix4x4& cMatrix4x4::operator += ( const cMatrix4x4& mat )
{
	m00 += mat.m00;  m01 += mat.m01;  m02 += mat.m02;  m03 += mat.m03;
	m10 += mat.m10;  m11 += mat.m11;  m12 += mat.m12;  m13 += mat.m13;
	m20 += mat.m20;  m21 += mat.m21;  m22 += mat.m22;  m23 += mat.m23;
	m30 += mat.m30;  m31 += mat.m31;  m32 += mat.m32;  m33 += mat.m33;
	return *this;
}

inline cMatrix4x4& cMatrix4x4::operator -= ( const cMatrix4x4& mat )
{
	m00 -= mat.m00;  m01 -= mat.m01;  m02 -= mat.m02;  m03 -= mat.m03;
	m10 -= mat.m10;  m11 -= mat.m11;  m12 -= mat.m12;  m13 -= mat.m13;
	m20 -= mat.m20;  m21 -= mat.m21;  m22 -= mat.m22;  m23 -= mat.m23;
	m30 -= mat.m30;  m31 -= mat.m31;  m32 -= mat.m32;  m33 -= mat.m33;
	return *this;
}

inline cMatrix4x4& cMatrix4x4::operator *= ( const cMatrix4x4& mat )
{
	cMatrix4x4 m;

	m.m00 = m00*mat.m00 + m01*mat.m10 + m02*mat.m20 + m03*mat.m30;
	m.m01 = m00*mat.m01 + m01*mat.m11 + m02*mat.m21 + m03*mat.m31;
	m.m02 = m00*mat.m02 + m01*mat.m12 + m02*mat.m22 + m03*mat.m32;
	m.m03 = m00*mat.m03 + m01*mat.m13 + m02*mat.m23 + m03*mat.m33;

	m.m10 = m10*mat.m00 + m11*mat.m10 + m12*mat.m20 + m13*mat.m30;
	m.m11 = m10*mat.m01 + m11*mat.m11 + m12*mat.m21 + m13*mat.m31;
	m.m12 = m10*mat.m02 + m11*mat.m12 + m12*mat.m22 + m13*mat.m32;
	m.m13 = m10*mat.m03 + m11*mat.m13 + m12*mat.m23 + m13*mat.m33;

	m.m20 = m20*mat.m00 + m21*mat.m10 + m22*mat.m20 + m23*mat.m30;
	m.m21 = m20*mat.m01 + m21*mat.m11 + m22*mat.m21 + m23*mat.m31;
	m.m22 = m20*mat.m02 + m21*mat.m12 + m22*mat.m22 + m23*mat.m32;
	m.m23 = m20*mat.m03 + m21*mat.m13 + m22*mat.m23 + m23*mat.m33;

	m.m30 = m30*mat.m00 + m31*mat.m10 + m32*mat.m20 + m33*mat.m30;
	m.m31 = m30*mat.m01 + m31*mat.m11 + m32*mat.m21 + m33*mat.m31;
	m.m32 = m30*mat.m02 + m31*mat.m12 + m32*mat.m22 + m33*mat.m32;
	m.m33 = m30*mat.m03 + m31*mat.m13 + m32*mat.m23 + m33*mat.m33;

	m00 = m.m00;  m01 = m.m01;  m02 = m.m02;  m03 = m.m03;
	m10 = m.m10;  m11 = m.m11;  m12 = m.m12;  m13 = m.m13;
	m20 = m.m20;  m21 = m.m21;  m22 = m.m22;  m23 = m.m23;
	m30 = m.m30;  m31 = m.m31;  m32 = m.m32;  m33 = m.m33;

	return *this;
}

inline cMatrix4x4 operator * ( const cMatrix4x4& mL, const cMatrix4x4& mR )
{
	return cMatrix4x4(
		mL.m00*mR.m00 + mL.m01*mR.m10 + mL.m02*mR.m20 + mL.m03*mR.m30,
		mL.m00*mR.m01 + mL.m01*mR.m11 + mL.m02*mR.m21 + mL.m03*mR.m31,
		mL.m00*mR.m02 + mL.m01*mR.m12 + mL.m02*mR.m22 + mL.m03*mR.m32,
		mL.m00*mR.m03 + mL.m01*mR.m13 + mL.m02*mR.m23 + mL.m03*mR.m33,
	
		mL.m10*mR.m00 + mL.m11*mR.m10 + mL.m12*mR.m20 + mL.m13*mR.m30,
		mL.m10*mR.m01 + mL.m11*mR.m11 + mL.m12*mR.m21 + mL.m13*mR.m31,
		mL.m10*mR.m02 + mL.m11*mR.m12 + mL.m12*mR.m22 + mL.m13*mR.m32,
		mL.m10*mR.m03 + mL.m11*mR.m13 + mL.m12*mR.m23 + mL.m13*mR.m33,

		mL.m20*mR.m00 + mL.m21*mR.m10 + mL.m22*mR.m20 + mL.m23*mR.m30,
		mL.m20*mR.m01 + mL.m21*mR.m11 + mL.m22*mR.m21 + mL.m23*mR.m31,
		mL.m20*mR.m02 + mL.m21*mR.m12 + mL.m22*mR.m22 + mL.m23*mR.m32,
		mL.m20*mR.m03 + mL.m21*mR.m13 + mL.m22*mR.m23 + mL.m23*mR.m33,
	
		mL.m30*mR.m00 + mL.m31*mR.m10 + mL.m32*mR.m20 + mL.m33*mR.m30,
		mL.m30*mR.m01 + mL.m31*mR.m11 + mL.m32*mR.m21 + mL.m33*mR.m31,
		mL.m30*mR.m02 + mL.m31*mR.m12 + mL.m32*mR.m22 + mL.m33*mR.m32,
		mL.m30*mR.m03 + mL.m31*mR.m13 + mL.m32*mR.m23 + mL.m33*mR.m33 );
}

inline cVector4 operator * ( const cMatrix4x4& m, const cVector4& v )
{
	return cVector4(
		m.m00*v.x + m.m01*v.y + m.m02*v.z + m.m03*v.w,
		m.m10*v.x + m.m11*v.y + m.m12*v.z + m.m13*v.w,
		m.m20*v.x + m.m21*v.y + m.m22*v.z + m.m23*v.w,
		m.m30*v.x + m.m31*v.y + m.m32*v.z + m.m33*v.w );
}

inline cVector4 operator * ( const cVector4& v, const cMatrix4x4& m )
{
	return cVector4(
		v.x*m.m00 + v.y*m.m10 + v.z*m.m20 + v.w*m.m30,
		v.x*m.m01 + v.y*m.m11 + v.z*m.m21 + v.w*m.m31,
		v.x*m.m02 + v.y*m.m12 + v.z*m.m22 + v.w*m.m32,
		v.x*m.m03 + v.y*m.m13 + v.z*m.m23 + v.w*m.m33 );
}

#endif //  __JL_cMatrix4x4_HG_20130314__