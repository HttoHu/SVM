#pragma once
#include <string>
namespace SVM
{
	class Error
	{
	public:
		Error(const std::string &str) :ems(str) {}
		std::string what()
		{
            return ems + "\n";
		}
	private:
		std::string ems;
	};
}