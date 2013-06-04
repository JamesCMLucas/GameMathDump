#include "cMeshGenerator.h"
#include "nMath.h"

void cMeshGenerator::CreateBox( float width, float height, float depth, cMesh& mesh )
{
	mesh.VerticesA.clear();
	mesh.Indices.clear();

	//
	// Create the vertices.
	//

	cVertex v[24];

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	// Fill in the front face vertex data.
	v[0] = cVertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = cVertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = cVertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = cVertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = cVertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[5] = cVertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[6] = cVertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[7] = cVertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8]  = cVertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9]  = cVertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = cVertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = cVertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = cVertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = cVertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = cVertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = cVertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = cVertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = cVertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = cVertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = cVertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = cVertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = cVertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = cVertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = cVertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	mesh.VerticesA.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	unsigned int i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7]  = 5; i[8]  = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] =  9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	mesh.Indices.assign(&i[0], &i[36]);
}

void cMeshGenerator::CreateSphere( float radius, unsigned int slices, unsigned int stacks, cMesh& mesh )
{
	mesh.VerticesA.clear();
	mesh.Indices.clear();

	cVertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	cVertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	mesh.VerticesA.push_back( topVertex );

	float phiStep   = nMath::PI / stacks;
	float thetaStep = 2.0f * nMath::PI / slices;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for( unsigned int i = 1; i <= stacks - 1; i++ )
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for( unsigned int j = 0; j <= slices; j++ )
		{
			float theta = j*thetaStep;

			cVertex v;

			// spherical to cartesian
			v.Position.x = radius*sinf(phi)*cosf(theta);
			v.Position.y = radius*cosf(phi);
			v.Position.z = radius*sinf(phi)*sinf(theta);
			v.Position.Normalize();

			// Partial derivative of P with respect to theta
			v.Tangent.x = -radius*sinf(phi)*sinf(theta);
			v.Tangent.y = 0.0f;
			v.Tangent.z = +radius*sinf(phi)*cosf(theta);
			v.Tangent.Normalize();


			v.TexCoord.x = theta / nMath::PI_MUL_2;
			v.TexCoord.y = phi / nMath::PI;

			mesh.VerticesA.push_back( v );
		}
	}

	mesh.VerticesA.push_back( bottomVertex );

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for( unsigned int i = 1; i <= slices; i++ )
	{
		mesh.Indices.push_back(0);
		mesh.Indices.push_back(i+1);
		mesh.Indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = slices + 1;
	for( unsigned int i = 0; i < stacks-2; i++ )
	{
		for( unsigned int j = 0; j < slices; j++ )
		{
			mesh.Indices.push_back(baseIndex + i*ringVertexCount + j);
			mesh.Indices.push_back(baseIndex + i*ringVertexCount + j+1);
			mesh.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j);

			mesh.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j);
			mesh.Indices.push_back(baseIndex + i*ringVertexCount + j+1);
			mesh.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j+1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	unsigned int southPoleIndex = mesh.VerticesA.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for( unsigned int i = 0; i < slices; i++ )
	{
		mesh.Indices.push_back(southPoleIndex);
		mesh.Indices.push_back(baseIndex+i);
		mesh.Indices.push_back(baseIndex+i+1);
	}
}

