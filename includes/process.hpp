#pragma once
#include <iostream>
#include "lexer.hpp"
namespace SVM
{
	extern std::map<Id*, size_t> id_pos_table;
	void replace_tag_and_id();
	extern std::vector<size_t> literary_size;
}