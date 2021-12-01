#include "Row.h"
#include <iostream>
#include <QtCore/qstring.h>
#include "qdebug.h"
#include <windows.h> 
#include "Console.h"

Row::Row(Column* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
    const uint8_t textColor, const uint8_t bgColor, const int level, const int childCount) 
    : Element(parent, ElementType::ROW, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent->getX() + parent->getPosX();
    m_y = parent->getY() + parent->getPosY();
    m_width = parent->getWidth();
    m_parentType = parent->getType();

    m_childCount = childCount;

    m_parent = parent;
}

Row::Row(Block* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
    const uint8_t textColor, const uint8_t bgColor, const int level, const int childCount) 
    : Element(parent, ElementType::ROW, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent->getX() + parent->getPosX();
    m_y = parent->getY() + parent->getPosY();
    m_width = parent->getWidth();
    m_parentType = parent->getType();

    m_childCount = childCount;

    m_parent = parent;
}

void Row::addElement(Element* element)
{
    switch (element->getType())
    {
    case ElementType::COLUMN:
        Element::addElement(element);
        m_posX += element->getWidth();
        if (m_childs.size() > m_childCount)
        {
            throw QString("Hierarchy error!");
        }
        if (m_width - m_posX < 0)
        {
            throw QString("Summary width is too big!");
        }
        break;
    case ElementType::BLOCK:
        Element::addElement(element);
        m_posX += element->getWidth();
        if (m_width - m_posX < 0)
        {
            throw QString("Summary width is too big!");
        }
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }

}

void Row::display()
{
    if (m_childs.size() == 0)
    {
        COORD position = { m_x,m_y };
        SetConsoleCursorPosition(Console::hConsole, position);
        int color = static_cast<int>(m_textColor) + static_cast<int>(m_bgColor) * 16;
        SetConsoleTextAttribute(Console::hConsole, color);
        for (int i = 0; i < m_height; i++)
        {
            QString res = "";
            for (int j = 0; j < m_width; j++)
            {
                res += " ";
            }
            COORD position = { m_x,m_y + i };
            SetConsoleCursorPosition(Console::hConsole, position);
            std::cout << res.toStdString();
        }
        if (m_text != "")
        {
            int x = 0;
            int y = 0;
            if (m_width < m_text.length())
            {
                throw QString("Text lenght bigger than width element!");
            }

            if (m_hAlign == HAlignType::left)
            {
                x = 0;
            }
            else if (m_hAlign == HAlignType::center)
            {
                x = (m_width - m_text.length()) / 2;
            }
            else if (m_hAlign == HAlignType::right)
            {
                x = m_width - m_text.length();
            }

            if (m_vAlign == VAlignType::bottom)
            {
                y = m_height - 1;
            }
            else if (m_vAlign == VAlignType::center)
            {
                y = m_height / 2;
            }
            else if (m_vAlign == VAlignType::top)
            {
                y = 0;
            }

            COORD position = { m_x + x, m_y + y };
            SetConsoleCursorPosition(Console::hConsole, position);
            std::cout << m_text.toStdString();
        }
    }
}

void Row::setText(QString text)
{
    m_text = text;
}

QString Row::getText() const
{
    return m_text;
}
