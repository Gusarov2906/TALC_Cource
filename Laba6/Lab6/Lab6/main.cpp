#include <iostream>
#include <QtCore>
#include <stdlib.h>
#include <windows.h> 
#include "ConsoleColors.h"
#include <stack>
#include "Element.h"
#include "Block.h"
#include "Column.h"
#include "Row.h"
#include "Console.h"

class XmlStreamLint
{
public:
    Q_DECLARE_TR_FUNCTIONS(XmlStreamLint)
};

void addNodeRoot(QXmlStreamReader& reader, std::map<int, Element*>& levelParents, Element*& nodeRoot)
{
    if (reader.name() == "block")
    {
        if (reader.attributes().size() > 0)
        {
            nodeRoot = new Block(0, 1);
            for (QXmlStreamAttribute atribute : reader.attributes())
            {
                QRegExp re("\\d+");
                if (re.exactMatch(atribute.value().toString()))
                {
                    //qDebug() << atribute.name();
                    if (atribute.name() == "rows")
                    {
                        static_cast<Block*>(nodeRoot)->setRowsCount(atribute.value().toInt());
                    }
                    else if (atribute.name() == "columns")
                    {
                        static_cast<Block*>(nodeRoot)->setColumnsCount(atribute.value().toInt());
                    }
                    else
                    {
                        throw (QString("Bad argument!"));
                    }
                }
                else
                {
                    throw (QString("Bad argument!"));
                }
            }
            std::pair<int, Element*> toAdd(0, nodeRoot);
            levelParents.insert(toAdd);
            //qDebug() << static_cast<Block*>(nodeRoot)->getColumnsCount() << static_cast<Block*>(nodeRoot)->getRowsCount();
        }
    }
}

void addBlock(QXmlStreamReader& reader, std::map<int, Element*>& levelParents, Element* parent)
{
    if (parent->getType() != ElementType::BLOCK)
    {
        if (reader.name() == "block")
        {
            int rowsCount = -1;
            int columnsCount = -1;
            if (reader.attributes().size() > 0)
            {
                for (QXmlStreamAttribute atribute : reader.attributes())
                {
                    QRegExp re("\\d+");
                    if (re.exactMatch(atribute.value().toString()))
                    {
                        //qDebug() << atribute.name();
                        if (atribute.name() == "rows")
                        {
                            rowsCount = atribute.value().toInt();
                        }
                        else if (atribute.name() == "columns")
                        {
                            columnsCount = atribute.value().toInt();
                        }
                        else
                        {
                            throw (QString("Bad argument!"));
                        }
                    }
                    else
                    {
                        throw (QString("Bad argument!"));
                    }
                }
                if ((rowsCount != -1 && columnsCount != -1) && (rowsCount >= 1 || columnsCount >= 1))
                {
                    Block* curElement = new Block(rowsCount, columnsCount, parent);
                    parent->addElement(curElement);
                    curElement->setLevel(parent->getLevel() + 1);
                    levelParents[curElement->getLevel()] = curElement;
                }
                else
                {
                    throw (QString("Doesn't required arguments existed!"));
                }
            }
            else
            {
                throw (QString("Doesn't required arguments existed!"));
            }
        }
    }
    else
    {
        throw (QString("Block nesting error!"));
    }
}

