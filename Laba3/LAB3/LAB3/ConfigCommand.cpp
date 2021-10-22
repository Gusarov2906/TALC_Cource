#include "ConfigCommand.h"
#include <iostream>

ConfigCommand::ConfigCommand(std::string inputVal, std::string pushdownVal, std::string result, std::string managmentUnitVal)
{
    m_inputVal = inputVal;
    m_managmentUnitVal = managmentUnitVal;
    m_pushdownVal = pushdownVal;
    m_result = result;
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
    return m_result;
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
        + m_result + "')";
}
