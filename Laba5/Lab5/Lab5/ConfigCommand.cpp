#include "ConfigCommand.h"
#include <iostream>
#include <sstream>
#include "StringHelper.h"

void ConfigCommand::setType(std::string inputVal, std::string pushdownVal)
{
    if (inputVal == "" && pushdownVal != "h0")
    {
        m_type = 1;
    }
    else if (inputVal == "" && pushdownVal == "h0")
    {
        m_type = 3;
    }
    else
    {
        m_type = 2;
    }
}

ConfigCommand::ConfigCommand()
{
    m_inputVal = "error";
    m_managmentUnitVal = "error";
    m_pushdownVal = "error";
    m_resultStates.push_back("error");
    m_type = 0;
}

ConfigCommand::ConfigCommand(std::string inputVal, std::string pushdownVal, std::vector<std::string> resultStates, std::string managmentUnitVal)
{
    m_inputVal = inputVal;
    m_managmentUnitVal = managmentUnitVal;
    m_pushdownVal = pushdownVal;
    m_resultStates = resultStates;
    setType(inputVal, pushdownVal);
}

ConfigCommand::ConfigCommand(std::string inputVal, std::string pushdownVal, std::string resultState, std::string managmentUnitVal)
{
    m_inputVal = inputVal;
    m_managmentUnitVal = managmentUnitVal;
    m_pushdownVal = pushdownVal;
    m_resultStates.push_back(resultState);
    setType(inputVal, pushdownVal);
}

std::string ConfigCommand::getInputVal() const
{
    return m_inputVal;
}

std::string ConfigCommand::getPushdownVal() const
{
    return m_pushdownVal;
}

std::string ConfigCommand::getResult() const
{
    return StringHelper::join(m_resultStates, "|");
}

int ConfigCommand::getType() const
{
    return m_type;
}

std::vector<std::string> ConfigCommand::getResultStates() const
{
    return m_resultStates;
}

std::string ConfigCommand::getManagmentUnitVal() const
{
    return m_managmentUnitVal;
}

std::string ConfigCommand::toString() const
{
    return "('" + m_managmentUnitVal + "', '"
        + m_inputVal + "', '"
        + m_pushdownVal + "') = ('"
        + m_managmentUnitVal + "', '"
        + getResult() + "')";
}
