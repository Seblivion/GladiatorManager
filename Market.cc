// Market.cc
#include "Market.h"

Market::Market():
    sell_list(),
    max_combatants(4) {
    std::vector<std::string> fname_list {"Debug", "Ludwig", "Max", "Sebastian"};
    std::vector<std::string> lname_list {"Trump", "Saltminer", "Hillary"};
    while (sell_list.size() < max_combatants) {
        add_new_combatant(fname_list, lname_list, rand() % 5);
    }
}

Market::Market(std::vector<std::string> fname, std::vector<std::string> lname):
    sell_list(),
    max_combatants(4) {
    while (sell_list.size() < max_combatants) {
	add_new_combatant(fname, lname, rand() % 5);
    }
    
}


// Misc. functions
void Market::add_new_combatant(std::vector<std::string> fname, std::vector<std::string> lname, int start_val) {
    Combatant rand_temp{fname, lname, start_val}; // Random generation combatant with name lists
    Market::add_combatant(rand_temp);
}

void Market::add_combatant(Combatant const &item) {
    if (sell_list.size() < max_combatants) {
        sell_list.push_back(item);
    }
}

void Market::remove_combatant(int const &index) {
    sell_list.erase(sell_list.begin() + index);
}

// Get
const Combatant& Market::get_combatant(int const &index) const {
    return sell_list.at(index);
}

unsigned int Market::get_max_combatants() const {
    return max_combatants;
}

// Set
void Market::set_combatant(Combatant const &item, int const &index) {
    sell_list.at(index) = item;
}
