#include "Integer_Math.h"

namespace nInt
{
	cInt128 cInt128::operator*(int64 b) const
	{
		bool negative = (int64) high < 0;
		cInt128 a = negative ? -*this : *this;
		if (b < 0)
		{
			negative = !negative;
			b = -b;
		}
		cInt128 result = mul(a.low, (uint64) b);
		result.high += a.high * (uint64) b;
		return negative ? -result : result;
	}

	cInt128 cInt128::mul(int64 a, int64 b)
	{
		cInt128 result;

		bool negative = a < 0;
		if (negative)
		{
			a = -a;
		}
		if (b < 0)
		{
			negative = !negative;
			b = -b;
		}
		cIntMul<uint64, uint>::mul((uint64) a, (uint64) b, result.low, result.high);
		return negative ? -result : result;
	}

	cInt128 cInt128::mul(uint64 a, uint64 b)
	{
		cInt128 result;

		cIntMul<uint64, uint>::mul(a, b, result.low, result.high);

		return result;
	}

	int cRational64::Compare(const cRational64& b) const
	{
		if (sign != b.sign)
		{
			return sign - b.sign;
		}
		else if (sign == 0)
		{
			return 0;
		}

		//	return (numerator * b.denominator > b.numerator * denominator) ? sign : (numerator * b.denominator < b.numerator * denominator) ? -sign : 0;

		return sign * cInt128::mul(mNumerator, b.mDenominator).ucmp(cInt128::mul(mDenominator, b.mNumerator));
	}

	int cRational128::Compare(const cRational128& b) const
	{
		if (sign != b.sign)
		{
			return sign - b.sign;
		}
		else if (sign == 0)
		{
			return 0;
		}
		if (isInt64)
		{
			return -b.Compare(sign * (int64) numerator.low);
		}

		cInt128 nbdLow, nbdHigh, dbnLow, dbnHigh;
		cIntMul<cInt128, uint64>::mul(numerator, b.denominator, nbdLow, nbdHigh);
		cIntMul<cInt128, uint64>::mul(denominator, b.numerator, dbnLow, dbnHigh);

		int cmp = nbdHigh.ucmp(dbnHigh);
		if (cmp)
		{
			return cmp * sign;
		}
		return nbdLow.ucmp(dbnLow) * sign;
	}

	int cRational128::Compare(int64 b) const
	{
		if (isInt64)
		{
			int64 a = sign * (int64) numerator.low;
			return (a > b) ? 1 : (a < b) ? -1 : 0;
		}
		if (b > 0)
		{
			if (sign <= 0)
			{
				return -1;
			}
		}
		else if (b < 0)
		{
			if (sign >= 0)
			{
				return 1;
			}
			b = -b;
		}
		else
		{
			return sign;
		}

		return numerator.ucmp(denominator * b) * sign;
	}
};