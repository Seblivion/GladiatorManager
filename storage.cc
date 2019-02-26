#include "storage.h"

Storage::Storage() :
  serialized_data{}
{
  read();
}

Storage::~Storage()
{
  write();
}

void Storage::write()
{
  std::ofstream out("savefile.txt", std::ofstream::trunc);
  for(auto tmp : serialized_data)
    if(tmp.second.second)
      {
	out << tmp.first
	    << ':'
	    << tmp.second.first
	    << ';'
	    << '\n';
      }
}

void Storage::read()
{
  std::ifstream in("savefile.txt");
  std::string key;
  std::string tmp;
  
  while(std::getline(in,key,':'))
    {
      std::getline(in, serialized_data[key].first, ';');
      serialized_data[key].second = false;
      std::getline(in,tmp,'\n');
      //försök till att ta bort '\n'
      //Missade att ta bort \n i slutet av raden,
      //då jag läser till ':' och ';' så tas de in i filen.
      //finns det något sett att ignorera vitatecken
      //innan läsning men ändo avsluta läsning på ':' ';'?
    }
}
