#include <libsolver/Util.h>
#include <libsolver/Matrix.h>
#include <libsolver/Fractional.h>
#include <stdio.h>

void Solver::PrintMatrix(const Solver::Matrix& matrix)
{
    const auto width  = matrix.Width();
    const auto height = matrix.Height();
    if(width == 0 || height == 0)
        return;
    for(size_t y = 0; y < height; ++y)
    {
        printf("[ ");
        for(size_t x = 0; x < width; ++x)
        {
            const float f = matrix.at(x, y).AsFloat();
            printf("%f", f);
            if(x != width - 1)
                printf(", ");
        }
        printf(" ]\n");
    }
}