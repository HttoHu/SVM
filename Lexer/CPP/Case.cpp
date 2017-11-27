#include "../HPP/Case.hpp"
#include "../HPP/Translator.hpp"
using namespace Simcc;
std::unordered_map<std::string, Case*> Case::case_table;
void Simcc::Case::set_positon(Token * tok, size_t pos)
{
	((Case*)tok)->position = pos;
}
Case* Case::find_case(const std::string &str)
{
  auto result=case_table.find(str);
  if(result==case_table.end())
  {
    return nullptr;
  }
  return result->second;
}

void Simcc::Case::write_to_binary_file() const
{
	char *v = (char*)&position;
	for (int i = 0; i < sizeof(double); i++)
	{
		BinFile::file_content += v[i];
		BinFile::index++;
	}
}
