#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

// 判断一行是否包含 "Node:" 键值对
bool containsNodeKey(const std::string &line)
{
    return line.find("Node:") != std::string::npos;
}

// 从输入流中收集符合条件的行
std::vector<std::string> collectNodeLines(std::istream &input)
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

// 测试示例
int main(int argc, const char *argv[])
{

    // 模拟输入流，这里用istringstream代替文件或标准输入
    for (size_t i = 0; argv[i]; i++)
    {

        std::ifstream ifs(argv[i]);
        if (ifs)
        {
            std::vector<std::string> nodeLines = collectNodeLines(ifs);

            for (const auto &line : nodeLines)
            {
                std::cout << line << std::endl;
            }
        }
    }

    return 0;
}
