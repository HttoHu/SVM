#pragma once
#include <string>
#include <vector>
namespace Simcc
{
	class Token;
	namespace Lexer
	{
		std::vector<Token*> &token_stream();
		void set_token_stream();
		void init(const std::string &str);
		extern std::string content;
		extern size_t index;
	}
}
