#pragma once
#include "Element.h"
#include <vector>

class Block : public Element
{
public:
    Block(const int rowsCount, const int columnsCount) : Element(nullptr, ElementType::BLOCK, 0, 0, 80, 24, 0),
                                             m_rowsCount(rowsCount), m_columnsCount(columnsCount), m_columnsCounter(0), m_rowsCounter(0) {}

    Block(const int rowsCount, const int columnsCount, Element* parent);
    void addElement(Element* element) override;
    bool validateCount();
    void setRowsCount(int num);
    void setColumnsCount(int num);
    int getRowsCount();
    int getColumnsCount();
    int getRowsCounter();
    int getColumnsCounter();

protected:
    int m_rowsCounter;
    int m_rowsCount;
    int m_columnsCounter;
    int m_columnsCount;
};