void cMeshGenerator::Subdivide( cMesh& mesh, bool doMerge )
{
	// Save a copy of the input geometry.
	cMesh inputCopy = mesh;


	mesh.VerticesA.resize(0);
	mesh.Indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	unsigned int numTris = inputCopy.Indices.size() / 3;
	for( unsigned int i = 0; i < numTris; i++ )
	{
		cVertex v0 = inputCopy.VerticesA[ inputCopy.Indices[i*3+0] ];
		cVertex v1 = inputCopy.VerticesA[ inputCopy.Indices[i*3+1] ];
		cVertex v2 = inputCopy.VerticesA[ inputCopy.Indices[i*3+2] ];

		//
		// Generate the midpoints.
		//

		cVertex m0, m1, m2;

		// For subdivision, we just care about the position component.  We derive the other
		// vertex components in CreateGeosphere.
		m0.Position = ( v0.Position + v1.Position ) * 0.5f;
		m1.Position = ( v1.Position + v2.Position ) * 0.5f;
		m2.Position = ( v0.Position + v2.Position ) * 0.5f;

		m0.Normal = ( v0.Normal + v1.Normal ) * 0.5f;
		m1.Normal = ( v1.Normal + v2.Normal ) * 0.5f;
		m2.Normal = ( v0.Normal + v2.Normal ) * 0.5f;

		m0.TexCoord = ( v0.TexCoord + v1.TexCoord ) * 0.5f;
		m1.TexCoord = ( v1.TexCoord + v2.TexCoord ) * 0.5f;
		m2.TexCoord = ( v0.TexCoord + v2.TexCoord ) * 0.5f;

		m0.Tangent = ( v0.Tangent + v1.Tangent ) * 0.5f;
		m1.Tangent = ( v1.Tangent + v2.Tangent ) * 0.5f;
		m2.Tangent = ( v0.Tangent + v2.Tangent ) * 0.5f;

		//
		// Add new geometry.
		//
		unsigned int idx = mesh.VerticesA.size();

		mesh.VerticesA.push_back(v0); // 0
		mesh.VerticesA.push_back(v1); // 1
		mesh.VerticesA.push_back(v2); // 2
		mesh.VerticesA.push_back(m0); // 3
		mesh.VerticesA.push_back(m1); // 4
		mesh.VerticesA.push_back(m2); // 5


		mesh.Indices.push_back(idx+0);
		mesh.Indices.push_back(idx+3);
		mesh.Indices.push_back(idx+5);

		mesh.Indices.push_back(idx+3);
		mesh.Indices.push_back(idx+4);
		mesh.Indices.push_back(idx+5);

		mesh.Indices.push_back(idx+5);
		mesh.Indices.push_back(idx+4);
		mesh.Indices.push_back(idx+2);

		mesh.Indices.push_back(idx+3);
		mesh.Indices.push_back(idx+1);
		mesh.Indices.push_back(idx+4);
	}
	if ( !doMerge )
	{
		return;
	}

}

void cMeshGenerator::CreateGeosphere( float radius, unsigned int numSubdivisions, cMesh& mesh )
{
	// Put a cap on the number of subdivisions.
	numSubdivisions = nMath::Min( numSubdivisions, (unsigned int)6 );

	// Approximate a sphere by tessellating an icosahedron.

	const float X = 0.525731f; 
	const float Z = 0.850651f;

	cVector3 pos[12] = 
	{
		cVector3(-X, 0.0f, Z),  cVector3(X, 0.0f, Z),  
		cVector3(-X, 0.0f, -Z), cVector3(X, 0.0f, -Z),    
		cVector3(0.0f, Z, X),   cVector3(0.0f, Z, -X), 
		cVector3(0.0f, -Z, X),  cVector3(0.0f, -Z, -X),    
		cVector3(Z, X, 0.0f),   cVector3(-Z, X, 0.0f), 
		cVector3(Z, -X, 0.0f),  cVector3(-Z, -X, 0.0f)
	};

	unsigned long k[60] = 
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,    
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0, 
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
	};

	mesh.VerticesA.resize(12);
	mesh.Indices.resize(60);

	for( unsigned int i = 0; i < 12; i++ )
	{
		mesh.VerticesA[i].Position = pos[i];
	}

	for( unsigned int i = 0; i < 60; i++ )
	{
		mesh.Indices[i] = k[i];
	}

	for( unsigned int i = 0; i < numSubdivisions; i++ )
	{
		Subdivide( mesh );
	}

	// Project vertices onto sphere and scale.
	for( unsigned int i = 0; i < mesh.VerticesA.size(); i++ )
	{
		// Project onto unit sphere.
		cVector3 n = mesh.VerticesA[i].Position;
		n.Normalize();

		// Project onto sphere.
		cVector3 p = n * radius;

		mesh.VerticesA[i].Position = p;
		mesh.VerticesA[i].Normal = n;

		// Derive texture coordinates from spherical coordinates.
		float theta = nMath::AngleFromXY(
			mesh.VerticesA[i].Position.x, 
			mesh.VerticesA[i].Position.z);

		float phi = acosf(mesh.VerticesA[i].Position.y / radius);

		mesh.VerticesA[i].TexCoord.x = theta / nMath::PI_MUL_2;
		mesh.VerticesA[i].TexCoord.y = phi / nMath::PI;

		// Partial derivative of P with respect to theta
		mesh.VerticesA[i].Tangent.x = -radius*sinf(phi)*sinf(theta);
		mesh.VerticesA[i].Tangent.y = 0.0f;
		mesh.VerticesA[i].Tangent.z = +radius*sinf(phi)*cosf(theta);
		mesh.VerticesA[i].Tangent.Normalize();
	}
}

