#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <gcheck.h>
#include <argument.h>
#include <redirectors.h>
#include "../src/rectangle.hpp"

std::string TRectangle(std::string input) {
    
    gcheck::StdinInjecter tin(input);
    gcheck::StdoutCapturer tout;
    
    Rectangle();
    
    return tout.str();
}


TEST(Rectangle, Test) {
    {
        std::vector correct_not_reserved = {"Please enter width and height\nArea: 1164.61\nCircumference: 148.621\n","Please enter width and height\nArea: 1852.2\nCircumference: 172.157\n","Please enter width and height\nArea: 2063.27\nCircumference: 214.474\n","Please enter width and height\nArea: 5242.85\nCircumference: 292.102\n","Please enter width and height\nArea: 4770.63\nCircumference: 281.363\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("51.849187 22.461441\n"),std::string("43.457977 42.620488\n"),std::string("82.108492 25.128630\n"),std::string("63.544822 82.506356\n"),std::string("57.028999 83.652639\n")});
        TestCase(5,correct_not_reserved,TRectangle,inputs_not_reserved0);
    };
}
