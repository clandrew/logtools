// FindSingleDivergentBranch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

struct Branch
{
    Branch() : PC(), Taken(0), NotTaken(0) {}
    wchar_t PC[6];
    int Taken;
    int NotTaken;
};
std::vector<Branch> branches;

struct CodeCoverage
{
    wchar_t PC[6];
    int HitCount;
};

void MarkBranch(
    wchar_t pc0, wchar_t pc1, wchar_t pc2, wchar_t pc3, wchar_t pc4, wchar_t pc5,
    wchar_t dest0, wchar_t dest1, wchar_t dest2, wchar_t dest3,
    wchar_t next0, wchar_t next1, wchar_t next2, wchar_t next3)
{
    Branch* pBranch = nullptr;
    for (size_t i = 0; i < branches.size(); ++i)
    {
        if (branches[i].PC[0] == pc0 && 
            branches[i].PC[1] == pc1 &&
            branches[i].PC[2] == pc2 &&
            branches[i].PC[3] == pc3 &&
            branches[i].PC[4] == pc4 &&
            branches[i].PC[5] == pc5)
        {
            pBranch = &branches[i];
            break;
        }
    }
    if (!pBranch)
    {
        Branch b{};
        b.PC[0] = pc0;
        b.PC[1] = pc1;
        b.PC[2] = pc2;
        b.PC[3] = pc3;
        b.PC[4] = pc4;
        b.PC[5] = pc5;
        b.Taken = 0;
        b.NotTaken = 0;
        branches.push_back(b);
        pBranch = &branches[branches.size() - 1];
    }

    if (dest0 == next0 &&
        dest1 == next1 &&
        dest2 == next2 &&
        dest3 == next3)
    {
        pBranch->Taken++;
    }
    else
    {
        pBranch->NotTaken++;
    }
}


void ParseFile(std::wstring const& inputPath)
{
    std::wifstream strm(inputPath);

    int lineindex = 0;
    while (strm.good())
    {
        lineindex++;

        std::wstring l;
        std::getline(strm, l);

        if (l.length() < 77)
            continue;

        wchar_t op0 = l[21];
        wchar_t op1 = l[22];
        wchar_t op2 = l[23];

        wchar_t pc0 = l[1];
        wchar_t pc1 = l[2];
        wchar_t pc2 = l[4];
        wchar_t pc3 = l[5];
        wchar_t pc4 = l[6];
        wchar_t pc5 = l[7];

        if ((op0 == 'B' && op1 == 'E' && op2 == 'Q') || 
            (op0 == 'B' && op1 == 'N' && op2 == 'E') ||
            (op0 == 'B' && op1 == 'C' && op2 == 'C') ||
            (op0 == 'B' && op1 == 'C' && op2 == 'S') ||
            (op0 == 'B' && op1 == 'M' && op2 == 'I') ||
            (op0 == 'B' && op1 == 'P' && op2 == 'L') ||
            (op0 == 'B' && op1 == 'V' && op2 == 'C') ||
            (op0 == 'B' && op1 == 'V' && op2 == 'S'))
        {
            wchar_t dest0 = l[34];
            wchar_t dest1 = l[35];
            wchar_t dest2 = l[36];
            wchar_t dest3 = l[37];

            // Now, peek at the next line
            std::wstring l2;
            std::getline(strm, l2);

            if (l2.length() < 77)
                continue;

            wchar_t next0 = l2[4];
            wchar_t next1 = l2[5];
            wchar_t next2 = l2[6];
            wchar_t next3 = l2[7];

            MarkBranch(pc0, pc1, pc2, pc3, pc4, pc5, dest0, dest1, dest2, dest3, next0, next1, next2, next3);
        }
    }
}

int main()
{
    std::string folder = "E:\\Emulation\\SNES\\snes9x1.51.ep10r2(debugger)\\Logs";

    std::string dirStringNarrow = folder;

    std::wstring dirName(dirStringNarrow.begin(), dirStringNarrow.end());

    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;


    std::wstring searchKey = dirName;
    searchKey.append(L"\\*");

    hFind = FindFirstFile(searchKey.c_str(), &ffd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("The input directory could not be opened.\n");
        return -1;
    }

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // Skip nested folders, and links like '.' and '..'
        }
        else
        {
            wprintf(L"Searching %s.\n", ffd.cFileName);

            // Open the file and append it
            std::wstring inputPath = dirName;
            inputPath.append(L"\\");
            inputPath.append(ffd.cFileName);

            ParseFile(inputPath);

        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

    for (size_t i = 0; i < branches.size(); ++i)
    {
        if ((branches[i].Taken == 1 && branches[i].NotTaken != 1) ||
            branches[i].Taken != 1 && branches[i].NotTaken == 1)
        {
            wprintf(L"Found branch that diverges once, at PC=%c%c%c%c%c%c, taken %i times, not taken %i times.\n", 
                branches[i].PC[0], branches[i].PC[1], branches[i].PC[2], branches[i].PC[3], branches[i].PC[4], branches[i].PC[5],
                branches[i].Taken, branches[i].NotTaken);
        }
    }

    wprintf(L"Finished.\n");
    return 0;
}