void cMeshGenerator::CreateCylinder( float bottomRadius, float topRadius, float height, unsigned int slices, unsigned int stacks, cMesh& mesh )
{
	mesh.VerticesA.clear();
	mesh.Indices.clear();

	//
	// Build Stacks.
	// 

	float stackHeight = height / stacks;

	// Amount to increment radius as we move up each stack level from bottom to top.
	float radiusStep = ( topRadius - bottomRadius ) / stacks;

	unsigned int ringCount = stacks + 1;

	// Compute vertices for each stack ring starting at the bottom and moving up.
	for( unsigned int i = 0; i < ringCount; i++ )
	{
		float y = -0.5f*height + i*stackHeight;
		float r = bottomRadius + i*radiusStep;

		// vertices of ring
		float dTheta = 2.0f*nMath::PI/slices;
		for( unsigned int j = 0; j <= slices; j++ )
		{
			cVertex vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);

			vertex.Position = cVector3( r*c, y, r*s );

			vertex.TexCoord.x = (float)j/slices;
			vertex.TexCoord.y = 1.0f - (float)i/stacks;

			// Cylinder can be parameterized as follows, where we introduce v
			// parameter that goes in the same direction as the v tex-coord
			// so that the bitangent goes in the same direction as the v tex-coord.
			//   Let r0 be the bottom radius and let r1 be the top radius.
			//   y(v) = h - hv for v in [0,1].
			//   r(v) = r1 + (r0-r1)v
			//
			//   x(t, v) = r(v)*cos(t)
			//   y(t, v) = h - hv
			//   z(t, v) = r(v)*sin(t)
			// 
			//  dx/dt = -r(v)*sin(t)
			//  dy/dt = 0
			//  dz/dt = +r(v)*cos(t)
			//
			//  dx/dv = (r0-r1)*cos(t)
			//  dy/dv = -h
			//  dz/dv = (r0-r1)*sin(t)

			// This is unit length.
			vertex.Tangent = cVector3(-s, 0.0f, c);

			float dr = bottomRadius-topRadius;
			cVector3 bitangent(dr*c, -height, dr*s);

			cVector3 T = vertex.Tangent;
			cVector3 B = bitangent;
			cVector3 N = T.Cross( B );
			N.Normalize();
			vertex.Normal = N;

			mesh.VerticesA.push_back(vertex);
		}
	}
	// Add one because we duplicate the first and last vertex per ring
	// since the texture coordinates are different.
	unsigned int ringVertexCount = slices + 1;

	// Compute indices for each stack.
	for( unsigned int i = 0; i < stacks; i++ )
	{
		for( unsigned int j = 0; j < slices; j++ )
		{
			mesh.Indices.push_back(i*ringVertexCount + j);
			mesh.Indices.push_back((i+1)*ringVertexCount + j);
			mesh.Indices.push_back((i+1)*ringVertexCount + j+1);

			mesh.Indices.push_back(i*ringVertexCount + j);
			mesh.Indices.push_back((i+1)*ringVertexCount + j+1);
			mesh.Indices.push_back(i*ringVertexCount + j+1);
		}
	}

	BuildCylinderTopCap( topRadius, topRadius, height, slices, stacks, mesh );
	BuildCylinderBottomCap( bottomRadius, topRadius, height, slices, stacks, mesh );
}

void cMeshGenerator::BuildCylinderTopCap( float bottomRadius, float topRadius, float height, unsigned int slices, unsigned int stacks, cMesh& mesh )
{
	unsigned int baseIndex = mesh.VerticesA.size();

	float y = 0.5f*height;
	float dTheta = 2.0f*nMath::PI/slices;

	// Duplicate cap ring vertices because the texture coordinates and normals differ.
	for( unsigned int i = 0; i <= slices; i++ )
	{
		float x = topRadius*cosf(i*dTheta);
		float z = topRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x/height + 0.5f;
		float v = z/height + 0.5f;

		mesh.VerticesA.push_back( cVertex(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v) );
	}

	// Cap center vertex.
	mesh.VerticesA.push_back( cVertex(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f) );

	// Index of center vertex.
	unsigned int centerIndex = mesh.VerticesA.size() - 1;

	for( unsigned int i = 0; i < slices; i++ )
	{
		mesh.Indices.push_back(centerIndex);
		mesh.Indices.push_back(baseIndex + i+1);
		mesh.Indices.push_back(baseIndex + i);
	}
}

