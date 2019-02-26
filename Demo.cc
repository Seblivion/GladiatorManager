// Demo.cc, not for release
#include "Market.h"
#include "Team.h"
#include "Combatant.h"
#include <iostream>
#include <string>
#include <vector>

void print_menu() {
    std::cout << "******************************************" << std::endl;
    std::cout << "* 1. Print market combatants.            *" << std::endl;
    std::cout << "* 2. Buy a combatant from the market.    *" << std::endl;
    std::cout << "* 3. Print team roster.                  *" << std::endl;
    std::cout << "* 4. Sell a combatant from the roster.   *" << std::endl;
    std::cout << "* 5. Quit menu.                          *" << std::endl;
    std::cout << "******************************************" << std::endl;
}


int main() {
    std::vector<std::string> fnames {"Charlie", "Parson", "Stanley", "Wanda"};
    std::vector<std::string> lnames {"Trump", "Clinton", "SysOP"};

    std::cout << "Hello and welcome to our demo!" << std::endl;
    int choice(0);
    Market Bazaar;
    Team NY_Giants;
    int index(0);
    Combatant tmp;
    NY_Giants.set_money(9999);

    while (choice != 5) {

	switch (choice) {
	case 1:
	    // Print Market
	    for (auto i=0; i<Bazaar.get_max_combatants(); ++i) {
		tmp = Bazaar.get_combatant(i);
		std::cout << i << ". " << tmp.get_first_name() << " " <<
		    tmp.get_last_name() << ". HP:" <<
		    tmp.get_hit_points() << "/" <<
		    tmp.get_max_hit_points() << ". Str:" <<
		    tmp.get_strength() << ". Agi:" <<
		    tmp.get_agility() << ". Dam:" <<
		    tmp.get_damage() << ". Price:" <<
		    tmp.get_value() << "." << std::endl;
	    }
	    break;
	case 2:
	    // Buy combatant
	    std::cout << "Which combatant did you want? " << std::flush;
	    std::cin >> index;
	    while (index >= Bazaar.get_max_combatants() or index < 0) {
		std::cout << "That's not an option, I'm afraid." << std::endl;
		std::cout << "Please pick one of the ones we sell: " << std::flush;
		std::cin >> index;
	    }
	    tmp = Bazaar.get_combatant(index);
	    if (tmp.get_value() <= NY_Giants.get_money()) {
		std::cout << "Excellent choice! It will now be added to your roster." << std::endl;
		NY_Giants.set_money(NY_Giants.get_money() - tmp.get_value());
		NY_Giants.add_combatant(tmp);
		Bazaar.remove_combatant(index);
		Bazaar.add_new_combatant(fnames, lnames); //Never run out!
	    }
	    else {
		std::cout << "We're sorry, you could not afford that one. Please buy something or leave our establisment, please." << std::endl;
	    }
	    break;
	case 3:
	    // Print roster
	    for (auto ii=0; ii<NY_Giants.get_roster_size(); ++ii) {
		tmp = NY_Giants.get_combatant(ii);
		std::cout << ii << ". " << tmp.get_first_name() << " " <<
		    tmp.get_last_name() << ". HP:" <<
		    tmp.get_hit_points() << "/" <<
		    tmp.get_max_hit_points() << ". Str:" <<
		    tmp.get_strength() << ". Agi:" <<
		    tmp.get_agility() << ". Dam:" <<
		    tmp.get_damage() << ". Price:" <<
		    tmp.get_value() << "." << std::endl;
	    }
	    std::cout << "Your team has: " << NY_Giants.get_money() << " dosh." << std::endl;
	    break;
	case 4:
	    // Sell combatant
	    std::cout << "Which combatant did you want to sell? " << std::flush;
	    std::cin >> index;
	    while (index >= NY_Giants.get_roster_size() or index < 0) {
		std::cout << "That's not an option, I'm afraid." << std::endl;
		std::cout << "Please pick one of the ones you have: " << std::flush;
		std::cin >> index;
	    }


	    tmp = NY_Giants.get_combatant(index);
	    std::cout << "Excellent, please have a bunch of cash!" << std::endl;
	    NY_Giants.set_money(NY_Giants.get_money() + tmp.get_value());
	    NY_Giants.remove_combatant(index);
	    break;
	case 5:
	    // Quit
	    std::cout << "Thank you, come again!" << std::endl;
	    break;
	default:
	    // Incorrect number
	    std::cout << "Here are the options you can pick:" << std::endl;
	    break;
	} // End switch case
	print_menu();
	std::cin >> choice;
    } // End while loop
} // End main function
