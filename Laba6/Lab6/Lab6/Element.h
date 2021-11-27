#pragma once
#include <string>
#include <vector>

enum class VAlignType
{
    TOP,
    CENTER,
    BOTTOM
};

enum class HAlignType
{
    LEFT,
    CENTER,
    RIGHT
};

enum class ElementType
{
    NONE,
    BLOCK,
    ROW,
    COLUMN
};

class Element
{
public:
    Element(const ElementType& type, const int& x, const int& y, const int& width, const int& height) : m_type(type), m_x(x), m_y(y),
                                                                     m_width(width), m_height(height),
                                                                     m_posX(0), m_posY(0){};
    Element(const ElementType& type) : m_type(type), m_x(0), m_y(0),
                                m_width(0), m_height(0),
                                m_posX(0), m_posY(0) {};

    virtual void addElement(const Element& element);
    int getHeight() const;
    int getWidth() const;
    int getX() const;
    int getY() const;
    int getPosX() const;
    int getPosY() const;
    ElementType getType() const;

protected:
    ElementType m_type;

    int m_height;
    int m_width;
    int m_x;
    int m_y;

    int m_posX;
    int m_posY;

    std::vector<Element> m_childs;
};

