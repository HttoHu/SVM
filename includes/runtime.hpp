#pragma once
#include <vector>
#include<functional>
namespace SVM
{
	struct Param
	{
		size_t p1;
		size_t p2;
		size_t p3;
	};
	using Instruction=std::function<void(Param)>;

	extern std::vector<std::pair<Instruction, Param>> instruction_table;

	extern size_t instruction_index;

	void  run();
}