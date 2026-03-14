#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // TODO: Uncomment the code below to pass the first stage

    std::cout << "$ ";
    std::string myStr;
    std::vector<std::string> commands;
    std::set<std::string> impl_commands = { "type", "echo", "exit" };
    while (true)
    {

        std::getline(std::cin, myStr); // "noah is" stored correctly

        if (myStr == "exit")
            break;

        if (myStr.starts_with("echo "))
        {
            std::cout << myStr.substr(5, myStr.length());
        }
        else if (myStr.starts_with("type "))
        {
            std::string type_str = myStr.substr(5, myStr.length());
            
            if(impl_commands.contains(type_str)){
              std::cout << type_str << " is a shell builtin";
            }
            else
            {
              std::cout << type_str << ": not found";
            }

        }
        else
        {
            //commands = split(myStr);

            //for (const std::string& command : commands)
            //{
            //    if(command == "echo")


            //}

            std::cout << myStr << ": command not found";
            
        }
        std::cout << "\n$ ";
    }
        

}

