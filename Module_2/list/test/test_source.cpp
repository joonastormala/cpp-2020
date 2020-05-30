#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/list.hpp"

gcheck::RandomSizeContainer<std::string, std::list> rnd(2, 10, std::initializer_list<std::string>
    {"", " ", "some text", "some more", "asd", "what else?", "even more text", "im out of ideas"});


std::vector<std::string> TGetLines(const std::list<std::string>& lines) {
    
    std::string input;
    
    for(auto line : lines)
        input += line + '\n';
    
    std::list<std::string> list;
    std::istringstream f(input);

    GetLines(f, list);
    
    return std::vector<std::string>(list.begin(), list.end());
}

TEST(List, GetLines) {
    {
        std::vector correct_not_reserved = {std::vector<std::string>({ "im out of ideas","some more","asd"," "}),std::vector<std::string>({ "","some text","asd"}),std::vector<std::string>({ "what else?","some more","what else?"," ","some text","what else?","im out of ideas","even more text"}),std::vector<std::string>({ "","some more","","asd"}),std::vector<std::string>({ "asd"," ","asd"," ","what else?","even more text","some text","some text","im out of ideas","asd"}),std::vector<std::string>({ "im out of ideas","what else?","some more","asd","asd",""}),std::vector<std::string>({ "","asd","even more text"}),std::vector<std::string>({ "even more text","asd",""}),std::vector<std::string>({ "even more text","some text","im out of ideas","what else?","asd","im out of ideas","even more text","what else?","im out of ideas"," "}),std::vector<std::string>({ "what else?","some more","im out of ideas"," ","some text"})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ "im out of ideas","some more","asd"," "}),std::list<std::string>({ "","some text","asd"}),std::list<std::string>({ "what else?","some more","what else?"," ","some text","what else?","im out of ideas","even more text"}),std::list<std::string>({ "","some more","","asd"}),std::list<std::string>({ "asd"," ","asd"," ","what else?","even more text","some text","some text","im out of ideas","asd"}),std::list<std::string>({ "im out of ideas","what else?","some more","asd","asd",""}),std::list<std::string>({ "","asd","even more text"}),std::list<std::string>({ "even more text","asd",""}),std::list<std::string>({ "even more text","some text","im out of ideas","what else?","asd","im out of ideas","even more text","what else?","im out of ideas"," "}),std::list<std::string>({ "what else?","some more","im out of ideas"," ","some text"})});
        TestCase(10,correct_not_reserved,TGetLines,inputs_not_reserved0);
    };
}


std::string TPrint(const std::list<std::string>& lines) {
    gcheck::StdoutCapturer tout;
    
    Print(lines);
    
    return tout.str();
}

TEST(List, Print) {
    {
        std::vector correct_not_reserved = {"\nsome text\nsome text\n \n","asd\nim out of ideas\n \nsome more\nwhat else?\nwhat else?\n","some more\n \nsome text\nsome text\nim out of ideas\nim out of ideas\nim out of ideas\n","asd\nwhat else?\n\n","what else?\n\n \n\neven more text\n","\n\nasd\neven more text\n","im out of ideas\nim out of ideas\nasd\nim out of ideas\n\n\nsome more\nsome text\nsome text\n","some text\nsome text\n","some more\n \nsome more\nsome text\n","\n \nim out of ideas\n\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ "","some text","some text"," "}),std::list<std::string>({ "asd","im out of ideas"," ","some more","what else?","what else?"}),std::list<std::string>({ "some more"," ","some text","some text","im out of ideas","im out of ideas","im out of ideas"}),std::list<std::string>({ "asd","what else?",""}),std::list<std::string>({ "what else?",""," ","","even more text"}),std::list<std::string>({ "","","asd","even more text"}),std::list<std::string>({ "im out of ideas","im out of ideas","asd","im out of ideas","","","some more","some text","some text"}),std::list<std::string>({ "some text","some text"}),std::list<std::string>({ "some more"," ","some more","some text"}),std::list<std::string>({ ""," ","im out of ideas",""})});
        TestCase(10,correct_not_reserved,TPrint,inputs_not_reserved0);
    };
}


std::vector<std::string> TSortAndUnique(std::list<std::string> lines) {
    SortAndUnique(lines);
    
    return std::vector<std::string>(lines.begin(), lines.end());
}

TEST(List, SortAndUnique) {
    {
        std::vector correct_not_reserved = {std::vector<std::string>({ ""," ","asd","even more text","im out of ideas"}),std::vector<std::string>({ " ","asd","im out of ideas","some text"}),std::vector<std::string>({ "","even more text","im out of ideas","some text","what else?"}),std::vector<std::string>({ " ","asd","some text","what else?"}),std::vector<std::string>({ "even more text","some more"}),std::vector<std::string>({ " ","what else?"}),std::vector<std::string>({ ""," ","some more","what else?"}),std::vector<std::string>({ "","asd","im out of ideas","some text"}),std::vector<std::string>({ "","asd","even more text","some text"}),std::vector<std::string>({ ""," ","asd","even more text","im out of ideas"})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ "","even more text","asd"," ","im out of ideas","even more text","asd","im out of ideas"}),std::list<std::string>({ " ","some text","im out of ideas","asd","some text"}),std::list<std::string>({ "some text","","","im out of ideas","what else?","","im out of ideas","even more text"}),std::list<std::string>({ "asd","some text"," ","some text","what else?","asd","some text","some text"}),std::list<std::string>({ "some more","some more","even more text"}),std::list<std::string>({ "what else?"," "}),std::list<std::string>({ "some more",""," ","what else?","some more"}),std::list<std::string>({ "im out of ideas","im out of ideas","","asd","some text","im out of ideas","some text","im out of ideas"}),std::list<std::string>({ "even more text","some text","even more text","asd","","some text","some text"}),std::list<std::string>({ "","im out of ideas","im out of ideas","asd"," ","even more text","even more text","even more text"})});
        TestCase(10,correct_not_reserved,TSortAndUnique,inputs_not_reserved0);
    };
}
