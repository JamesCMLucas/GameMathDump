#include "cConvexHullGenerator.h"


cConvexHullGenerator::cConvexHullGenerator()
	: InnerRadius(0.f)
	, OuterRadius(0.f)
{

}

cConvexHullGenerator::~cConvexHullGenerator()
{

}

bool cConvexHullGenerator::Generate( const std::vector<cVector3>& coords, float shrink, float shrinkClamp )
{
	if ( coords.size() < 1 )
	{
		return false;
	}




	return false;
}
