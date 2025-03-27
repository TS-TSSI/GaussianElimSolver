#include <libsolver/Solver.h>
#include <libsolver/Matrix.h>
#include <libsolver/Fractional.h>
#include <gtest/gtest.h>

void CompareMatrices(const Solver::Matrix& a, const Solver::Matrix& b)
{
    EXPECT_EQ(a.Width(), b.Width())   << "Matrices of different sizes";
    EXPECT_EQ(a.Height(), b.Height()) << "Matrices of different sizes";;
    for (size_t y = 0; y < a.Height(); y++)
    {
        for (size_t x = 0; x < a.Width(); x++)
        {
            EXPECT_FLOAT_EQ(a.at(x, y).AsFloat(), b.at(x, y).AsFloat()) << "Element-wise comparison failed at row: " << y << ", column: " << x;
        }
    }
}

TEST(solvertests, test_case_1)
{
    // Equations:
    // 2x +  y =  -1
    // 3x - 5y = -21
    // Augmented matrix:
    // [ 2,  1,  -1 ]
    // [ 3, -5, -21 ]
    Solver::Matrix augInput = {3,2};
    augInput.at(0, 0) =   2;
    augInput.at(1, 0) =   1;
    augInput.at(2, 0) =  -1;
    augInput.at(0, 1) =   3;
    augInput.at(1, 1) =  -5;
    augInput.at(2, 1) = -21;
    // Expected output:
    // [ 1, 0, -2 ]
    // [ 0, 1,  3 ]
    Solver::Matrix exp = {3,2};
    exp.at(0, 0) =  1;
    exp.at(1, 0) =  0;
    exp.at(2, 0) = -2;
    exp.at(0, 1) =  0;
    exp.at(1, 1) =  1;
    exp.at(2, 1) =  3;
    Solver::Matrix res = {};
    Solver::SolveGaussianElimination(augInput, res);

    CompareMatrices(exp, res);
}

TEST(solvertests, test_case_2)
{
    // Equations:
    // 7x + 5y = -12
    // 3x - 4y =   1
    // Augmented matrix:
    // [ 7,  5, -12 ]
    // [ 3, -4,   1 ]
    Solver::Matrix augInput = {3,2};
    augInput.at(0, 0) =   7;
    augInput.at(1, 0) =   5;
    augInput.at(2, 0) = -12;
    augInput.at(0, 1) =   3;
    augInput.at(1, 1) =  -4;
    augInput.at(2, 1) =   1;
    // Expected output:
    // [ 1, 0, -1 ]
    // [ 0, 1, -1 ]
    Solver::Matrix exp = {3,2};
    exp.at(0, 0) =  1;
    exp.at(1, 0) =  0;
    exp.at(2, 0) = -1;
    exp.at(0, 1) =  0;
    exp.at(1, 1) =  1;
    exp.at(2, 1) = -1;
    Solver::Matrix res = {};
    Solver::SolveGaussianElimination(augInput, res);

    CompareMatrices(exp, res);
}

TEST(solvertests, test_case_3)
{
    // Equations:
    // -3x + 2y - 1z = -1
    //  6x - 6y + 7z = -7
    //  3x - 4y + 4z = -6
    // Augmented matrix:
    // [ -3,  2, -1, -1 ]
    // [  6, -6,  7, -7 ]
    // [  3, -4,  4, -6 ]
    Solver::Matrix augInput = {4,3};
    augInput.at(0, 0) = -3;
    augInput.at(1, 0) =  2;
    augInput.at(2, 0) = -1;
    augInput.at(3, 0) = -1;
    augInput.at(0, 1) =  6;
    augInput.at(1, 1) = -6;
    augInput.at(2, 1) =  7;
    augInput.at(3, 1) = -7;
    augInput.at(0, 2) =  3;
    augInput.at(1, 2) = -4;
    augInput.at(2, 2) =  4;
    augInput.at(3, 2) = -6;
    // Expected output:
    // [ 1,  0,  0,  2 ]
    // [ 0,  1,  0,  2 ]
    // [ 0,  0,  1, -1 ]
    Solver::Matrix exp = {4,3};
    exp.at(0, 0) =  1;
    exp.at(1, 0) =  0;
    exp.at(2, 0) =  0;
    exp.at(3, 0) =  2;
    exp.at(0, 1) =  0;
    exp.at(1, 1) =  1;
    exp.at(2, 1) =  0;
    exp.at(3, 1) =  2;
    exp.at(0, 2) =  0;
    exp.at(1, 2) =  0;
    exp.at(2, 2) =  1;
    exp.at(3, 2) = -1;
    Solver::Matrix res = {};
    Solver::SolveGaussianElimination(augInput, res);

    CompareMatrices(exp, res);
}

TEST(solvertests, test_case_4)
{
    // Equations:
    // y = 2x + 1
    // y = 3x + 0
    //      2x - y = -1
    //      3x - y = 0
    // Augmented matrix:
    // [ 2, -1, -1 ]
    // [ 3, -1,  0 ]
    Solver::Matrix augInput = {3,2};
    augInput.at(0, 0) =  2;
    augInput.at(1, 0) = -1;
    augInput.at(2, 0) = -1;
    augInput.at(0, 1) =  3;
    augInput.at(1, 1) = -1;
    augInput.at(2, 1) =  0;
    // [ 1, 0, 1 ]
    // [ 0, 1, 3 ]
    Solver::Matrix exp = {3,2};
    exp.at(0, 0) = 1;
    exp.at(1, 0) = 0;
    exp.at(2, 0) = 1;
    exp.at(0, 1) = 0;
    exp.at(1, 1) = 1;
    exp.at(2, 1) = 3;
    Solver::Matrix res = {};
    Solver::SolveGaussianElimination(augInput, res);

    CompareMatrices(exp, res);
}