#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>

#include <gcheck.h>
#include <argument.h>
#include "../src/vector.hpp"

auto TMin(const std::vector<int>& items) {
    return GetMin(items);
}
TEST(Vector, Min) {
    {
        std::vector correct_not_reserved = {26,-10,-52,-92,-15};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({26}),std::vector<int>({-10, 1}),std::vector<int>({-24, 42, -22, -5, -7, -52, 1, 78, 92, -17}),std::vector<int>({-92, 85, 79, -16}),std::vector<int>({40, 79, 90, -15})});
        TestCase(5,correct_not_reserved,TMin,inputs_not_reserved0);
    };
}

auto TMax(const std::vector<int>& items) {
    return GetMax(items);
}
TEST(Vector, Max) {
    {
        std::vector correct_not_reserved = {68,74,95,84,80};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({-19, 13, 68, -57, 31}),std::vector<int>({-39, 32, 60, 15, -28, 52, -73, 74}),std::vector<int>({7, 66, -10, -81, -48, 51, -45, 95}),std::vector<int>({-45, 2, 84, 17, -30, 49, 27, 33, 65, -17}),std::vector<int>({-79, 20, 80, 21, 7, 35, 25, 75, 11})});
        TestCase(5,correct_not_reserved,TMax,inputs_not_reserved0);
    };
}

std::string TAverage(const std::vector<int>& items) {
    return std::to_string(GetAvg(items));
}
TEST(Vector, Average) {
    {
        std::vector correct_not_reserved = {"19.800000","-6.250000","-38.000000","-10.800000","18.000000"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({6, 66, 95, 10, 15, 28, 58, 91, -89, -82}),std::vector<int>({-8, -82, -49, 29, 39, -85, 16, 90}),std::vector<int>({-44, -32}),std::vector<int>({43, -32, -3, -20, -42}),std::vector<int>({18})});
        TestCase(5,correct_not_reserved,TAverage,inputs_not_reserved0);
    };
}
