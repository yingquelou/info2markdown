#include "utils.h"
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;
using namespace utils;

struct Node {
    string name;
    string parent;
    vector<string> children;
    int level = 0;
};

unordered_map<string, string> utils::parseLine(const string& line) {
    unordered_map<string, string> kv;
    stringstream ss(line);
    string part;
    while (getline(ss, part, ',')) {
        size_t pos = part.find(':');
        if (pos != string::npos) {
            string key = part.substr(0, pos);
            string val = part.substr(pos + 1);
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            val.erase(0, val.find_first_not_of(" \t"));
            val.erase(val.find_last_not_of(" \t") + 1);
            kv[key] = val;
        }
    }
    return kv;
}
std::unordered_map<std::string, int> utils::getNodeLevels(const std::vector<std::string> &lines) {
    unordered_map<string, Node> nodes;

    // 解析节点
    for (const auto& line : lines) {
        auto kv = parseLine(line);
        if (kv.find("Node") == kv.end()) continue;
        string nodeName = kv["Node"];
        string parentName = kv.count("Up") ? kv["Up"] : "";

        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node{nodeName, parentName, {}, 0};
        } else {
            nodes[nodeName].parent = parentName;
        }
    }

    // 建立父子关系
    for (auto& [name, node] : nodes) {
        if (!node.parent.empty() && nodes.find(node.parent) != nodes.end()) {
            nodes[node.parent].children.push_back(name);
        }
    }

    // 计算层级
    queue<string> q;
    for (auto& [name, node] : nodes) {
        if (node.parent.empty() || nodes.find(node.parent) == nodes.end()) {
            node.level = 1;
            q.push(name);
        }
    }

    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        int currLevel = nodes[curr].level;
        for (const auto& childName : nodes[curr].children) {
            nodes[childName].level = currLevel + 1;
            q.push(childName);
        }
    }

    // 准备返回结果
    unordered_map<string, int> result;
    for (const auto& [name, node] : nodes) {
        result[name] = node.level;
    }
    return result;
}
// 判断一行是否包含 "Node:" 键值对
bool containsNodeKey(const std::string &line)
{
    return line.find("Node:") != std::string::npos;
}

// 从输入流中收集符合条件的行
std::vector<std::string> utils::collectNodeLines(std::istream &input)
{
    std::vector<std::string> result;
    std::string line;
    while (std::getline(input, line))
    {
        if (containsNodeKey(line))
        {
            result.push_back(line);
        }
    }
    return result;
}