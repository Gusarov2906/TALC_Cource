#pragma once
#include "Element.h"
#include "Block.h"
#include <qstring.h>

class Row;

class Column : public Element
{
public:
    Column(const int width, const VAlignType& vAlign = VAlignType::top, const HAlignType hAlign = HAlignType::left,
        const uint8_t textColor = 15, const uint8_t bgColor = 0, const int level = 0) :
        Element(nullptr, ElementType::COLUMN, 0, 0, 0, width, level),
        m_vAlign(vAlign), m_hAlign(hAlign), m_textColor(textColor),
        m_bgColor(bgColor), m_parentType(ElementType::NONE){}

    Column(Row* parent, const int width, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int level, const int childCount);
    Column(Block* parent, const int width, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int level, const int childCount);

    void addElement(Element* element) override;
    void display();
    void setText(QString text);
    QString getText() const;

protected:
    VAlignType m_vAlign;
    HAlignType m_hAlign;
    uint8_t m_textColor;
    uint8_t m_bgColor;
    ElementType m_parentType;
    QString m_text;
};

