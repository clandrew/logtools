// DumbAndCheapDiff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, wchar_t** argv)
{
    std::wifstream f1(L"D:\\repos\\fnxide\\bin\\Debug\\log.orig.txt");
    std::wifstream f2(L"D:\\repos\\fnxide\\bin\\Debug\\log.fixed.txt");

    int startindex = 145250 + 500;

    int lineindex = 0;
    bool differenceFound = false;
    while (f1.good() && f2.good())
    {
        lineindex++;

        std::wstring s1, s2;

        std::getline(f1, s1);
        std::getline(f2, s2);

        if (lineindex > startindex)
        {
            if (s1 != s2)
            {
                std::wcout << L"Difference found at line " << lineindex << L".\n";
                std::wcout << L"File 1: " << s1 << L"\n";
                std::wcout << L"File 2: " << s2 << L"\n";
                differenceFound = true;
                break;
            }
        }
    }

    if (!differenceFound)
    {
        std::wcout << L"No differences found in " << lineindex << L" lines.\n";
    }
}
