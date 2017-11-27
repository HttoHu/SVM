#pragma once
#include "Token.hpp"
namespace Simcc
{
	class LInt:public Token
	{
	public:
		LInt(int v) :Token(Tag::Num), content(v) {		}
		std::string to_string()const override
		{
			return "<Num:"+std::to_string(content)+">";
		}
		size_t token_length()const override
		{
			return 4;
		}
		void write_to_binary_file()const override;
		int content;
	};
	class LLInt :public Token
	{
	public:
		LLInt(int v) :Token(Tag::Lonum), content(v) {
		}
		std::string to_string()const override
		{
			return "<LNum:" + std::to_string(content) + ">";
		}
		size_t token_length()const override
		{
			return 8;
		}
		void write_to_binary_file()const override;
		int64_t content;
	};
	class LChar :public Token
	{
	public:
		LChar(char v) :Token(Tag::LChar), content(v) {
		}
		std::string to_string()const override
		{
			return "<LC:" + std::to_string(content) + ">";
		}
		size_t token_length()const override
		{
			return 1;
		}
		void write_to_binary_file()const override;
		char content;
	};
	class LDouble :public Token
	{
	public:
		LDouble(double v) :Token(Tag::Dec), content(v) {
		}
		std::string to_string()const override
		{
			return "<LD:" + std::to_string(content) + ">";
		}
		size_t token_length()const override
		{
			return sizeof(double);
		}
		void write_to_binary_file()const override;
		double content;
	};
	class LString :public Token
	{
	public:
		LString(const std::string & v) :Token(Tag::LiteralString), content(v) {
		}
		std::string to_string()const override
		{
			return "<LSTR: " + content + ">";
		}
		size_t token_length()const override
		{
			return content.size();
		}
		void write_to_binary_file()const override;
		std::string content;
	};
}