#include "Literal.hpp"
#include "Translator.hpp"
void Simcc::LInt::write_to_binary_file() const
{
	char *v = (char*)&content;
	for (int i = 0; i < sizeof(int); i++)
	{
		BinFile::file_content+= v[i];
		BinFile::index++;
	}
}

void Simcc::LLInt::write_to_binary_file() const
{
	char *v = (char*)&content;
	for (int i = 0; i < sizeof(int64_t); i++)
	{
		BinFile::file_content += v[i];
		BinFile::index++;
	}
}

void Simcc::LChar::write_to_binary_file() const
{
	char *v = (char*)&content;
	for (int i = 0; i < sizeof(char); i++)
	{
		BinFile::file_content += v[i];
		BinFile::index++;
	}
}

void Simcc::LDouble::write_to_binary_file() const
{
	char *v = (char*)&content;
	for (int i = 0; i < sizeof(double); i++)
	{
		BinFile::file_content += v[i];
		BinFile::index++;
	}
}

void Simcc::LString::write_to_binary_file() const
{
	for (int i = 0; i < content.size(); i++)
	{
		BinFile::file_content += content[i];
		BinFile::index++;
	}
	BinFile::file_content += '\0';
	BinFile::index++;
}
