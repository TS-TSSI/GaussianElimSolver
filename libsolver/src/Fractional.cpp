#include <libsolver/Fractional.h>
#include <assert.h>

static uint32_t FindLCM(uint32_t a, uint32_t b)
{
    uint32_t totalMul = 1;
    while(true)
    {
        const uint32_t min = a > b ? b : a;
        bool found = false;
        for(int32_t i = 2; i < min; ++i)
        {
            if(a % i != 0 || b % i != 0)
                continue;
            totalMul *= i;
            found = true;
            a /= i;
            b /= i;
            break;
        }
        if(!found)
            return totalMul * a * b;
    }
}

static uint32_t FindGCD(uint32_t a, uint32_t b)
{
    assert(a > 0);
    assert(b > 0);
    if(b > a)
    {
        const auto tmp = a;
        a = b;
        b = tmp;
    }
    while(true)
    {
        const auto f = a % b;
        if(f == 0)
            return b;
        a = a / b;
        b = f;
    }
}

namespace Solver
{

    Fractional::Fractional() : nom(0), den(1) { }
    Fractional::Fractional(int32_t integer) : nom(integer), den(1) { }
    Fractional::Fractional(int32_t nominator, int32_t denominator) : nom(nominator), den(denominator) { assert(denominator != 0); }
    float Fractional::AsFloat() const { return float(nom) / den; }
    Fractional Fractional::GetNegative() const { return { -nom, den }; }
    Fractional Fractional::GetInverse() const  { return Fractional{  den, nom }; }
    bool Fractional::IsZero() const  { return (nom == 0); }
    void Fractional::Reduce()
    {
        if(den < 0)
        {
            nom = -nom;
            den = -den;
        }
        
        if(nom == 0)
        {
            den = 1;
        }
        else
        {
            const bool isNegative = nom < 0;
            const uint32_t absNom = isNegative ? -nom : nom;
            const int32_t gcd = FindGCD(absNom, den);
            nom /= gcd;
            den /= gcd;
        }
    }

    Fractional operator +(const Fractional& a, const Fractional& b)
    {
        if(a.den == b.den)
        {
            return { a.nom + b.nom, a.den };
        }
        else
        {
            const int32_t newNominator = a.nom * b.den + b.nom * a.den;
            const int32_t newDenominator = (newNominator == 0) ? 1 : a.den * b.den;
            return { newNominator, newDenominator };
        }
    }
    Fractional operator *(const Fractional& a, const Fractional& b)
    {
        const auto newNominator = a.nom * b.nom;
        Fractional out{ newNominator, (newNominator == 0) ? 1 : a.den * b.den };
        out.Reduce();
        return out;
    }
    
    Fractional operator -(const Fractional& a, const Fractional& b) { return a + b.GetNegative(); }
    Fractional operator /(const Fractional& a, const Fractional& b) { return a * b.GetInverse(); }

    void operator +=(Fractional& a, const Fractional& b) { a = a + b; }
    void operator -=(Fractional& a, const Fractional& b) { a = a - b; }
    void operator *=(Fractional& a, const Fractional& b) { a = a * b; }
    void operator /=(Fractional& a, const Fractional& b) { a = a / b; }

} // namespace Solver