#include <iostream>
#include <string>
#include <fstream>

void PrintUsage()
{
    std::cout << "Usage: StripIRQFromCPULog.exe [inputLog] [outputLog]\n";
    std::cout << "Example:\n";
    std::cout << "    StripIRQFromCPULog.exe input.log output.log\n";
}

int main(int argc, char** argv)
{
#if _DEBUG
    std::string logPath = "D:\\repos\\nhl94e\\Decompress2\\Tests\\asw0.log";
    std::string outputPath = "D:\\repos\\nhl94e\\Decompress2\\Tests\\asw0.noirq.log";
#else
    if (argc != 3)
    {
        PrintUsage();
        return -1;
    }
    std::string logPath = argv[1];
    std::string outputPath = argv[2];
#endif
    
    std::ifstream instrm(logPath);
    std::ofstream outstrm(outputPath);

    std::string line;
    int outputLevel = 0;

    while (std::getline(instrm, line))
    {
        if (line == "*** IRQ")
        {
            outputLevel--;
        }

        if (line == "*** NMI")
        {
            outputLevel--;
        }

        if (outputLevel == 0)
        {
            outstrm << line << "\n";
        }
        
        if (line.length() >= 24 && line[21] == 'R' && line[22] == 'T' && line[23] == 'I')
        {
            outputLevel++;
        }
    }
}