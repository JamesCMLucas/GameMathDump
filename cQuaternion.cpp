#include "cQuaternion.h"
#include "nMath.h"

cQuaternion::cQuaternion( const cVector3& v, float theta )
{
	float sinHalfTheta = sin( theta*0.5f );
	x = v.x * sinHalfTheta;
	y = v.y * sinHalfTheta;
	z = v.z * sinHalfTheta;
	w = cos( theta*0.5f );
}

cVector3 cQuaternion::AppliedTo( const cVector3& v )
{
	cQuaternion vq, rq;
	vq.x = v.x;
	vq.y = v.y;
	vq.z = v.z;
	vq.w = 0.0f;
	rq = vq*Conjugate();
	rq = *this * rq;

	return cVector3( rq.x, rq.y, rq.z );
}

cQuaternion cQuaternion::AppliedTo( const cQuaternion& q )
{
	return *this * ( q * Conjugate() );
}


float cQuaternion::Angle()
{
	return ( 2.f * acosf(w) );
}

cVector3 cQuaternion::Axis()
{
	float om2 = 1.f - ( w * w );
	if ( om2 < 10.f * FLT_EPSILON )
	{
		return cVector3( 0.f, 1.f, 0.f );
	}
	float om = nMath::InverseSqrt( om2 );
	return cVector3( x*om, y*om, z*om );
}

void cQuaternion::Normalize( float tol /*= FLT_EPSILON */ )
{
	float mag2 = x*x + y*y + z*z + w*w;
	if ( mag2 < tol )
	{
		return;
	}

	float magInv = 1.0f/sqrt(mag2);
	x *= magInv;
	y *= magInv;
	z *= magInv;
	w *= magInv;
}

float cQuaternion::Length() const
{
	return sqrt( x*x + y*y + z*z + w*w );
}

float cQuaternion::Len2() const
{
	return x*x + y*y + z*z + w*w;
}

float cQuaternion::Dot( const cQuaternion& q ) const
{
	return x*q.x + y*q.y + z*q.z + w*q.w;
}

void cQuaternion::Dampen( float factor, float tol /*= FLT_EPSILON */ )
{
	if ( w*w > 1.0 - tol )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	else
	{
		float halfTheta = acos( w );
		float newHalfTheta = factor*halfTheta;
		float gamma = sin( newHalfTheta )/sin( halfTheta );

		x *= gamma;
		y *= gamma;
		z *= gamma;
		w = cos( newHalfTheta );
	}
}

void cQuaternion::FromEulerAngles( float yaw, float pitch, float roll )
{
	float sinRoll = sin( roll * 0.5f );
	float sinYaw = sin( yaw * 0.5f );
	float sinPitch = sin( pitch * 0.5f );
	float cosRoll = cos( roll * 0.5f );
	float cosYaw = cos( yaw * 0.5f );
	float cosPitch = cos( pitch * 0.5f );

	this->x = cosYaw*sinPitch*cosRoll - sinYaw*cosPitch*sinRoll;
	this->y = sinYaw*cosPitch*cosRoll + cosYaw*sinPitch*sinRoll;
	this->z = cosYaw*cosPitch*sinRoll - sinYaw*sinPitch*cosRoll;
	this->w = cosYaw*cosPitch*cosRoll + sinYaw*sinPitch*sinRoll;
	
	
	Normalize();
}

void cQuaternion::FromAxisRotation( float xValue, float yValue, float zValue, float theta )
{
	float sinHalfTheta = sin( theta*0.5f );
	x = xValue * sinHalfTheta;
	y = yValue * sinHalfTheta;
	z = zValue * sinHalfTheta;
	w = cos( theta*0.5f );
}

void cQuaternion::FromAxisRotation( const cVector3& v, float theta )
{
	float sinHalfTheta = sin( theta*0.5f );
	x = v.x * sinHalfTheta;
	y = v.y * sinHalfTheta;
	z = v.z * sinHalfTheta;
	w = cos( theta*0.5f );
}

void cQuaternion::FromMatrix3x3( const float* m )
{
	if ( m[0] + m[4] + m[8] > 0.f )
	{
		float t = m[0] + m[4] + m[8] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		w = s * t;
		z = ( m[1] - m[3] ) * s;
		y = ( m[6] - m[2] ) * s;
		x = ( m[5] - m[7] ) * s;
	}
	else if ( m[0] > m[4] && m[0] > m[8] )
	{
		float t = m[0] - m[4] - m[8] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		x = s * t;
		y = ( m[1] + m[3] ) * s;
		z = ( m[6] + m[2] ) * s;
		w = ( m[8] - m[7] ) * s;
	}
	else if ( m[7] > m[8] )
	{
		float t = -m[0] + m[4] - m[8] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		y = s * t;
		x = ( m[1] + m[4] ) * s;
		w = ( m[6] - m[2] ) * s;
		y = ( m[5] + m[4] ) * s;
	}
	else
	{
		float t = -m[0] - m[4] + m[8] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		z = s * t;
		w = ( m[1] - m[3] ) * s;
		x = ( m[6] + m[2] ) * s;
		y = ( m[5] + m[7] ) * s;
	}
}