void cMeshGenerator::BuildCylinderBottomCap( float bottomRadius, float topRadius, float height, unsigned int slices, unsigned int stacks, cMesh& mesh )
{
	// 
	// Build bottom cap.
	//

	unsigned int baseIndex = mesh.VerticesA.size();
	float y = -0.5f*height;

	// vertices of ring
	float dTheta = 2.0f*nMath::PI/slices;
	for( unsigned int i = 0; i <= slices; i++ )
	{
		float x = bottomRadius*cosf(i*dTheta);
		float z = bottomRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x/height + 0.5f;
		float v = z/height + 0.5f;

		mesh.VerticesA.push_back( cVertex(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v) );
	}

	// Cap center vertex.
	mesh.VerticesA.push_back( cVertex(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f) );

	// Cache the index of center vertex.
	unsigned int centerIndex = mesh.VerticesA.size() - 1;

	for( unsigned int i = 0; i < slices; i++ )
	{
		mesh.Indices.push_back(centerIndex);
		mesh.Indices.push_back(baseIndex + i);
		mesh.Indices.push_back(baseIndex + i+1);
	}
}

void cMeshGenerator::CreateGrid( float width, float depth, unsigned int m, unsigned int n, cMesh& mesh )
{
	unsigned int vertexCount = m*n;
	unsigned int faceCount   = (m-1)*(n-1)*2;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;

	float dx = width / (n-1);
	float dz = depth / (m-1);

	float du = 1.0f / (n-1);
	float dv = 1.0f / (m-1);

	mesh.VerticesA.resize(vertexCount);
	for( unsigned int i = 0; i < m; i++ )
	{
		float z = halfDepth - i*dz;
		for( unsigned int j = 0; j < n; ++j)
		{
			float x = -halfWidth + j*dx;

			mesh.VerticesA[i*n+j].Position = cVector3( x, 0.0f, z );
			mesh.VerticesA[i*n+j].Normal   = cVector3( 0.0f, 1.0f, 0.0f );
			mesh.VerticesA[i*n+j].Tangent = cVector3( 1.0f, 0.0f, 0.0f );

			// Stretch texture over grid.
			mesh.VerticesA[i*n+j].TexCoord.x = j*du;
			mesh.VerticesA[i*n+j].TexCoord.y = i*dv;
		}
	}

	//
	// Create the indices.
	//

	mesh.Indices.resize(faceCount*3); // 3 indices per face

	// Iterate over each quad and compute indices.
	unsigned int k = 0;
	for( unsigned int i = 0; i < m-1; i++ )
	{
		for( unsigned int j = 0; j < n-1; j++ )
		{
			mesh.Indices[k]   = i*n+j;
			mesh.Indices[k+1] = i*n+j+1;
			mesh.Indices[k+2] = (i+1)*n+j;

			mesh.Indices[k+3] = (i+1)*n+j;
			mesh.Indices[k+4] = i*n+j+1;
			mesh.Indices[k+5] = (i+1)*n+j+1;

			k += 6; // next quad
		}
	}
}

void cMeshGenerator::CreateFullScreenQuad( cMesh& mesh )
{
	mesh.VerticesA.resize(4);
	mesh.Indices.resize(6);

	// Position coordinates specified in NDC space.
	mesh.VerticesA[0] = cVertex(
		-1.0f, -1.0f, 0.0f, 
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f);

	mesh.VerticesA[1] = cVertex(
		-1.0f, +1.0f, 0.0f, 
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f);

	mesh.VerticesA[2] = cVertex(
		+1.0f, +1.0f, 0.0f, 
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f);

	mesh.VerticesA[3] = cVertex(
		+1.0f, -1.0f, 0.0f, 
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f);

	mesh.Indices[0] = 0;
	mesh.Indices[1] = 1;
	mesh.Indices[2] = 2;

	mesh.Indices[3] = 0;
	mesh.Indices[4] = 2;
	mesh.Indices[5] = 3;
}