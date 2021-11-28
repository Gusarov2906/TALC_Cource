#include "Block.h"
#include <iostream>
#include <QtCore/qstring.h>

Block::Block(const int rowsCount, const int columnsCount, Element* parent) : Element(parent, ElementType::BLOCK)
{
    m_columnsCount = columnsCount;
    m_rowsCount = rowsCount;
    m_x = parent->getX();
    m_y = parent->getY();
    m_width = parent->getWidth();
    m_height = parent->getHeight();

    m_posX = 0;
    m_posY = 0;
}

void Block::addElement(Element* element)
{
    switch (element->getType())
    {
    case ElementType::ROW:
        if (m_childs.size() > 0)
        {
            if (m_childs[0]->getType() == ElementType::ROW)
            {
                Element::addElement(element);
                m_posY += element->getHeight();
            }
            else
            {
                throw QString("Unexpected element type!");
            }
        }
        else
        {
            m_childCount = m_rowsCount;
            Element::addElement(element);
            m_posY += element->getHeight();
        }

        break;
    case ElementType::COLUMN:
        if (m_childs.size() > 0)
        {
            if (m_childs[0]->getType() == ElementType::COLUMN)
            {
                Element::addElement(element);
                m_posX += element->getWidth();
            }
            else
            {
                throw QString("Unexpected element type!");
            }
        }
        else
        {
            m_childCount = m_columnsCount;
            Element::addElement(element);
            m_posX += element->getWidth();
        }
        break;
    default:
        std::cout << "Error in addElement with type";
        break;
    }
    if (m_childs.size() > m_childCount)
    {
        throw QString("Hierarchy error!");
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
