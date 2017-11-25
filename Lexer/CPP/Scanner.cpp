#include "../HPP/Scanner.hpp"
#include "../HPP/Literal.hpp"
#include "../HPP/Id.hpp"
#include <fstream>
using namespace Simcc::Lexer;
void read_string() {
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
		return;
	}
	if (content[index] != '.')
	{
		if (isN)
			intPart = -intPart;
		token_stream().push_back(new Simcc::LInt(static_cast<int32_t>(intPart)));
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
}
void read_word()
{
	std::string word;
	while ((isalnum(content[index]) || content[index] == '_') && index < content.size())
	{
		word += content[index++];
	}
	auto result = Simcc::Token::symbol_map.find(word);
	if (result == Simcc::Token::symbol_map.end())
	{
		Simcc::Id *tmp = Simcc::Id::find_id(word);
		if (tmp == nullptr)
		{
			tmp = new Simcc::Id(word);
		}
		token_stream().push_back(tmp);
		return;
	}
	token_stream().push_back(result->second);

}
void init(const std::string &str)
{
  using namespace std;
	ifstream ifs(str);
	content = std::string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
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
	if (content[index] == ' '&&content[index] == '\t')
		index++;
	switch (content[index])
	{
	case '\"':
		read_string();
		return;
	case '1':case '2':case '3':case '4':case '5':case '6':case'7':case '8':case'9':case'0':case '-':
		read_number();
		return;
	default:
		read_word();
		break;
	}
	set_token_stream();
}
