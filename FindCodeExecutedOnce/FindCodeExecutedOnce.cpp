
#include "pch.h"

struct CodeCoverage
{
    wchar_t PC[6];
    int HitCount;
};
std::vector<CodeCoverage> coverages;
void MarkCodeCoverage(wchar_t pc0, wchar_t pc1, wchar_t pc2, wchar_t pc3, wchar_t pc4, wchar_t pc5)
{
    CodeCoverage* pCoverage = nullptr;
    for (size_t i = 0; i < coverages.size(); ++i)
    {
        if (coverages[i].PC[0] == pc0 &&
            coverages[i].PC[1] == pc1 &&
            coverages[i].PC[2] == pc2 &&
            coverages[i].PC[3] == pc3 &&
            coverages[i].PC[4] == pc4 &&
            coverages[i].PC[5] == pc5)
        {
            pCoverage = &coverages[i];
            break;
        }
    }
    if (!pCoverage)
    {
        CodeCoverage b{};
        b.PC[0] = pc0;
        b.PC[1] = pc1;
        b.PC[2] = pc2;
        b.PC[3] = pc3;
        b.PC[4] = pc4;
        b.PC[5] = pc5;
        b.HitCount = 0;
        coverages.push_back(b);
        pCoverage = &coverages[coverages.size() - 1];
    }

    pCoverage->HitCount = pCoverage->HitCount + 1;
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

        MarkCodeCoverage(pc0, pc1, pc2, pc3, pc4, pc5);
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

    for (size_t i = 0; i < coverages.size(); ++i)
    {
        if (coverages[i].HitCount == 1)
        {
            wprintf(L"Found code this executed once, at PC=%c%c%c%c%c%c.\n",
                coverages[i].PC[0], coverages[i].PC[1], coverages[i].PC[2], coverages[i].PC[3], coverages[i].PC[4], coverages[i].PC[5]);
        }
    }

    wprintf(L"Finished.\n");
    return 0;
}