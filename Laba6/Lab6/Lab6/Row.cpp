#include "Row.h"
#include <iostream>

Row::Row(Column* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
    const uint8_t textColor, const uint8_t bgColor, const int level) : Element(parent, ElementType::ROW, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent->getPosX();
    m_y = parent->getPosY();
    m_width = parent->getWidth();
    m_parentType = parent->getType();

    m_parent = parent;
}

Row::Row(Block* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
    const uint8_t textColor, const uint8_t bgColor, const int level) : Element(parent, ElementType::ROW, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_height = height;
    m_x = parent->getPosX();
    m_y = parent->getPosY();
    m_width = parent->getWidth();
    m_parentType = parent->getType();

    m_parent = parent;
}

void Row::addElement(Element* element)
{
    switch (element->getType())
    {
    case ElementType::COLUMN:
        Element::addElement(element);
        m_posX += element->getWidth();
        break;
    case ElementType::BLOCK:
        Element::addElement(element);
        m_posX += element->getWidth();
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }

}

void Row::display()
{
}
