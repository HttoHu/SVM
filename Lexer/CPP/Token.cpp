#include "../HPP/Token.hpp"
using namespace Simcc;
std::unordered_map<std::string, Token*> Token::symbol_map
{
	{ "int",new Token(Tag::Int) },{ "string",new Token(Tag::String) },
	{ "char",new Token(Tag::Char) },{ "double",new Token(Tag::Double) },
	{ "long",new Token(Tag::Long) },
	{"add",new Token(Tag::Add)},{ "sub",new Token(Tag::Sub) },
	{ "mov",new Token(Tag::Mov) },{ "mul",new Token(Tag::Mul) },
	{ "div",new Token(Tag::Div) },{ "imov8",new Token(Tag::IMov8) },
	{ "imov16",new Token(Tag::IMov16) },{ "imov32",new Token(Tag::IMov32) },
	{ "imov64",new Token(Tag::IMov64) },{ "cmp",new Token(Tag::Cmp) },
	{ "jeq",new Token(Tag::Jeq) },{ "jne",new Token(Tag::Jne) },
	{ "jge",new Token(Tag::Jge) },{ "jgt",new Token(Tag::Jgt) },
	{ "jle",new Token(Tag::Jle) },{ "jlt",new Token(Tag::Jlt) },
};

Token * Simcc::Token::find(const std::string &str)
{
	auto result = symbol_map.find(str);
	if (result == symbol_map.end())
		return nullptr;
	return result->second;
}
