#include "PythonVM.h"
#include <iostream>


const char* info = "***minipython***\n";
const char* prompt = ">>> ";

int main()
{
    std::string m_command;
    std::cout << info;
    std::cout << prompt;
    while (getline(std::cin, m_command))
    {
        if (m_command.size() == 0)
        {
            std::cout << prompt;
            continue;
        }
        else if (m_command == "exit")
        {
            return 0;
        }
        else
        {
            ExecuteCommand(m_command);
        }
    }
}