#ifndef __JL_Rendering_Structs_2D_HG_20130403__
#define __JL_Rendering_Structs_2D_HG_20130403__

#include "cVector2.h"

/// Describes a rectangle used for 2D rendering
struct sRect2D
{
	sRect2D() : Rotation(0.f) {};
	sRect2D( const cVector2& pos, const cVector2& hw, float rotation = 0.f )
	{
		Position = pos;
		HalfWidths = hw;
		Rotation = rotation;
	}

	sRect2D( float xCentre, float yCentre, float xHalfWidth, float yHalfWidth, float rotation = 0.f )
	{
		Position = cVector2( xCentre, yCentre );
		HalfWidths = cVector2( xHalfWidth, yHalfWidth );
		Rotation = rotation;
	}

	// Centre of the rectangle
	cVector2 Position;
	// Half-widths (x,y)
	cVector2 HalfWidths;
	// Rotation (in radians)
	float Rotation;



	// Helper
	static sRect2D FromLeftRightTopBottom( float left, float right, float top, float bottom, float rotation = 0.f )
	{
		return sRect2D( (( right + left ) * 0.5f) , (( top + bottom ) * 0.5f), 
			(( right - left ) * 0.5f), (( top - bottom ) * 0.5f), rotation );
	}
	// Helper
	static sRect2D FromCentreWidths( float xCentre, float yCentre, float xWidth, float yWidth, float rotation = 0.f )
	{
		return sRect2D( xCentre, yCentre, ( xWidth * 0.5f ), ( yWidth * 0.5f ), rotation );
	}
};


#endif  //  __JL_Rendering_Structs_2D_HG_20130403__