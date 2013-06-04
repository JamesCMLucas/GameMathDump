#ifndef __JL_cQuaternion_HG_20130314__
#define __JL_cQuaternion_HG_20130314__

#include "cVector4.h"

class cQuaternion
{
public:
	float x, y, z, w;

	cQuaternion() : x(0.f), y(0.f), z(0.f), w(1.f) {};
	cQuaternion( float x_, float y_, float z_, float w_ )
		: x(x_), y(y_), z(z_), w(w_) {}
	cQuaternion( const cVector3& v, float theta );
	cQuaternion( const cVector4& v ) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	cQuaternion( const cQuaternion& q ) : x(q.x), y(q.y), z(q.z), w(q.w) {}
	~cQuaternion() {};

	cQuaternion& operator = ( const cQuaternion& q );
	cQuaternion& operator = ( const cVector4& v );

	cQuaternion& operator += ( const cQuaternion& q );
	cQuaternion& operator -= ( const cQuaternion& q );
	cQuaternion& operator *= ( const cQuaternion& q );

	cQuaternion& operator += ( float val );
	cQuaternion& operator -= ( float val );
	cQuaternion& operator *= ( float val );
	cQuaternion& operator /= ( float val );

	float& operator [] ( int i );
	const float& operator [] ( int i ) const;

	cQuaternion Conjugate() const;

	cVector3 AppliedTo( const cVector3& v );
	cQuaternion AppliedTo( const cQuaternion& q );
	float Angle();
	cVector3 Axis();

	void Normalize( float tol = nMath::EPSILON );
	float Length() const;
	float Len2() const;
	float Dot( const cQuaternion& q ) const;

	void Dampen( float factor, float tol = FLT_EPSILON );
	void FromEulerAngles( float yaw, float pitch, float roll );
	void FromAxisRotation( float xValue, float yValue, float zValue, float theta );
	void FromAxisRotation( const cVector3& v, float theta );
	void FromMatrix3x3( const float* m );
	void FromMatrix4x4( const float* m );
	void SetMatrix3x3( float* m );
	void SetMatrix4x4( float* m );

	cQuaternion Exp();
	cQuaternion Log();
	cQuaternion Inverse();

	cVector3 GetLocalXAxis() const;
	cVector3 GetLocalYAxis() const;
	cVector3 GetLocalZAxis() const;
};

inline cQuaternion& cQuaternion::operator=( const cQuaternion& q )
{
	if ( this != &q )
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	return *this;
}

inline cQuaternion& cQuaternion::operator = ( const cVector4& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}


inline cQuaternion& cQuaternion::operator += ( const cQuaternion& q )
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}

inline cQuaternion& cQuaternion::operator -= ( const cQuaternion& q )
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}

inline cQuaternion& cQuaternion::operator *= ( const cQuaternion& q )
{
	float x_ = w*q.x + x*q.w + y*q.z - z*q.y;
	float y_ = w*q.y + y*q.w + z*q.x - x*q.z;
	float z_ = w*q.z + z*q.w + x*q.y - y*q.x;
	w = w*q.w - x*q.x - y*q.y - z*q.z;
	x = x_;
	y = y_;
	z = z_;
	return *this;
}


inline cQuaternion& cQuaternion::operator += ( float val )
{
	x += val;
	y += val;
	z += val;
	w += val;
	return *this;
}

inline cQuaternion& cQuaternion::operator -= ( float val )
{
	x -= val;
	y -= val;
	z -= val;
	w -= val;
	return *this;
}

inline cQuaternion& cQuaternion::operator *= ( float val )
{
	x *= val;
	y *= val;
	z *= val;
	w *= val;
	return *this;
}

inline cQuaternion& cQuaternion::operator /= ( float val )
{
	x /= val;
	y /= val;
	z /= val;
	w /= val;
	return *this;
}


inline float& cQuaternion::operator [] ( int i )
{
	return ( &x )[i];
}

inline const float& cQuaternion::operator [] ( int i ) const
{
	return ( &x )[i];
}

inline cQuaternion cQuaternion::Conjugate() const
{
	return cQuaternion( -x, -y, -z, w );
}


inline cQuaternion operator * ( const cQuaternion& q, float f )
{
	return cQuaternion( ( q.x * f ), ( q.y * f ), ( q.z * f ), ( q.w * f ) );
}

inline cQuaternion operator / ( const cQuaternion& q, float f )
{
	return cQuaternion( ( q.x / f ), ( q.y / f ), ( q.z / f ), ( q.w / f ) );
}

inline cQuaternion operator + ( const cQuaternion& qL, const cQuaternion& qR )
{
	return cQuaternion( ( qL.x + qR.x ), ( qL.y + qR.y ), ( qL.z + qR.z ), ( qL.w + qR.w ) );
}

inline cQuaternion operator - ( const cQuaternion& qL, const cQuaternion& qR )
{
	return cQuaternion( ( qL.x - qR.x ), ( qL.y - qR.y ), ( qL.z - qR.z ), ( qL.w - qR.w ) );
}


inline cQuaternion operator * ( const cQuaternion& q1, const cQuaternion& q2 )
{
	return cQuaternion( 
		q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
		q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z,
		q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x,
		q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z );
}


// grassman product (if applying a rotation, just use cQuaternion::AppliedTo function)
inline cQuaternion operator * ( const cVector3& v, const cQuaternion& q )
{
	return cQuaternion( 
		q.w*v.x + q.y*v.z - q.z*v.y,
		q.w*v.y + q.z*v.x - q.x*v.z,
		q.w*v.z + q.x*v.y - q.y*v.x,
		q.x*v.x - q.y*v.y - q.z*v.z );
}

// grassman product (if applying a rotation, just use cQuaternion::AppliedTo function)
inline cQuaternion operator * ( const cQuaternion& q, const cVector3& v )
{
	return cQuaternion( 
		v.x*q.w + v.y*q.z - v.z*q.y,
		v.y*q.w + v.z*q.x - v.x*q.z,
		v.z*q.w + v.x*q.y - v.y*q.x,
		v.x*q.x - v.y*q.y - v.z*q.z );
}


// linear interpolation
cQuaternion Lerp( const cQuaternion& qA, const cQuaternion& qB, float t );

// spherical interpolation
cQuaternion SLerp( const cQuaternion& qA, const cQuaternion& qB, float t );

#endif  //  __JL_cQuaternion_HG_20130314__