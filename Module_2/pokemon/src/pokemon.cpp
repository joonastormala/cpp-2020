#include "pokemon.hpp"
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

PokemonCollection::PokemonCollection(PokemonCollection collection, PokemonCollection collection2)
{
    copy(collection.begin(), collection.end(), back_inserter(pokemons_));
    copy(collection2.begin(), collection2.end(), back_inserter(pokemons_));
    pokemons_.sort();
    pokemons_.unique();
}

void PokemonCollection::Add(const string &name, size_t id)
{
    pokemons_.push_back({name, id});
}

bool PokemonCollection::Remove(const std::string &name, size_t id)
{
    for (list<pair<string, size_t>>::iterator i = pokemons_.begin();
         i != pokemons_.end(); i++)
    {
        if (i->first == name && i->second == id)
        {
            pokemons_.erase(i);
            return true;
        }
    }
    return false;
}

void PokemonCollection::Print() const
{
    for (auto i : pokemons_)
    {
        cout << "id: " << i.second << ", name: " << i.first << endl;
    }
}

void PokemonCollection::SortByName()
{
    pokemons_.sort();
}

void PokemonCollection::SortById()
{
    pokemons_.sort([](auto &right, auto &left) {
        return left.second > right.second;
    });
}