void addElement(ElementType elementType, QXmlStreamReader& reader,
    std::map<int, Element*>& levelParents, Element* parent)
{
    VAlignType vAlign = VAlignType::top;
    HAlignType hAlign = HAlignType::left;
    uint8_t textColor = 15;
    uint8_t bgColor = 0;
    int width = -1;
    int height = -1;
    ElementType parentType;
    QRegExp re("\\d+");
    bool isNeededWidth = false;
    bool isNeededHeight = false;

    if (elementType == ElementType::COLUMN)
    {
        isNeededWidth = true;
    }
    else if (elementType == ElementType::ROW)
    {
        isNeededHeight = true;
    }

    bool foundWidth = false;
    bool foundHeight = false;

    if (parent)
    {
        parentType = parent->getType();
        if (parentType == ElementType::BLOCK)
        {
            if (elementType == ElementType::COLUMN)
            {
                if (static_cast<Block*>(parent)->getColumnsCount() == (static_cast<Block*>(parent)->getChildsSize()+1))
                {
                    isNeededWidth = false;
                    width = parent->getWidth() - parent->getPosX();
                }
                else if (static_cast<Block*>(parent)->getColumnsCount() < (static_cast<Block*>(parent)->getChildsSize()+1))
                {
                    throw QString("Bad count columns!");
                }
            }
            else if (elementType == ElementType::ROW)
            {
                if (static_cast<Block*>(parent)->getRowsCount() == (static_cast<Block*>(parent)->getChildsSize()+1))
                {
                    isNeededHeight = false;
                    height = parent->getHeight() - parent->getPosY();
                }
                else if (static_cast<Block*>(parent)->getRowsCount() < (static_cast<Block*>(parent)->getChildsSize()+1))
                {
                    throw QString("Bad count rows!");
                }
            }
        }
        else if (parentType == ElementType::ROW || parentType == ElementType::COLUMN)
        {
            if (parent->getParent()->getType() == ElementType::BLOCK)
            {
                if (elementType == ElementType::COLUMN)
                {
                    if (static_cast<Row*>(parent)->getChildCount() == static_cast<Row*>(parent)->getChildsSize()+1)
                    {
                        isNeededWidth = false;
                        width = parent->getWidth() - parent->getPosX();
                    }
                }
                else if (elementType == ElementType::ROW)
                {
                    if (static_cast<Column*>(parent)->getChildCount() == static_cast<Column*>(parent)->getChildsSize()+1)
                    {
                        isNeededHeight = false;
                        height = parent->getHeight() - parent->getPosY();
                    }
                }
            }
        }
    }

    if (reader.attributes().size() > 0)
    {
        for (QXmlStreamAttribute atribute : reader.attributes())
        {
            if (atribute.name() == "valign")
            {
                QString val = atribute.value().toString();
                if (val == "top")
                {
                    vAlign = VAlignType::top;
                }
                else if (val == "center")
                {
                    vAlign = VAlignType::center;
                }
                else if (val == "bottom")
                {
                    vAlign = VAlignType::bottom;
                }
                else
                {
                    throw (QString("Bad argument!"));
                }
            }
            else if (atribute.name() == "halign")
            {
                QString val = atribute.value().toString();
                if (val == "left")
                {
                    hAlign = HAlignType::left;
                }
                else if (val == "center")
                {
                    hAlign = HAlignType::center;
                }
                else if (val == "right")
                {
                    hAlign = HAlignType::right;
                }
                else
                {
                    throw (QString("Bad argument!"));
                }
            }
            else if (re.exactMatch(atribute.value().toString()))
            {
                if (atribute.name() == "textcolor")
                {
                    textColor = atribute.value().toInt();
                    if (bgColor > 15 || bgColor < 0)
                    {
                        throw (QString("Bad text color number!"));
                    }
                }
                else if (atribute.name() == "bgcolor")
                {
                    bgColor = atribute.value().toInt();
                    if (bgColor > 15 || bgColor < 0)
                    {
                        throw (QString("Bad background color number!"));
                    }
                }
                else if (elementType == ElementType::COLUMN && atribute.name() == "width")
                {
                    foundWidth = true;
                    width = atribute.value().toInt();
                }
                else if (elementType == ElementType::ROW && atribute.name() == "height")
                {
                    foundHeight = true;
                    height = atribute.value().toInt();
                }
                else
                {
                    throw (QString("Bad argument!"));
                }
            }
            else
            {
                throw (QString("Bad argument!"));
            }
        }

        if (isNeededWidth)
        {
            if (!foundWidth && elementType == ElementType::COLUMN)
            {
                throw (QString("No width argument!"));
            }
        }
        else if (isNeededHeight)
        {
            if (!foundHeight && elementType == ElementType::ROW)
            {
                throw (QString("No height argument!"));
            }
        }

    }

    if (width == -1 && elementType == ElementType::COLUMN)
    {
        throw (QString("No width argument!"));
    }
    else if (height == -1 && elementType == ElementType::ROW)
    {
        throw (QString("No height argument!"));
    }

    Element* curElement = nullptr;
    if (parent != nullptr && parent->getType() == ElementType::BLOCK)
    {
        if (elementType == ElementType::COLUMN)
        {
            curElement = new Column(static_cast<Block*>(parent), width, vAlign,
                hAlign, textColor, bgColor, parent->getLevel() + 1, 
                static_cast<Block*>(parent)->getRowsCount());
        }
        else if (elementType == ElementType::ROW)
        {
            curElement = new Row(static_cast<Block*>(parent), height, vAlign,
                hAlign, textColor, bgColor, parent->getLevel() + 1,
                static_cast<Block*>(parent)->getColumnsCount());
        }
    }
    else if (parent != nullptr && parent->getType() == ElementType::ROW && elementType == ElementType::COLUMN)
    {
        curElement = new Column(static_cast<Row*>(parent), width, vAlign,
            hAlign, textColor, bgColor, parent->getLevel()+1, 0);
    }
    else if (parent != nullptr && parent->getType() == ElementType::COLUMN && elementType == ElementType::ROW)
    {
        curElement = new Row(static_cast<Column*>(parent), height, vAlign,
            hAlign, textColor, bgColor, parent->getLevel() + 1, 0);
    }
    if (curElement != nullptr)
    {
        parent->addElement(curElement);

        //std::pair<int, Element*> toAdd(curElement->getLevel(), curElement);
        levelParents[curElement->getLevel()] = curElement;
    }
}

