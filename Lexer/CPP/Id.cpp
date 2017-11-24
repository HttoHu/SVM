#include "../HPP/Id.hpp"
using namespace Simcc;
std::unordered_map<std::string, Id*> Id::id_table{
  std::unordered_map<std::string,Id*>()
};
Id* Id::find_id(const std::string &str){
  auto result=id_table.find(str);
  if(result==id_table.end())
  {
    return nullptr;
  }
  return result->second;
}
