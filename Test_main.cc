#include <string>
#include <sstream>
#include <iostream>

#include "storage.h"
#include "Combatant.h"
#include "Team.h"

int main()
{
  Combatant obj1{"Max","Nordin",50,60,5,10,2,100};
  Combatant obj2{"Christoffer","Holm",13,20,3,6,20,200};
  Team team1;
  team1.add_combatant(obj1);
  team1.add_combatant(obj2);
  Team team2;
  
  {
    Storage store;
    store.save(team1, "Player Team");
    //    store.save(obj2, "Combatant2");
    //store.save(obj3, "Ex1");
  } 
  
  Storage store;
  //store.load(obj3, "Ex1");
  //store.save(obj3, "Ex1");

  //store.save(obj2, "Combatant3");
  store.load(team2, "Player Team");
  store.save(team1, "Player Team");//måste spara igen då jag använder trunc

  std::string tmp{team2.serialize()};
  
  std::cout << tmp;
  return 0;
}
