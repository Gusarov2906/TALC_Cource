#include <iostream>
#include <QtCore>
#include <stdlib.h>
#include <windows.h> 
#include "ConsoleColors.h"


class XmlStreamLint
{
public:
    Q_DECLARE_TR_FUNCTIONS(XmlStreamLint)
};

int main(int argc, char *argv[])
{
    HANDLE  hConsole;
    //int k;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // color your text in Windows console mode
    // colors are 0=black 1=blue 2=green and so on to 15=white  
    // colorattribute = foreground + background * 16
    // to get red text on yellow use 4 + 14*16 = 228
    // light red on yellow would be 12 + 14*16 = 236


    int k = static_cast<int>(ConsoleColors::DARK_BLUE_BACKGROUND) + static_cast<int>(ConsoleColors::LIGHT_CYAN_TEXT);
    SetConsoleTextAttribute(hConsole, k);
    std::cout << k
        << " I want to be nice today!" << std::endl;
    SetConsoleTextAttribute(hConsole, 15);


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

    while (!reader.atEnd())
    {
        reader.readNext();

        if (reader.error())
        {
            errorStream << XmlStreamLint::tr(
                "Error: %1 in file %2 at line %3, column %4.\n").arg(
                    reader.errorString(), inputFilePath,
                    QString::number(reader.lineNumber()),
                    QString::number(reader.columnNumber()));
            return ParseFailure;
        }
        else
        {

            qout << reader.name() << reader.text() << "(" << reader.tokenString() << ")";
            if (reader.attributes().size() > 0)
            {
                qout << reader.attributes()[0].name() << reader.attributes()[0].value();
            }
        }
    }
    return Success;
}

//for (k = 1; k < 255; k++)
//{
//    // pick the colorattribute k you want
//    SetConsoleTextAttribute(hConsole, k);
//    std::cout << k << " I want to be nice today!" << std::endl;
//}

//system("Color 1A");
//printf("\n");
//printf("\x1B[31mTexting\033[0m\t\t");
//printf("\x1B[32mTexting\033[0m\t\t");
//printf("\x1B[33mTexting\033[0m\t\t");
//printf("\x1B[34mTexting\033[0m\t\t");
//printf("\x1B[35mTexting\033[0m\n");

//printf("\x1B[36mTexting\033[0m\t\t");
//printf("\x1B[36mTexting\033[0m\t\t");
//printf("\x1B[36mTexting\033[0m\t\t");
//printf("\x1B[37mTexting\033[0m\t\t");
//printf("\x1B[93mTexting\033[0m\n");

//printf("\033[3;42;30mTexting\033[0m\t\t");
//printf("\033[3;43;30mTexting\033[0m\t\t");
//printf("\033[3;44;30mTexting\033[0m\t\t");
//printf("\033[3;104;30mTexting\033[0m\t\t");
//printf("\033[3;100;30mTexting\033[0m\n");

//printf("\033[3;47;35mTexting\t\t");
//printf("\033[2;47;35mTexting\033[0m\t\t");
//printf("\033[1;47;35mTexting\033[0m\t\t");
//printf("\t\t");
//printf("\n");