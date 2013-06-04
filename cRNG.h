/* Random number generator class
 * James Lucas
 * uses a Mersenne Twister to generate uniform variates
 * uses a Ziggurat algorithm to generate standard uniform variates
 */

#ifndef __JL_cRNG_HG_20130314__
#define __JL_cRNG_HG_20130314__


class cRNG
{
public:
	cRNG();
	cRNG( unsigned long s );
	~cRNG();
	
	unsigned long Random();
	
	double Unif();
	double Unif( double a, double b );
	
	double Normal();
	double Normal( double mu, double var );

	static void BuildPerlinMap( double** ppMap, int w, int h, double pVal );
private:
	cRNG( const cRNG& r ) {}
	void operator=( const cRNG& r ) {}

	void SetSeed( unsigned long s );
	double PerlinFade( double f );
	double PerlinGrad( int hash, double x, double y, double z );
	double Lerp( double a, double b, double t );
	double GetPerlinValue( int* p, double x, double y, double z );
	double* kn;
	double* wn;
	double* fn;

	int MT_Next;
	// constants that work well
	int MT_N;
	int MT_M;
	// matrix A
	unsigned long MT_A;
	// upper limit
	unsigned long MT_U;
	// lower limit
	unsigned long MT_L;
	// maximum
	unsigned long MT_MAX;
	// for convenience
	double MT_FACT;
	// pool
	unsigned long* x;

	void Setup();
	void BuildZiggs();
};

#endif  //  __JL_cRNG_HG_20130314__