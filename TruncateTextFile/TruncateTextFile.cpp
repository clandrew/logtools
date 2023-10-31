#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, wchar_t** argv)
{
    std::wstring srcPath1 = L"D:\\repos\\fnxide\\bin\\Debug\\log.orig.txt";
    std::wstring dstPath1 = L"D:\\repos\\fnxide\\bin\\Debug\\log.orig.trunc3.txt";

    std::wstring srcPath2 = L"D:\\repos\\fnxide\\bin\\Debug\\log.fixed.txt";
    std::wstring dstPath2 = L"D:\\repos\\fnxide\\bin\\Debug\\log.fixed.trunc3.txt";

    int startIndex = 145600 + 6300 + 100000;
    int length = 20000;

    {
        std::wifstream src(srcPath1);
        std::wofstream dst(dstPath1);

        //int startIndex = 145600 + 6300; // No earlier than here
        int endIndex = startIndex + length;


        int lineindex = 0;
        while (src.good())
        {
            lineindex++;

            std::wstring s;
            std::getline(src, s);
            if (lineindex >= startIndex)
            {
                dst << s << "\n";
            }
            if (lineindex > endIndex)
            {
                break;
            }

        }

        std::wcout << L"Finished writing " << length << L" lines to " << dstPath1 << ".\n";
    }

    {
        std::wifstream src(srcPath2);
        std::wofstream dst(dstPath2);

        //int startIndex = 145600 + 6300; // No earlier than here
        int endIndex = startIndex + length;


        int lineindex = 0;
        while (src.good())
        {
            lineindex++;

            std::wstring s;
            std::getline(src, s);
            if (lineindex >= startIndex)
            {
                dst << s << "\n";
            }
            if (lineindex > endIndex)
            {
                break;
            }

        }

        std::wcout << L"Finished writing " << length << L" lines to " << dstPath2 << ".\n";
    }
}
