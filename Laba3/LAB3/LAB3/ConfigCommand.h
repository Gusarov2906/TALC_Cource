#pragma once
#include <string>

class ConfigCommand
{
public:
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::string result, std::string managmentUnitVal = "S0");
    std::string getInputVal();
    std::string getPushdownVal();
    std::string getResult();
    std::string getManagmentUnitVal();
    std::string toString();

private:
    std::string m_inputVal;
    std::string m_pushdownVal;
    std::string m_result;
    std::string m_managmentUnitVal;
};

