#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

void initSymbolList(std::map<std::string, int>& addressMap)
{
    addressMap.insert(std::pair<int, std::string>(0, "R0"));
    addressMap.insert(std::pair<int, std::string>(1, "R1"));
    addressMap.insert(std::pair<int, std::string>(2, "R2"));
    addressMap.insert(std::pair<int, std::string>(3, "R3"));
    addressMap.insert(std::pair<int, std::string>(4, "R4"));
    addressMap.insert(std::pair<int, std::string>(5, "R5"));
    addressMap.insert(std::pair<int, std::string>(6, "R6"));
    addressMap.insert(std::pair<int, std::string>(7, "R7"));
    addressMap.insert(std::pair<int, std::string>(8, "R8"));
    addressMap.insert(std::pair<int, std::string>(9, "R9"));
    addressMap.insert(std::pair<int, std::string>(10, "R10"));
    addressMap.insert(std::pair<int, std::string>(11, "R11"));
    addressMap.insert(std::pair<int, std::string>(12, "R12"));
    addressMap.insert(std::pair<int, std::string>(13, "R13"));
    addressMap.insert(std::pair<int, std::string>(14, "R14"));
    addressMap.insert(std::pair<int, std::string>(15, "R15"));
    addressMap.insert_or_assign(0, "SP");
    addressMap.insert_or_assign(1, "LCL");
    addressMap.insert_or_assign(2, "ARG");
    addressMap.insert_or_assign(3, "THIS");
    addressMap.insert_or_assign(4, "THAT");
    addressMap.insert(std::pair<int, std::string>(16384, "SCREEN"));
    addressMap.insert(std::pair<int, std::string>(24576, "KBD"));
}

void removeWhitespace(std::string& line)
{
    std::regex whiteSpace{ "[ ]+" };
    std::smatch match;

    std::regex_search(line, match, whiteSpace);
    auto pos = match.position();
    auto length = match.length();
    line.erase(pos, length);
}

void removeComments(std::string& line)
{
    std::regex comment{ "[/]+.*" };
    std::smatch match;

    std::regex_search(line, match, comment);
    auto pos = match.position();
    auto length = match.length();
    line.erase(pos, length);
}

void firstPass(std::vector<std::string> &asmLines, std::map<std::string, int> &addressMap)
{
    std::regex parseLabels{ "[A-Za-z0-9]*" };
    std::regex whiteSpaceLine{ "\\s*" };
    
    std::string label;
    int lineCount{ 0 };

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        removeWhitespace(asmLines[line]);
    }

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        removeComments(asmLines[line]);
    }

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        if (std::regex_match(asmLines[line], whiteSpaceLine))
        {
            asmLines.erase(asmLines.begin() + line);
        }
    }

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        if (std::regex_match(asmLines[line], whiteSpaceLine))
        {
            asmLines.erase(asmLines.begin() + line);
        }
    }

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        if (std::regex_match(asmLines[line], whiteSpaceLine))
        {
            asmLines.erase(asmLines.begin() + line);
        }
    }

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        if (asmLines[line].find('(') != std::string::npos)
        {
            asmLines[line].erase(0, 1);
            asmLines[line].erase(asmLines[line].end() - 1, asmLines[line].end());
            label = asmLines[line];
            addressMap.insert(std::pair<std::string, int>(label, lineCount));
            --lineCount;
        }
        ++lineCount;
    }
}

