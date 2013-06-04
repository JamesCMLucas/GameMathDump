#ifndef __JL_iMeshT_HG_20130315__
#define __JL_iMeshT_HG_20130315__

#include <vector>

/// Describes an indexed mesh with one type of vertex
template <class A>
class iMeshA
{
public:
	typedef typename std::vector<A>::iterator VertexIA;
	typedef std::vector<unsigned int> IndexI;

	iMeshA() {}

	iMeshA( const iMeshA<A>& meshA )
		: VerticesA(meshA.VerticesA)
		, Indices(meshA.Indices) {}

	virtual ~iMeshA() {}
	
	std::vector<A> VerticesA;
	std::vector<unsigned int> Indices;
};

/// Describes an indexed mesh with two types of vertices
template <class A, class B>
class iMeshAB : public iMeshA<A>
{
public:
	typedef typename std::vector<B>::iterator VertexIB;

	iMeshAB() {}

	iMeshAB( const iMeshA<A>& meshA )
		: VerticesA(meshA.VerticesA)
		, Indices(meshA.Indices)
	{
		VerticesB.resize(VerticesA.size());
	}

	iMeshAB( const iMeshAB<A,B>& meshAB )
		: VerticesA(meshAB.VerticesA)
		, VerticesB(meshAB.VerticesB)
		, Indices(meshAB.Indices) {}

	virtual ~iMeshAB() {}

	std::vector<B> VerticesB;
};

/// Describes an indexed mesh with three types of vertices
template <class A, class B, class C>
class iMeshABC : public iMeshAB<A,B>
{
public:
	typedef typename std::vector<C>::iterator VertexIC;

	iMeshABC() {}

	iMeshABC( const iMeshA<A>& meshA )
		: VerticesA(meshA.VerticesA)
		, Indices(meshA.Indices)
	{
		VerticesB.resize(VerticesA.size());
		VerticesC.resize(VerticesA.size());
	}

	iMeshABC( const iMeshAB<A,B>& meshAB )
		: VerticesA(meshAB.VerticesA)
		, VerticesB(meshAB.VerticesB)
		, Indices(meshAB.Indices)
	{
		VerticesC.resize(VerticesA.size());
	}

	iMeshABC( const iMeshABC<A,B,C>& meshABC )
		: VerticesA(meshABC.VerticesA)
		, VerticesB(meshABC.VerticesB)
		, VerticesC(meshABC.VerticesC)
		, Indices(meshABC.Indices) {}

	virtual ~iMeshABC() {}

	std::vector<C> VerticesC;
};

/// Describes an indexed mesh with four types of vertices
template <class A, class B, class C, class D>
class iMeshABCD : public iMeshABC<A,B,C>
{
public:
	typedef typename std::vector<D>::iterator VertexID;

	iMeshABCD() {}

	iMeshABCD( const iMeshA<A>& meshA )
		: VerticesA(meshA.VerticesA)
		, Indices(meshA.Indices)
	{
		VerticesB.resize(VerticesA.size());
		VerticesC.resize(VerticesA.size());
		VerticesD.resize(VerticesA.size());
	}

	iMeshABCD( const iMeshAB<A,B>& meshAB )
		: VerticesA(meshAB.VerticesA)
		, VerticesB(meshAB.VerticesB)
		, Indices(meshAB.Indices)
	{
		VerticesC.resize(VerticesA.size());
		VerticesD.resize(VerticesA.size());
	}

	iMeshABCD( const iMeshABC<A,B,C>& meshABC )
		: VerticesA(meshABC.VerticesA)
		, VerticesB(meshABC.VerticesB)
		, VerticesC(meshABC.VerticesC)
		, Indices(meshABC.Indices)
	{
		VerticesD.resize(VerticesA.size());
	}

	iMeshABCD( const iMeshABCD<A,B,C,D>& meshABCD )
		: VerticesA(meshABCD.VerticesA)
		, VerticesB(meshABCD.VerticesB)
		, VerticesC(meshABCD.VerticesC)
		, VerticesD(meshABCD.VerticesD)
		, Indices(meshABCD.Indices) {}

	virtual ~iMeshABCD() {}

	std::vector<D> VerticesD;
};



#endif  // __JL_iMeshT_HG_20130315__