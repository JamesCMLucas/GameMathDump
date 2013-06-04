#include "cMatrix4x4.h"


cMatrix4x4::cMatrix4x4( float* mIn )
{
	if ( mIn )
	{
		for ( int i = 0; i < 16; i++ )
		{
			m[i] = mIn[i];
		}
	}
	else
	{
		mn[0][0] = 1.f;  mn[0][1] = 0.f;  mn[0][2] = 0.f;  mn[0][3] = 0.f;
		mn[1][0] = 0.f;  mn[1][1] = 1.f;  mn[1][2] = 0.f;  mn[1][3] = 0.f;
		mn[2][0] = 0.f;  mn[2][1] = 0.f;  mn[2][2] = 1.f;  mn[2][3] = 0.f;
		mn[3][0] = 0.f;  mn[3][1] = 0.f;  mn[3][2] = 0.f;  mn[3][3] = 1.f;
	}
}


float cMatrix4x4::GetDeterminant() const
{
	return 
		  (m00*m11*m22*m33) + (m00*m12*m23*m31) + (m00*m13*m21*m32)
		+ (m01*m10*m23*m32) + (m01*m12*m20*m33) + (m01*m13*m22*m30)
		+ (m02*m10*m21*m33) + (m02*m11*m23*m30) + (m02*m13*m20*m31)
		+ (m03*m10*m22*m31) + (m03*m11*m20*m32) + (m03*m12*m21*m30)
		- (m00*m11*m23*m32) - (m00*m12*m21*m33) - (m00*m13*m22*m31)
		- (m01*m10*m22*m33) - (m01*m12*m23*m30) - (m01*m13*m20*m32)
		- (m02*m10*m23*m31) - (m02*m11*m20*m33) - (m02*m13*m21*m30)
		- (m03*m10*m21*m32) - (m03*m11*m22*m30) - (m03*m12*m20*m31);
}


cMatrix4x4 cMatrix4x4::Ones()
{
	return cMatrix4x4(
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f );
}

cMatrix4x4 cMatrix4x4::Zeroes()
{
	return cMatrix4x4(
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f );
}

