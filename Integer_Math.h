#include <float.h>
#ifndef __JL_Integer_Math_HG_20130315__
#define __JL_Integer_Math_HG_20130315__

namespace nInt
{
	typedef long long int64;
	typedef unsigned int uint;
	typedef unsigned long long uint64;

	class cPoint64
	{
	public:
		int64 x;
		int64 y;
		int64 z;

		cPoint64( int64 x, int64 y, int64 z )
			: x(x), y(y), z(z) {}

		bool IsZero()
		{
			return ( x == 0 ) && ( y == 0 ) && ( z == 0 );
		}

		int64 Dot( const cPoint64& b ) const
		{
			return x * b.x + y * b.y + z * b.z;
		}
	};

	class cPoint32
	{
	public:
		int x;
		int y;
		int z;
		int index;

		cPoint32() {}

		cPoint32(int x, int y, int z)
			: x(x), y(y), z(z), index(-1) {}

		bool operator == ( const cPoint32& b ) const
		{
			return ( x == b.x ) && ( y == b.y ) && ( z == b.z );
		}

		bool operator != ( const cPoint32& b ) const
		{
			return ( x != b.x ) || ( y != b.y ) || ( z != b.z );
		}

		bool IsZero()
		{
			return ( x == 0 ) && ( y == 0 ) && ( z == 0 );
		}

