#ifndef __JL_Scalar_Primitives_HG_20130314__
#define __JL_Scalar_Primitives_HG_20130314__

class cInt2
{
public:
	union
	{
		struct  
		{
			int x, y;
		};
		struct  
		{
			int a, b;
		};
	};
	

	cInt2() : x(0), y(0) {}
	cInt2( int x_, int y_ )
		: x(x_), y(y_) {}
	const int& operator[]( int i ) const { return (&x)[i]; }
	int& operator[](int i) { return (&x)[i]; }
};

class cInt3
{
public:
	union
	{
		struct 
		{
			int x, y, z;
		};
		struct 
		{
			int a, b, c;
		};
	};

	cInt3() : x(0), y(0), z(0) {}
	cInt3( int x_, int y_, int z_ )
		: x(x_), y(y_), z(z_) {}
	const int& operator[]( int i ) const { return (&x)[i]; }
	int& operator[](int i) { return (&x)[i]; }
};

class cInt4
{
public:
	union
	{
		struct 
		{
			int x, y, z, w;
		};
		struct 
		{
			int a, b, c, d;
		};
	};

	cInt4() : x(0), y(0), z(0), w(0) {}
	cInt4( int x_, int y_, int z_, int w_ )
		: x(x_), y(y_), z(z_), w(w_) {}
	const int& operator[]( int i ) const { return (&x)[i]; }
	int& operator[](int i) { return (&x)[i]; }
};

class cUint2
{
public:
	union
	{
		struct 
		{
			unsigned int x, y;
		};
		struct 
		{
			unsigned int a, b;
		};
	};

	cUint2() : x(0), y(0) {}
	cUint2( unsigned int x_, unsigned int y_ )
		: x(x_), y(y_) {}
	const unsigned int& operator[]( int i ) const { return (&x)[i]; }
	unsigned int& operator[](int i) { return (&x)[i]; }
};

class cUint3
{
public:
	union
	{
		struct 
		{
			unsigned int x, y, z;
		};
		struct 
		{
			unsigned int a, b, c;
		};
	};

	cUint3() : x(0), y(0), z(0) {}
	cUint3( unsigned int x_, unsigned int y_, unsigned int z_ )
		: x(x_), y(y_), z(z_) {}
	const unsigned int& operator[]( int i ) const { return (&x)[i]; }
	unsigned int& operator[](int i) { return (&x)[i]; }
};

class cUint4
{
public:
	union
	{
		struct 
		{
			unsigned int x, y, z, w;
		};
		struct 
		{
			unsigned int a, b, c, d;
		};
	};

	cUint4() : x(0), y(0), z(0), w(0) {}
	cUint4( unsigned int x_, unsigned int y_, unsigned int z_, unsigned int w_ )
		: x(x_), y(y_), z(z_), w(w_) {}
	const unsigned int& operator[]( int i ) const { return (&x)[i]; }
	unsigned int& operator[](int i) { return (&x)[i]; }
};

class cFloat2
{
public:
	union
	{
		struct 
		{
			float x, y;
		};
		struct
		{
			float u, v;
		};
	};

	cFloat2() : x(0), y(0) {}
	cFloat2( float x_, float y_ )
		: x(x_), y(y_) {}
	const float& operator[]( int i ) const { return (&x)[i]; }
	float& operator[]( int i) { return (&x)[i]; }
};

class cFloat3
{
public:
	union
	{
		struct 
		{
			float x, y, z;
		};
		struct
		{
			float r, b, g;
		};
	};
	cFloat3() : x(0), y(0), z(0) {}
	cFloat3( float x_, float y_, float z_ )
		: x(x_), y(y_), z(z_) {}
	const float& operator[]( int i ) const { return (&x)[i]; }
	float& operator[]( int i) { return (&x)[i]; }
};

class cFloat4
{
public:
	union
	{
		struct 
		{
			float x, y, z, w;
		};
		struct
		{
			float r, b, g, a;
		};
	};
	cFloat4() : x(0), y(0), z(0), w(0) {}
	cFloat4( float x_, float y_, float z_, float w_ )
		: x(x_), y(y_), z(z_), w(w_) {}
	const float& operator[]( int i ) const { return (&x)[i]; }
	float& operator[]( int i) { return (&x)[i]; }
};

#endif  // __JL_Scalar_Primitives_HG_20130314__