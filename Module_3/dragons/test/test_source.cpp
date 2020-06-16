#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <tuple>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/dragon.hpp"
#include "../src/fantasy_dragon.hpp"
#include "../src/magic_dragon.hpp"
#include "../src/dragon_cave.hpp"

std::string to_string(TreasureType t) {
    switch (t) {
    case Wisdom:
        return "Wisdom";
    case Potions:
        return "Potions";
    case Jewellery:
        return "Jewellery";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Treasure& t) {
    return "[" + to_string(t.type) + ", " + t.name + "]";
}
bool operator==(const Treasure& l, const Treasure& r) {
    return l.type == r.type && l.name == r.name;
}

std::string to_string(FoodType t) {
    switch (t) {
    case People:
        return "People";
    case PeopleFood:
        return "PeopleFood";
    case Herbs:
        return "Herbs";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Food& f) {
    return "[" + to_string(f.type) + ", " + f.name + "]";
}
bool operator==(const Food& l, const Food& r) {
    return l.type == r.type && l.name == r.name;
}

std::vector<Treasure> CreateRandomTreasures(size_t count) {
    std::vector<Treasure> treasures;
    
    // Jewellery
    gcheck::Random j_names({"Ruby", "Gold bar", "Agate", "Amber", "Silver coins", "Jade stone", "Bag of pearls", "Topaz", "Sapphire dust"});
    // Wisdom
    gcheck::Random w_names({"Scroll of infinite wisdom", "Sun Tzu's Art of War", "Biographia literaria", "MAOL", "Gabriel's Wing", "Critique of pure reason", "The C++ standard", "The Symposium", "Thus Spoke Zarathustra"});
    // Potions
    gcheck::Random p_names({"Cough syrup", "Liquid luck", "Stoneskin potion", "Blemish blitzer", "Elixir of euphoria", "Garroting gas", "Essence of insanity", "Gin tonic", "Truth serum"});

    gcheck::Random rnd_type(std::vector<TreasureType>({Jewellery, Wisdom, Potions}));
    std::unordered_map<TreasureType, gcheck::Random<const char*>*> names({std::pair(Jewellery, &j_names), std::pair(Wisdom, &w_names), std::pair(Potions, &p_names)});

    for(size_t i = 0; i < count; i++) {
        TreasureType type = rnd_type.Next();
        treasures.push_back({type, std::string(names[type]->Next())});
    }

    return treasures;
}

std::vector<Food> CreateRandomFood(size_t count) {
    std::vector<Food> food;

    // PeopleFood
    gcheck::Random pf_names({"Tenderloin steak", "Carnivore pizza", "Beef chuck", "Pork ribs", "Cornered beef", "Flank steak", "Pork rack", "Half of a pork's ass", "Horse (salami)"});
    // People
    gcheck::Random p_names({"Raimo", "Petteri", "Joonas", "Konsta", "Jack Sparrow", "John Smith", "Random crusader", "Barack Obama", "The Pope"});
    // Herbs
    gcheck::Random h_names({"Arrowroot", "Bay leaves", "Hawthorn", "Hypericum perforatum", "Poppy seeds", "Magic mushrooms", "Salvia divinorum", "Salvia officinalis", "Peppermint root"});

    gcheck::Random rnd_type(std::vector<FoodType>({People, PeopleFood, Herbs}));
    std::unordered_map<FoodType, gcheck::Random<const char*>*> names({std::pair(People, &p_names), std::pair(PeopleFood, &pf_names), std::pair(Herbs, &h_names)});

    for(size_t i = 0; i < count; i++) {
        FoodType type = rnd_type.Next();
        food.push_back({type, std::string(names[type]->Next())});
    }

    return food;
}

gcheck::RandomSizeContainer<Treasure, std::list> rnd_treasures(10, 30, CreateRandomTreasures(50));
gcheck::RandomSizeContainer<Food, std::list> rnd_foods(10, 30, CreateRandomFood(50));
gcheck::Random<std::string> rnd_name(std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
gcheck::Random<size_t> rnd_age(0, 10000);
gcheck::Random<size_t> rnd_size(5, 30);
gcheck::RandomContainer<std::string> rnd_names(3, std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
gcheck::RandomContainer<size_t> rnd_ages(3, (size_t)0, (size_t)10000);
gcheck::RandomContainer<size_t> rnd_sizes(3, (size_t)5, (size_t)30);


PREREQ_TEST(Dragons, constructors, 1, 0) {

    int puff_age = rnd_age.Next();
    int bahamut_age = rnd_age.Next();
    int puff_size = rnd_size.Next();
    int bahamut_size = rnd_size.Next();
    MagicDragon* mdragon = new MagicDragon("Puff", puff_age, puff_size);
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", bahamut_age, bahamut_size);

    EXPECT_EQ("Puff", mdragon->GetName());
    EXPECT_EQ(puff_age, mdragon->GetAge());
    EXPECT_EQ(puff_size, mdragon->GetSize());

    EXPECT_EQ("Bahamut", fdragon->GetName());
    EXPECT_EQ(bahamut_age, fdragon->GetAge());
    EXPECT_EQ(bahamut_size, fdragon->GetSize());

    delete fdragon;
    delete mdragon;
}

template<typename T>
std::string THoardOutput(std::list<Treasure> treasures) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Hoard(treasures);
    return tout.str();
} 
template<typename T>
std::vector<Treasure> THoardList(std::list<Treasure> treasures) {
    T("", 0, 0).Hoard(treasures);
    return std::vector<Treasure>(treasures.begin(), treasures.end());
} 
template<typename T>
std::vector<Treasure> THoardDragons(std::list<Treasure> treasures) {
    T dragon("", 0, 0);
    dragon.Hoard(treasures);
    auto& treas = dragon.GetTreasures();
    return std::vector<Treasure>(treas.begin(), treas.end());
} 

PREREQ_TEST(MagicDragon, Hoard_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Magic dragon received: Liquid luck\nMagic dragon received: Elixir of euphoria\nMagic dragon received: Cough syrup\nMagic dragon received: Truth serum\nMagic dragon received: Cough syrup\nMagic dragon received: Liquid luck\nMagic dragon received: Liquid luck\n","Magic dragon received: Garroting gas\nMagic dragon received: Cough syrup\nMagic dragon received: Essence of insanity\nMagic dragon received: Cough syrup\nMagic dragon received: Truth serum\nMagic dragon received: Garroting gas\nMagic dragon received: Essence of insanity\nMagic dragon received: Garroting gas\nMagic dragon received: Cough syrup\n","Magic dragon received: Essence of insanity\nMagic dragon received: Stoneskin potion\nMagic dragon received: Truth serum\nMagic dragon received: Blemish blitzer\nMagic dragon received: Essence of insanity\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Bag of pearls")}}),std::list({Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")}}),std::list({Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The Symposium")}})});
        TestCase(3,correct_not_reserved,THoardOutput<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Fantasy dragon received: Silver coins\nFantasy dragon received: Topaz\nFantasy dragon received: Jade stone\nFantasy dragon received: Silver coins\nFantasy dragon received: Gold bar\n","Fantasy dragon received: Topaz\nFantasy dragon received: Agate\nFantasy dragon received: Agate\nFantasy dragon received: Topaz\nFantasy dragon received: Gold bar\nFantasy dragon received: Ruby\nFantasy dragon received: Topaz\nFantasy dragon received: Agate\n","Fantasy dragon received: Agate\nFantasy dragon received: Silver coins\nFantasy dragon received: Gold bar\nFantasy dragon received: Ruby\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Cough syrup")}}),std::list({Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")}}),std::list({Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("The Symposium")}})});
        TestCase(3,correct_not_reserved,THoardOutput<FantasyDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Hoard_treasures_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")}}),std::vector({Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("The Symposium")}}),std::vector({Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Liquid luck")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Stoneskin potion")}}),std::list({Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("The Symposium")}}),std::list({Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Cough syrup")}})});
        TestCase(3,correct_not_reserved,THoardList<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_treasures_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")}}),std::vector({Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("MAOL")}}),std::vector({Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Truth serum")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")}}),std::list({Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("MAOL")}}),std::list({Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Ruby")}})});
        TestCase(3,correct_not_reserved,THoardList<FantasyDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Hoard_dragons_treasures, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")}}),std::vector({Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Blemish blitzer")}}),std::vector({Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Liquid luck")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Critique of pure reason")}}),std::list({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Liquid luck")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Gold bar")}}),std::list({Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")}})});
        TestCase(3,correct_not_reserved,THoardDragons<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_dragons_treasures, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Gold bar")}}),std::vector({Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Jade stone")}}),std::vector({Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Agate")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Gold bar")}}),std::list({Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Potions, std::string("Liquid luck")}}),std::list({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Liquid luck")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Agate")}})});
        TestCase(3,correct_not_reserved,THoardDragons<FantasyDragon>,inputs_not_reserved0);
    };
}

