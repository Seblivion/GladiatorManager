// Demo.cc, not for release
#include "Combatant.h"
#include "Mechanics.h"

#include <iostream>
#include <string>
#include <vector>
#include <time.h>


void print_menu() {
    std::cout << "******************************************" << std::endl;
    std::cout << "* 1. Print market combatants.            *" << std::endl;
    std::cout << "* 2. Buy a combatant from the market.    *" << std::endl;
    std::cout << "* 3. Print team roster.                  *" << std::endl;
    std::cout << "* 4. Sell a combatant from the roster.   *" << std::endl;
    std::cout << "* 5. Select arena combatant.             *" << std::endl;
    std::cout << "* 6. Next arena step.                    *" << std::endl;
    std::cout << "* 7. Show arena logs.                    *" << std::endl;
    std::cout << "* 8. Train team.                         *" << std::endl;
    std::cout << "* 9. Quit menu.                          *" << std::endl;
    std::cout << "******************************************" << std::endl;
}


int main() {
    srand(time(NULL));
    
    std::vector<std::string> fnames {"Charlie", "Parson", "Stanley", "Wanda", "Jillian", "DonKing", "Ansom", "Sizemore", "Maggie", "Isaac", "Jack"};
    std::vector<std::string> lnames {"Trump", "Clinton", "SysOP", "Saltminer", "Tester", "Bystander", "PleaseSaveMe"};

    std::cout << "Hello and welcome to our demo v2, now with (terribly) random names!" << std::endl;
    std::cout << "This demo shows off the combat system and the training as well! More names, improved stat usage and restricted team sizes!" << std::endl;

    int choice(0);
    Mechanics mecha{fnames, lnames};
    
    int index(0);
    Combatant tmp;
    mecha.set_money(200);

    while (choice != 9) {

	switch (choice) {
	case 1:
	    // Print Market
	    for (unsigned int i=0; i<mecha.get_market_max_combatants(); ++i) {
		tmp = mecha.get_market_combatant(i);
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

	    if (mecha.can_buy_combatant(index)) {
		std::cout << "Congratulations, you could buy it!" << std::endl;
	    }
	    else {
		std::cout << "Sorry, you could not buy that one." << std::endl;
	    }
	    mecha.buy_combatant(index);

	    break;
	case 3:
	    // Print roster
	    for (unsigned int ii=0; ii<mecha.get_roster_size(); ++ii) {
		tmp = mecha.get_team_combatant(ii);
		std::cout << ii << ". " << tmp.get_first_name() << " " <<
		    tmp.get_last_name() << ". HP:" <<
		    tmp.get_hit_points() << "/" <<
		    tmp.get_max_hit_points() << ". Str:" <<
		    tmp.get_strength() << ". Agi:" <<
		    tmp.get_agility() << ". Dam:" <<
		    tmp.get_damage() << ". Price:" <<
		    tmp.get_value() << "." << std::endl;
	    }
	    std::cout << "Your team has: " << mecha.get_money() << " dosh." << std::endl;
	    break;
	case 4:
	    // Sell combatant
	    std::cout << "Which combatant did you want to sell? " << std::flush;
	    std::cin >> index;
	    
	    mecha.sell_combatant(index);
	    break;
	case 5:
	    // Select arena combatant
	    std::cout << "Which combatant should go to the arena? " << std::flush;
	    std::cin >> index;

	    mecha.select_arena_fighter(index);
	    mecha.generate_arena_opponent(); // Generates random opponent
	    mecha.set_fastest(); // Agility determines who is fastest and acts first.
	    mecha.clear_logs(); // This will remove all the text logs in the arena_logs vector.
	    break;
	case 6:
	    // Next arena step
	    if (! mecha.is_combat_over()) {
		mecha.next_combat_step();
		std::cout << mecha.get_logs().back() << std::endl; // Returns the last combat log to be entered and shows it
	    } else {
		std::cout << "Combat's over, ";
		if (mecha.player_lost()) {
		    std::cout << "you lost...";
		} else {
		    std::cout << "a winner is you!";
		}
		std::cout << std::endl;
	    }
	    break;
	case 7:
	    // Show arena logs
	    for (auto i=mecha.get_logs().begin(); i != mecha.get_logs().end(); ++i) {
		std::cout << *i << std::endl;
	    }
	    break;
	case 8:
	    // Train team
	    std::cout << "You are now training the team, check to see their improvement!" << std::endl;
	    mecha.train_team();
	    break;
	case 9:
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
