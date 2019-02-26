#ifndef STORAGE
#define STORAGE

#include <map>
#include <string>
#include <utility>

using been_used = bool;

class Storage
{
public:
  Storage();
  ~Storage();
  /*För att spara måste ADTn ha funktionen 'std::string serialize()', 
    funktionen ska lägga all variabeldata som skall sparas i en std::string. 
    Det ska även finnas en "Identifieringsnyckel" (std::string) för att kunna identifiera vilken data det är.

    OBS!!! Identifieringsnyckeln FÅR INTE innehålla ':',bool
    Nyckeln kan (men bör inte) innehålla ';' då det är ';' som avslutar vad som definieras som spardata.
    Spardata kan (men bör inte) innehålla ':'

    Format: <data>
    Exempel: first_name=stig last_name=helmer hit_points=50 max_hit_points=60 strength=1 agility=2 value=77 dmg=0 */

  
  template<typename T>
  void save(const T& data,
	    std::string key);

  /*för att kunna använda load-funktionen måste ADTn ha en deserialize().
    deserialize() skall kunna ta resultatet från serialize() (se save-funktionen)
    och få ut orginaldatan igen*/
  template<typename T>
  void load(T& data, //retunerade T tidigare
	 std::string key);
  
private:
  std::map<std::string,std::pair<std::string,been_used>> serialized_data;
  void write();
  void read();
};

#include "storage.tpp"

#endif //STORAGE
