#include "../HPP/Scanner.hpp"
#include "../HPP/Literal.hpp"
#include "../HPP/Id.hpp"
#include "../HPP/Case.hpp"
#include <iostream>
#include <fstream>
using namespace Simcc::Lexer;
size_t Simcc::Lexer::index = 0;
std::string Simcc::Lexer::content;
void read_string()
{
	std::string value;
	if (content[index] == '\"')
		index++;
	else
		throw std::runtime_error("a string-literal must start with\"");
	for (; content[index] != '\"'; index++)
	{
		if (index >= content.size())
		{
			throw std::runtime_error("string-literal isn't matched");
		}
		if (content[index] == '\\')
		{
			if (index >= content.size() - 1)
			{
				throw std::runtime_error("string-literal isn't matched");
			}
			index++;
			switch (content[index]) {
			case 'n':
				value += '\n';
				break;
			case 't':
				value += '\t';
				break;
			case '\"':
				value += '\"';
				break;
			case '\'':
				value += '\'';
				break;
			case '\\':
				value += '\\';
				break;
			}
		}
		else
			value += content[index];
	}
	index++;
	token_stream().push_back(new Simcc::LString(value));
	Simcc::Token::wpos += value.size();
}
void read_number()
{
	int64_t intPart = 0;
	bool isN = content[index] == '-';
	if (isN)
	{
		index++;
	}
	while (isdigit(content[index]))
	{
		intPart = intPart * 10 + (content[index++] - 48);
	}
	if (content[index] == 'L')
	{
		index++;
		if (isN)
			intPart = -intPart;
		token_stream().push_back(new Simcc::LLInt(intPart));
		Simcc::Token::wpos += 8;
		return;
	}
	if (content[index] != '.')
	{
		if (isN)
			intPart = -intPart;
		token_stream().push_back(new Simcc::LInt(static_cast<int32_t>(intPart)));
		Simcc::Token::wpos += 4;
		return;
	}
	index++;
	double v = (double)intPart;
	double v2 = 0.1;
	while (isdigit(content[index]))
	{
		v += v2*(content[index++] - 48);
		v2 /= 10;
	}
	if (isN)
		v = -v;
	token_stream().push_back(new Simcc::LDouble(v));
	Simcc::Token::wpos += 8;
}
void read_word()
{
	std::string word;
	while ((isalnum(content[index]) || content[index] == '_') && index < content.size())
	{
		word += content[index++];
	}
	if (content[index] == '@')
	{
		index++;
		Simcc::Case *c = Simcc::Case::find_case(word);
		if (c != nullptr)
		{
			token_stream().push_back(c);
			Simcc::Token::wpos += c->token_length();
			return;
		}
		else
		{
			c= new Simcc::Case(word);
			Simcc::Case::case_table[word] = c;
			token_stream().push_back(c);
			Simcc::Token::wpos += c->token_length();
			return;
		}
	}
	if (content[index] == ':')
	{
		index++;
		auto result = Simcc::Case::case_table.find(word);
		if (result != Simcc::Case::case_table.end())
		{
			result->second->resetPos();
		}
		else
		{
			Simcc::Case::case_table[word] = new Simcc::Case(word);
		}
		return;
	}
	//First search whether case_table contains a key matched word. If exist the key, then push the value into token_stream


	// search symbol_map 
	auto id_result = Simcc::Token::symbol_map.find(word);
	if (id_result == Simcc::Token::symbol_map.end())
	{
		// if symbol_map not contains a key matched word. then create an id by word and push into token_stream.
		Simcc::Id *tmp = Simcc::Id::find_id(word);
		if (tmp == nullptr)
		{
			tmp = new Simcc::Id(word);
			Simcc::Token::wpos += 3;
		}
		token_stream().push_back(tmp);
		Simcc::Token::wpos += 1;
		return;
	}
	Simcc::Token::wpos += 1;
	token_stream().push_back(id_result->second);

}
void Simcc::Lexer::init(const std::string &str)
{
	using namespace std;
	ifstream ifs(str);
	content = std::string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	std::cout << "INIT SUCCESS:File Content: ";
	const int FRAMEW = 20;
	const char FRAME = '-';
	std::cout << "\n" + std::string(FRAMEW, '=') + str + std::string(FRAMEW, '=') + "\n";
	std::cout << content;
	std::cout << "\n" + std::string(FRAMEW * 2 + str.size(), '=') + "\n";
}
std::vector<Simcc::Token*>& Simcc::Lexer::token_stream()
{
	static std::vector<Simcc::Token*>ts;
	return ts;
}

void Simcc::Lexer::set_token_stream()
{
	if (index >= content.size())
		return;
	std::cout << "Index:" << index << std::endl;
	if (content[index] == ' ' || content[index] == '\t')
		index++;
	switch (content[index])
	{
	case '\n':
		index++;
		token_stream().push_back(new Token(Tag::ENDL));
		break;
	case '\"':
		read_string();
		break;
	case '1':case '2':case '3':case '4':case '5':case '6':case'7':case '8':case'9':case'0':case '-':
		read_number();
		break;
	default:
		read_word();
		break;
	}
	set_token_stream();
}
