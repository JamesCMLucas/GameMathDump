#include "cMatrix3x3.h"
#include "nMath.h"

cMatrix3x3::cMatrix3x3( float* mIn )
{
	if ( mIn )
	{
		for ( int i = 0; i < 9; i++ )
		{
			m[i] = mIn[i];
		}
	}
	else
	{
		this->SetIdentity();
	}
}

cMatrix3x3& cMatrix3x3::operator = ( const cMatrix3x3& mat )
{
	if ( this != &mat )
	{
		for ( int i = 0; i < 9; i++ )
		{
			m[i] = mat.m[i];
		}
	}
	return *this;
}

cMatrix3x3& cMatrix3x3::operator += ( const cMatrix3x3& mat )
{
	for ( int i = 0; i < 9; i++ )
	{
		m[i] += mat.m[i];
	}
	return *this;
}

cMatrix3x3& cMatrix3x3::operator -= ( const cMatrix3x3& mat )
{
	for ( int i = 0; i < 9; i++ )
	{
		m[i] -= mat.m[i];
	}
	return *this;
}

cMatrix3x3& cMatrix3x3::operator *= ( const cMatrix3x3& mat )
{
	float* tmp = new float[9];
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			tmp[i*3 + j] = 0.f;
			for ( int k = 0; k < 3; k++ )
			{
				tmp[i*3 + j] += ( m[i*3 + k] * mat.m[j + 3*k] );
			}
		}
	}
	for ( int k = 0; k < 9; k++ )
	{
		m[k] = tmp[k];
	}
	delete[] tmp;
	return *this;
}


float& cMatrix3x3::operator () ( int i, int j )
{
	return m[ i*3 + j ];
}

const float& cMatrix3x3::operator () ( int i, int j ) const
{
	return m[ i*3 + j ];
}

void cMatrix3x3::SetIdentity()
{
	m[0] = 1.f;  m[1] = 0.f;  m[2] = 0.f;
	m[3] = 0.f;  m[4] = 1.f;  m[5] = 0.f;
	m[6] = 0.f;  m[7] = 0.f;  m[8] = 1.f;
}

void cMatrix3x3::SetDiagonals( float val, bool bSetRemainingZeroes )
{
	m[0] = val;
	m[4] = val;
	m[8] = val;

	if ( bSetRemainingZeroes )
	{
		m[1] = 0.f;  m[2] = 0.f;
		m[3] = 0.f;  m[5] = 0.f;
		m[6] = 0.f;  m[7] = 0.f;
	}
}

cVector3 cMatrix3x3::GetDiagonals() const
{
	return cVector3( m00, m11, m22 );
}


void cMatrix3x3::SetRows( const cVector3& a, const cVector3& b, const cVector3& c )
{
	m[0] = a.x;  m[1] = a.y;  m[2] = a.z;
	m[3] = b.x;  m[4] = b.y;  m[5] = b.z;
	m[6] = c.x;  m[7] = c.y;  m[8] = c.z;
}

void cMatrix3x3::SetCols( const cVector3& a, const cVector3& b, const cVector3& c )
{
	m[0] = a.x;  m[1] = b.x;  m[2] = c.x;
	m[3] = a.y;  m[4] = b.y;  m[5] = c.y;
	m[6] = a.z;  m[7] = b.z;  m[8] = c.z;
}


cVector3 cMatrix3x3::GetRow( int i ) const
{
	int j = i*3;
	return cVector3( m[j], m[j+1], m[j+2] );
}

cVector3 cMatrix3x3::GetCol( int j ) const
{
	return cVector3( m[j], m[j+3], m[j+6] );
}

float cMatrix3x3::Tr() const
{
	return ( m[0] + m[4] + m[8] );
}

float cMatrix3x3::Det() const
{
	return (  
		  m[0]*( m[4]*m[8] - m[5]*m[7] )
		- m[1]*( m[3]*m[8] - m[5]*m[6] )
		+ m[2]*( m[3]*m[7] - m[4]*m[6] ) );
}

cMatrix3x3 cMatrix3x3::Inverse( float tol /*= nMath::EPSILON */ ) const
{
	cMatrix3x3 matR;

	float detInv = this->Det();
	if ( fabs( detInv ) < tol )
	{
		return matR;
	}
	detInv = 1.f/detInv;

	float* tmp = new float[9];
	matR.m[0] =  m[4]*m[8] - m[5]*m[7];
	matR.m[1] = -m[1]*m[8] + m[2]*m[7];
	matR.m[2] =  m[1]*m[5] - m[2]*m[4];

	matR.m[3] = -m[3]*m[8] + m[5]*m[6];
	matR.m[4] =  m[0]*m[8] - m[2]*m[6];
	matR.m[5] = -m[0]*m[5] + m[2]*m[3];

	matR.m[6] =  m[3]*m[7] - m[4]*m[6];
	matR.m[7] = -m[0]*m[7] + m[1]*m[6];
	matR.m[8] =  m[0]*m[4] - m[1]*m[3];

	for ( int k = 0; k < 9; k++ )
	{
		matR.m[k] *= detInv;
	}

	return matR;
}

