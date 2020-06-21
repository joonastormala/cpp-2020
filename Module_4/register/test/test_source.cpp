#include <iostream>
#include <string>
#include <fstream>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/register.hpp"
#include "../src/vehicle.hpp"
#include "../src/boat.hpp"
#include "../src/aircraft.hpp"

std::string empty_content = "";
std::string three_items_content = 
R"(A;G_BOAC;British Airways;Concorde SST;80.8;2000
A;RU-123;Russian Federation;MiG-21;80.8;1600
B;FI123;Pekka Purjehtija;Mariella;1.8;0)";
std::string two_with_malformed_lines_content = 
R"(B;SINKED;Francesco Schettino;Costa Concordia;8.2;103000
K;MAG 1C;Paul Daniels;Bentley;650;0
D;OH-LVI;Finnair;Airbus 350;67.2;900
A;OH-LVI;Finnair;Airbus 350;67.2;900
Z;asdsad;sadsad;sadsad;0;0)";

gcheck::Random<std::string> rnd_reg({"G_BOAC", "YUU-123", "RU-123", "EES-321", "FI123"});
gcheck::Random<std::string> rnd_name({"Mariella", "USS Sinking", "Boat"});
gcheck::Random<std::string> rnd_model({"MiG-21", "707", "737", "F-22"});
gcheck::Random<std::string> rnd_owner({"British Airways", "Teemu Teekkari", "Russian Federation", "Nikola", "Pekka Purjehtija"});
gcheck::Random rnd_range(0u, 1000u);
gcheck::Random<bool> rnd_inspection(std::vector<bool>{false,true});
gcheck::Random<double> rnd_double(0,1000);
gcheck::Random<unsigned int> rnd_uint(0,1000);
gcheck::Random<std::string> rnd_line({"A;G_BOAC;British Airways;Concorde SST;80.8;2000\n",
"A;RU-123;Russian Federation;MiG-21;80.8;1600\n",
"B;FI123;Pekka Purjehtija;Mariella;1.8;0\n"});

std::string UniqueName() {
    gcheck::RandomContainer<char> rnd_filename(20, 'a', 'z');
    std::string filename;
    do {
        std::vector v = rnd_filename.Next();
        filename = std::string(v.begin(), v.end()) + ".txt";
    } while(std::ifstream(filename).is_open());
    return filename;
}

std::string WriteFile(std::string content) {
    std::string filename = UniqueName();
    
    std::ofstream file(filename);
    if(!file.is_open())
        return "";
    
    file << content;
    file.close();
    
    return filename;
}

template<typename V, typename T, typename S>
std::string TPrint(std::string register_number, std::string owner, std::string third, T fourth, S fifth) {
    V vehicle(register_number, owner, third, fourth, fifth);
    gcheck::StdoutCapturer tout;
    vehicle.Print();
    return tout.str();
}
template<typename V, typename T, typename S>
std::string TWrite(std::string register_number, std::string owner, std::string third, T fourth, S fifth) {
    V vehicle(register_number, owner, third, fourth, fifth);
    std::stringstream ss;
    vehicle.Write(ss);
    return ss.str();
}

template<typename V>
std::string TRead(std::string str) {
    std::stringstream ss(str);
    V* vehicle = V::Read(ss);
    if(vehicle == nullptr)
        return "nullptr";
    
    ss.str("");
    ss.clear();
    vehicle->Write(ss);
    std::string asd = ss.str();
    return asd;
}

