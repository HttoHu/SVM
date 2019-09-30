#include <iostream>
#include <time.h>
#include <fstream>
#include "../includes/lexer.hpp"
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

int main()
{
	std::string file_content = get_file_content("test.svm");
	LexerTools::build_token_stream(file_content);
	token_stream.print();
	while (std::cin.get());
    return 0;
}