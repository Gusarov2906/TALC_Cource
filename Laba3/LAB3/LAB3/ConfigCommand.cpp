#include "ConfigCommand.h"
#include <iostream>
#include <sstream>
#include "StringHelper.h"

void ConfigCommand::setType(std::string inputVal, std::string pushdownVal)
{
    if (inputVal == " " && pushdownVal != "h0")
    {
        m_type = 1;
    }
    else if (inputVal == " " && pushdownVal == "h0")
    {
        m_type = 3;
    }
    else
    {
        m_type = 2;
    }
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

std::string ConfigCommand::getInputVal()
{
    return m_inputVal;
}

std::string ConfigCommand::getPushdownVal()
{
    return m_pushdownVal;
}

std::string ConfigCommand::getResult()
{
    return StringHelper::join(m_resultStates, "|");
}

int ConfigCommand::getType()
{
    return m_type;
}

std::vector<std::string> ConfigCommand::getResultStates()
{
    return m_resultStates;
}

std::string ConfigCommand::getManagmentUnitVal()
{
    return m_managmentUnitVal;
}

std::string ConfigCommand::toString()
{
    return "('" + m_managmentUnitVal + "', '"
        + m_inputVal + "', '"
        + m_pushdownVal + "') = ('"
        + m_managmentUnitVal + "', '"
        + getResult() + "')";
}
