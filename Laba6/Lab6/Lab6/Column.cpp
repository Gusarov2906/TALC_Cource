#include "Column.h"
#include "Row.h"
#include <iostream>

Column::Column(const Row& parent, const VAlignType& vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int width) : Element(ElementType::COLUMN)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_width = width;
    m_x = parent.getPosX();
    m_y = parent.getPosY();
    m_height = parent.getHeight();
    m_parentType = parent.getType();
}

Column::Column(const Block& parent, const VAlignType vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int width) : Element(ElementType::COLUMN)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = 0;
    m_posY = 0;

    m_width = width;
    m_x = parent.getPosX();
    m_y = parent.getPosY();
    m_height = parent.getHeight();
    m_parentType = parent.getType();
}

void Column::addElement(const Element& element)
{
    switch (element.getType())
    {
    case ElementType::ROW:
        Element::addElement(element);
        m_posY = element.getHeight();
        break;
    case ElementType::BLOCK:
        Element::addElement(element);
        m_posY = element.getHeight();
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }
}

void Column::display()
{
}
