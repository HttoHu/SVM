#include "..\includes\data.hpp"
namespace SVM
{
	Bin file_data;

	SVM::Bin::Bin()
	{
		data = new char[capacity];
		index = data;
	}
}

