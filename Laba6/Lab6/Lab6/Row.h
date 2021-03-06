#pragma once
#include "Element.h"
#include "Column.h"
#include "Block.h"
#include <qstring.h>

class Row : public Element
{
public:
    Row(const VAlignType vAlign, const HAlignType hAlign, const uint8_t textColor, const uint8_t bgColor, const int height, const int level) :
        Element(nullptr, ElementType::ROW, 0, 0, 0, height, level),
        m_vAlign(vAlign), m_hAlign(hAlign), m_textColor(textColor),
        m_bgColor(bgColor), m_parentType(ElementType::NONE), m_text("") {}

    Row(Column* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int level, const int childCounter);
    Row(Block* parent, const int height, const VAlignType vAlign, const HAlignType hAlign,
        const uint8_t textColor, const uint8_t bgColor, const int level, const int childCounter);

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

