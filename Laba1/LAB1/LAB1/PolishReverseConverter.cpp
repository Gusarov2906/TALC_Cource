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
        //if (lexemes.at(i).getType() == LexemeType::function)
        //{
        //    if (lexemes.at(i).getString() == "log(")
        //    {
        //        while (operations.size() > 0 && (operations.top().getType() == LexemeType::operation
        //            || operations.top().getType() == LexemeType::function))
        //        {
        //            if (operations.top().getPriority() >= lexemes.at(i).getPriority())
        //            {
        //                res.push_back(operations.top());
        //                operations.pop();
        //            }
        //            else
        //            {
        //                break;
        //            }
        //        }
        //        operations.push((lexemes.at(i)));
        //    }
        //}

        if (lexemes.at(i).getType() == LexemeType::operation)
        {
            while (operations.size() > 0 && (operations.top().getType() == LexemeType::operation))
                /*|| operations.top().getType() == LexemeType::function)*/
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

        if (lexemes.at(i).getType() == LexemeType::parenthesis || lexemes.at(i).getType() == LexemeType::function)
        {
            if (lexemes.at(i).getString() == "(" || lexemes.at(i).getString() == "log(")
            {
                operations.push(lexemes.at(i).getString());
            }
            else if (lexemes.at(i).getString() == ")")
            {
                while (operations.size() > 0 && operations.top().getType() == LexemeType::operation)
                {
                    res.push_back(operations.top());
                    operations.pop();
                }
                if (operations.top().getString() == "log(")
                {
                    res.push_back(Lexeme("log("));
                }
                if (operations.size() > 0)
                {
                    operations.pop();
                }
            }
        }
    }


    while (operations.size() != 0)
    {
        res.push_back(operations.top());
        operations.pop();

    }
    return res;
}
