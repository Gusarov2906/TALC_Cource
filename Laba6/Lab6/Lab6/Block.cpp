#include "Block.h"
#include <iostream>

Block::Block(const int rowsCount, const int columnsCount, Element* parent) : Element(parent, ElementType::BLOCK)
{
    m_columnsCount = columnsCount;
    m_rowsCount = rowsCount;
    m_x = parent->getX();
    m_y = parent->getY();
    m_width = parent->getWidth();
    m_height = parent->getHeight();

    m_rowsCounter = 0;
    m_columnsCounter = 0;

    m_posX = 0;
    m_posY = 0;
}

void Block::addElement(Element* element)
{
    switch (element->getType())
    {
    case ElementType::ROW:
        Element::addElement(element);
        m_posY += element->getHeight();
        m_rowsCounter++;
        break;
    case ElementType::COLUMN:
        Element::addElement(element);
        m_posX += element->getWidth();
        m_columnsCounter++;
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

void Block::setRowsCount(int num)
{
    m_rowsCount = num;
}

void Block::setColumnsCount(int num)
{
    m_columnsCount = num;
}

int Block::getRowsCount()
{
    return m_rowsCount;
}

int Block::getColumnsCount()
{
    return m_columnsCount;
}

int Block::getRowsCounter()
{
    return m_rowsCounter;
}

int Block::getColumnsCounter()
{
    return m_columnsCounter;
}
