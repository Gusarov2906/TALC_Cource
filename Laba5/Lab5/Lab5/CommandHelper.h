#pragma once
#include <vector>
#include <string>

enum class CommandType
{
    None = 0,
    For,
    If,
    Else,
    Print,
    Scan,
    Assign
};

class CommandHelper
{
public:
    static std::vector<std::string> commands;
    static CommandType getCommandType(std::string);
};

std::vector<std::string> CommandHelper::commands = { "for", "if", "else", "print", "scan", "assign" };

CommandType CommandHelper::getCommandType(std::string str)
{
    for (int i = 0; i < static_cast<int>(commands.size()); i++)
    {
        if (commands[i] == str)
        {
            return static_cast<CommandType>(i+1);
        }
    }
    return CommandType::None;
}