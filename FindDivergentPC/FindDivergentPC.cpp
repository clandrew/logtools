#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

int main()
{
    std::wifstream f1(L"D:\\repos\\fnxide\\bin\\Debug\\log.orig.txt");
    std::wifstream f2(L"D:\\repos\\fnxide\\bin\\Debug\\log.fixed.txt");

    std::set<std::wstring> pcs1;
    std::set<std::wstring> pcs2;

    int startindex = 145250 + 500;

    int lineindex = 0;
    bool differenceFound = false;
    while (f1.good() && f2.good())
    {
        lineindex++;

        std::wstring s1, s2;

        std::getline(f1, s1);
        std::getline(f2, s2);

        std::wstring pc1 = s1.substr(0, 6);
        std::wstring pc2 = s2.substr(0, 6);

        pcs1.insert(pc1);
        pcs2.insert(pc2);
    }

    std::wcout << L"Things which appeared in the first one, but not the second:\n";
    for (auto it = pcs1.begin(); it != pcs1.end(); ++it)
    {
        if (pcs2.find(*it) == pcs2.end())
        {
            std::wcout << (*it) << L"\n";
        }
    }

    std::wcout << L"Things which appeared in the second one, but not the first:\n";
    for (auto it = pcs2.begin(); it != pcs2.end(); ++it)
    {
        if (pcs1.find(*it) == pcs1.end())
        {
            std::wcout << (*it) << L"\n";
        }
    }
}