template<typename T>
std::string TEatOutput(std::list<Food> foods) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Eat(foods);
    return tout.str();
} 
template<typename T>
std::vector<Food> TEatList(std::list<Food> foods) {
    T("", 0, 0).Eat(foods);
    return std::vector<Food>(foods.begin(), foods.end());
} 
template<typename T>
size_t TEatSize(std::list<Food> foods) {
    T dragon("", 0, 0);
    dragon.Eat(foods);
    return dragon.GetSize();
} 

PREREQ_TEST(MagicDragon, Eat_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Magic dragon ate: Salvia officinalis\nMagic dragon ate: Salvia divinorum\nMagic dragon ate: Bay leaves\nMagic dragon ate: Hypericum perforatum\nMagic dragon ate: Salvia officinalis\n","Magic dragon ate: Salvia officinalis\nMagic dragon ate: Bay leaves\nMagic dragon ate: Salvia divinorum\n","Magic dragon ate: Salvia officinalis\nMagic dragon ate: Poppy seeds\nMagic dragon ate: Hypericum perforatum\nMagic dragon ate: Salvia divinorum\nMagic dragon ate: Hypericum perforatum\nMagic dragon ate: Salvia officinalis\nMagic dragon ate: Hypericum perforatum\nMagic dragon ate: Salvia divinorum\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Petteri")}}),std::list({Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Raimo")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Pork rack")}}),std::list({Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Beef chuck")},Food{People, std::string("John Smith")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("The Pope")}})});
        TestCase(3,correct_not_reserved,TEatOutput<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Fantasy dragon ate: Petteri\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Raimo\nFantasy dragon ate: Konsta\nFantasy dragon ate: The Pope\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Cornered beef\n","Fantasy dragon ate: Horse (salami)\nFantasy dragon ate: Beef chuck\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Beef chuck\nFantasy dragon ate: Carnivore pizza\nFantasy dragon ate: Konsta\nFantasy dragon ate: Carnivore pizza\nFantasy dragon ate: Pork ribs\nFantasy dragon ate: Petteri\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Raimo\nFantasy dragon ate: The Pope\n","Fantasy dragon ate: Random crusader\nFantasy dragon ate: Tenderloin steak\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Carnivore pizza\nFantasy dragon ate: The Pope\nFantasy dragon ate: The Pope\nFantasy dragon ate: John Smith\nFantasy dragon ate: Carnivore pizza\nFantasy dragon ate: Petteri\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Beef chuck\nFantasy dragon ate: Jack Sparrow\nFantasy dragon ate: Carnivore pizza\nFantasy dragon ate: Tenderloin steak\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Raimo")},Food{People, std::string("Konsta")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")}}),std::list({Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("Konsta")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Peppermint root")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Raimo")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia divinorum")}}),std::list({Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Peppermint root")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")},Food{People, std::string("John Smith")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Tenderloin steak")}})});
        TestCase(3,correct_not_reserved,TEatOutput<FantasyDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Eat_foods_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("John Smith")},Food{People, std::string("Barack Obama")}}),std::vector({Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Beef chuck")},Food{People, std::string("The Pope")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Horse (salami)")}}),std::vector({Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("John Smith")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Barack Obama")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Barack Obama")}}),std::list({Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Random crusader")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Hypericum perforatum")}}),std::list({Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("John Smith")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Barack Obama")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")}})});
        TestCase(3,correct_not_reserved,TEatList<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_foods_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Food{Herbs, std::string("Peppermint root")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Hypericum perforatum")}}),std::vector({Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Bay leaves")}}),std::vector({Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("Konsta")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Petteri")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Peppermint root")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Petteri")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Petteri")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Carnivore pizza")}}),std::list({Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Random crusader")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("The Pope")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Cornered beef")}}),std::list({Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("John Smith")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia officinalis")}})});
        TestCase(3,correct_not_reserved,TEatList<FantasyDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Eat_dragon_size, 1, 1) {
    {
        std::vector correct_not_reserved = {(size_t)4,(size_t)5,(size_t)4};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("The Pope")},Food{People, std::string("Barack Obama")},Food{People, std::string("Konsta")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Beef chuck")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Horse (salami)")}}),std::list({Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Petteri")}}),std::list({Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Barack Obama")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Barack Obama")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("John Smith")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Barack Obama")},Food{People, std::string("The Pope")}})});
        TestCase(3,correct_not_reserved,TEatSize<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_dragon_size, 1, 1) {
    {
        std::vector correct_not_reserved = {(size_t)15,(size_t)14,(size_t)13};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("Petteri")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("Barack Obama")},Food{People, std::string("Barack Obama")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("John Smith")}}),std::list({Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Hypericum perforatum")},Food{People, std::string("The Pope")},Food{People, std::string("Barack Obama")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Peppermint root")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Hypericum perforatum")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Barack Obama")},Food{People, std::string("The Pope")},Food{People, std::string("Petteri")}}),std::list({Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Hypericum perforatum")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")},Food{People, std::string("Konsta")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Petteri")},Food{People, std::string("Barack Obama")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("John Smith")}})});
        TestCase(3,correct_not_reserved,TEatSize<FantasyDragon>,inputs_not_reserved0);
    };
}


