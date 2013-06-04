#ifndef __JL_cMeshGenerator_HG_20130315__
#define __JL_cMeshGenerator_HG_20130315__

#include "cVector3.h"
#include "iMesh_Templates.h"

class cMeshGenerator
{
public:
	class cVertex
	{
	public:
		cVertex() {}
		cVertex( const cVector3& pos, const cVector3& norm, const cVector3& tangent, const cTexCoord& texCoord )
			: Position(pos), Normal(norm), Tangent(tangent), TexCoord(texCoord) {}
		cVertex( float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float tu, float tv )
			: Position(px,py,pz), Normal(nx,ny,nz), Tangent(tx,ty,tz), TexCoord(tu,tv) {}
		cVertex( const cVertex& other )
			: Position(other.Position), Normal(other.Normal), Tangent(other.Tangent), TexCoord(other.TexCoord) {}
		cVertex& operator = ( const cVertex& other )
		{
			if ( &other != this )
			{
				Position = other.Position;
				Normal = other.Normal;
				Tangent = other.Tangent;
				TexCoord = other.TexCoord;
			}
			return *this;
		}
		~cVertex() {}

		cVector3 Position;
		cVector3 Normal;
		cTexCoord TexCoord;
		cVector3 Tangent;
	};

	class cMesh : public iMeshA<cVertex>
	{
	public:
		cMesh() {}
		virtual ~cMesh() {}
	};

	cMeshGenerator() {}
	virtual ~cMeshGenerator() {}

	void CreateBox( float width, float height, float depth, cMesh& mesh );

	void CreateSphere( float radius, unsigned int slices, unsigned int stacks, cMesh& mesh );

	void Subdivide( cMesh& mesh, bool doMerge = true );

	void CreateGeosphere( float radius, unsigned int numSubdivisions, cMesh& mesh );

	void CreateCylinder( float bottomRadius, float topRadius, float height, unsigned int slices, unsigned int stacks, cMesh& mesh );

	void CreateGrid(float width, float depth, unsigned int m, unsigned int n, cMesh& mesh );

	void CreateFullScreenQuad( cMesh& mesh );
protected:
	void BuildCylinderTopCap( float bottomRadius, float topRadius, float height, unsigned int sliceCount, unsigned int stackCount, cMesh& mesh );
	void BuildCylinderBottomCap( float bottomRadius, float topRadius, float height, unsigned int sliceCount, unsigned int stackCount, cMesh& mesh );
};

#endif