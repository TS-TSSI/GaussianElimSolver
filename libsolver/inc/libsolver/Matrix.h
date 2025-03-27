#pragma once
#include <vector>
#include <cstddef>

namespace Solver
{
    class Fractional;
    class Matrix
    {
        size_t width  = 0;
        size_t height = 0;
        std::vector<Fractional> values;
        public:
        Matrix() = default;
        Matrix(size_t width, size_t height);
        const size_t Width() const;
        const size_t Height() const;
        const Fractional& at(size_t x, size_t y) const;
        Fractional& at(size_t x, size_t y);

        void SwapRows(size_t rowIndex0, size_t rowIndex1);
        void ReduceElements();

        Fractional* data();
        const Fractional* data() const;

#if (__cplusplus >= 202302L)
        inline const Fractional& operator[](size_t x, size_t y) const { return at(x,y); }
        inline Fractional& operator[](size_t x, size_t y) { return at(x,y); }
#endif

    };

} // namespace Solver