template<typename T>
std::string TPrint(std::tuple<std::list<Treasure>, std::string, size_t, size_t> input) {
    std::list<Treasure>& treasures = std::get<0>(input);
    std::string& name = std::get<1>(input);
    size_t& age = std::get<2>(input);
    size_t& size = std::get<3>(input);
    T dragon(name, age, size);
    dragon.Hoard(treasures);
    std::stringstream os;
    os << dragon;
    return os.str();
} 


PREREQ_TEST(Dragon, ostream_write_operator, 1, 2) {
    {
        std::vector correct_not_reserved = {"Dragon named: Drogon, age: 7872, size: 12\nTreasures:\nBlemish blitzer\nGarroting gas\nGin tonic\nGin tonic\nCough syrup\nLiquid luck\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::string, size_t, size_t>(std::list({Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Ruby")}}),"Drogon",7872,12)});
        TestCase(1,correct_not_reserved,TPrint<MagicDragon>,inputs_not_reserved0);
    };
    {
        std::vector correct_not_reserved = {"Dragon named: Puff, age: 6525, size: 21\nTreasures:\nGold bar\nSapphire dust\nSapphire dust\nTopaz\nBag of pearls\nRuby\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::string, size_t, size_t>(std::list({Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Ruby")}}),"Puff",6525,21)});
        TestCase(1,correct_not_reserved,TPrint<FantasyDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(DragonCave, Accommodate, 2, 2) {
    
    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(mdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(fdragon, *it) << "Second item in GetDragons";
}

TEST_(DragonCave, Evict, 3) {
    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());
    MagicDragon* mdragon2 = new MagicDragon("Drogon", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    cave.Accommodate(mdragon2);

    cave.Evict("Puff");

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(fdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(mdragon2, *it) << "Second item in GetDragons";

    delete mdragon;
}

std::string TCavePrint(std::tuple<std::list<Treasure>, std::vector<std::string>, std::vector<size_t>, std::vector<size_t>> input) {
    std::list<Treasure>& treasures = std::get<0>(input);
    std::vector<std::string>& names = std::get<1>(input);
    std::vector<size_t>& ages = std::get<2>(input);
    std::vector<size_t>& sizes = std::get<3>(input);
    DragonCave cave;
    MagicDragon* mdragon = new MagicDragon(names[0], ages[0], sizes[0]);
    FantasyDragon* fdragon = new FantasyDragon(names[1], ages[1], sizes[1]);
    mdragon->Hoard(treasures);
    fdragon->Hoard(treasures);
    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    std::stringstream os;
    os << cave;
    return os.str();
} 

TEST_(DragonCave, stream_write_operator, 3) {
    {
        std::vector correct_not_reserved = {"DragonCave dwellers:\n\nDragon named: Puff, age: 6914, size: 8\nTreasures:\nStoneskin potion\nLiquid luck\nCough syrup\nBlemish blitzer\nStoneskin potion\nElixir of euphoria\n\nDragon named: Bahamut, age: 7974, size: 18\nTreasures:\nRuby\nAgate\nAgate\nBag of pearls\nTopaz\nGold bar\nAgate\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::vector<std::string>, std::vector<size_t>, std::vector<size_t>>(std::list({Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Liquid luck")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Gold bar")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("MAOL")}}),std::vector({std::string("Puff"),std::string("Bahamut"),std::string("Puff")}),std::vector({(size_t)6914,(size_t)7974,(size_t)8921}),std::vector({(size_t)8,(size_t)18,(size_t)21}))});
        TestCase(1,correct_not_reserved,TCavePrint,inputs_not_reserved0);
    };
}
namespace {
    template<class>
    struct sfinae_bool {};
    template<class T>
    struct sfinae_true : sfinae_bool<T>, std::true_type{};
    template<class T>
    struct sfinae_false : sfinae_bool<T>, std::false_type{};
}

namespace detail {
    template<class T>
    static auto has_copy_constructor(int) -> sfinae_true<decltype(T(std::declval<T>()))>;
    template<class T>
    static auto has_copy_constructor(long) -> sfinae_false<T>;
    
    template<class T>
    static auto has_copy_assignment(int) -> sfinae_true<decltype(std::declval<T>() = std::declval<T>())>;
    template<class T>
    static auto has_copy_assignment(long) -> sfinae_false<T>;
} // detail

template<class T>
struct has_copy_constructor_t : decltype(detail::has_copy_constructor<T>(0)){};
template<class T>
struct has_copy_assignment_t : decltype(detail::has_copy_assignment<T>(0)){};

TEST_(DragonCave, copy_assignment_constructor, 2) {
    bool has_copy_constructor = has_copy_constructor_t<DragonCave>();
    bool has_copy_assignment = has_copy_assignment_t<DragonCave>();
    EXPECT_FALSE(has_copy_constructor) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Dragon)\nfor any changes to this to take effect when running locally";
    EXPECT_FALSE(has_copy_assignment) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Dragon)\nfor any changes to this to take effect when running locally";
}