#include "TextManager.hpp"

#include <map>

auto TextManager::InsertString(std::string key, std::string value) -> void {

    if (TextMap().find(key) == TextMap().end()) { // file not loaded yet
        TextManager::TextMap().insert(std::make_pair(key, value));
    } else {
        return;
    }
}

auto TextManager::GetString(std::string key) -> std::string {
    if (TextMap().find(key) != TextMap().end()) {
        return TextMap().at(key);
    }
    return std::string(" ");
}

auto TextManager::TextMap() -> std::map<std::string, std::string> & {
    static std::map<std::string, std::string> m = {};
    return m;
}
