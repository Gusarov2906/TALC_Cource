#pragma once
#include <string>
#include <vector>

class ConfigCommand
{
public:
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::vector<std::string> resultStates, std::string managmentUnitVal = "S0");
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::string resultState, std::string managmentUnitVal = "S0");
    std::string getInputVal();
    std::string getPushdownVal();
    std::string getResult();
    int getType();
    std::vector<std::string> getResultStates();
    std::string getManagmentUnitVal();
    std::string toString();

private:
    void setType(std::string inputVal, std::string pushdownVal);

    std::string m_inputVal;
    std::string m_pushdownVal;
    std::string m_managmentUnitVal;
    int m_type;
    std::vector<std::string> m_resultStates;
};

