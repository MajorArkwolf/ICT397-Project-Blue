#pragma once
#include <string>
#include <map>

class TextManager {
  private:
    static auto TextMap() -> std::map<std::string, std::string> &;
    static auto InsertString(std::string key, std::string value) -> void;
    static auto GetString(std::string key) -> std::string;

    friend class ResourceManager;
};
