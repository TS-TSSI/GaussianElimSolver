#include <libsolver/Solver.h>
#include <libsolver/Matrix.h>
#include <libsolver/Fractional.h>
#include <assert.h>
#include <optional>

static void MultiplyRowBy(Solver::Matrix& m, size_t rowIndex, Solver::Fractional multiplier)
{
    const auto width = m.Width();
    for(size_t x = 0; x < width; ++x)
        m.at(x, rowIndex) *= multiplier;
}

static void Gauss(Solver::Matrix& mat, bool reducedRowEchlon)
{
    const size_t width  = mat.Width();
    const size_t height = mat.Height();
    
    for(size_t startingRowIdx = 0; startingRowIdx < height; ++startingRowIdx)
    {
        // Find leftmost column which is not entirely zeros
        for(size_t col = 0; col < width; ++col)
        {
            std::optional<size_t> nonZeroRowIndex = std::nullopt;
            for(size_t elem = startingRowIdx; elem < height ; ++elem)
            {
                if(mat.at(col, elem).nominator == 0)
                    continue;
                nonZeroRowIndex = std::make_optional(elem);
                break;
            }

            // Move the row which contains first non-zero in the found column to the top starting/working row
            const bool isNonZeroColumn = nonZeroRowIndex.has_value();
            if(!isNonZeroColumn)
                continue;
            
            if(startingRowIdx != nonZeroRowIndex.value())
                mat.SwapRows(nonZeroRowIndex.value(), startingRowIdx);

            // Multiply the row by a number which would make it's leading element 1
            constexpr bool reducedRowEchlon = true; // false for row echlon form, true for reduced row echlon form
            if(reducedRowEchlon)
            {
                const auto rowMultiplier = mat.at(col, startingRowIdx).GetInverse(); // Inverse of leading non-zero element
                MultiplyRowBy(mat, startingRowIdx, rowMultiplier);
            }
            const auto leadingElemValue = mat.at(col, startingRowIdx);

            // Zero out leading non-zeros of rows below the working/starting row by adding a multiple
            // of the starting/working row to it
            for(size_t y = startingRowIdx + 1; y < height; ++y)
            {
                const auto value = mat.at(col, y);
                if(value.nom == 0)
                    continue; // Leading value at this row is already zero. skip and proceed
                const auto rowZeroingMultiplier = value.GetNegative() * leadingElemValue.GetInverse();
                for(size_t x = col; x < width; ++x)
                    mat.at(x, y) += mat.at(x, startingRowIdx) * rowZeroingMultiplier;
            }
            break;
        }
    }
}

static void Jordan(Solver::Matrix& augmentedMatrix)
{
    const size_t width  = augmentedMatrix.Width();
    const size_t height = augmentedMatrix.Height();
    assert(width > 1 && height > 0);

    for(size_t y = height; y-- > 0;)
    {
        for(size_t x = 0; x < width - 1; ++x)
        {
            const auto leadingValue = augmentedMatrix.at(x, y);
            if(leadingValue.IsZero())
                continue;
            for(size_t r = y; r-- > 0;)
            {
                const auto& elem = augmentedMatrix.at(x, r);
                if(elem.IsZero())
                    continue;
                const auto multiplier = elem.GetNegative() * leadingValue.GetInverse();
                for(size_t c = x; c < width; ++c)
                    augmentedMatrix.at(c, r) += augmentedMatrix.at(c, y) * multiplier;
            }
            break;
        }
    }
}

void Solver::SolveGaussianElimination(const Solver::Matrix& inAugmentedMatrix, Solver::Matrix& outResult, MLASolverMethod method)
{
    Solver::Matrix sln = inAugmentedMatrix;
    const bool gaussReducedRE = (method != MLASolverMethod::GaussRowEchlon);
    Gauss(sln, gaussReducedRE);
    if(method == MLASolverMethod::GaussJordan)
        Jordan(sln);
    outResult = std::move(sln);
}