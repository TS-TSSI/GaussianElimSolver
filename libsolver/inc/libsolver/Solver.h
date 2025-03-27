#pragma once
#include <cstdint>

namespace Solver
{
    class Matrix;

    enum class MLASolverMethod
    {
        GaussRowEchlon,
        GaussReducedRowEchlon,
        GaussJordan,
    };

    void SolveGaussianElimination(const Matrix& inAugmentedMatrix, Matrix& outResult, MLASolverMethod method = MLASolverMethod::GaussJordan);
}