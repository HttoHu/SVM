#pragma once
#include"Token.hpp"
#include <unordered_map>
#include <list>
namespace Simcc
{
	class Id :public Token {
	public:
		static std::unordered_map<std::string, Id*> id_table;
		static Id* find_id(const std::string &str);
		Id(const std::string &v) :Token(Tag::TId),name(v){
			static int in=0;
			index=in++;
			id_table.insert({v,this});
		}
		std::string to_string()const override{
			return "<id: " + name + ">";
		}
	private:
		std::string name;
		size_t index;
	};
}
