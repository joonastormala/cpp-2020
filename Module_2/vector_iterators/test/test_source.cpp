#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/vector_it.hpp"

gcheck::RandomSizeContainer rnd(1, 20, 0, 1000);

std::vector<int> TRead(const std::vector<int>& v) {
    std::string input;
    for(auto i : v) {
        input += std::to_string(i) + " ";
    }
    input += "!\n";
    gcheck::StdinInjecter tin(input);
    
    std::vector<int> out = ReadVector();
    
    return out;
}

TEST(Iterator, ReadVector) {
    {
        std::vector correct_not_reserved = {std::vector<int>{ 876},std::vector<int>{ 536,196,97,177,404,656,383,64,985,367,386,69,892,20,711,254},std::vector<int>{ 452,172,336,701},std::vector<int>{ 29,690,356,835,40,768,744,662,520},std::vector<int>{ 907,184},std::vector<int>{ 287,390,855},std::vector<int>{ 938},std::vector<int>{ 992,931,375,151,377,796,220,120,127,404,560,964},std::vector<int>{ 342,0,33,909,751,187,914,225,358,54,174,564,212,518},std::vector<int>{ 308,580,299,655,420,34,497}};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({876}),std::vector<int>({536, 196, 97, 177, 404, 656, 383, 64, 985, 367, 386, 69, 892, 20, 711, 254}),std::vector<int>({452, 172, 336, 701}),std::vector<int>({29, 690, 356, 835, 40, 768, 744, 662, 520}),std::vector<int>({907, 184}),std::vector<int>({287, 390, 855}),std::vector<int>({938}),std::vector<int>({992, 931, 375, 151, 377, 796, 220, 120, 127, 404, 560, 964}),std::vector<int>({342, 0, 33, 909, 751, 187, 914, 225, 358, 54, 174, 564, 212, 518}),std::vector<int>({308, 580, 299, 655, 420, 34, 497})});
        TestCase(10,correct_not_reserved,TRead,inputs_not_reserved0);
    };
}


std::string TPrintSum1(const std::vector<int> v) {
    gcheck::StdoutCapturer tout;
    
    PrintSum1(v);
    
    return tout.str();
}

TEST(Iterator, PrintSum1) {
    {
        std::vector correct_not_reserved = {"223 457 1199 1198 843 1242 973 858 756 140 247 \n","792 1123 707 1202 1707 1073 290 894 1314 693 666 1146 1485 1392 1010 578 500 \n","1140 662 803 1074 689 627 674 588 1158 1004 \n","967 1036 1309 1329 582 200 515 549 998 \n","1051 \n","\n","432 454 453 310 367 723 1466 953 928 \n","914 1044 1468 1649 1433 1130 1485 1112 364 321 460 421 821 \n","1636 1059 1050 1606 1576 1577 1304 712 \n","448 90 946 1586 1153 668 438 510 1122 988 341 663 1464 1737 1003 272 779 \n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({220, 3, 454, 745, 453, 390, 852, 121, 737, 19, 121, 126}),std::vector<int>({43, 749, 374, 333, 869, 838, 235, 55, 839, 475, 218, 448, 698, 787, 605, 405, 173, 327}),std::vector<int>({580, 560, 102, 701, 373, 316, 311, 363, 225, 933, 71}),std::vector<int>({306, 661, 375, 934, 395, 187, 13, 502, 47, 951}),std::vector<int>({819, 232}),std::vector<int>({927}),std::vector<int>({328, 104, 350, 103, 207, 160, 563, 903, 50, 878}),std::vector<int>({598, 316, 728, 740, 909, 524, 606, 879, 233, 131, 190, 270, 151, 670}),std::vector<int>({842, 794, 265, 785, 821, 755, 822, 482, 230}),std::vector<int>({431, 17, 73, 873, 713, 440, 228, 210, 300, 822, 166, 175, 488, 976, 761, 242, 30, 749})});
        TestCase(10,correct_not_reserved,TPrintSum1,inputs_not_reserved0);
    };
}


std::string TPrintSum2(const std::vector<int> v) {
    gcheck::StdoutCapturer tout;
    
    PrintSum2(v);
    
    return tout.str();
}

TEST(Iterator, PrintSum2) {
    {
        std::vector correct_not_reserved = {"1591 1505 872 1329 535 1309 852 375 1236 338 \n","513 1039 564 967 815 1356 \n","1549 1264 \n","781 531 609 884 1384 452 1089 634 \n","608 \n","517 \n","512 1431 782 1635 362 1189 915 519 \n","423 369 922 \n","1733 1756 \n","1067 714 1417 800 1386 \n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({975, 616, 820, 643, 32, 984, 175, 200, 932, 261, 77, 304, 175, 677, 325, 503, 686, 52, 889, 616}),std::vector<int>({16, 836, 159, 197, 714, 415, 57, 941, 101, 770, 405, 203, 497}),std::vector<int>({941, 895, 369, 608}),std::vector<int>({717, 209, 403, 556, 814, 64, 749, 230, 124, 404, 340, 388, 570, 328, 206, 322, 64}),std::vector<int>({64, 821, 544}),std::vector<int>({77, 440}),std::vector<int>({138, 643, 161, 974, 136, 920, 404, 355, 587, 164, 511, 269, 226, 661, 621, 788, 374}),std::vector<int>({127, 80, 112, 810, 289, 296}),std::vector<int>({775, 897, 859, 958}),std::vector<int>({96, 179, 883, 399, 842, 544, 401, 534, 535, 971})});
        TestCase(10,correct_not_reserved,TPrintSum2,inputs_not_reserved0);
    };
}
