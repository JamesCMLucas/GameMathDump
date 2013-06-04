#include "cTransform.h"

cTransform::cTransform() {}

cTransform::cTransform( const cVector3& translation, const cQuaternion& rotation )
	: Translation(translation)
	, Rotation(rotation)
{

}

cMatrix4x4 cTransform::BuildMatrix()
{
	cMatrix4x4 matFinal = cMatrix4x4::Rotation( Rotation );

	matFinal.mn[3][0] = Translation.x;
	matFinal.mn[3][1] = Translation.y;
	matFinal.mn[3][2] = Translation.z;
	matFinal.mn[3][3] = 1.f;

	return matFinal;
}

cTransform cTransform::Interpolate( const cTransform& trA, const cTransform& trB, float interp /* 0.f < interp <= 1.f */ )
{
	cTransform tr;
	tr.Translation = trA.Translation + ( ( trB.Translation - trA.Translation ) * interp );
	tr.Rotation = SLerp( trA.Rotation, trB.Rotation, interp );
	tr.Rotation.Normalize();
	return tr;
}



cTransformWithScale::cTransformWithScale()
{
	Scale.Ones();
}

cTransformWithScale::cTransformWithScale( const cVector3& translation, const cQuaternion& rotation, const cVector3& scale /*= cVector3(1.f,1.f,1.f) */ )
	: Translation(translation)
	, Rotation(rotation)
	, Scale(scale)
{

}

cMatrix4x4 cTransformWithScale::BuildMatrix()
{
	cMatrix4x4 matScale = cMatrix4x4::Scaling( Scale );
	cMatrix4x4 matFinal = cMatrix4x4::Rotation( Rotation );

	matFinal = matScale * matFinal;

	matFinal.SetTranslation( Translation );

	return matFinal;
}

cTransformWithScale cTransformWithScale::Interpolate( const cTransformWithScale& trA, const cTransformWithScale& trB, float interp /* 0.f < interp <= 1.f */ )
{
	cTransformWithScale tr;
	tr.Scale = trA.Scale + ( ( trB.Scale - trA.Scale ) * interp );
	tr.Translation = trA.Translation + ( ( trB.Translation - trA.Translation ) * interp );
	tr.Rotation = SLerp( trA.Rotation, trB.Rotation, interp );
	tr.Rotation.Normalize();
	return tr;
}