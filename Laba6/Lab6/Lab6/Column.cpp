#include "Column.h"
#include "Row.h"
#include <iostream>
#include <QtCore/qstring.h>

Column::Column(Row* parent, const int width, const VAlignType vAlign,
    const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor,
    const int level, const int childCount) : Element(parent, ElementType::COLUMN, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = parent->getPosX();
    m_posY = parent->getPosY();

    m_width = width;
    m_x = parent->getPosX();
    m_y = parent->getPosY();
    m_height = parent->getHeight();
    m_parentType = parent->getType();

    m_childCount = childCount;

    m_parent = parent;
}

Column::Column(Block* parent, const int width, const VAlignType vAlign,
    const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor,
    const int level, const int childCount) : Element(parent, ElementType::COLUMN, level)
{
    m_vAlign = vAlign;
    m_hAlign = hAlign;
    m_textColor = textColor;
    m_bgColor = bgColor;

    m_posX = parent->getPosX();
    m_posY = parent->getPosY();

    m_width = width;
    m_x = parent->getPosX();
    m_y = parent->getPosY();
    m_height = parent->getHeight();
    m_parentType = parent->getType();

    m_childCount = childCount;

    m_parent = parent;
}

void Column::addElement(Element* element)
{
    switch (element->getType())
    {
    case ElementType::ROW:
        Element::addElement(element);
        m_posY += element->getHeight();
        if (m_childs.size() > m_childCount)
        {
            throw QString("Hierarchy error!");
        }
        //if (element->getParent()->getType() == ElementType::BLOCK)
        //{
        //    static_cast<Block*>(element->getParent())->setRowsCounter(static_cast<Block*>(m_parent->getParent())->getRowsCounter() + 1);
        //}
        //else
        //{
        //    throw QString("Hierarchy error!");
        //}
        break;
    case ElementType::BLOCK:
        Element::addElement(element);
        m_posY += element->getHeight();
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }
}

void Column::display()
{
}
