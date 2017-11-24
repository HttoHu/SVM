#include "../HPP/Case.hpp"
using namespace Simcc;
std::unordered_map<std::string, Simcc::Lexer::Case*> Lexer::Case::case_table;

void Simcc::Lexer::Case::create_new_case(const std::string &name,size_t index)
{
	case_table.insert({ name,new Case(index) });
}

Simcc::Lexer::Token* Simcc::Lexer::Case::find_case(const std::string &str)
{
	auto result = case_table.find(str);
	if (result == case_table.end())
		return nullptr;
	return result->second;
}
