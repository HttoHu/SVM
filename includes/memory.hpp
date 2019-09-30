#pragma once
#include <iostream>
#include <stack>
#include <vector>
namespace SVM
{
	class Memory
	{
	public:
		Memory();
		size_t push();
		size_t push(size_t size);
		size_t new_obj();
		void del_obj(size_t sz);
		void *& at(size_t index) {
			return mem[index];
		}
	private:
		void check();
		void extend();
		size_t index = 0;
		size_t current = 0;
		size_t capacity = 2048;
		std::stack<size_t>free_pos_stack;
		size_t heap_index = 1024;
		size_t heap_pos = 0;
		std::vector<void*> mem;
	};
	extern Memory memory;
	extern Memory const_mem;
}