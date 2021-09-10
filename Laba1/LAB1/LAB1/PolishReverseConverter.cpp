#include "PolishReverseConverter.h"
#include <iostream>

PolishReverseConverter::PolishReverseConverter()
{
}

PolishReverseConverter::~PolishReverseConverter()
{
}

LexemeString PolishReverseConverter::convert(LexemeString lexemes)
{
    LexemeString res;
    for (int i = 0; i < lexemes.size(); i++)
    {
        if (lexemes.at(i).getType() == LexemeType::parenthesis)
        {
            if (lexemes.at(i).getString() == "(")
            {
                operations.push((lexemes.at(i)));
            }
            else if (lexemes.at(i).getString() == ")")
            {
                while (operations.top().getType() != LexemeType::parenthesis)
                {
                    res.push_back(operations.top());
                    operations.pop();
                }
                operations.pop();
            }
        }
        if (lexemes.at(i).getType() == LexemeType::operation)
        {
            while (operations.size() > 0 && operations.top().getType() == LexemeType::operation)
            {
                if (operations.top().getPriority() >= lexemes.at(i).getPriority())
                {
                    res.push_back(operations.top());
                    operations.pop();
                }
                else
                {
                    break;
                }
            }
            operations.push((lexemes.at(i)));
        }
        if (lexemes.at(i).getType() == LexemeType::decimal)
        {
            res.push_back((lexemes.at(i)));

        }
        operations.size();
    }
    while (operations.size() != 0)
    {
        res.push_back(operations.top());
        operations.pop();

    }
    return res;
}
