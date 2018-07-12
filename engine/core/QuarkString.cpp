#include "QuarkString.h"

qe::core::QuarkString::QuarkString()
{
}

qe::core::QuarkString::~QuarkString()
{
}

std::vector<std::string> qe::core::QuarkString::split(std::string str, const std::string & split_str)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += split_str;
    int size = str.size();

    for (int i = 0; i < size + 1; i++)
    {
        pos = str.find(split_str, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + split_str.size() - 1;
        }
    }
    return result;
}

std::string qe::core::QuarkString::get_path_prefixed(const std::string & path)
{
    auto name = get_file_name(path);
    if (name == "") return path;

    auto lists = split(path, name);
    int size = lists.size();
    if (size == 0 || size < 2) return nullptr;

    return lists[0];
}

std::string qe::core::QuarkString::get_file_name(const std::string & path)
{
    auto lists = split(path, "/");
    auto file_name = lists[lists.size() - 1];
    auto names = split(file_name, ".");

    if (names.size() == 0) return nullptr;

    return names[0];
}

std::string qe::core::QuarkString::get_file_format(const std::string & path)
{
    auto lists = split(path, "/");
    auto file_name = lists[lists.size() - 1];
    auto names = split(file_name, ".");

    int size = names.size();
    if (size == 0 || size < 2) return nullptr;

    return names[size-1];
}


