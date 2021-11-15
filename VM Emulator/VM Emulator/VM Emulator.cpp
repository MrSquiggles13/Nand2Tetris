#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <vector>

int compareCount{ 0 };
int returnCount{ 0 };

void buildVector(std::vector<std::string>& infileStrings, std::ifstream &file)
{
	std::string line;

	while (std::getline(file, line))
		infileStrings.push_back(line);
}

void removeComments(std::vector<std::string>& infileStrings)
{
	int index;
	for (int line{ 0 }; line < infileStrings.size(); ++line)
	{
		if (infileStrings[line].find("//") != std::string::npos)
		{
			index = infileStrings[line].find_first_of("//");
			infileStrings[line].erase(index);
		}
	}
}

void convertToAssemblyCommand(std::string command, std::string type, std::string index, std::vector<std::string> &asmCode, std::string filename)
{
	if (command == "push")
	{
		if(type == "local" || type == "argument" || type == "this" || type == "that" || type == "constant")
		{
			asmCode.push_back('@' + index);
			asmCode.push_back("D=A");
		}
		if (type == "local")
			asmCode.push_back("@LCL");
		else if (type == "argument")
			asmCode.push_back("@ARG");
		else if (type == "this")
			asmCode.push_back("@THIS");
		else if (type == "that")
			asmCode.push_back("@THAT");
		else if (type == "pointer")
		{
			if (index == "1")
				asmCode.push_back("@THAT");
			else if (index == "0")
				asmCode.push_back("@THIS");

			asmCode.push_back("D=M");
		}
		else if (type == "constant");
		else if (type == "temp")
		{
			std::stringstream in(index);
			int numIndex;
			in >> numIndex;
			numIndex += 5;
			asmCode.push_back("@" + std::to_string(numIndex));
		}
		else if (type == "static")
			asmCode.push_back('@' + filename + '.' + index);

		if (type == "constant");
		else if (type == "pointer");
		else if (type == "temp" || type == "static")
			asmCode.push_back("D=M");
		else
		{
			asmCode.push_back("A=D+M");
			asmCode.push_back("D=M");
		}
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
	}
	if (command == "pop")
	{
		if (type == "local" || type == "argument" || type == "this" || type == "that" || type == "constant")
		{
			asmCode.push_back('@' + index);
			asmCode.push_back("D=A");
		}
		if (type == "local")
			asmCode.push_back("@LCL");
		else if (type == "argument")
			asmCode.push_back("@ARG");
		else if (type == "this")
			asmCode.push_back("@THIS");
		else if (type == "that")
			asmCode.push_back("@THAT");
		else if (type == "pointer")
		{
			asmCode.push_back("@SP");
			asmCode.push_back("AM=M-1");
			asmCode.push_back("D=M");
			if (index == "1")
				asmCode.push_back("@THAT");
			else if (index == "0")
				asmCode.push_back("@THIS");
			asmCode.push_back("M=D");
			
		}
		else if (type == "constant");
		else if (type == "temp")
		{
			std::stringstream in(index);
			int numIndex;
			in >> numIndex;
			numIndex += 5;
			asmCode.push_back("@SP");
			asmCode.push_back("AM=M-1");
			asmCode.push_back("D=M");
			asmCode.push_back("@" + std::to_string(numIndex));
			asmCode.push_back("M=D");
		}
		else if (type == "static")
		{
			asmCode.push_back("@SP");
			asmCode.push_back("AM=M-1");
			asmCode.push_back("D=M");
			asmCode.push_back('@' + filename + '.' + index);
			asmCode.push_back("M=D");
		}

		if (type == "local" || type == "argument" || type == "this" || type == "that")
		{
			asmCode.push_back("D=D+M");
			asmCode.push_back("@R13");
			asmCode.push_back("M=D");

			asmCode.push_back("@SP");
			asmCode.push_back("AM=M-1");
			asmCode.push_back("D=M");

			asmCode.push_back("@R13");
			asmCode.push_back("A=M");
			asmCode.push_back("M=D");
		}
	}
	if (command == "add" || command == "sub" || command == "eq" || command == "gt" || command == "lt" || command == "or" || command == "and")
	{
		asmCode.push_back("@SP");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M-1");
		if (command == "add")
			asmCode.push_back("M=M+D");
		else if (command == "sub")
			asmCode.push_back("M=M-D");
		else if (command == "or")
			asmCode.push_back("M=M|D");
		else if (command == "and")
			asmCode.push_back("M=M&D");
		else if (command == "eq")
		{
			asmCode.push_back("D=M-D");
			asmCode.push_back("@TRUE" + std::to_string(compareCount));
			asmCode.push_back("D;JEQ");
			asmCode.push_back("(FALSE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@0");
			asmCode.push_back("D=A");
			asmCode.push_back("@ENDEQ" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(TRUE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@1");
			asmCode.push_back("D=A");
			asmCode.push_back("D=-D");
			asmCode.push_back("@ENDEQ" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(ENDEQ" + std::to_string(compareCount) + ')');
			asmCode.push_back("@SP");
			asmCode.push_back("A=M-1");
			asmCode.push_back("M=D");

			++compareCount;
		}
		else if (command == "lt")
		{
			asmCode.push_back("D=M-D");
			asmCode.push_back("@TRUE" + std::to_string(compareCount));
			asmCode.push_back("D;JLT");
			asmCode.push_back("(FALSE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@0");
			asmCode.push_back("D=A");
			asmCode.push_back("@ENDLT" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(TRUE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@1");
			asmCode.push_back("D=A");
			asmCode.push_back("D=-D");
			asmCode.push_back("@ENDLT" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(ENDLT" + std::to_string(compareCount) + ')');
			asmCode.push_back("@SP");
			asmCode.push_back("A=M-1");
			asmCode.push_back("M=D");

			++compareCount;
		}
		else if (command == "gt")
		{
			asmCode.push_back("D=M-D");
			asmCode.push_back("@TRUE" + std::to_string(compareCount));
			asmCode.push_back("D;JGT");
			asmCode.push_back("(FALSE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@0");
			asmCode.push_back("D=A");
			asmCode.push_back("@ENDGT" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(TRUE" + std::to_string(compareCount) + ')');
			asmCode.push_back("@1");
			asmCode.push_back("D=A");
			asmCode.push_back("D=-D");
			asmCode.push_back("@ENDGT" + std::to_string(compareCount));
			asmCode.push_back("0;JMP");
			asmCode.push_back("(ENDGT" + std::to_string(compareCount) + ')');
			asmCode.push_back("@SP");
			asmCode.push_back("A=M-1");
			asmCode.push_back("M=D");

			++compareCount;
		}
	}
	if (command == "neg")
	{
		asmCode.push_back("@SP");
		asmCode.push_back("A=M-1");
		asmCode.push_back("M=-M");
	}
	if (command == "not")
	{
		asmCode.push_back("@SP");
		asmCode.push_back("A=M-1");
		asmCode.push_back("M=!M");
	}
}

void convertToAssemblyBranch(std::string branch, std::string label, std::vector<std::string>& asmCode, std::string filename)
{
	if (branch == "label")
		asmCode.push_back('(' + label + ')');
	else if (branch == "goto")
	{
		asmCode.push_back("@" + label);
		asmCode.push_back("0;JMP");
	}
	else if (branch == "if-goto")
	{
		asmCode.push_back("@SP");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@" + label);
		asmCode.push_back("D;JNE");
	}
}

void convertToAssemblyFunction(std::string function, std::string label, std::string index, std::string returnLabel, std::vector<std::string>& asmCode, std::string filename)
{
	if (function == "function")
	{
		std::stringstream x{ index };
		int ind;
		x >> ind;
		asmCode.push_back("(" + label + ")");
		for (int i{ 0 }; i < ind; ++i)
		{
			asmCode.push_back("@0");
			asmCode.push_back("D=A");
			asmCode.push_back("@SP");
			asmCode.push_back("A=M");
			asmCode.push_back("M=D");
			asmCode.push_back("@SP");
			asmCode.push_back("M=M+1");
		}
	}
	else if (function == "call")
	{
		asmCode.push_back("@re" + returnLabel + std::to_string(returnCount));
		asmCode.push_back("D=A");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
		asmCode.push_back("@LCL");
		asmCode.push_back("D=M");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
		asmCode.push_back("@ARG");
		asmCode.push_back("D=M");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
		asmCode.push_back("@THIS");
		asmCode.push_back("D=M");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
		asmCode.push_back("@THAT");
		asmCode.push_back("D=M");
		asmCode.push_back("@SP");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("M=M+1");
		asmCode.push_back("@5");
		asmCode.push_back("D=A");
		asmCode.push_back("@" + index);
		asmCode.push_back("D=D+A");
		asmCode.push_back("@SP");
		asmCode.push_back("D=M-D");
		asmCode.push_back("@ARG");
		asmCode.push_back("M=D");
		asmCode.push_back("@SP");
		asmCode.push_back("D=M");
		asmCode.push_back("@LCL");
		asmCode.push_back("M=D");
		asmCode.push_back("@" + label);
		asmCode.push_back("0;JMP");
		asmCode.push_back("(re" + returnLabel + std::to_string(returnCount++) + ")");
	}
	else if (function == "return")
	{
		asmCode.push_back("@LCL");
		asmCode.push_back("D=M");
		asmCode.push_back("@R13");
		asmCode.push_back("M=D");

		asmCode.push_back("@5");
		asmCode.push_back("D=A");
		asmCode.push_back("@R13");
		asmCode.push_back("D=M-D");
		asmCode.push_back("A=D");
		asmCode.push_back("D=M");
		asmCode.push_back("@R14");
		asmCode.push_back("M=D");

		asmCode.push_back("@SP");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@ARG");
		asmCode.push_back("A=M");
		asmCode.push_back("M=D");
		asmCode.push_back("@ARG");
		asmCode.push_back("D=M+1");
		asmCode.push_back("@SP");
		asmCode.push_back("M=D");
		asmCode.push_back("@R13");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@THAT");
		asmCode.push_back("M=D");
		asmCode.push_back("@R13");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@THIS");
		asmCode.push_back("M=D");
		asmCode.push_back("@R13");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@ARG");
		asmCode.push_back("M=D");
		asmCode.push_back("@R13");
		asmCode.push_back("AM=M-1");
		asmCode.push_back("D=M");
		asmCode.push_back("@LCL");
		asmCode.push_back("M=D");
		asmCode.push_back("@R14");
		asmCode.push_back("A=M");
		asmCode.push_back("0;JMP");
	}
}

void bootStrapCode(std::vector<std::string>& asmCode)
{
	asmCode.push_back("@256");
	asmCode.push_back("D=A");
	asmCode.push_back("@SP");
	asmCode.push_back("M=D");
	convertToAssemblyFunction("call", "Sys.init", "0", "reSys.init", asmCode, "");
}

void stringParse(std::vector<std::string> &infileStrings, std::vector<std::string> &asmCode, std::string filename)
{
	std::regex command{ "^(push|pop|add|sub|neg|eq|gt|lt|and|or|not)" };
	std::regex type{ "(argument|this|that|temp|local|constant|static|pointer)" };
	std::regex index{ "[0-9]" };
	std::regex branch{ "^(goto|if-goto|label)" };
	std::regex function{ "^(call|function|return)" };
	std::regex label{ "[A-Za-z].*" };
	std::string word;
	std::string branchStr;
	std::string functionStr;
	std::string returnLabel;
	std::string labelStr;
	std::string commandStr;
	std::string typeStr;
	std::string indexStr;
	for (int line{ 0 }; line < infileStrings.size(); ++line)
	{
		asmCode.push_back("//" + infileStrings[line]);
		if (std::regex_search(infileStrings[line], command))
		{
			int i{ 0 };
			for (auto letter : infileStrings[line])
			{
				++i;
				if (letter != ' ')
				{
					word += letter;
				}
				if (letter == ' ' || i == infileStrings[line].length())
				{
					if (std::regex_search(word, command))
						commandStr = word;
					if (std::regex_search(word, type))
						typeStr = word;
					if (std::regex_search(word, index))
						indexStr = word;
					word = "";
				}
			}
			word = "";
			convertToAssemblyCommand(commandStr, typeStr, indexStr, asmCode, filename);
		}
		else if (std::regex_search(infileStrings[line], branch))
		{
			int i{ 0 };
			for (auto letter : infileStrings[line])
			{
				++i;
				if (letter != ' ')
				{
					word += letter;
				}
				if (letter == ' ' || i == infileStrings[line].length())
				{
					if (std::regex_search(word, branch))
						branchStr = word;
					else if (std::regex_search(word, label))
						labelStr = word;
					word = "";
				}
			}
			word = "";
			convertToAssemblyBranch(branchStr, labelStr, asmCode, filename);
		}
		else if (std::regex_search(infileStrings[line], function))
		{
			int i{ 0 };
			for (auto letter : infileStrings[line])
			{
				++i;
				if (letter != ' ')
				{
					word += letter;
				}
				if (letter == ' ' || i == infileStrings[line].length())
				{
					if (functionStr == "function")
						returnLabel = labelStr;
					if (std::regex_search(word, function))
						functionStr = word;
					else if (std::regex_search(word, label))
						labelStr = word;
					else if (std::regex_search(word, index))
						indexStr = word;
					word = "";
				}
			}
			word = "";
			convertToAssemblyFunction(functionStr, labelStr, indexStr, returnLabel, asmCode, filename);
		}
	}
}

int main()
{
	std::string dirName;
	std::cout << "Enter Directory To Open: ";
	std::cin >> dirName;
	std::string filename;
	std::vector<std::string> asmCode;
	bootStrapCode(asmCode);

	for (auto& dirEntry : std::filesystem::recursive_directory_iterator(dirName))
	{
		
		std::filesystem::path filePath = dirEntry.path();
		
		if (filePath.extension() == ".vm")
		{
			std::ifstream file;
			filename = filePath.stem().string();
			file.open(filePath);
			std::vector<std::string> infileStrings;
			
			
			if (file.is_open())
			{
				buildVector(infileStrings, file);
				removeComments(infileStrings);
				stringParse(infileStrings, asmCode, filename);
				file.close();
			}
		}
	}

	std::ofstream newFile;
	newFile.open(dirName + ".asm");
	for (int line{ 0 }; line < asmCode.size(); ++line)
		newFile << asmCode[line] << '\n';
	newFile.close();
}

//take vm code as input
//parse each string
//seperate each command into 3 parts{command, type, index}
//take each part and do correct assembly for each one ie index @index
//build a vector of assembly instructions
//output asm file