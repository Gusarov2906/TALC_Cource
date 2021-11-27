#pragma once
#include "Element.h"
#include "Column.h"
#include "Block.h"

class Row : public Element
{
public:
    Row(const VAlignType vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int height) :
        Element(ElementType::ROW, 0, 0, 0, height),
        m_vAlign(vAlign), m_hAlign(hAlign), m_textColor(textColor),
        m_bgColor(bgColor), m_parentType(ElementType::NONE) {}

    Row(const Column& parent, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int height);
    Row(const Block& parent, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int height);

    void addElement(const Element& element) override;
    void display();

protected:
    VAlignType m_vAlign;
    HAlignType m_hAlign;
    uint8_t m_textColor;
    uint8_t m_bgColor;
    ElementType m_parentType;
};

