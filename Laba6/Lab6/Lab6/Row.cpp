#include "Row.h"
#include <iostream>

Row::Row(const Column& parent, const VAlignType vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int height) : Element(ElementType::ROW)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent.getPosX();
    m_y = parent.getPosY();
    m_width = parent.getWidth();
    m_parentType = parent.getType();
}

Row::Row(const Block& parent, const VAlignType vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int height) : Element(ElementType::ROW)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent.getPosX();
    m_y = parent.getPosY();
    m_width = parent.getWidth();
    m_parentType = parent.getType();
}

void Row::addElement(const Element& element)
{
    switch (element.getType())
    {
    case ElementType::COLUMN:
        Element::addElement(element);
        m_posX = element.getWidth();
        break;
    case ElementType::BLOCK:
        Element::addElement(element);
        m_posX = element.getWidth();
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }

}

void Row::display()
{
}
