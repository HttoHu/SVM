#pragma once
#include "Token.hpp"
#include <iostream>
namespace Simcc
{
	class Case :public Token
	{
	public:
		static void set_positon(Token* tok, size_t pos);
		static std::unordered_map<std::string, Case*> case_table;
		static Case* find_case(const std::string &str);

		Case(const std::string &v, size_t pos = 0) :Token(Tag::TCase), content(v) {
			position = Token::wpos;
			case_table.insert({ content,this });
		}
		void write_to_binary_file()const override;
		std::string to_string()const override {
			return "<Case: " + content + " Pos:" + std::to_string(position) + ">";
		}
		size_t token_length()const override
		{
			return sizeof(size_t);
		}

		void resetPos()
		{
			position = Token::wpos;
		}
	private:
		std::string content;
		size_t position;
	};
}