std::string convertBinary(std::string &line)
{
    std::string newBinary;
    std::stringstream newLine{ line };
    int binary;

    newLine >> binary;

    newBinary.append("0");

    if (binary / 16384 == 1)
    {
        newBinary.append("1");
        binary -= 16384;
    }
    else
        newBinary.append("0");
    
    if (binary / 8192 == 1)
    {
        newBinary.append("1");
        binary -= 8192;
    }
    else
        newBinary.append("0");

    if (binary / 4096 == 1)
    {
        newBinary.append("1");
        binary -= 4096;
    }
    else
        newBinary.append("0");

    if (binary / 2048 == 1)
    {
        newBinary.append("1");
        binary -= 2048;
    }
    else
        newBinary.append("0");

    if (binary / 1024 == 1)
    {
        newBinary.append("1");
        binary -= 1024;
    }
    else
        newBinary.append("0");

    if (binary / 512 == 1)
    {
        newBinary.append("1");
        binary -= 512;
    }
    else
        newBinary.append("0");

    if (binary / 256 == 1)
    {
        newBinary.append("1");
        binary -= 256;
    }
    else
        newBinary.append("0");

    if (binary / 128 == 1)
    {
        newBinary.append("1");
        binary -= 128;
    }
    else
        newBinary.append("0");

    if (binary / 64 == 1)
    {
        newBinary.append("1");
        binary -= 64;
    }
    else
        newBinary.append("0");

    if (binary / 32 == 1)
    {
        newBinary.append("1");
        binary - 32;
    }
    else
        newBinary.append("0");

    if (binary / 16 == 1)
    {
        newBinary.append("1");
        binary -= 16;
    }
    else
        newBinary.append("0");

    if (binary / 8 == 1)
    {
        newBinary.append("1");
        binary -= 8;
    }
    else
        newBinary.append("0");

    if (binary / 4 == 1)
    {
        newBinary.append("1");
        binary -= 4;
    }
    else
        newBinary.append("0");

    if (binary / 2 == 1)
    {
        newBinary.append("1");
        binary -= 2;
    }
    else
        newBinary.append("0");

    if (binary / 1 == 1)
    {
        newBinary.append("1");
        binary -= 1;
    }
    else
        newBinary.append("0");

    return newBinary;
}

std::string Ctable(std::string&line)
{
    std::cout << line << '\n';
    std::string newLine;
    newLine.append("111");

    std::regex dest{ ".*=" };
    std::regex jump{ ";.+" };
    
    std::smatch destMatch;
    std::smatch jumpMatch;

    std::string substringDest;
    std::string substringJump;
    std::string substringAorD;

    std::regex_search(line, destMatch, dest);
    std::regex_search(line, jumpMatch, jump);

    auto posD = destMatch.position();
    auto lengthD = destMatch.length();

    substringDest = line.substr(posD, lengthD - 1);

    auto posJ = jumpMatch.position();
    auto lengthJ = jumpMatch.length();

    substringJump = line.substr(posJ, lengthJ);

    if (!substringJump.empty())
        substringAorD = line.substr(posD + lengthD - 1, posJ);
    else
        substringAorD = line.substr(posD + lengthD, line.length());

    if (substringAorD == "0")
        newLine.append("0101010");
    if (substringAorD == "1")
        newLine.append("0111111");
    if (substringAorD == "-1")
        newLine.append("0111010");
    if (substringAorD == "D")
        newLine.append("0001100");
    if (substringAorD == "A")
        newLine.append("0110000");
    if (substringAorD == "!D")
        newLine.append("0001101");
    if (substringAorD == "!A")
        newLine.append("0110001");
    if (substringAorD == "-D")
        newLine.append("0001111");
    if (substringAorD == "-A")
        newLine.append("0110011");
    if (substringAorD == "D+1")
        newLine.append("0011111");
    if (substringAorD == "A+1")
        newLine.append("0110111");
    if (substringAorD == "D-1")
        newLine.append("0001110");
    if (substringAorD == "A-1")
        newLine.append("0110010");
    if (substringAorD == "D+A")
        newLine.append("0000010");
    if (substringAorD == "D-A")
        newLine.append("0010011");
    if (substringAorD == "A-D")
        newLine.append("0000111");
    if (substringAorD == "D&A")
        newLine.append("0000000");
    if (substringAorD == "D|A")
        newLine.append("0010101");
    if (substringAorD == "M")
        newLine.append("1110000");
    if (substringAorD == "!M")
        newLine.append("1110001");
    if (substringAorD == "-M")
        newLine.append("1110011");
    if (substringAorD == "M-1")
        newLine.append("1110010");
    if (substringAorD == "M+1")
        newLine.append("1110111");
    if (substringAorD == "D+M")
        newLine.append("1000010");
    if (substringAorD == "D-M")
        newLine.append("1010011");
    if (substringAorD == "M-D")
        newLine.append("1000111");
    if (substringAorD == "D&M")
        newLine.append("1000000");
    if (substringAorD == "D|M")
        newLine.append("1010101");

    if (substringDest.empty())
        newLine.append("000");
    if (substringDest == "M")
        newLine.append("001");
    if (substringDest == "D")
        newLine.append("010");
    if (substringDest == "MD")
        newLine.append("011");
    if (substringDest == "A")
        newLine.append("100");
    if (substringDest == "AM")
        newLine.append("101");
    if (substringDest == "AD")
        newLine.append("110");
    if (substringDest == "AMD")
        newLine.append("111");

    if (substringJump.empty())
        newLine.append("000");
    if (substringDest == "JGT")
        newLine.append("001");
    if (substringDest == "JEQ")
        newLine.append("010");
    if (substringDest == "JGE")
        newLine.append("011");
    if (substringDest == "JLT")
        newLine.append("100");
    if (substringDest == "JNE")
        newLine.append("101");
    if (substringDest == "JLE")
        newLine.append("110");
    if (substringDest == "JMP")
        newLine.append("111");
    std::cout << substringAorD << " " << substringDest << " " << substringJump << '\n';
    return newLine;
}

