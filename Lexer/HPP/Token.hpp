#pragma once
#include <string>
#include <unordered_map>

namespace Simcc
{
	enum Tag
	{
		Num=0x00, Lonum=0x01, Dec=0x02, LiteralString=0x03, LChar=0x04,
		Mov, IMov8, IMov16, IMov32, IMov64, SMov,
		Add, Sub, Mul, Div,
		DAdd,DSub,DMul,DDiv,
		Int, Double, Long, String, Char,
		Cmp, Jeq, Jne, Jgt, Jge, Jlt, Jle,
		Jmp, TCase,
		TId,
		ENDL,
	};
	extern std::unordered_map<Tag, std::string> tag_to_string_table;
	class Token
	{
	public:
		static size_t wpos;
		static std::unordered_map<std::string, Token*> symbol_map;
		static Token* find(const std::string &str);
		Token(Tag t) :tag(t) {
		}
		virtual size_t token_length()const 
		{
			return 1;
		}
		virtual void write_to_binary_file()const;
		virtual std::string to_string()const;
		virtual ~Token() {}

	private:
		Tag tag;
	};

}
