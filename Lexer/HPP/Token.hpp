#pragma once
// By 胡远韬 Simcc Hu
#include <iostream>
#include <string>
#include <unordered_map>
namespace Simcc
{
	namespace Lexer
	{
		enum Tag
		{
			SInt, SDouble, SLong, SChar, SString, SBool,
			TLiteralInt, TLiteralLong, TLiteralDouble, TLiteralChar, TLiteralString,
			Symbol,
			Id,
			True, False,
			TTag,
			Add,Sub,Mul,Div,
			INT,
			Goto,CMP,JGE,JGT,JLE,JLT,JNE,JMP,
			RET,
			And, Or, // && ,||
			LSB, RSB,// [ ]
			Comma,// ,
			Endl,
		};
		std::unordered_map<std::string, Tag>& keyword_map();
		std::unordered_map<std::string, Tag>& symbol_map();
		class Token
		{
		public:
			Token(Tag t) :tag(t) {}
			virtual std::string to_string()const
			{
				switch (tag)
				{
				case True:
					return "<true>";
				case False:
					return "<false>";
				case SBool:
					return "<bool>";
				case SInt:
					return "<int32_t>";
				case SLong:
					return "<long>";
				case SString:
					return "<string>";
				case SDouble:
					return "<double>";
				case SChar:
					return "<char>";
				case TTag:
					return "<Tag>";
				case Endl:
					return "<endline>\n";
				case Simcc::Lexer::TLiteralInt:
					return "<tint>";
				case Simcc::Lexer::TLiteralLong:
					return "<tlong>";
				case Simcc::Lexer::TLiteralDouble:
					return "<tdouble>";
				case Simcc::Lexer::TLiteralChar:
					return "<tchar>";
				case Simcc::Lexer::TLiteralString:
					return "<tstring>";
				case Simcc::Lexer::Symbol:
					return "<symbol>";
				case Simcc::Lexer::And:
					return "<&&>";
				case Simcc::Lexer::Or:
					return "<||>";
				case Simcc::Lexer::LSB:
					return "<[>";
				case Simcc::Lexer::RSB:
					return "<]>";
				case Simcc::Lexer::Comma:
					return "<,>";
				default:
					return "<unknown>";
					break;
				}
			}
			virtual void* get_value()
			{
				return nullptr;
			}
			virtual const void* const get_value()const
			{
				return nullptr;
			}
			Tag get_tag()const { return tag; }
			virtual ~Token() {}
		private:
			Tag tag;
		};
	}
}