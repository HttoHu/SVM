#include "../HPP/Token.hpp"
using namespace Simcc::Lexer;
std::unordered_map<std::string, Tag>& Simcc::Lexer::keyword_map()
{
	static std::unordered_map<std::string, Tag> ret{
		{ "true",Tag::True },{ "false",Tag::False },{"int",Tag::SInt},{"double",Tag::SDouble},{"long",Tag::SLong},
		{"char",Tag::SChar},{"string",Tag::SString},{"bool",Tag::SBool},
		 {"jmp",Tag::JMP},{"jge",Tag::JGE},{"jne",Tag::JNE},
		{"cmp",Tag::CMP},{"jle",Tag::JLE},{"jlt",Tag::JLT},{"jgt",Tag::JGT},{"ret",Tag::RET},
		{ "And",Tag::And },{ "OR",Tag::Or },
	};
	return ret;
}

std::unordered_map<std::string, Tag>& Simcc::Lexer::symbol_map()
{
	static std::unordered_map<std::string, Tag> ret{
		{ "[",Tag::LSB },{ "]",Tag::RSB },
		{",",Tag::Comma},
		{":",Tag::TTag}
	};
	return ret;
}