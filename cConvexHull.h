#ifndef __JL_cConvexHull_HG_20130314__
#define __JL_cConvexHull_HG_20130314__

#include "cVector3.h"
#include <vector>
#include "Geometry_Primitives.h"


/// NOT IMPLEMENTED
/// TO DO: SEE CONVEX HULL GENERATOR
class cConvexHull
{
public:
	struct sHullVertex
	{
		sHullVertex() {}
		sHullVertex( const cVector3& pos ) : Position(pos) {}

		cVector3 Position;
		std::vector<unsigned int> Edges;
	};

	struct sHullEdge
	{
		sHullEdge() {}
		sHullEdge( unsigned int vA, unsigned int vB, unsigned int p )
			: VertexAIndex(vA), VertexBIndex(vB), PlaneIndex(p) {}
		unsigned int VertexAIndex;
		unsigned int VertexBIndex;
		unsigned int PlaneIndex;
	};

	cConvexHull() {}

	std::vector<sHullVertex>	Vertices;
	std::vector<sHullEdge>		Edges;
	std::vector<sPlane>			Planes;
};

#endif  //  __JL_cConvexHull_HG_20130314__