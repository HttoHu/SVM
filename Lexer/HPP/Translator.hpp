#pragma once
namespace Simcc
{
  class BinFile{
  public:
    static void output(const std::string &str);
    static std::string file_content;
    static size_t index;
  };
}
