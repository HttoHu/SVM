#include "../includes/runtime.hpp"
namespace SVM
{
	std::vector<std::pair<Instruction, Param>> instruction_table;
	size_t instruction_index;
	void run()
	{
		for (; instruction_index < instruction_table.size(); instruction_index++)
		{
			instruction_table[instruction_index].first(instruction_table[instruction_index].second);
		}
	}
}