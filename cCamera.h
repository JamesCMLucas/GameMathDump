#ifndef __JL_cCamera_HG_20130318__
#define __JL_cCamera_HG_20130318__

#include "cMatrix4x4.h"

class cCamera
{
public:
	cCamera();
	virtual ~cCamera();

	const cVector3& GetPosition() const;
	void SetPosition( const cVector3& pos );
	
	float GetTargetDistance() const;
	void SetTargetDistance( float dist );

	cVector3 GetTarget() const;

	const cQuaternion& GetRotation() const;
	void SetRotation( const cQuaternion& rot );
	void SetRotation( float yaw, float pitch, float roll );

	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspect() const;
	const cVector2& GetFov() const;
	float GetFovY() const;
	float GetFovX() const;
	const cVector2& GetNearWindowSize() const;
	const cVector2& GetFarWindowSize() const;

	void SetView( const cMatrix4x4& view );
	void SetScreen( float w, float h );
	void SetLens( float fovY, float zNear, float zFar );
	
	cMatrix4x4 GetView();
	cMatrix4x4 GetOrthogonalProjection();

	const cMatrix4x4& GetPerspectiveProjection() const;

	void Yaw( float radians );
	void Pitch( float radians );
	void Roll( float radians );
protected:
	void UpdateProjection();
	/// Projection matrix
	cMatrix4x4 mProjection;
	/// Viewing target distance
	float			mTargetDistance;
	/// Position of the camera
	cVector3		mPosition;
	/// Rotation of the camera
	cQuaternion		mRotation;

	/// Field of view in X and Y directions
	cVector2		mFov;
	/// Aspect ratio Width / Height
	float			mAspectRatio;
	/// Near Z clipping plane distance
	float			mNearZ;
	/// Far Z clipping plane distance
	float			mFarZ;
	/// Size of the near window
	cVector2		mNearWindowSize;
	/// Size of the far window
	cVector2		mFarWindowSize;
	/// Size of the screen
	cVector2		mScreenSize;
};

#endif  //  __JL_cCamera_HG_20130318__