#ifndef __JL_cConvexHullGenerator_HG_20130315__
#define __JL_cConvexHullGenerator_HG_20130315__

// TO DO:  Look up that convex hull project from 3rd year and stick it in here!

#include <vector>
#include "cVector3.h"

class cConvexHullGenerator
{
public:
	public:
	cConvexHullGenerator();
	virtual ~cConvexHullGenerator();

	bool Generate( const std::vector<cVector3>& coords, float shrink, float shrinkClamp );

	float InnerRadius;
	float OuterRadius;
};


#endif