#include "../HPP/Case.hpp"
using namespace Simcc;
std::unordered_map<std::string, Case*> Case::case_table;
Case* Case::find_case(const std::string &str)
{
  auto result=case_table.find(str);
  if(result==case_table.end())
  {
    return nullptr;
  }
  return result->second;
}