void cQuaternion::FromMatrix4x4( const float* m )
{
	if ( m[0] + m[5] + m[10] > 0.f )
	{
		float t = m[0] + m[5] + m[10] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		w = s * t;
		z = ( m[1] - m[4] ) * s;
		y = ( m[8] - m[2] ) * s;
		x = ( m[6] - m[9] ) * s;
	}
	else if ( m[0] > m[5] && m[0] > m[10] )
	{
		float t = m[0] - m[5] - m[10] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		x = s * t;
		y = ( m[1] + m[4] ) * s;
		z = ( m[8] + m[2] ) * s;
		w = ( m[10]- m[9] ) * s;
	}
	else if ( m[9] > m[10] )
	{
		float t = -m[0] + m[5] - m[10] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		y = s * t;
		x = ( m[1] + m[4] ) * s;
		w = ( m[8] - m[2] ) * s;
		y = ( m[6] + m[5] ) * s;
	}
	else
	{
		float t = -m[0] - m[5] + m[10] + 1.f;
		float s = nMath::InverseSqrt( t ) * 0.5f;

		z = s * t;
		w = ( m[1] - m[4] ) * s;
		x = ( m[8] + m[2] ) * s;
		y = ( m[6] + m[9] ) * s;
	}
}

void cQuaternion::SetMatrix3x3( float* m )
{
	if ( !m ) return;

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	{
		float xx2 = x * x2;
		float yy2 = y * y2;
		float zz2 = z * z2;

		m[0] = 1.f - yy2 - zz2;
		m[4] = 1.f - xx2 - zz2;
		m[8] = 1.f - xx2 - yy2;
	}
	{
		float yz2 = y * z2;
		float wx2 = w * x2;

		m[7] = yz2 - wx2;
		m[5] = yz2 + wx2;
	}
	{
		float xy2 = x * y2;
		float wz2 = w * z2;

		m[3] = xy2 - wz2;
		m[1] = xy2 + wz2;
	}
	{
		float xz2 = x * z2;
		float wy2 = w * y2;

		m[ 2] = xz2 - wy2;
		m[ 6] = xz2 + wy2;
	}
}

void cQuaternion::SetMatrix4x4( float* m )
{
	if ( !m ) return;

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	{
		float xx2 = x * x2;
		float yy2 = y * y2;
		float zz2 = z * z2;

		m[ 0] = 1.f - yy2 - zz2;
		m[ 5] = 1.f - xx2 - zz2;
		m[10] = 1.f - xx2 - yy2;
	}
	{
		float yz2 = y * z2;
		float wx2 = w * x2;

		m[ 9] = yz2 - wx2;
		m[ 6] = yz2 + wx2;
	}
	{
		float xy2 = x * y2;
		float wz2 = w * z2;

		m[ 4] = xy2 - wz2;
		m[ 1] = xy2 + wz2;
	}
	{
		float xz2 = x * z2;
		float wy2 = w * y2;

		m[ 2] = xz2 - wy2;
		m[ 8] = xz2 + wy2;
	}

	m[  3 ] = 0.f;
	m[  7 ] = 0.f; 
	m[ 11 ] = 0.f; 

	m[ 12 ] = 0.f;
	m[ 13 ] = 0.f;
	m[ 14 ] = 0.f;
	m[ 15 ] = 1.f;
}


cQuaternion cQuaternion::Exp()
{
	float length = sqrt( x*x + y*y + z*z );
	float sinL = sin( length );

	cQuaternion q;
	q.w = cos( length );;

	if ( length > 0 )
	{
		q.x = sinL * ( x / length );
		q.y = sinL * ( y / length );
		q.z = sinL * ( z / length );
	}
	else
	{
		q.x = q.y = q.z = 0.f;
	}

	return q;
}

cQuaternion cQuaternion::Log()
{
	float a = acos( w );
	float sinA = sin( a );

	cQuaternion q;
	q.w = 0;

	if ( sinA > 0 )
	{
		q.x = a * ( x / sinA );
		q.y = a * ( y / sinA );
		q.z = a * ( z / sinA );
	}
	else
	{
		q.x = q.y = q.z = 0.f;
	}

	return q;
}

cQuaternion cQuaternion::Inverse()
{
	return this->Conjugate() / this->Len2();
}

cVector3 cQuaternion::GetLocalXAxis() const
{
	return cVector3( 
		1.f - 2.f*( y*y + z*z ), 
		2.f*( x*y + z*w ), 
		2.f*( x*z - y*w ) );

	/*cQuaternion rq( w, z, -y, x );
	rq = (*this)*rq;
	return cVector3( rq.x, rq.y, rq.z );*/
}

cVector3 cQuaternion::GetLocalYAxis() const
{
	return cVector3( 
		2.f*( x*y - z*w ), 
		1.f - 2.f*( x*x + z*z ),
		2.f*( y*z + x*w ) );
	/*cQuaternion rq( -z, w, x, y );
	rq = (*this)*rq;
	return cVector3( rq.x, rq.y, rq.z );*/
}

cVector3 cQuaternion::GetLocalZAxis() const
{
	return cVector3( 
		2.f*( x*z + y*w ),
		2.f*( y*z - x*w ),
		1.f - 2.f*( x*x + y*y ) );
	/*cQuaternion rq( y, -x, w, z );
	rq = (*this)*rq;
	return cVector3( rq.x, rq.y, rq.z );*/
}





cQuaternion Lerp( const cQuaternion& qA, const cQuaternion& qB, float t )
{
	cQuaternion q = qA*( 1.f - t ) + qB*t;
	q.Normalize();
	return q;
}

cQuaternion SLerp( const cQuaternion& qA, const cQuaternion& qB, float t )
{
	cQuaternion qC;
	float d = qA.Dot( qB );

	if ( d < 0.f )
	{
		d = -d;
		qC = qB.Conjugate();
	}
	else
	{
		qC = qB;
	}

	if ( d < ( 1.f - FLT_EPSILON ) )
	{
		float theta = acos(d);
		return ( ( qA * sin( theta * ( 1.f - t ) ) ) + ( qC * sin( theta * t ) / sin( theta ) ) );
	}
	else
	{
		return Lerp( qA, qB, t );
	}
}
