#pragma once
#include "Token.hpp"
namespace Simcc
{
	namespace Lexer
	{
		class Case final:public Token
		{
		public:
			static void create_new_case(std::string name,size_t index);
			static Case find_case();
			static std::unordered_map<std::string, Case*> case_table;
			Case(size_t index) :Token(Tag::TTag),content(index) {}
			
		private:
			size_t content;
		};
	}
}