void secondPass(std::vector<std::string>& asmLines, std::map<std::string, int>& addressMap, std::vector<std::string> &machineLang)
{
    std::regex label{ "\\([A-Za-z].*\\)" };
    std::regex Ainstruct{ "@.*" };
    std::regex Cinstruct{ "[^@][=MDA01+-].+" };
    std::regex letter{ "[A-Za-z].*" };
    std::string machineCode;

    bool isVariable{ false };
    int containerLimit{ 16 };
    int container{ 0 };

    for (int line{ 0 }; line < asmLines.size(); ++line)
    {
        container = 0;
        //std::cout << asmLines[line] << '\n';

        if (std::regex_match(asmLines[line], Ainstruct))
        {
            if (asmLines[line].find("@") != std::string::npos)
                asmLines[line].erase(0, 1);
            if (std::regex_match(asmLines[line], letter))
            {
                std::pair<int, std::string> highest = *addressMap.rbegin();
                std::map<int, std::string>::iterator mapIter = addressMap.begin();
                while (addressMap.value_comp()(*mapIter++,highest))
                {
                    if (asmLines[line] == mapIter->second)
                    {
                        isVariable = true;
                        asmLines[line] = mapIter->first;
                        break;
                    }
                }
                if (!isVariable);
                {
                    container = 0;
                    while (!addressMap[container].empty())
                        ++container;
                    addressMap[container] = asmLines[line];

                    asmLines[line] = std::to_string(container);
                    ++containerLimit;
                }
            }
            machineCode = convertBinary(asmLines[line]);
            machineLang.push_back(machineCode);
        }

        if (std::regex_match(asmLines[line], Cinstruct))
        {
            machineCode = Ctable(asmLines[line]);
            machineLang.push_back(machineCode);
        }

        if (std::regex_match(asmLines[line], label))
        {
            asmLines.erase(asmLines.begin() + line);
            --line;
        }
    }
}

int main()
{
    //create map of addresses and vector of textfile lines
    std::map<std::string, int> addressMap;
    std::vector<std::string> asmLines;
    std::vector<std::string> machineLang;

    std::string line;
    asmLines.reserve(1);

    //have user enter file name
    std::string filename = "Max.asm";
    //std::cout << "Enter File Name: ";
    //std::cin >> filename;
    std::ifstream asmFile;
    asmFile.open(filename);
    if (asmFile.is_open())
    {
        //fill vector with text file lines
        while (getline(asmFile, line))
            asmLines.push_back(line);

        initSymbolList(addressMap); //init standard hack symbols
        firstPass(asmLines, addressMap); //put labels in address map remove line comments
        secondPass(asmLines, addressMap, machineLang); // convert asm to machine language and put variables in address map

        asmFile.close();
    }

    std::ofstream newFile;
    newFile.open("example.hack");

    for (int i{ 0 }; i < machineLang.size(); ++i)
    {
        newFile << machineLang[i] << '\n';
    }
    newFile.close();
}

// Upload and open asm file
// Ignore whitespace comments and labels
// Create "Map" for address table of symbols used in first pass
// Determine if C or A instruction
// Parse strings into parts
// Convert each part into machine language
// Export hack file
