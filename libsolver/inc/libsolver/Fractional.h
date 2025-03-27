#pragma once
#include <cstdint>

namespace Solver
{

struct Fractional
{
    union
    {
        int32_t nominator;
        int32_t nom;
    };
    union
    {
        int32_t denominator;
        int32_t den;
    };

    Fractional();
    Fractional(int32_t integer);
    Fractional(int32_t nominator, int32_t denominator);
    float AsFloat() const;
    Fractional GetNegative() const;
    Fractional GetInverse() const;
    bool IsZero() const;
    void Reduce();
};

Fractional operator + (const Fractional& a, const Fractional& b);
Fractional operator * (const Fractional& a, const Fractional& b);
Fractional operator -(const Fractional& a, const Fractional& b);
Fractional operator /(const Fractional& a, const Fractional& b);

void operator +=(Fractional& a, const Fractional& b);
void operator -=(Fractional& a, const Fractional& b);
void operator *=(Fractional& a, const Fractional& b);
void operator /=(Fractional& a, const Fractional& b);

} // namespace Solver