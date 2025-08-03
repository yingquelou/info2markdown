#pragma once
#ifndef UTILS_H
#define UTILS_H 1
#include <string>
#include <vector>
#include <unordered_map>
namespace utils
{
    std::unordered_map<std::string, int> getNodeLevels(const std::vector<std::string> &lines);
    std::vector<std::string> collectNodeLines(std::istream &input);
    std::unordered_map<std::string, std::string> parseLine(const std::string &line);
} // namespace utils
#endif

