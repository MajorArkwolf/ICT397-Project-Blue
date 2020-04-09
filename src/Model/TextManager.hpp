#pragma once
#include <vector>
#include <string>
#include <map>

class TextManager {
  public:
    static auto InsertString(std::string key, std::string value) -> void;
    static auto GetString(std::string key) -> std::string;


  private:
    static auto TextMap() -> std::map<std::string, std::string> &;
};
