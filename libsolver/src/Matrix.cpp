#include <libsolver/Matrix.h>
#include <libsolver/Fractional.h>
#include <assert.h>

namespace Solver
{
    
Matrix::Matrix(size_t width, size_t height) : width(width), height(height), values(width * height) { }

const size_t Matrix::Width() const { return width; }
const size_t Matrix::Height() const { return height; }
const Fractional& Matrix::at(size_t x, size_t y) const
{ 
    assert(x < width); 
    assert(y < height);
    return values.data()[y * width + x];
}
Fractional& Matrix::at(size_t x, size_t y)
{ 
    assert(x < width); 
    assert(y < height);
    return values.data()[y * width + x];
}

void Matrix::SwapRows(size_t rowIndex0, size_t rowIndex1)
{
    assert(rowIndex0 < height);
    assert(rowIndex1 < height);
    if(rowIndex0 == rowIndex1)
        return; // This operation is NOOP. Early out.
    for(size_t x = 0; x < width ; ++x)
    {
        const auto tmp = at(x, rowIndex0);
        at(x, rowIndex0) = at(x, rowIndex1);
        at(x, rowIndex1) = tmp;
    }
}

void Matrix::ReduceElements()
{
    for(auto& v : values)
        v.Reduce();
}

Fractional* Matrix::data() { return values.data(); }
const Fractional* Matrix::data() const { return values.data(); }

} // namespace Solver