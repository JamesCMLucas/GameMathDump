#ifndef __JL_cMatrix3x3_HG_20130314__
#define __JL_cMatrix3x3_HG_20130314__


#include "cVector3.h"
#include "cQuaternion.h"

class cMatrix3x3
{
public:
	union
	{
		float mn[3][3];
		float m[9];
		struct
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};
	};

	// initializes as an identity matrix
	cMatrix3x3() 
		: m00(1.f), m01(0.f), m02(0.f)
		, m10(0.f), m11(1.f), m12(0.f)
		, m20(0.f), m21(0.f), m22(1.f) {}

	cMatrix3x3( float* mIn );
	cMatrix3x3( const cMatrix3x3& mat )
		: m00(mat.m00), m01(mat.m01), m02(mat.m02)
		, m10(mat.m10), m11(mat.m11), m12(mat.m12)
		, m20(mat.m20), m21(mat.m21), m22(mat.m22) {}
	cMatrix3x3( const cVector3& v0, const cVector3& v1, const cVector3& v2 )
		: m00(v0.x), m01(v0.y), m02(v0.z)
		, m10(v1.x), m11(v1.y), m12(v1.z)
		, m20(v2.x), m21(v2.y), m22(v2.z) {}
	cMatrix3x3( 
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22	)
		: m00(a00), m01(a01), m02(a02)
		, m10(a10), m11(a11), m12(a12)
		, m20(a20), m21(a21), m22(a22) {}

	~cMatrix3x3() {}
	
	cMatrix3x3& operator=( const cMatrix3x3& mat );

	cMatrix3x3& operator += ( const cMatrix3x3& mat );
	cMatrix3x3& operator -= ( const cMatrix3x3& mat );
	cMatrix3x3& operator *= ( const cMatrix3x3& mat );

	/// gets a specific entry
	/// i:  row number
	/// j:  column number
	float& operator () ( int i, int j );

	/// gets a specific entry
	/// i:  row number
	/// j:  column number
	const float& operator () ( int i, int j ) const;

	/// makes this an identity matrix
	void SetIdentity();

	/// sets the diagonal entries
	void SetDiagonals( float val, bool bSetRemainingZeroes );

	/// gets the diagonal entries
	cVector3 GetDiagonals() const;

	/// sets the rows
	void SetRows( const cVector3& a, const cVector3& b, const cVector3& c );

	/// sets the columns
	void SetCols( const cVector3& a, const cVector3& b, const cVector3& c );

	/// gets a given row
	cVector3 GetRow( int i ) const;

	/// gets a given column
	cVector3 GetCol( int j ) const;

	/// gets the trace
	float Tr() const;

	/// gets the determinant
	float Det() const;

	/// gets the inverse of this matrix
	/// returns an identity matrix if it's singular
	cMatrix3x3 Inverse( float tol = nMath::EPSILON ) const;

	cMatrix3x3 ColumnScaled( const cVector3& scales ) const;

	/// gets a transpose version of this matrix
	cMatrix3x3 Transpose() const;

	/// tries to invert this matrix
	/// returns true if successful
	/// returns false if this matrix is singular (nothing changes)
	bool Invert( float tol = nMath::EPSILON );
	static cMatrix3x3 Identity();
	static cMatrix3x3 Inverse( const cMatrix3x3& m );
	
	static cMatrix3x3 RotationX( float rad );
	static cMatrix3x3 RotationY( float rad );
	static cMatrix3x3 RotationZ( float rad );
	static cMatrix3x3 Rotation( const cVector3& axis, float rad );
	static cMatrix3x3 Rotation( const cQuaternion& q );
};

inline cMatrix3x3 operator - ( const cMatrix3x3& mL, const cMatrix3x3& mR )
{
	return cMatrix3x3( 
		(mL.m00 - mR.m00), (mL.m01 - mR.m01), (mL.m02 - mR.m02),
		(mL.m10 - mR.m10), (mL.m11 - mR.m11), (mL.m12 - mR.m12),
		(mL.m20 - mR.m20), (mL.m21 - mR.m21), (mL.m22 - mR.m22) );
}

inline cMatrix3x3 operator + ( const cMatrix3x3& mL, const cMatrix3x3& mR )
{
	return cMatrix3x3( 
		(mL.m00 + mR.m00), (mL.m01 + mR.m01), (mL.m02 + mR.m02),
		(mL.m10 + mR.m10), (mL.m11 + mR.m11), (mL.m12 + mR.m12),
		(mL.m20 + mR.m20), (mL.m21 + mR.m21), (mL.m22 + mR.m22) );
}

inline cMatrix3x3 operator * ( const cMatrix3x3& mL, const cMatrix3x3& mR )
{
	return cMatrix3x3(
		mL.m00*mR.m00 + mL.m01*mR.m10 + mL.m02*mR.m20,
		mL.m00*mR.m01 + mL.m01*mR.m11 + mL.m02*mR.m21,
		mL.m00*mR.m02 + mL.m01*mR.m12 + mL.m02*mR.m22,

		mL.m10*mR.m00 + mL.m11*mR.m10 + mL.m12*mR.m20,
		mL.m10*mR.m01 + mL.m11*mR.m11 + mL.m12*mR.m21,
		mL.m10*mR.m02 + mL.m11*mR.m12 + mL.m12*mR.m22,

		mL.m20*mR.m00 + mL.m21*mR.m10 + mL.m22*mR.m20,
		mL.m20*mR.m01 + mL.m21*mR.m11 + mL.m22*mR.m21,
		mL.m20*mR.m02 + mL.m21*mR.m12 + mL.m22*mR.m22 );
}

/// multiply matrix m and vector v (column)
inline cVector3 operator * ( const cMatrix3x3& m, const cVector3& v )
{
	return cVector3(
		( (m.m00*v.x)+(m.m01*v.y)+(m.m02*v.z) ),
		( (m.m10*v.x)+(m.m11*v.y)+(m.m12*v.z) ),
		( (m.m20*v.x)+(m.m21*v.y)+(m.m22*v.z) ) );
}

/// multiply vector v (as a row vector) and matrix m
inline cVector3 operator * ( const cVector3& v, const cMatrix3x3& m )
{
	return cVector3(
		( (v.x*m.m00)+(v.y*m.m10)+(v.z*m.m20) ),
		( (v.x*m.m01)+(v.y*m.m11)+(v.z*m.m21) ),
		( (v.x*m.m02)+(v.y*m.m12)+(v.z*m.m22) ) );
}

inline cMatrix3x3 operator * ( const cMatrix3x3& m, float val )
{
	return cMatrix3x3(
		m.m00*val, m.m01*val, m.m02*val,
		m.m10*val, m.m11*val, m.m12*val,
		m.m20*val, m.m21*val, m.m22*val );
}

#endif //  __JL_cMatrix3x3_HG_20130314__