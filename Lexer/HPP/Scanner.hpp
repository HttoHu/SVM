#pragma once
#include <string>
#include "Token.hpp"

namespace Simcc
{
	namespace Lexer
	{
		std::vector<Token*> &token_stream();
		void init(const std::string &str);
		void set_token_stream();

	}
}