int main(int argc, char *argv[])
{
    //int k;
    std::stack<QString> nestingStack;
    std::map<int, Element*> levelParents;
    Element* nodeRoot;
    Element* curElemnt;
    int level = 0;

    QString buf = "";

    Console::setFont();

    // color your text in Windows console mode
    // colors are 0=black 1=blue 2=green and so on to 15=white  
    // colorattribute = foreground + background * 16
    // to get red text on yellow use 4 + 14*16 = 228
    // light red on yellow would be 12 + 14*16 = 236


    //int k = static_cast<int>(ConsoleColors::DARK_BLUE_BACKGROUND) + static_cast<int>(ConsoleColors::LIGHT_CYAN_TEXT);
    //SetConsoleTextAttribute(Console::hConsole, k);
    //std::cout << k
    //    << " I want to be nice today!" << std::endl;
    //SetConsoleTextAttribute(Console::hConsole, 15);
    //COORD position = { 5,5 };
    //SetConsoleCursorPosition(Console::hConsole, position);


    enum ExitCode
    {
        Success,
        ParseFailure,
        ArgumentError,
        WriteError,
        FileFailure
    };

    QCoreApplication app(argc, argv);

    QTextStream errorStream(stderr);
    QTextStream qout(stdout);
    QString inputFilePath("test.xml");
    QFile inputFile("test.xml");

    if (!QFile::exists(inputFilePath))
    {
        errorStream << XmlStreamLint::tr(
            "File %1 does not exist.\n").arg(inputFilePath);
        return FileFailure;

    }
    else if (!inputFile.open(QIODevice::ReadOnly)) {
        errorStream << XmlStreamLint::tr(
            "Failed to open file %1.\n").arg(inputFilePath);
        return FileFailure;
    }

    QXmlStreamReader reader(&inputFile);

    int counter = 1;

    bool isFirstElem = true;

    while (!reader.atEnd())
    {
        reader.readNext();

        if (reader.error())
        {
            COORD position = { 0 ,25 };
            SetConsoleCursorPosition(Console::hConsole, position);
            int color = static_cast<int>(ConsoleColors::LIGHT_WHITE_TEXT) + static_cast<int>(ConsoleColors::BLACK) * 16;
            SetConsoleTextAttribute(Console::hConsole, color);
            errorStream << XmlStreamLint::tr(
                "Error: %1 in file %2 at line %3, column %4.\n").arg(
                    reader.errorString(), inputFilePath,
                    QString::number(reader.lineNumber()),
                    QString::number(reader.columnNumber()));
            return ParseFailure;
        }
        else
        {
            try
            {
                if (isFirstElem && reader.name() == "block")
                {
                    level = 0;
                    nestingStack.push(reader.tokenString() + "_" + reader.name());
                    addNodeRoot(reader, levelParents, nodeRoot);
                    isFirstElem = false;
                }
                else if (reader.name() == "column" && reader.tokenString() == "StartElement")
                {
                    nestingStack.push(reader.tokenString() + "_" + reader.name());
                    addElement(ElementType::COLUMN ,reader, levelParents, levelParents[level]);
                    level++;
                }
                else if (reader.name() == "row" && reader.tokenString() == "StartElement")
                {
                    nestingStack.push(reader.tokenString() + "_" + reader.name());
                    addElement(ElementType::ROW, reader, levelParents, levelParents[level]);
                    level++;
                }
                else if (reader.name() == "block" && reader.tokenString() == "StartElement")
                {
                    nestingStack.push(reader.tokenString() + "_" + reader.name());
                    addBlock(reader, levelParents, levelParents[level]);
                    level++;
                }
                else if (reader.tokenString() == "EndElement")
                {
                    if (buf != "")
                    {
                        if (levelParents[level]->getChildsSize() == 0)
                        {
                            if (levelParents[level]->getType() == ElementType::COLUMN)
                            {
                                static_cast<Column*>(levelParents[level])->setText(buf);
                                //qDebug() << static_cast<Column*>(levelParents[level])->getText();
                            }
                            else if (levelParents[level]->getType() == ElementType::ROW)
                            {
                                static_cast<Row*>(levelParents[level])->setText(buf);
                                //qDebug() << static_cast<Row*>(levelParents[level])->getText();
                            }
                            buf = "";
                        }
                        else
                        {
                            throw (QString("The position of the text is incorrect!"));
                        }
                    }
                    if (levelParents[level]->getChildsSize() == 0)
                    {
                        if (levelParents[level]->getType() == ElementType::COLUMN)
                        {
                            static_cast<Column*>(levelParents[level])->display();
                        }
                        else if (levelParents[level]->getType() == ElementType::ROW)
                        {
                            static_cast<Row*>(levelParents[level])->display();
                        }
                    }
                    nestingStack.pop();
                    level--;
                }
                else if(reader.name() == "")
                {
                    buf = "";
                    QRegExp re("[^\n\t\r]+");
                    //qDebug() << "!" << reader.text().toString();
                    if (re.exactMatch(reader.text().toString()))
                    {
                        buf = reader.text().toString();
                    }
                }

            }
            catch (QString& error)
            {
                COORD position = { 0 ,25 };
                SetConsoleCursorPosition(Console::hConsole, position);
                int color = static_cast<int>(ConsoleColors::LIGHT_WHITE_TEXT) + static_cast<int>(ConsoleColors::BLACK) * 16;
                SetConsoleTextAttribute(Console::hConsole, color);
                errorStream << XmlStreamLint::tr(
                    "Error: %1 in file %2 at line %3, column %4.\n").arg(
                        error, inputFilePath,
                        QString::number(reader.lineNumber()),
                        QString::number(reader.columnNumber()));
                return ParseFailure;
            }


            //qout << reader.name() << reader.text() << "(" << reader.tokenString() << ")";
            //if (reader.attributes().size() > 0)
            //{
            //    qout << reader.attributes()[0].name() << reader.attributes()[0].value();
            //}
        }
    }
    COORD position = { 0 ,25 };
    SetConsoleCursorPosition(Console::hConsole, position);
    int color = static_cast<int>(ConsoleColors::LIGHT_WHITE_TEXT) + static_cast<int>(ConsoleColors::BLACK) * 16;
    SetConsoleTextAttribute(Console::hConsole, color);
    return Success;
}
