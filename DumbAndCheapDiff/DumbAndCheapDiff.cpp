// DumbAndCheapDiff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, wchar_t** argv)
{
    std::wifstream f1(L"D:\\repos\\logtools\\DumbAndCheapDiff\\JP.noirq.txt");
    std::wifstream f2(L"D:\\repos\\logtools\\DumbAndCheapDiff\\EN.noirq.txt");

    int startindex = 0;

    int lineindex = 0;
    bool differenceFound = false;
    bool lFound = false;
    bool rFound = false;
    while (f1.good() && f2.good())
    {
        lineindex++;

        std::wstring s1, s2;

        std::getline(f1, s1);
        std::getline(f2, s2);

        if (lineindex > startindex)
        {
            if (s1.find(L"$C0/1064") != -1)
            {
                std::wcout << L"Found search string in file JP.noirq.txt at " << lineindex << L".\n";
                lFound = true;
            }
            if (s2.find(L"$C0/1064") != -1)
            {
                std::wcout << L"Found search string in file EN.noirq.txt at " << lineindex << L".\n";
                rFound = true;
            }

            if (lFound && rFound)
            {
                std::wcout << L"Exiting.\n";
                break;
            }
        }
    }
}
