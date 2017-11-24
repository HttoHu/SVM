#pragma once
#include "Token.hpp"
namespace Simcc
{
  class Case:public Token
  {
  public:
    static std::unordered_map<std::string, Case*> case_table;
    static Case* find_case(const std::string &str);
    Case(const std::string &v,size_t pos):Token(Tag::TCase),content(v),position(pos){
      case_table.insert({content,this});
    }
    std::string to_string()const override{
        return "<Case: "+content+" Pos:"+std::to_string(position)+">";
    }
  private:
    const std::string &content;
    size_t position;
  }
}
