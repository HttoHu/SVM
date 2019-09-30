#pragma once
#include <iostream>
#include <string.h>
using ins_type=char;
using addr_type=int32_t;
using length_record=int16_t;
namespace SVM
{
	class Bin
	{
	public:
		Bin();
		template<typename T>
		void write(T data)
		{
			memcpy(index, &data, sizeof(T));
			index += sizeof(T);
		}
		template <typename T>
		T read(size_t pos)
		{
			return *(T*)(data + pos);
		}
	private:
		char* data;
		size_t capacity = 1024;
		char* index;
	};
	extern Bin file_data;
}