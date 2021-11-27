#pragma once
#include "Element.h"
#include "Block.h"

class Row;

class Column : public Element
{
public:
    Column(const VAlignType vAlign, const HAlignType hAlign, 
        const uint8_t textColor, const uint8_t bgColor, const int width) :
        Element(ElementType::COLUMN, 0, 0, 0, width),
        m_vAlign(vAlign), m_hAlign(hAlign), m_textColor(textColor),
        m_bgColor(bgColor), m_parentType(ElementType::NONE){}

    Column(const Row& parent, const VAlignType& vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int width);
    Column(const Block& parent, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int width);

    void addElement(const Element& element) override;
    void display();

protected:
    VAlignType m_vAlign;
    HAlignType m_hAlign;
    uint8_t m_textColor;
    uint8_t m_bgColor;
    ElementType m_parentType;
};

