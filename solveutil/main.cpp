#include <stdio.h>
#include <string>
#include <cstring>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <libsolver/Fractional.h>
#include <libsolver/Matrix.h>
#include <libsolver/Solver.h>
#include <libsolver/Util.h>
#include "config.h"

// Some string processing routines copy-pasta
// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// https://stackoverflow.com/questions/10464344/reading-from-stdin-in-c

// trim from start (in place)
inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline std::string trim(std::string s)
{
    rtrim(s);
    ltrim(s);
    return s;
}

std::vector<std::string> splitLineGetTokens(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        tokens.push_back(trim(token));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(trim(s));

    return tokens;
}

Solver::Matrix ReadInputMatrix()
{
    size_t numColumns = 0;
    uint32_t ln = 0;
    std::vector<int32_t> values;
    for (std::string line; std::getline(std::cin, line);)
    {
        ln++;
        if(line.empty())
            continue;

        auto tokens = splitLineGetTokens(line, ",");
        if(numColumns != 0 && tokens.size() != numColumns)
        {
            fprintf(stderr, "matrix num columns mismatch\n");
            fprintf(stderr, "Line %u: '%s'\n", ln, line.c_str());
            fprintf(stderr, "Has %lu tokens, previously %lu\n", tokens.size(), numColumns);
            throw std::runtime_error("Error has occurred");
        }
        numColumns = tokens.size();
        for (const auto& t : tokens)
        {
            int32_t val = std::atoi(t.c_str());
            values.push_back(val);
        }
    }

    if(values.size() % numColumns != 0)
        throw std::runtime_error("Error has occurred");
    const size_t numRows = values.size() / numColumns;
    
    Solver::Matrix mat{ numColumns, numRows };
    for (size_t i = 0; i < values.size(); i++)
        mat.data()[i] = values[i];
    return mat;
}

int main(int numArgs, const char* const * args)
{
    bool version = false;
    bool print   = false;
    bool solve   = false;
    bool help    = false;
    std::string str;
    for (size_t i = 1; i < numArgs; i++)
    {
        if(strcmp(args[i], "--version") == 0 || strcmp(args[i], "-v") == 0)
            version = true;
        if(strcmp(args[i], "--help") == 0 || strcmp(args[i], "-h") == 0)
            help = true;
        if(strcmp(args[i], "--print") == 0 || strcmp(args[i], "--p") == 0)
            print = true;
        if(strcmp(args[i], "--solve") == 0 || strcmp(args[i], "-s") == 0)
        {
            print = true;
            solve = true;
        }
    }

    if(!version && !help && !print && !solve)
    {
        printf("No parameters provided. Nothing to do.\n");
    }

    if(version)
        printf("Solver utility version: %u.%u.%u\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    
    if(help)
    {
        printf("    --version [-v]: Print program version\n");
        printf("    --print   [-p]: Print the input matrix\n");
        printf("    --solve   [-s]: Solves the system of equations streamed in to the input (implies -p)\n");
        printf("    --help    [-h]: Prints this help\n");
    }

    if(!print)
        return 0;

    const auto input = ReadInputMatrix();
    printf("Input matrix: \n");
    Solver::PrintMatrix(input);

    if(!solve)
        return 0;
    Solver::Matrix result;
    Solver::SolveGaussianElimination(input, result);
    printf("Solver result matrix: \n");
    Solver::PrintMatrix(result);

    return 0;
}