cMatrix4x4 cMatrix4x4::Identity()
{
	return cMatrix4x4 (
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::Inverse( const cMatrix4x4& m )
{
	float det = m.GetDeterminant();
	if ( det == 0.f )
	{
		return cMatrix4x4::Identity();
	}
	
	float detInv = 1.f / det;
	return cMatrix4x4(
	( detInv * ( (m.m11*m.m22*m.m33) + (m.m12*m.m23*m.m31) + (m.m13*m.m21*m.m32) - (m.m11*m.m23*m.m32) - (m.m12*m.m21*m.m33) - (m.m13*m.m22*m.m31) ) ),
	( detInv * ( (m.m01*m.m23*m.m32) + (m.m02*m.m21*m.m33) + (m.m03*m.m22*m.m31) - (m.m01*m.m22*m.m33) - (m.m02*m.m23*m.m31) - (m.m03*m.m21*m.m32) ) ),
	( detInv * ( (m.m01*m.m12*m.m33) + (m.m02*m.m13*m.m31) + (m.m03*m.m11*m.m32) - (m.m01*m.m13*m.m32) - (m.m02*m.m11*m.m33) - (m.m03*m.m12*m.m31) ) ),
	( detInv * ( (m.m01*m.m13*m.m22) + (m.m02*m.m11*m.m23) + (m.m03*m.m12*m.m21) - (m.m01*m.m12*m.m23) - (m.m02*m.m13*m.m21) - (m.m03*m.m11*m.m22) ) ),

	( detInv * ( (m.m10*m.m23*m.m31) + (m.m12*m.m20*m.m33) + (m.m13*m.m22*m.m30) - (m.m10*m.m22*m.m33) - (m.m12*m.m23*m.m30) - (m.m13*m.m20*m.m32) ) ),
	( detInv * ( (m.m00*m.m22*m.m33) + (m.m02*m.m23*m.m30) + (m.m03*m.m20*m.m32) - (m.m00*m.m23*m.m32) - (m.m02*m.m20*m.m33) - (m.m03*m.m22*m.m30) ) ),
	( detInv * ( (m.m00*m.m13*m.m32) + (m.m02*m.m10*m.m33) + (m.m03*m.m12*m.m30) - (m.m00*m.m12*m.m33) - (m.m02*m.m13*m.m30) - (m.m03*m.m10*m.m32) ) ),
	( detInv * ( (m.m00*m.m12*m.m23) + (m.m02*m.m13*m.m20) + (m.m03*m.m10*m.m22) - (m.m00*m.m13*m.m22) - (m.m02*m.m10*m.m23) - (m.m03*m.m12*m.m20) ) ),

	( detInv * ( (m.m10*m.m21*m.m33) + (m.m11*m.m23*m.m30) + (m.m13*m.m20*m.m31) - (m.m10*m.m23*m.m31) - (m.m11*m.m20*m.m33) - (m.m13*m.m21*m.m30) ) ),
	( detInv * ( (m.m00*m.m23*m.m31) + (m.m01*m.m20*m.m33) + (m.m03*m.m21*m.m30) - (m.m00*m.m21*m.m33) - (m.m01*m.m23*m.m30) - (m.m03*m.m20*m.m31) ) ),
	( detInv * ( (m.m00*m.m11*m.m33) + (m.m01*m.m13*m.m30) + (m.m03*m.m10*m.m31) - (m.m00*m.m13*m.m31) - (m.m01*m.m10*m.m33) - (m.m03*m.m11*m.m30) ) ),
	( detInv * ( (m.m00*m.m13*m.m21) + (m.m01*m.m10*m.m23) + (m.m03*m.m11*m.m20) - (m.m00*m.m11*m.m23) - (m.m01*m.m13*m.m20) - (m.m03*m.m10*m.m21) ) ),

	( detInv * ( (m.m10*m.m22*m.m31) + (m.m11*m.m20*m.m32) + (m.m12*m.m21*m.m30) - (m.m10*m.m21*m.m32) - (m.m11*m.m22*m.m30) - (m.m12*m.m20*m.m31) ) ),
	( detInv * ( (m.m00*m.m21*m.m32) + (m.m01*m.m22*m.m30) + (m.m02*m.m20*m.m31) - (m.m00*m.m22*m.m31) - (m.m01*m.m20*m.m32) - (m.m02*m.m21*m.m30) ) ),
	( detInv * ( (m.m00*m.m12*m.m31) + (m.m01*m.m10*m.m32) + (m.m02*m.m11*m.m30) - (m.m00*m.m11*m.m32) - (m.m01*m.m12*m.m30) - (m.m02*m.m10*m.m31) ) ),
	( detInv * ( (m.m00*m.m11*m.m22) + (m.m01*m.m12*m.m20) + (m.m02*m.m10*m.m21) - (m.m00*m.m12*m.m21) - (m.m01*m.m10*m.m22) - (m.m02*m.m11*m.m20) ) ) );
}

cMatrix4x4 cMatrix4x4::Transpose( const cMatrix4x4& m )
{
	return cMatrix4x4(
		m.m00, m.m10, m.m20, m.m30,
		m.m01, m.m11, m.m21, m.m31,
		m.m02, m.m12, m.m22, m.m32,
		m.m03, m.m13, m.m23, m.m33 );
}


cMatrix4x4 cMatrix4x4::InverseTranspose( const cMatrix4x4& mat )
{
	cMatrix4x4 r = mat;
	r.m30 = 0.f;
	r.m31 = 0.f;
	r.m32 = 0.f;
	r.m33 = 1.f;
	return cMatrix4x4::Transpose( cMatrix4x4::Inverse( r ) );
}


cMatrix4x4 cMatrix4x4::Transpose() const
{
	return cMatrix4x4(
		m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33 );
}

cMatrix4x4 cMatrix4x4::Scaling( float scale )
{
	return cMatrix4x4 (
		scale, 0.f, 0.f, 0.f,
		0.f, scale, 0.f, 0.f,
		0.f, 0.f, scale, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::Scaling( float sx, float sy, float sz )
{
	return cMatrix4x4 (
		sx, 0.f, 0.f, 0.f,
		0.f, sy, 0.f, 0.f,
		0.f, 0.f, sz, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::Scaling( const cVector3& vs )
{
	return cMatrix4x4 (
		vs.x, 0.f, 0.f, 0.f,
		0.f, vs.y, 0.f, 0.f,
		0.f, 0.f, vs.z, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::RotationX( float rad )
{
	/*
	returns
		1      0         0       0
		0   cos(rad)  sin(rad)   0
		0  -sin(rad)  cos(rad)   0
		0      0         0       1
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix4x4 (
		1.f, 0.f, 0.f, 0.f,
		0.f, cR, -sR, 0.f,
		0.f, sR, cR, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::RotationY( float rad )
{
	/*
	returns
		cos(rad)  0  -sin(rad)   0
		   0      1      0       0
		sin(rad)  0	  cos(rad)   0
		   0      0      0       1
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix4x4 (
		cR, 0.f, -sR, 0.f,
		0.f, 1.f, 0.f, 0.f,
		sR, 0.f, cR, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::RotationZ( float rad )
{
	/*
	returns
		 cos(rad)  sin(rad)   0    0
		-sin(rad)  cos(rad)   0    0
		    0         0       1    0
			0         0       0    1
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix4x4 (
		cR, -sR, 0.f, 0.f,
		sR, cR, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f );
}

cMatrix4x4 cMatrix4x4::Rotation( const cVector3& axis, float rad )
{
	/*
	returns
		 a*a*(1-cos(rad)) +  cos(rad)     a*b*(1-cos(rad)) + c*sin(rad)     a*c*(1-cos(rad)) - b*sin(rad)     0
		 a*b*(1-cos(rad)) - c*sin(rad)     b*b*(1-cos(rad)) + cos(rad)      b*c*(1-cos(rad)) + a*sin(rad)     0
		 a*c*(1-cos(rad)) + b*sin(rad)    b*c*(1-cos(rad)) - a*sin(rad)     c*c*(1-cos(rad)) +  cos(rad)      0
		               0                                  0                                 0                 1
	*/
	cVector3 v(axis);
	v.Normalize();
	float ab = v.x*v.y;
	float ac = v.x*v.z;
	float bc = v.y*v.z;
	float cR = cosf(rad);
	float cR1 = 1.f - cR;
	float sR = sinf(rad);
	
	return cMatrix4x4(
		v.x*v.x*cR1 + cR,  ab*cR1 + v.z*sR,  ac*cR1 - v.y*sR,  0.f,
		ab*cR1 - v.z*sR, v.y*v.y*cR1 + cR, bc*cR1 + v.x*sR,  0.f,
		ac*cR1 + v.y*sR, bc*cR1 - v.x*sR,  v.z*v.z*cR1 + cR, 0.f,
		0.f, 0.f, 0.f, 1.f
		);
}

cMatrix4x4 cMatrix4x4::Rotation( const cQuaternion& q )
{
	// this assumes q is normalized...
	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;

	float xx2 = q.x * x2;
	float yy2 = q.y * y2;
	float zz2 = q.z * z2;

	float yz2 = q.y * z2;
	float wx2 = q.w * x2;

	float xy2 = q.x * y2;
	float wz2 = q.w * z2;

	float xz2 = q.x * z2;
	float wy2 = q.w * y2;

	return cMatrix4x4(
		( 1.f - yy2 - zz2 ), ( xy2 + wz2 ), ( xz2 - wy2 ), 0.f,
		( xy2 - wz2 ), ( 1.f - xx2 - zz2 ), ( yz2 + wx2 ), 0.f,
		( xz2 + wy2 ), ( yz2 - wx2 ), ( 1.f - xx2 - yy2 ), 0.f,
		0.f, 0.f, 0.f, 1.f );
}


cMatrix4x4 cMatrix4x4::Translation( float x, float y, float z )
{
	return cMatrix4x4 (
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x, y, z, 1.f );
}

cMatrix4x4 cMatrix4x4::Translation( const cVector3& vt )
{
	return cMatrix4x4 (
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		vt.x, vt.y, vt.z, 1.f );
}

cMatrix4x4 cMatrix4x4::ViewLH( const cVector3& eye, const cVector3& at, const cVector3& up )
{
	cVector3 zAxis = at - eye;
	zAxis.Normalize();
	cVector3 xAxis = up.Cross(zAxis);
	xAxis.Normalize();
	cVector3 yAxis = zAxis.Cross(xAxis);
	
	return cMatrix4x4(
		xAxis.x, yAxis.x, zAxis.x, 0.f,
		xAxis.y, yAxis.y, zAxis.y, 0.f,
		xAxis.z, yAxis.z, zAxis.z, 0.f,
		-xAxis.Dot(eye), -yAxis.Dot(eye), -zAxis.Dot(eye), 1.f );
}

cMatrix4x4 cMatrix4x4::ViewLH( const cVector3& pos, const cQuaternion& rot )
{
	cVector3 target = pos;
	target += rot.GetLocalZAxis();
	cVector3 up = rot.GetLocalYAxis();
	return ViewLH( pos, target, up );
}

cMatrix4x4 cMatrix4x4::ViewRH( const cVector3& eye, const cVector3& at, const cVector3& up )
{
	cVector3 zAxis = eye - at;
	zAxis.Normalize();
	cVector3 xAxis = up.Cross(zAxis);
	xAxis.Normalize();
	cVector3 yAxis = zAxis.Cross(xAxis);

	return cMatrix4x4(
		xAxis.x, yAxis.x, zAxis.x, 0.f,
		xAxis.y, yAxis.y, zAxis.y, 0.f,
		xAxis.z, yAxis.z, zAxis.z, 0.f,
		-xAxis.Dot(eye), -yAxis.Dot(eye), -zAxis.Dot(eye), 1.f );
}

cMatrix4x4 cMatrix4x4::ViewRH( const cVector3& pos, const cQuaternion& rot )
{
	cVector3 target = pos;
	target -= rot.GetLocalZAxis();
	cVector3 up = rot.GetLocalYAxis();
	return ViewRH( pos, target, up );
}

cMatrix4x4 cMatrix4x4::OrthogonalProjectionLH( float width, float height, float zNear, float zFar )
{
	float rangeInv = 1.f / ( zFar - zNear );

	return cMatrix4x4 (
		( 2.f / width ), 0.f, 0.f, 0.f,
		0.f, ( 2.f / height ), 0.f, 0.f,
		0.f, 0.f, rangeInv, 0.f,
		0.f, 0.f, ( -zNear*rangeInv ), 1.f );
}

cMatrix4x4 cMatrix4x4::OrthogonalProjectionRH( float width, float height, float zNear, float zFar )
{
	float rangeInv = 1.f / ( zFar - zNear );

	return cMatrix4x4 (
		( 2.f / width ), 0.f, 0.f, 0.f,
		0.f, ( 2.f / height ), 0.f, 0.f,
		0.f, 0.f, -rangeInv, 0.f,
		0.f, 0.f, ( -zNear*rangeInv ), 1.f );
}

cMatrix4x4 cMatrix4x4::OrthogonalOffCentreProjectionLH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	return cMatrix4x4 (
		( 2.f/(maxX-minX) ), 0.f, 0.f, 0.f,
		0.f, ( 2.f/(maxY-minY) ), 0.f, 0.f,
		0.f, 0.f, ( 1.f/(maxZ-minZ) ), 0.f,
		( (minX+maxX)/(minX-maxX) ), ( (minY+maxY)/(minY-maxY) ), ( minZ/(minZ-maxZ) ), 1.f );
}

cMatrix4x4 cMatrix4x4::OrthogonalOffCentreProjectionRH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	return cMatrix4x4 (
		( 2.f/(maxX-minX) ), 0.f, 0.f, 0.f,
		0.f, ( 2.f/(maxY-minY) ), 0.f, 0.f,
		0.f, 0.f, ( 1.f/(minZ-maxZ) ), 0.f,
		( (minX+maxX)/(minX-maxX) ), ( (minY+maxY)/(minY-maxY) ), ( minZ/(minZ-maxZ) ), 1.f );
}

cMatrix4x4 cMatrix4x4::PerspectiveProjectionLH( float zFar, float zNear, float aspectWdivH, float fovH )
{
	float range = zFar - zNear;
	float q = zFar / range;
	float yScale = 1.f / tanf( fovH*0.5f );

	return cMatrix4x4 (
		( yScale / aspectWdivH ), 0.f, 0.f, 0.f,
		0.f, yScale, 0.f, 0.f,
		0.f, 0.f, q, 1.f,
		0.f, 0.f, -q*zNear, 0.f );
}

cMatrix4x4 cMatrix4x4::PerspectiveProjectionRH( float zFar, float zNear, float aspectWdivH, float fovH )
{
	float range = zFar - zNear;
	float q = zFar / range;
	float yScale = 1.f / tanf( fovH*0.5f );

	return cMatrix4x4 (
		( yScale / aspectWdivH ), 0.f, 0.f, 0.f,
		0.f, yScale, 0.f, 0.f,
		0.f, 0.f, q, 1.f,
		0.f, 0.f, q*zNear, 0.f );
}

cMatrix4x4 cMatrix4x4::PerspectiveOffCentreProjectionLH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	return cMatrix4x4 (
		(2.f*minZ)/(maxX-minX), 0.f, 0.f, 0.f,
		0.f, (2.f*minZ)/(maxY-minY), 0.f, 0.f,
		(minX+maxX)/(minX-maxX), (minY+maxY)/(minY-maxY), maxZ/(maxZ-minZ), 1.f,
		0.f, 0.f, minZ*maxZ/(minZ-maxZ), 0.f );
}

cMatrix4x4 cMatrix4x4::PerspectiveOffCentreProjectionRH( float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	return cMatrix4x4 (
		(2.f*minZ)/(maxX-minX), 0.f, 0.f, 0.f,
		0.f, (2.f*minZ)/(maxY-minY), 0.f, 0.f,
		(minX+maxX)/(maxX-minX), (minY+maxY)/(minY-maxY), maxZ/(minZ-maxZ), -1.f,
		0.f, 0.f, minZ*maxZ/(minZ-maxZ), 0.f );
}


cMatrix4x4 cMatrix4x4::PerspectiveObliqueProjectionLH( float left, float right, float top, float bottom, float nearZ, float farZ )
{
	float width = 1.f/(right - left);
	float height = 1.f/(top - bottom);
	
	return cMatrix4x4 (
		(2.f*nearZ)/width, 0.f, 0.f, 0.f,
		0.f, (2.f*nearZ)/height, 0.f, 0.f,
		(right + left)/width, (top + bottom)/height, (nearZ+farZ)/(nearZ-farZ), -1.f,
		0.f, 0.f, (2.f*nearZ*farZ)/(nearZ-farZ), 0.f );
}


cMatrix4x4 cMatrix4x4::WorldLH( const cVector3& pos, const cQuaternion& q )
{
	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;

	float xx2 = q.x * x2;
	float yy2 = q.y * y2;
	float zz2 = q.z * z2;

	float yz2 = q.y * z2;
	float wx2 = q.w * x2;

	float xy2 = q.x * y2;
	float wz2 = q.w * z2;

	float xz2 = q.x * z2;
	float wy2 = q.w * y2;

	return cMatrix4x4(
		( 1.f - yy2 - zz2 ), ( xy2 + wz2 ), ( xz2 - wy2 ), 0.f,
		( xy2 - wz2 ), ( 1.f - xx2 - zz2 ), ( yz2 + wx2 ), 0.f,
		( xz2 + wy2 ), ( yz2 - wx2 ), ( 1.f - xx2 - yy2 ), 0.f,
		pos.x, pos.y, pos.z, 1.f );
}

cMatrix4x4 cMatrix4x4::WorldLH( const cVector3& pos, const cQuaternion& rot, const cVector3& scale )
{
	cMatrix4x4 matScale = Scaling( scale );
	cMatrix4x4 matRot = Rotation( rot );
	cMatrix4x4 m = matScale * matRot;
	m.m30 = pos.x;  m.m31 = pos.y;  m.m32 = pos.z;  m.m33 = 1.f;
	return m;
}

cMatrix4x4 cMatrix4x4::ShadowTransform( const sPlane& plane, const cVector3& light, bool bIsDirectional )
{
	cVector4 P( plane.vec, plane.val );
	cVector4 L( light, 0.f );
	if ( bIsDirectional )
	{
		L.w = 1.f;
	}
	float d = -P.Dot(L);

	return cMatrix4x4(
		(P.x*L.x) + d, (P.x*L.y), (P.x*L.z), (P.x*L.w),
		(P.y*L.x), (P.y*L.y) + d, (P.y*L.z), (P.y*L.w),
		(P.z*L.x), (P.z*L.y), (P.z*L.z) + d, (P.z*L.w),
		(P.w*L.x), (P.w*L.y), (P.w*L.z), (P.w*L.w) + d );
}

cMatrix4x4 cMatrix4x4::ShadowTransform( const cVector4& plane, const cVector3& light, bool bIsDirectional )
{
	cVector4 P(plane);
	P.Normalize();
	cVector4 L( light, 0.f );
	if ( bIsDirectional )
	{
		L.w = 1.f;
	}
	float d = -P.Dot(L);

	return cMatrix4x4(
		(P.x*L.x) + d, (P.x*L.y), (P.x*L.z), (P.x*L.w),
		(P.y*L.x), (P.y*L.y) + d, (P.y*L.z), (P.y*L.w),
		(P.z*L.x), (P.z*L.y), (P.z*L.z) + d, (P.z*L.w),
		(P.w*L.x), (P.w*L.y), (P.w*L.z), (P.w*L.w) + d );
}

cMatrix4x4 cMatrix4x4::ReflectionMatrix( const sPlane& plane )
{
	cVector4 P( plane.vec, plane.val );
	return ReflectionMatrix( P );
}

cMatrix4x4 cMatrix4x4::ReflectionMatrix( const cVector4& plane )
{
	cVector4 P(plane);
	P.Normalize();
	float xyn2 = -2.f * P.x * P.y;
	float xzn2 = -2.f * P.x * P.z;
	float yzn2 = -2.f * P.y * P.z;

	return cMatrix4x4(
		( -2.f * P.x * P.x ) + 1.f, xyn2, xzn2, 0.f,
		xyn2, ( -2.f * P.y * P.y ) + 1.f, yzn2, 0.f,
		xzn2, yzn2, ( -2.f * P.z * P.z ) + 1.f, 0.f,
		-2.f * P.x * P.w, -2.f * P.y * P.w, -2.f * P.z * P.w, 1.f );
}

void cMatrix4x4::Translate( const cVector3& vt )
{
	m30 += vt.x;  m31 += vt.y;  m32 += vt.z;
}

void cMatrix4x4::Translate( float x, float y, float z )
{
	m30 += x;  m31 += y;  m32 += z;
}

void cMatrix4x4::SetTranslation( const cVector3& vt )
{
	m30 = vt.x;  m31 = vt.y;  m32 = vt.z;
}

void cMatrix4x4::SetTranslation( float x, float y, float z )
{
	m30 = x;  m31 = y;  m32 = z;
}

