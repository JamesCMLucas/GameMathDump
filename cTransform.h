#ifndef __JL_cTransform_HG_20130314__
#define __JL_cTransform_HG_20130314__

#include "cVector3.h"
#include "cQuaternion.h"
#include "cMatrix4x4.h"

/// Represents a physical transformation
/// with a vector position and quaternion rotation
class cTransform
{
public:
	cTransform();
	cTransform( const cTransform& other )
		: Translation(other.Translation), Rotation(other.Rotation) {}
	const cTransform& operator = ( const cTransform& other )
	{
		if ( &other != this )
		{
			Translation = other.Translation;
			Rotation = other.Rotation;
		}
		return *this;
	}
	cTransform( const cVector3& translation, const cQuaternion& rotation );

	~cTransform() {}

	cVector3 Translation;
	cQuaternion Rotation;
	
	/// Description:  Builds a matrix version of this transformation
	cMatrix4x4 BuildMatrix();
	/// Description:  Builds a matrix, interpolated between this and another transformation
	static cTransform Interpolate( const cTransform& trA, const cTransform& trB, float interp /* 0.f < interp <= 1.f */);
};

/// Same as cTransform, but with scale
class cTransformWithScale
{
public:
	cTransformWithScale();
	cTransformWithScale( const cTransformWithScale& other )
		: Translation(other.Translation), Rotation(other.Rotation), Scale(other.Scale) {}
	const cTransformWithScale& operator = ( const cTransformWithScale& other )
	{
		if ( &other != this )
		{
			Translation = other.Translation;
			Rotation = other.Rotation;
			Scale = other.Scale;
		}
		return *this;
	}
	cTransformWithScale( const cVector3& translation, const cQuaternion& rotation, const cVector3& scale = cVector3(1.f,1.f,1.f) );

	~cTransformWithScale() {}

	cVector3 Translation;
	cQuaternion Rotation;
	cVector3 Scale;

	/// Description:  Builds a matrix version of this transformation
	cMatrix4x4 BuildMatrix();

	/// Description:  Builds a matrix, interpolated between this and another transformation
	static cTransformWithScale Interpolate( const cTransformWithScale& trA, const cTransformWithScale& trB, float interp /* 0.f < interp <= 1.f */);
};

#endif  //  __JL_cTransform_HG_20130314__