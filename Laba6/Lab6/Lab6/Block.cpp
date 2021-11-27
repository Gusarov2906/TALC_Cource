#include "Block.h"
#include <iostream>

Block::Block(const int rowsCount, const int columnsCount, const Element& parent) : Element(ElementType::BLOCK)
{
    m_columnsCount = columnsCount;
    m_rowsCount = rowsCount;
    m_x = parent.getX();
    m_y = parent.getY();
    m_width = parent.getWidth();
    m_height = parent.getHeight();

    m_posX = 0;
    m_posY = 0;
}

void Block::addElement(const Element& element)
{
    switch (element.getType())
    {
    case ElementType::ROW:
        Element::addElement(element);
        m_posY = element.getHeight();
        break;
    case ElementType::COLUMN:
        Element::addElement(element);
        m_posX = element.getHeight();
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }
}

bool Block::validateCount()
{
    return false;
}
