#include "Element.h"

void Element::addElement(const Element& element)
{
    m_childs.push_back(element);
}

int Element::getHeight() const
{
    return m_height;
}

int Element::getWidth() const
{
    return m_width;
}

int Element::getX() const
{
    return m_x;
}

int Element::getY() const
{
    return m_y;
}

int Element::getPosX() const
{
    return m_posX;
}

int Element::getPosY() const
{
    return m_posY;
}

ElementType Element::getType() const
{
    return m_type;
}
