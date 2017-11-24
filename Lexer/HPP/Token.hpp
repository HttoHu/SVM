#pragma once
#include <string>
#include <unordered_map>
namespace Simcc
{
	enum Tag
	{
		Num, Lonum, Dec, LiteralString, LChar,
		Mov, IMov8, IMov16, IMov32, IMov64, SMov,
		Add, Sub, Mul, Div,
		Int, Double, Long, String, Char,
		Cmp, Jeq, Jne, Jgt, Jge, Jlt, Jle,
		Jmp, TCase,
		TId,
	};
	class Token
	{
	public:
		static std::unordered_map<std::string, Token*> symbol_map;
		static Token* find(const std::string &str);
		Token(Tag t) :tag(t) {}
		virtual void write_to_binary_file()
		{

		}
		virtual std::string to_string()const { return "<empty>"; }
		virtual ~Token() {}

	private:
		Tag tag;
	};

}