cMatrix3x3 cMatrix3x3::Inverse( const cMatrix3x3& m )
{
	float detInv = m.Det();
	if ( fabs( detInv ) == 0.f )
	{
		return Identity();
	}
	detInv = 1.f/detInv;

	return cMatrix3x3(
		detInv*(m.m[4]*m.m[8] - m.m[5]*m.m[7]), detInv*(-m.m[1]*m.m[8] + m.m[2]*m.m[7]), detInv*(m.m[1]*m.m[5] - m.m[2]*m.m[4]),
		detInv*(-m.m[3]*m.m[8] + m.m[5]*m.m[6]), detInv*(m.m[0]*m.m[8] - m.m[2]*m.m[6]), detInv*(-m.m[0]*m.m[5] + m.m[2]*m.m[3]),
		detInv*(m.m[3]*m.m[7] - m.m[4]*m.m[6]), detInv*(-m.m[0]*m.m[7] + m.m[1]*m.m[6]), detInv*(m.m[0]*m.m[4] - m.m[1]*m.m[3]) );
}

bool cMatrix3x3::Invert( float tol /*= nMath::EPSILON */ )
{
	float detInv = this->Det();
	if ( fabs( detInv ) < tol )
	{
		return false;
	}
	detInv = 1.f/detInv;

	float* tmp = new float[9];
	tmp[0] =  m[4]*m[8] - m[5]*m[7];
	tmp[1] = -m[1]*m[8] + m[2]*m[7];
	tmp[2] =  m[1]*m[5] - m[2]*m[4];

	tmp[3] = -m[3]*m[8] + m[5]*m[6];
	tmp[4] =  m[0]*m[8] - m[2]*m[6];
	tmp[5] = -m[0]*m[5] + m[2]*m[3];

	tmp[6] =  m[3]*m[7] - m[4]*m[6];
	tmp[7] = -m[0]*m[7] + m[1]*m[6];
	tmp[8] =  m[0]*m[4] - m[1]*m[3];

	for ( int k = 0; k < 9; k++ )
	{
		m[k] = tmp[k]*detInv;
	}
	delete[] tmp;

	return true;
}

cMatrix3x3 cMatrix3x3::RotationX( float rad )
{
	/*
	returns
		1      0         0
		0   cos(rad)  sin(rad)
		0  -sin(rad)  cos(rad)
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix3x3 (
		1.f, 0.f, 0.f,
		0.f, cR, -sR,
		0.f, sR,  cR );
}

cMatrix3x3 cMatrix3x3::RotationY( float rad )
{
	/*
	returns
		cos(rad)  0  -sin(rad)
		   0      1      0
		sin(rad)  0	  cos(rad)
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix3x3 (
		cR,  0.f, -sR,
		0.f, 1.f,  0.f,
		sR,  0.f,  cR  );
}

cMatrix3x3 cMatrix3x3::RotationZ( float rad )
{
	/*
	returns
		 cos(rad)  sin(rad)   0
		-sin(rad)  cos(rad)   0
		    0         0       1
	*/
	float sR = sinf(rad);
	float cR = cosf(rad);
	return cMatrix3x3 (
		cR, -sR,  0.f,
		sR,  cR,  0.f,
		0.f, 0.f, 1.f );
}

cMatrix3x3 cMatrix3x3::Rotation( const cVector3& axis, float rad )
{
	/*
	returns
		 a*a*(1-cos(rad)) +  cos(rad)     a*b*(1-cos(rad)) + c*sin(rad)     a*c*(1-cos(rad)) - b*sin(rad)
		 a*b*(1-cos(rad)) - c*sin(rad)     b*b*(1-cos(rad)) + cos(rad)      b*c*(1-cos(rad)) + a*sin(rad)
		 a*c*(1-cos(rad)) + b*sin(rad)    b*c*(1-cos(rad)) - a*sin(rad)     c*c*(1-cos(rad)) +  cos(rad)
		 */
	cVector3 v(axis);
	v.Normalize();
	float ab = v.x*v.y;
	float ac = v.x*v.z;
	float bc = v.y*v.z;
	float cR = cosf(rad);
	float cR1 = 1.f - cR;
	float sR = sinf(rad);
	
	return cMatrix3x3(
		v.x*v.x*cR1 + cR,   ab*cR1 + v.z*sR,   ac*cR1 - v.y*sR,
		ab*cR1 - v.z*sR,   v.y*v.y*cR1 + cR,   bc*cR1 + v.x*sR,
		ac*cR1 + v.y*sR,    bc*cR1 - v.x*sR,   v.z*v.z*cR1 + cR );
}

cMatrix3x3 cMatrix3x3::Rotation( const cQuaternion& q )
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

	return cMatrix3x3(
		( 1.f - yy2 - zz2 ), ( xy2 + wz2 ), ( xz2 - wy2 ),
		( xy2 - wz2 ), ( 1.f - xx2 - zz2 ), ( yz2 + wx2 ),
		( xz2 + wy2 ), ( yz2 - wx2 ), ( 1.f - xx2 - yy2 ) );
}

cMatrix3x3 cMatrix3x3::ColumnScaled( const cVector3& scales ) const
{
	return cMatrix3x3(
		m00*scales.x, m01*scales.y, m02*scales.z,
		m10*scales.x, m11*scales.y, m12*scales.z,
		m20*scales.x, m21*scales.y, m22*scales.z );
}

cMatrix3x3 cMatrix3x3::Transpose() const
{
	return cMatrix3x3(
		m00, m10, m20,
		m01, m11, m21,
		m02, m12, m22 );
}

cMatrix3x3 cMatrix3x3::Identity()
{
	return cMatrix3x3(
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f );
}
