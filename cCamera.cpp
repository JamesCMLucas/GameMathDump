#include "cCamera.h"

cCamera::cCamera()
	: mTargetDistance(1.f)
	, mRotation()
	, mPosition()
{

}

cCamera::~cCamera()
{

}

const cVector3& cCamera::GetPosition() const
{
	return mPosition;
}

void cCamera::SetPosition( const cVector3& pos )
{
	mPosition = pos;
}

float cCamera::GetTargetDistance() const
{
	return mTargetDistance;
}

void cCamera::SetTargetDistance( float dist )
{
	mTargetDistance = dist;
}

cVector3 cCamera::GetTarget() const
{
	return mPosition - ( mRotation.GetLocalZAxis() * mTargetDistance );
}

const cQuaternion& cCamera::GetRotation() const
{
	return mRotation;
}

void cCamera::SetRotation( const cQuaternion& rot )
{
	mRotation = rot;
}

void cCamera::SetRotation( float yaw, float pitch, float roll )
{
	mRotation.FromEulerAngles( yaw, pitch, roll );
}

float cCamera::GetNearZ() const
{
	return mNearZ;
}

float cCamera::GetFarZ() const
{
	return mFarZ;
}

float cCamera::GetAspect() const
{
	return mAspectRatio;
}

const cVector2& cCamera::GetFov() const
{
	return mFov;
}

float cCamera::GetFovY() const
{
	return mFov.y;
}

float cCamera::GetFovX() const
{
	return mFov.x;
}

const cVector2& cCamera::GetNearWindowSize() const
{
	return mNearWindowSize;
}

const cVector2& cCamera::GetFarWindowSize() const
{
	return mFarWindowSize;
}

void cCamera::SetScreen( float w, float h )
{
	mScreenSize = cVector2( w, h );
	mAspectRatio = w / h;
	mFov.x = mFov.y * mAspectRatio;
	mNearWindowSize.x = mNearWindowSize.y * mAspectRatio;
	mFarWindowSize.x = mFarWindowSize.y * mAspectRatio;
	
	UpdateProjection();
}

void cCamera::SetLens( float fovY, float zNear, float zFar )
{
	mFov.y = fovY;
	mFov.x = fovY * mAspectRatio;
	mNearZ = zNear;
	mFarZ = zFar;
	
	float tanHalfY2 = 2.f * tanf( 0.5f * mFov.y );
	mNearWindowSize.y = mNearZ *tanHalfY2;
	mFarWindowSize.y = mFarZ * tanHalfY2;
	mNearWindowSize.x = mNearWindowSize.y * mAspectRatio;
	mFarWindowSize.x = mFarWindowSize.y * mAspectRatio;

	UpdateProjection();
}

void cCamera::UpdateProjection()
{
	mProjection = cMatrix4x4::PerspectiveProjectionLH( mFarZ, mNearZ, mAspectRatio, mFov.y );
}

cMatrix4x4 cCamera::GetView()
{
	return cMatrix4x4::ViewLH( mPosition, mRotation );
}

cMatrix4x4 cCamera::GetOrthogonalProjection()
{
	return cMatrix4x4::OrthogonalProjectionLH( mScreenSize.x, mScreenSize.y, mNearZ, mFarZ );
}

const cMatrix4x4& cCamera::GetPerspectiveProjection() const
{
	return mProjection;
}

void cCamera::Yaw( float radians )
{
	mRotation = mRotation * cQuaternion( cVector3( 0.f, 1.f, 0.f ), radians );
}

void cCamera::Pitch( float radians )
{
	mRotation = mRotation * cQuaternion( cVector3( 1.f, 0.f, 0.f ), radians );
}

void cCamera::Roll( float radians )
{
	mRotation = mRotation * cQuaternion( cVector3( 0.f, 0.f, 1.f ), radians );
}

void cCamera::SetView( const cMatrix4x4& view )
{
	mPosition.x = view.m20;
	mPosition.y = view.m21;
	mPosition.z = view.m22;
	mRotation.FromMatrix4x4( view.m );
}
