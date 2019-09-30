#include <iostream>
#include <time.h>
#include <fstream>
#include "../includes/lexer.hpp"
#include "../includes/data.hpp"
using namespace SVM;
std::string get_file_content(const std::string& filename)
{
	using namespace std;
	ifstream ifs(filename);
	if (!ifs)
	{
		throw std::runtime_error("invalid file");
	}
	std::string file_content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	return file_content;
}
void fun()
{
	std::string file_content = get_file_content("test.svm");
	SVM::LexerTools::build_token_stream(file_content);
	SVM::token_stream.print();
}
int main()
{
	try
	{ 
		fun();
	}
	catch (SVM::Error& e)
	{
		std::cout << e.what();
	}
	while (std::cin.get());
    return 0;
}