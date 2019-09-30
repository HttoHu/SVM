#include "../includes/lexer.hpp"
namespace SVM
{
	std::string content;
	size_t Endl::current_line=0;
	size_t Endl::unins_count=0;
	std::map<TokenTag, std::string> TagStrMap
	{
		{EPT,"EPT"},{INTEGER,"INTEGER"},{ID,"ID"},
		{REAL,"REAL"},{BYTE,"BYTE"},{STRLIT,"STRLIT"},
		{IADD,"IADD"},{ISUB,"ISUB"},{IMUL,"IMUL"},{IDIV,"IDIV"},
		{IGT,"IGT"},{IST,"IST" },{IEQ,"IEQ"},{IEGT,"IEGT"},{IEST,"IEST"},
		{RADD,"RADD"},{RSUB,"RSUB"},{RMUL,"RMUL"},{RDIV,"RDIV"},
		{RGT,"RGT"},{RST,"RST"},{REQ,"REQ"},{REGT,"REGT"},{REST,"REST"},
		{SADD,"SADD"},{SSUB,"SSUB"},{SMUL,"SMUL"},{SSUB,"SSUB"},
		{RSADD,"RSADD"},{RSSUB,"RSSUB"},{RSMUL,"RSMUL"},{RSDIV,"RSDIV"},
		{AND,"AND"},{OR,"OR"},{INC,"INC"},{DEC,"DEC"}, {FALSE,"FALSE"},{TRUE,"TRUE"},
		{GOTO,"GOTO"},{IFTRUE,"IFTRUE"},{IFFALSE,"IFFALSE"},{POSTAG,"POSTAG"},{PUSH,"PUSH"},
		{CALL,"CALL"},{OFFSET,"OFFSET"},{VAR,"VAR"},
		{DOT,"DOT"},{COLON,"COLON"},{ADDR_TAG,"ADDR_TAG"},{STRUCT,"STRUCT"},
		{ENDL,"ENDL"}
	};
	std::map<std::string, Token*> KeyWord
	{
		{"var",new Token(VAR)},
		{"iadd",new Token(IADD)},{"isub",new Token(ISUB)},{"imul",new Token(IMUL)},{"idiv",new Token(IDIV)},
		{"ieq",new Token(IEQ)},{"ist",new Token(IST)},{"igt",new Token(IGT)},{"iegt",new Token(IEGT)},{"iest",new Token(IEST)},
		{"ssub",new Token(SSUB)},{"sadd",new Token(SADD)},{"smul",new Token(SMUL)},{"sdiv",new Token(SDIV)},
		{"radd",new Token(RADD)},{"rsub",new Token(RSUB)},{"rmul",new Token(RMUL)},{"rdiv",new Token(RDIV)},
		{"req",new Token(REQ)},{"rst",new Token(RST)},{"rgt",new Token(RGT)},{"regt",new Token(REGT)},{"rest",new Token(REST)},
		{"rssub",new Token(RSSUB)},{"rsadd",new Token(RSADD)},{"rsmul",new Token(RSMUL)},{"rsdiv",new Token(RSDIV)},
		{"and",new Token(AND)},{"or",new Token(OR)},{"false",new Token(FALSE)},{"true",new Token(TRUE)},
		{"inc",new Token(INC)},{"dec",new Token(DEC)}, {"goto",new Token(GOTO)},{"iftrue",new Token(IFTRUE)},
		{"iffalse",new Token(IFFALSE)},{"push",new Token(PUSH)},{"call",new Token(CALL)}
	};
	TokenStream token_stream;
	std::string Token::to_string()
	{
		auto result = TagStrMap.find(tag);
		if (result == TagStrMap.end())
			throw Error("illegal token");
		return "<" + result->second + ">";
	}
	Token* Id::find(std::string str)
	{
		for (size_t i = 0; i < id_table().size(); i++)
		{
			auto result = id_table().find(str);
			if (result == id_table().end())
				continue;
			return result->second;
		}
		return nullptr;
	}
	std::string Id::to_string()
	{
		return "<Id: " + id + ">";
	}
	void TokenStream::push_back(Token* tok)
	{
		content.push_back(tok);
	}
	Token* TokenStream::this_token()
	{
		while (content[pos]->get_tag() == TokenTag::ENDL)
			advance();
		return content[pos];
	}
	void TokenStream::next()
	{
		if (this_token()->get_tag() == TokenTag::ENDL || this_token()->get_tag() == TokenTag::EPT)
		{
			advance();
			next();
		}
		advance();
	}
	void TokenStream::advance()
	{
		pos++;
		if (pos >= content.size())
		{
			throw Error("to the end of token_stream");
		}
	}
	void TokenStream::match(TokenTag t)
	{
		// to check the token whether it is right, and if matched call advance, or throw an error.
		// example: match(PLUS); 
		if (this_token()->get_tag() == TokenTag::ENDL)
		{
			advance();
			match(t);
		}
		else if (this_token()->get_tag() == t)
			advance();
		else
			throw Error(this_token()->to_string() + " not match with " + TagStrMap[t]);
	}
	void TokenStream::print()
	{
		for (auto& a : content)
			std::cout << a->to_string();
	}
	TokenTag TokenStream::this_tag()
	{
		return this_token()->get_tag();
	}