PREREQ_TEST(Boat, Print, 1, 0) {
    {
        std::vector correct_not_reserved = {"B;RU-123;Teemu Teekkari;Mariella;234.464;234.464\n","B;YUU-123;Pekka Purjehtija;Boat;202.943;202.943\n","B;YUU-123;Russian Federation;USS Sinking;67.8202;67.8202\n","B;G_BOAC;Russian Federation;Mariella;312.985;312.985\n","B;YUU-123;British Airways;USS Sinking;79.8726;79.8726\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("RU-123"),std::string("YUU-123"),std::string("YUU-123"),std::string("G_BOAC"),std::string("YUU-123")});
        gcheck::SequenceArgument inputs_not_reserved1({std::string("Teemu Teekkari"),std::string("Pekka Purjehtija"),std::string("Russian Federation"),std::string("Russian Federation"),std::string("British Airways")});
        gcheck::SequenceArgument inputs_not_reserved2({std::string("Mariella"),std::string("Boat"),std::string("USS Sinking"),std::string("Mariella"),std::string("USS Sinking")});
        gcheck::SequenceArgument inputs_not_reserved3({234.464115,202.942711,67.820159,312.984973,79.872612});
        gcheck::SequenceArgument inputs_not_reserved4({234.464115,202.942711,67.820159,312.984973,79.872612});
        TestCase(5,correct_not_reserved,TPrint<Boat, double, double>,inputs_not_reserved0,inputs_not_reserved1,inputs_not_reserved2,inputs_not_reserved3,inputs_not_reserved4);
    };
}
PREREQ_TEST(Boat, Write, 1, 1) {
    {
        std::vector correct_not_reserved = {"B;YUU-123;Pekka Purjehtija;Boat;752.597;752.597\n","B;YUU-123;Teemu Teekkari;Boat;390.631;390.631\n","B;FI123;Pekka Purjehtija;Mariella;768.087;768.087\n","B;FI123;Russian Federation;USS Sinking;76.2089;76.2089\n","B;RU-123;Russian Federation;Boat;866.888;866.888\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("YUU-123"),std::string("YUU-123"),std::string("FI123"),std::string("FI123"),std::string("RU-123")});
        gcheck::SequenceArgument inputs_not_reserved1({std::string("Pekka Purjehtija"),std::string("Teemu Teekkari"),std::string("Pekka Purjehtija"),std::string("Russian Federation"),std::string("Russian Federation")});
        gcheck::SequenceArgument inputs_not_reserved2({std::string("Boat"),std::string("Boat"),std::string("Mariella"),std::string("USS Sinking"),std::string("Boat")});
        gcheck::SequenceArgument inputs_not_reserved3({752.597193,390.631271,768.086689,76.208879,866.888288});
        gcheck::SequenceArgument inputs_not_reserved4({752.597193,390.631271,768.086689,76.208879,866.888288});
        TestCase(5,correct_not_reserved,TWrite<Boat, double, double>,inputs_not_reserved0,inputs_not_reserved1,inputs_not_reserved2,inputs_not_reserved3,inputs_not_reserved4);
    };
}
TEST_(Boat, Read, 2) {
    {
        std::vector correct_not_reserved = {"B;FI123;Pekka Purjehtija;Mariella;1.8;0\n","nullptr","nullptr","nullptr","B;FI123;Pekka Purjehtija;Mariella;1.8;0\n","nullptr","nullptr","nullptr","nullptr","nullptr"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("B;FI123;Pekka Purjehtija;Mariella;1.8;0"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("B;FI123;Pekka Purjehtija;Mariella;1.8;0"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600")});
        TestCase(10,correct_not_reserved,TRead<Boat>,inputs_not_reserved0);
    };
}

PREREQ_TEST(Aircraft, Print, 1, 0) {
    {
        std::vector correct_not_reserved = {"A;EES-321;Russian Federation;MiG-21;211.169;722\n","A;FI123;British Airways;707;502.687;186\n","A;FI123;Pekka Purjehtija;MiG-21;899.62;339\n","A;G_BOAC;Nikola;707;813.252;425\n","A;RU-123;Nikola;F-22;486.327;371\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("EES-321"),std::string("FI123"),std::string("FI123"),std::string("G_BOAC"),std::string("RU-123")});
        gcheck::SequenceArgument inputs_not_reserved1({std::string("Russian Federation"),std::string("British Airways"),std::string("Pekka Purjehtija"),std::string("Nikola"),std::string("Nikola")});
        gcheck::SequenceArgument inputs_not_reserved2({std::string("MiG-21"),std::string("707"),std::string("MiG-21"),std::string("707"),std::string("F-22")});
        gcheck::SequenceArgument inputs_not_reserved3({211.169048,502.686789,899.61992,813.251601,486.32693});
        gcheck::SequenceArgument inputs_not_reserved4({722,186,339,425,371});
        TestCase(5,correct_not_reserved,TPrint<Aircraft, double, unsigned int>,inputs_not_reserved0,inputs_not_reserved1,inputs_not_reserved2,inputs_not_reserved3,inputs_not_reserved4);
    };
}
PREREQ_TEST(Aircraft, Write, 1, 1) {
    {
        std::vector correct_not_reserved = {"A;FI123;Pekka Purjehtija;737;842.795;320\n","A;YUU-123;British Airways;737;884.093;492\n","A;EES-321;Pekka Purjehtija;MiG-21;307.408;548\n","A;YUU-123;Nikola;707;936.181;681\n","A;RU-123;Nikola;F-22;990.24;963\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("FI123"),std::string("YUU-123"),std::string("EES-321"),std::string("YUU-123"),std::string("RU-123")});
        gcheck::SequenceArgument inputs_not_reserved1({std::string("Pekka Purjehtija"),std::string("British Airways"),std::string("Pekka Purjehtija"),std::string("Nikola"),std::string("Nikola")});
        gcheck::SequenceArgument inputs_not_reserved2({std::string("737"),std::string("737"),std::string("MiG-21"),std::string("707"),std::string("F-22")});
        gcheck::SequenceArgument inputs_not_reserved3({842.795094,884.09259,307.407623,936.180674,990.240237});
        gcheck::SequenceArgument inputs_not_reserved4({320,492,548,681,963});
        TestCase(5,correct_not_reserved,TWrite<Aircraft, double, unsigned int>,inputs_not_reserved0,inputs_not_reserved1,inputs_not_reserved2,inputs_not_reserved3,inputs_not_reserved4);
    };
}
TEST_(Aircraft, Read, 2) {
    {
        std::vector correct_not_reserved = {"nullptr","A;RU-123;Russian Federation;MiG-21;80.8;1600\n","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n","A;RU-123;Russian Federation;MiG-21;80.8;1600\n","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n","nullptr","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n","A;G_BOAC;British Airways;Concorde SST;80.8;2000\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("B;FI123;Pekka Purjehtija;Mariella;1.8;0"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;RU-123;Russian Federation;MiG-21;80.8;1600"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("B;FI123;Pekka Purjehtija;Mariella;1.8;0"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000"),std::string("A;G_BOAC;British Airways;Concorde SST;80.8;2000")});
        TestCase(10,correct_not_reserved,TRead<Aircraft>,inputs_not_reserved0);
    };
}

TEST(Register, ReadLine) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;
    
    EXPECT_EQ(0, reg.Size()) << "None read yet";
    std::stringstream ss(two_with_malformed_lines_content);
    reg.ReadLine(ss);
    EXPECT_EQ(1, reg.Size()) << "Read one line";
    reg.ReadLine(ss);
    EXPECT_EQ(1, reg.Size()) << "Read a line with unknown vehicle";
    
    std::string next_line_in_stream;
    std::getline(ss, next_line_in_stream);
    EXPECT_EQ("D;OH-LVI;Finnair;Airbus 350;67.2;900", next_line_in_stream);
    
    reg.ReadLine(ss);
    EXPECT_EQ(2, reg.Size()) << "Read one line";
    
    std::getline(ss, next_line_in_stream);
    EXPECT_EQ("Z;asdsad;sadsad;sadsad;0;0", next_line_in_stream);
}

TEST(Register, Load_1) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;
    
    std::string nonexistent = UniqueName();
    EXPECT_EQ(-1, reg.Load(UniqueName())) << "Loading from a nonexistent file";
    
    EXPECT_EQ(0, reg.Size());

    gcheck::StdoutCapturer tout;
    reg.Print();

    std::string Print_out = tout.str();

    std::string correct = "";
    
    EXPECT_EQ(correct, Print_out);
}

TEST(Register, Load_2) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;
    
    std::string empty = WriteFile(empty_content);
    if(empty == "") { FAIL() << "Couldn't write test file"; }
    EXPECT_EQ(0, reg.Load(empty)) << "Loading from an empty file";
    std::remove(empty.c_str());
    
    EXPECT_EQ(0, reg.Size());

    gcheck::StdoutCapturer tout;
    reg.Print();

    std::string Print_out = tout.str();

    std::string correct = "";
    
    EXPECT_EQ(correct, Print_out);
}

TEST(Register, Load_3) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;
    
    std::string three_items = WriteFile(three_items_content);
    if(three_items == "") { FAIL() << "Couldn't write test file"; }
    EXPECT_EQ(3, reg.Load(three_items)) << "Loading from a file with 3 items";
    std::remove(three_items.c_str());
    
    EXPECT_EQ(3, reg.Size());

    gcheck::StdoutCapturer tout;
    reg.Print();

    std::string Print_out = tout.str();

    std::string correct =
        "A;G_BOAC;British Airways;Concorde SST;80.8;2000\n"
        "A;RU-123;Russian Federation;MiG-21;80.8;1600\n"
        "B;FI123;Pekka Purjehtija;Mariella;1.8;0\n";
    
    EXPECT_EQ(correct, Print_out);
}

TEST(Register, Load_4) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;
    
    std::string two_with_malformed_lines = WriteFile(two_with_malformed_lines_content);
    if(two_with_malformed_lines == "") { FAIL() << "Couldn't write test file"; }
    EXPECT_EQ(2, reg.Load(two_with_malformed_lines)) << "Loading from a file with 2 items and unknown vehicle types";
    std::remove(two_with_malformed_lines.c_str());
    
    EXPECT_EQ(2, reg.Size());

    gcheck::StdoutCapturer tout;
    reg.Print();

    std::string Print_out = tout.str();

    std::string correct =
        "B;SINKED;Francesco Schettino;Costa Concordia;8.2;103000\n"
        "A;OH-LVI;Finnair;Airbus 350;67.2;900\n";
    
    EXPECT_EQ(correct, Print_out);
}

TEST(Register, Add_Save_1) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;

    reg.Add(new Aircraft("G_BOAC", "British Airways", "Concorde SST", 80.8, 2000));
    EXPECT_EQ(1, reg.Size());
    reg.Add(new Aircraft("RU-123", "Russian Federation", "MiG-21", 80.8, 1600));
    reg.Add(new Boat("FI123", "Pekka Purjehtija", "Mariella", 1.8, 0));
    EXPECT_EQ(3, reg.Size());

    std::string filename = UniqueName();
    reg.Save(filename);

    std::ifstream test(filename);
    std::stringstream ss;
    ss << test.rdbuf();
    std::string Save_out = ss.str();
    std::remove(filename.c_str());

    std::string correct =
        "A;G_BOAC;British Airways;Concorde SST;80.8;2000\n"
        "A;RU-123;Russian Federation;MiG-21;80.8;1600\n"
        "B;FI123;Pekka Purjehtija;Mariella;1.8;0\n";
    
    EXPECT_EQ(correct, Save_out);
}

TEST(Register, Add_Save_2) {
    GradingMethod(gcheck::AllOrNothing);
    Register reg;

    EXPECT_EQ(0, reg.Size());
    reg.Add(new Boat("SINKED", "Francesco Schettino", "Costa Concordia", 8.2, 103000));
    reg.Add(new Aircraft("OH-LVI", "Finnair", "Airbus 350", 67.2, 900));
    EXPECT_EQ(2, reg.Size());

    std::string filename = UniqueName();
    reg.Save(filename);

    std::ifstream test(filename);
    std::stringstream ss;
    ss << test.rdbuf();
    std::string Save_out = ss.str();
    std::remove(filename.c_str());

    std::string correct =
        "B;SINKED;Francesco Schettino;Costa Concordia;8.2;103000\n"
        "A;OH-LVI;Finnair;Airbus 350;67.2;900\n";
    
    EXPECT_EQ(correct, Save_out);
}
