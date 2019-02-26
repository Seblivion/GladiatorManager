#include <fstream>

template<typename T>
void Storage::save(const T& data,
		   std::string key)
{
  serialized_data[key].first = data.serialize();
  serialized_data[key].second = true;
}

template<typename T>
void Storage::load(T& data,
		std::string key)
{
  serialized_data[key].second = true;
  return data.deserialize(serialized_data[key].first);
}
