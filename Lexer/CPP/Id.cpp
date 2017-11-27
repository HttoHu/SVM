#include "../HPP/Id.hpp"
#include "../HPP/Translator.hpp"
using namespace Simcc;
std::unordered_map<std::string, Id*> Id::id_table{

};
Id* Id::find_id(const std::string &str) {
	auto result = id_table.find(str);
	if (result == id_table.end())
	{
		return nullptr;
	}
	return result->second;
}
void Id::write_to_binary_file()const
{
	char *v = (char*)&index;
	for (int i = 0; i < sizeof(size_t); i++)
	{
		BinFile::file_content += v[i];
		BinFile::index++;
	}
}
