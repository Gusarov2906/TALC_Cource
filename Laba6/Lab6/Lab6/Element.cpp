#include "Element.h"

void Element::addElement(Element* element)
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

int Element::getLevel() const
{
    return m_level;
}

void Element::setLevel(int num)
{
    m_level = num;
}

ElementType Element::getType() const
{
    return m_type;
}

Element* Element::getParent()
{
    return m_parent;
}
