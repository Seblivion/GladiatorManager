// Market.h
#ifndef MARKET_H_G
#define MARKET_H_G
#include "Team.h"
#include <vector>
#include <string>

class Market
{
public:
    // Constructor
    Market(); // Make market, mostly for debugging purposes
    Market(std::vector<std::string> fname, std::vector<std::string> lname);

    // Misc. Functions
    void add_new_combatant(std::vector<std::string> fname, std::vector<std::string> lname, int start_val);
    void add_combatant(Combatant const &item);
    void remove_combatant(int const &index);

    // Get
    const Combatant& get_combatant(int const &index) const;
    unsigned int get_max_combatants() const;
    

    // Set
    void set_combatant(Combatant const &item, int const &index);

protected:
    std::vector<Combatant> sell_list;
    unsigned int max_combatants;


};


#endif
