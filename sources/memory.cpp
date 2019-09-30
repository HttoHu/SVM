#include "../includes/memory.hpp"

namespace SVM
{
	Memory memory;
	Memory const_mem;

	Memory::Memory() :mem(capacity){}

	size_t Memory::push()
	{
		check();
		return index++;
	}

	size_t Memory::push(size_t size)
	{
		check();
		return index++;
	}

	size_t Memory::new_obj()
	{
		if (free_pos_stack.empty())
			return heap_pos + (heap_index++);
		auto ret = free_pos_stack.top();
		free_pos_stack.pop();
		return ret;
	}

	void Memory::del_obj(size_t sz)
	{
		free_pos_stack.push(sz);
	}
	void Memory::check()
	{
		while (index + current > 0.5L * capacity)
		{
			extend();
			capacity *= 2;
			heap_pos *= 2;
		}
	}
	// stack_mem alloc
	void Memory::extend()
	{
		mem.resize(capacity * 2);
		capacity *= 2;
		heap_index *= 2;
	}
}