		cPoint64 Cross( const cPoint32& b ) const
		{
			return cPoint64(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
		}

		cPoint64 Cross( const cPoint64& b ) const
		{
			return cPoint64(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
		}

		int64 Dot( const cPoint32& b ) const
		{
			return x * b.x + y * b.y + z * b.z;
		}

		int64 Dot( const cPoint64& b ) const
		{
			return x * b.x + y * b.y + z * b.z;
		}

		cPoint32 operator + ( const cPoint32& b ) const
		{
			return cPoint32(x + b.x, y + b.y, z + b.z);
		}

		cPoint32 operator - ( const cPoint32& b ) const
		{
			return cPoint32(x - b.x, y - b.y, z - b.z);
		}
	};

	class cInt128
	{
	public:
		uint64 low;
		uint64 high;

		cInt128() {}

		cInt128( uint64 low, uint64 high )
			: low(low), high(high) {}

		cInt128( uint64 low )
			: low(low), high(0) {}

		cInt128( int64 value )
			: low(value), high((value >= 0) ? 0 : (uint64) -1LL) {}

		static cInt128 mul( int64 a, int64 b );

		static cInt128 mul( uint64 a, uint64 b );

		cInt128 operator - () const
		{
			return cInt128( (uint64) -(int64)low, ~high + (low == 0) );
		}

		cInt128 operator + (const cInt128& b) const
		{
			uint64 lo = low + b.low;
			return cInt128(lo, high + b.high + (lo < low));
		}

		cInt128 operator - ( const cInt128& b ) const
		{
			return *this + -b;
		}

		cInt128& operator += ( const cInt128& b )
		{
			uint64 lo = low + b.low;
			if (lo < low)
			{
				++high;
			}
			low = lo;
			high += b.high;

			return *this;
		}

		cInt128& operator ++ ()
		{
			if (++low == 0)
			{
				++high;
			}
			return *this;
		}

		cInt128 operator * (int64 b) const;

		float ToFloat() const
		{
			return ((int64) high >= 0) ? float(high) * (float(0x100000000LL) * float(0x100000000LL)) + float(low)
				: -(-*this).ToFloat();
		}

		int GetSign() const
		{
			return ( (int64) high < 0 ) ? -1 : (high || low) ? 1 : 0;
		}

		bool operator < ( const cInt128& b ) const
		{
			return (high < b.high) || ( (high == b.high) && (low < b.low) );
		}

		int ucmp( const cInt128&b ) const
		{
			if ( high < b.high )
			{
				return -1;
			}
			if ( high > b.high )
			{
				return 1;
			}
			if ( low < b.low )
			{
				return -1;
			}
			if ( low > b.low )
			{
				return 1;
			}
			return 0;
		}
	};


	class cRational64
	{
	private:
		uint64 mNumerator;
		uint64 mDenominator;
		int sign;

	public:
		cRational64( int64 numerator, int64 denominator )
		{
			if ( numerator > 0 )
			{
				sign = 1;
				mNumerator = (uint64) numerator;
			}
			else if ( numerator < 0 )
			{
				sign = -1;
				mNumerator = (uint64) -numerator;
			}
			else
			{
				sign = 0;
				mNumerator = 0;
			}
			if ( denominator > 0 )
			{
				mDenominator = (uint64) denominator;
			}
			else if ( denominator < 0 )
			{
				sign = -sign;
				mDenominator = (uint64) -denominator;
			}
			else
			{
				mDenominator = 0;
			}
		}

		bool IsNegativeInfinity() const
		{
			return (sign < 0) && (mDenominator == 0);
		}

		bool IsNaN() const
		{
			return (sign == 0) && (mDenominator == 0);
		}

		int Compare(const cRational64& b) const;

		float ToFloat() const
		{
			return sign * ((mDenominator == 0) ? FLT_MAX : (float) mNumerator / mDenominator);
		}
	};


	class cRational128
	{
	private:
		cInt128 numerator;
		cInt128 denominator;
		int sign;
		bool isInt64;

	public:
		cRational128( int64 value )
		{
			if ( value > 0 )
			{
				sign = 1;
				this->numerator = value;
			}
			else if ( value < 0 )
			{
				sign = -1;
				this->numerator = -value;
			}
			else
			{
				sign = 0;
				this->numerator = (uint64) 0;
			}
			this->denominator = (uint64) 1;
			isInt64 = true;
		}

		cRational128( const cInt128& numerator, const cInt128& denominator )
		{
			sign = numerator.GetSign();
			if ( sign >= 0 )
			{
				this->numerator = numerator;
			}
			else
			{
				this->numerator = -numerator;
			}
			int dsign = denominator.GetSign();
			if ( dsign >= 0 )
			{
				this->denominator = denominator;
			}
			else
			{
				sign = -sign;
				this->denominator = -denominator;
			}
			isInt64 = false;
		}

		int Compare( const cRational128& b ) const;

		int Compare( int64 b ) const;

		float ToFloat() const
		{
			return sign * ( (denominator.GetSign() == 0) ? FLT_MAX : numerator.ToFloat() / denominator.ToFloat() );
		}
	};

	class cPointR128
	{
	public:
		cInt128 x;
		cInt128 y;
		cInt128 z;
		cInt128 denominator;

		cPointR128() {}

		cPointR128( cInt128 x, cInt128 y, cInt128 z, cInt128 denominator )
			: x(x), y(y), z(z), denominator(denominator) {}

		float GetX() const
		{
			return x.ToFloat() / denominator.ToFloat();
		}

		float GetY() const
		{
			return y.ToFloat() / denominator.ToFloat();
		}

		float GetZ() const
		{
			return z.ToFloat() / denominator.ToFloat();
		}
	};

	
	template<typename UWord, typename UHWord>
	class cIntMul
	{
	private:
		static uint high( uint64 value )
		{
			return (uint) (value >> 32);
		}

		static uint low( uint64 value )
		{
			return (uint) value;
		}

		static uint64 mul( uint a, uint b )
		{
			return (uint64) a * (uint64) b;
		}

		static void shlHalf( uint64& value )
		{
			value <<= 32;
		}

		static uint64 high( cInt128 value )
		{
			return value.high;
		}

		static uint64 low( cInt128 value )
		{
			return value.low;
		}

		static cInt128 mul( uint64 a, uint64 b )
		{
			return cInt128::mul(a, b);
		}

		static void shlHalf( cInt128& value )
		{
			value.high = value.low;
			value.low = 0;
		}

	public:

		static void mul( UWord a, UWord b, UWord& resLow, UWord& resHigh )
		{
			UWord p00 = mul( low(a), low(b) );
			UWord p01 = mul( low(a), high(b) );
			UWord p10 = mul( high(a), low(b) );
			UWord p11 = mul( high(a), high(b) );
			UWord p0110 = UWord( low(p01) ) + UWord( low(p10) );
			p11 += high( p01 );
			p11 += high( p10 );
			p11 += high( p0110 );
			shlHalf( p0110 );
			p00 += p0110;
			if ( p00 < p0110 )
			{
				++p11;
			}
			resLow = p00;
			resHigh = p11;
		}
	};
};



#endif  //  __JL_Integer_Math_HG_20130315__