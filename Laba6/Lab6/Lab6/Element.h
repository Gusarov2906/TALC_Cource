#pragma once
#include <string>
#include <vector>

enum class VAlignType
{
    top,
    center,
    bottom
};

enum class HAlignType
{
    left,
    center,
    right
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
    Element(Element* parent, const ElementType& type, const int& x, const int& y, const int& width, const int& height, const int& level) : m_parent(parent), m_type(type), m_x(x), m_y(y),
                                                                     m_width(width), m_height(height),
                                                                     m_posX(0), m_posY(0), m_level(level){};
    Element(Element* parent, const ElementType& type, const int& level = 0) : m_parent(parent), m_type(type), m_x(0), m_y(0),
                                m_width(0), m_height(0),
                                m_posX(0), m_posY(0), m_level(level) {};

    virtual void addElement(Element* element);
    int getHeight() const;
    int getWidth() const;
    int getX() const;
    int getY() const;
    int getPosX() const;
    int getPosY() const;
    int getLevel() const;
    void setLevel(int num);
    ElementType getType() const;
    Element* getParent();

protected:
    ElementType m_type;

    int m_height;
    int m_width;
    int m_x;
    int m_y;

    int m_level;

    int m_posX;
    int m_posY;

    std::vector<Element*> m_childs;
    Element* m_parent;
};

