#include "cRNG.h"
#include <Windows.h>
#include <cmath>


cRNG::cRNG()
{
	this->Setup();

	LARGE_INTEGER tmpLrg;
	QueryPerformanceCounter( &tmpLrg );
	unsigned long long uLL = static_cast<unsigned long long>( tmpLrg.QuadPart );
	unsigned long s = static_cast<unsigned long>( uLL );

	SetSeed( s );
	BuildZiggs();
}


cRNG::cRNG( unsigned long s )
{
	this->Setup();
	SetSeed( s );
	BuildZiggs();
}

cRNG::~cRNG()
{
	delete[] x;
	delete[] kn;
	delete[] wn;
	delete[] fn;
};

void cRNG::SetSeed( unsigned long s )
{
	int i;

	x[0] = s & 0xffffffffUL;

	for ( i=1; i<MT_N; i++ )
	{
		x[i] = ( 1812433253UL * ( x[i-1] ^ ( x[i-1] >> 30 ) ) + i );
		x[i] &= MT_MAX;
	}
};

double cRNG::Unif()
{
	return Random()*MT_FACT;
};

double cRNG::Unif( double a, double b )
{
	double r = b - a;
	return ( Random()*MT_FACT )*r + a;
}

unsigned long cRNG::Random()
{
	unsigned long num, a;
	int i;

	// refill x if needed
	if ( MT_Next == MT_N ) {

		// reset the index

		MT_Next = 0;

		for ( i=0; i<MT_N-1; i++ ) {
			num = (x[i] & MT_U ) | x[i+1] & MT_L;
			a = ( num & 0x1UL ) ? MT_A : 0x0UL;
			x[i] = x[( i + MT_M ) % MT_N] ^ ( num >> 1 ) ^ a;
		}

		num = ( x[MT_N - 1] & MT_U ) | x[0] & MT_L;
		a = ( num & 0x1UL ) ? MT_A : 0x0UL;
		x[MT_N - 1] = x[MT_M - 1] ^ ( num >> 1 ) ^ a;
	}

	// get the next number
	num = x[MT_Next++];
	// black magic that improves distribution
	num ^= ( num >> 11 );
	num ^= ( num << 7 ) & 0x9d2c5680UL;
	num ^= ( num << 15 ) & 0xefc60000UL;
	num ^= ( num >> 18 );

	return num;
};

double cRNG::Normal()
{
	double x, y;
	long num = Random();
	long iz = num&127;

	if ( fabs(double(num)) < kn[iz] )
	{
		return num*wn[iz];
	}
	else
	{
		float r = 3.442620f;
		x = num*wn[iz];
		if ( iz == 0 )
		{
			while ( true )
			{
				x = -log( Unif() )*0.2904764;
				y = -log( Unif() );
				if ( ( y + y ) < ( x * x ) ) break;
			}
			return ( num > 0 )? r+x: -r-x;
		}

		if ( fn[iz] + Unif()*( fn[iz-1]-fn[iz] ) < exp( -0.5*x*x ) )
		{
			return x;
		}

		num = Random();
		iz = num&127;
		if ( fabs( double(num) ) < kn[iz] )
		{
			return num*wn[iz];
		}
	}
	return 0.0;
};

double cRNG::Normal( double mu, double var )
{
	return mu + Normal()*var;
}

void cRNG::Setup()
{
	MT_Next = 0;

	MT_N = 624;
	MT_M = 397;
	// matrix A
	MT_A = 0x9908b0dfUL;
	// upper limit
	MT_U = 0x80000000UL;
	// lower limit
	MT_L = 0x7fffffffUL;
	// maximum
	MT_MAX = 0xffffffffUL;
	// for convenience
	MT_FACT = ( 1.0 / ( MT_MAX + 1.0 ) );
	// pool
	x = new unsigned long[MT_N];
}

// building ziggurat tables for normal()
void cRNG::BuildZiggs()
{
	kn = new double[128];
	wn = new double[128];
	fn = new double[128];

	double m1 = 2147483648.0;
	double m2 = 4294967296.0;
	double dn = 3.442619855899;
	double tn = dn;
	double vn = 9.91256303526217e-3;
	double q = vn/exp( -.5*dn*dn );

	kn[0] = ( dn/q )*m1;
	kn[1] = 0;

	wn[0] = q/m1;
	wn[127] = dn/m1;

	fn[0] = 1.0;
	fn[127] = exp( -0.5*dn*dn );

	for ( int i = 126; i >= 1; i-- )
	{
		dn = sqrt( -2.0*log( vn/dn + exp( -0.5*dn*dn ) ) );
		kn[i + 1] = ( dn/tn )*m1;
		tn = dn;
		fn[i] = exp( -0.5*dn*dn );
		wn[i] = dn/m1;
	}
};

void cRNG::BuildPerlinMap( double** ppMap, int w, int h, double pVal )
{
	

	int* permutations = new int[256];
	cRNG* rng = new cRNG();
	for ( int i = 0; i < 256; i++ )
	{
		permutations[i] = (int)floor(rng->Unif() * 255.99);
	}

	for ( int i = 0; i < h; i++ )
	{
		for ( int j = 0; j < w; j++ )
		{
			double x = (double)j / ((double)w);
			double y = (double)i / ((double)h);
			double z = rng->GetPerlinValue( permutations, x, y, pVal );
			z = z - floor(z);
			ppMap[i][j] = z;
		}
	}

	delete [] permutations;
	delete rng;
}

double cRNG::PerlinFade( double f )
{
	return f * f * f * ( f * ( f * 6 - 15 ) + 10 );
}

double cRNG::PerlinGrad( int hash, double x, double y, double z )
{
	int h = hash & 15;
	double u = h < 8 ? x : y;
	double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double cRNG::Lerp( double a, double b, double t )
{
	return a + ( ( b - a ) * t );
}

double cRNG::GetPerlinValue( int* p, double x, double y, double z )
{
	int X = (int) floor(x) & 255;
	int Y = (int) floor(y) & 255;
	int Z = (int) floor(z) & 255;

	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	double u = PerlinFade( x );
	double v = PerlinFade( y );
	double w = PerlinFade( z );

	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;
	
	// blend
	double res = Lerp(w, Lerp(v, Lerp(u, PerlinGrad(p[AA], x, y, z), PerlinGrad(p[BA], x-1, y, z)), Lerp(u, PerlinGrad(p[AB], x, y-1, z), PerlinGrad(p[BB], x-1, y-1, z))),	Lerp(v, Lerp(u, PerlinGrad(p[AA+1], x, y, z-1), PerlinGrad(p[BA+1], x-1, y, z-1)), Lerp(u, PerlinGrad(p[AB+1], x, y-1, z-1),	PerlinGrad(p[BB+1], x-1, y-1, z-1))));
	return ( res + 1.0 ) * 0.5;
}
