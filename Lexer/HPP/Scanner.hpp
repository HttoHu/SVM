#pragma once
#include <string>
#include "Token.hpp"

namespace Simcc
{
	namespace Lexer
	{
		std::vector<Token*> &token_stream();
		void set_token_stream();
		std::string content;
		size_t index;
	}
}
