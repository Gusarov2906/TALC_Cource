#pragma once
#include <string>
#include <vector>

class ConfigCommand
{
public:
    ConfigCommand();
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::vector<std::string> resultStates, std::string managmentUnitVal = "S0");
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::string resultState, std::string managmentUnitVal = "S0");
    std::string getInputVal() const;
    std::string getPushdownVal() const;
    std::string getResult() const;
    int getType() const;
    std::vector<std::string> getResultStates() const;
    std::string getManagmentUnitVal() const;
    std::string toString() const;

private:
    void setType(std::string inputVal, std::string pushdownVal);

    std::string m_inputVal;
    std::string m_pushdownVal;
    std::string m_managmentUnitVal;
    int m_type;
    std::vector<std::string> m_resultStates;
};

