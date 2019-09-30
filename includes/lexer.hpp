/*
	SVM is a virtual mechine for merdog
	By HttoHu 2019
*/
#pragma once
#include <deque>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "error.hpp"
namespace SVM
{
	enum TokenTag
	{
		// Integer literary
		EPT,ID,
		INTEGER, REAL, BYTE,STRLIT,
		IADD, ISUB, IMUL, IDIV, IGT, IST, IEQ,IEGT,IEST,
		RADD, RSUB, RMUL, RDIV, RGT, RST, REQ, REGT, REST,
		SADD, INC, DEC,SSUB,SMUL,SDIV,
		RSADD,RSSUB,RSMUL,RSDIV,
		AND, OR,FALSE,TRUE,
		GOTO, IFTRUE, IFFALSE,
		POSTAG,PUSH,
		CALL, OFFSET, VAR, MEMB,
		DOT, COLON, ADDR_TAG, STRUCT,
		ENDL,TAG,END,
	};
	class Token
	{
	public:
		Token(TokenTag tg) :tag(tg) {}
		virtual ~Token() {}
		virtual std::string to_string();
		virtual size_t* get_add() { throw Error("try to call get_add() at Token"); }
		TokenTag get_tag() { return tag; }
	private:
		TokenTag tag;
	};

	class Id :public Token
	{
	public:
		Id(std::string str) :Token(ID), id(str) 
		{
			id_table().insert({ str ,this });
		}
		static std::map<std::string, Token*>& id_table()
		{
			static std::map<std::string, Token*> ret;
			return ret;
		}
		static Token* find(std::string str);
		size_t* get_add()override { return &pos; }
		std::string to_string()override;
		std::string get_value() { return id; }
	private:
		std::string id;
		size_t pos;
	};
	class Tag :public Token
	{
	public:
		Tag(std::string str);
		size_t* get_add()override { return &sz; }
		std::string to_string()override {
			return "<Tag: " + std::to_string(sz) + ">";
		}
	private:
		size_t sz;
	};
	class Number :public Token
	{
	public:
		Number(int v) :Token(INTEGER), value(v) {}
		int get_value() { return value; }
		size_t* get_add()override { return &pos; }
		std::string to_string()override;
	private:
		int value;
		size_t pos;
	};

	class Float :public Token
	{
	public:
		Float(double v) :Token(REAL), value(v) {}
		double get_value() { return value; }
		size_t* get_add()override { return &pos; }
		std::string to_string()override;
	private:
		size_t pos;
		double value;
	};

	class Byte :public Token
	{
	public:
		Byte(char v) :Token(BYTE), value(v) {}
		char get_value()const { return value; }
		size_t* get_add()override { return &pos; }
	private:
		size_t pos;
		char value;
	};

	class StringToken :public Token
	{
	public:
		StringToken(std::string v) :Token(STRLIT), value(v) {}
		std::string get_value()const { return value; }
		size_t* get_add()override { return &pos; }
	private:
		std::string value;
		size_t pos;
	};

	class TokenStream
	{
	public:
		TokenStream() {}
		Token* this_token();
		TokenTag this_tag();
		size_t size() { return content.size(); }
		void push_back(Token* tok);
		void next();
		void advance();
		void match(TokenTag t);
		void print();
	private:
		std::vector<Token*> content;
		size_t pos = 0;
	};

	class Endl :public Token
	{
	public:
		Endl() :Token(TokenTag::ENDL)
		{
			line_no = ++current_line;
		}
		size_t get_value(Token* tok) { return line_no; }
		static size_t current_line;
		static size_t unins_count;
		std::string to_string()override {
			return "\n";
		}

	private:
		size_t line_no;
	};
	extern std::map<TokenTag, std::string> TagStrMap;
	extern std::map<std::string, Token*> KeyWord;
	extern TokenStream token_stream;
	namespace LexerTools {
		Token* process_number(const std::string& str, size_t& pos);
		Token* process_word(const std::string& str, size_t& pos);
		Token* process_string(const std::string& str, size_t& pos);
		void build_token_stream(const std::string& content);

	}
}