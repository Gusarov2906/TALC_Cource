#pragma once
#include "Element.h"
#include <vector>

class Block : public Element
{
public:
    Block(const int rowsCount, const int columnsCount) : Element(ElementType::BLOCK, 0, 0, 80, 24),
                                             m_rowsCount(rowsCount), m_columnsCount(columnsCount) {}

    Block(const int rowsCount, const int columnsCount, const Element& parent);
    void addElement(const Element& element) override;
    bool validateCount();

protected:
    int m_rowsCount;
    int m_columnsCount;
};