	std::string Number::to_string()
	{
		return "<Integer:" + std::to_string(value) + ">";
	}
	std::string Float::to_string()
	{
		return "<float:" + std::to_string(value) + ">";
	}
	namespace LexerTools
	{
		Token* process_number(const std::string& str, size_t& pos)
		{
			bool is_nag = str[pos] == '-';
			if (is_nag)
				pos++;
			int ret = 0;
			for (; pos < str.size(); pos++)
			{
				if (isdigit(str[pos]))
					ret = ret * 10 + (str[pos] - 48);
				else
				{
					break;
				}
			}
			double tmp = 0.0;
			double tmp2 = 1;
			if (str[pos] == '.')
			{
				pos++;
				for (; pos < str.size(); pos++)
				{
					if (isdigit(str[pos]))
					{
						tmp2 /= 10;
						tmp = tmp + tmp2 * (str[pos] - (short)48);
					}
					else
					{
						if(is_nag)
							return new Float(-((double)ret + tmp));
						return new Float((double)ret + tmp);
					}
				}
			}
			if (is_nag)
				return new Number(-ret);
			return new Number(ret);
		}
		Token* process_string(const std::string& str, size_t& pos)
		{
			std::string value;
			if (str[pos] == '\'')
				pos++;
			else
				throw Error("a string-literal must start with\'");
			for (; pos < str.size(); pos++)
			{
				if (str[pos] == '\'')
					break;
				if (str[pos] == '\\')
				{
					pos++;
					if (pos >= str.size())
						throw Error("out of range");
					switch (str[pos])
					{
					case 'a':
						value += '\a';
						break;
					case 'b':
						value += '\b';
						break;
					case 'n':
						value += '\n';
						break;
					case 'r':
						value += '\r';
						break;
					case 't':
						value += '\t';
						break;
					case '\\':
						value += '\\';
						break;
					case '\'':
						value += '\'';
						break;
					default:
						throw Error("no matched escape character");
					}
				}
				else
					value += str[pos];
			}
			return new StringToken(value);
		}
		Token* process_word(const std::string& str, size_t& pos)
		{
			std::string ret;
			bool is_tag = false;
			if (str[pos]==':')
			{
				is_tag = true;
				pos++;
			}
			bool first_char = true;
			for (; pos < str.size(); pos++)
			{
				if (first_char)
				{
					first_char = false;
					if (isalpha(str[pos]) || str[pos] == '_')
						ret += str[pos];
					continue;
				}
				else
				{
					if (isalnum(str[pos]) || str[pos] == '_')
						ret += str[pos];
					else
					{
						pos--;
						break;
					}
				}
			}
			auto result = KeyWord.find(ret);
			if (result != KeyWord.end())
			{
				return result->second;
			}
			auto id_result = Id::find(ret);
			if (id_result != nullptr)
				return id_result;
			else
			{
				if (is_tag)
					return new Tag(ret);
				return new Id(ret);
			}
		}
		void build_token_stream(const std::string& content)
		{
			std::string tmp_str;
			token_stream.push_back(new Endl());
			for (size_t i = 0; i < content.size(); i++)
			{
				switch (content[i])
				{
				case '\"':
					token_stream.push_back(process_string(content, i));
					break;
				
				case '\r':
				case '\n':
					token_stream.push_back(new Endl());
					break;
				case '.':
					token_stream.push_back(new Token(DOT));
					break;
				case '\t':
					break;
				case ' ':
					break;
				case '-':
				case '0':case '1':case '2':case '3':case '4':case '5':case '6':
				case '7':case '8':case '9':
					token_stream.push_back(process_number(content, i));
					i--;
					break;
				case ':':
				default:
					token_stream.push_back(process_word(content, i));
					break;
				}
			}
		}
	}

	Tag::Tag(std::string str):Token(TAG)
	{
		sz = Endl::current_line-Endl::unins_count-1;
		Endl::unins_count++;
		Id::id_table().insert({ str,this });
	}

}

