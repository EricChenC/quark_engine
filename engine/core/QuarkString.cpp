#include "QuarkString.h"

qe::core::QuarkString::QuarkString()
{
}

qe::core::QuarkString::~QuarkString()
{
}

auto qe::core::QuarkString::Split(const std::string& str, const std::string & delimiter) -> std::vector<std::string>
{
    std::string strings = str;
    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = strings.find(delimiter)) != std::string::npos) {
        token = strings.substr(0, pos);
        result.push_back(std::move(token));
        strings.erase(0, pos + delimiter.length());
    }

    result.push_back(std::move(strings));

    return result;
}

auto qe::core::QuarkString::PathPrefixed(const std::string & path) -> std::string
{
    auto name = FileName(path);
    if (name == "") return path;

    auto lists = Split(path, name);
    int size = lists.size();
    if (size == 0 || size < 2) return nullptr;

    return lists[0];
}

auto qe::core::QuarkString::FileName(const std::string & path) -> std::string
{
    auto lists = Split(path, "/");
    auto file_name = lists[lists.size() - 1];
    auto names = Split(file_name, ".");

    if (names.size() == 0) return nullptr;

    return names[0];
}

std::string qe::core::QuarkString::FileFormat(const std::string & path)
{
    auto lists = Split(path, "/");
    auto file_name = lists[lists.size() - 1];
    auto names = Split(file_name, ".");

    int size = names.size();
    if (size == 0 || size < 2) return nullptr;

    return names[size-1];
}


