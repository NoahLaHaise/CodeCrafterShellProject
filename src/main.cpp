#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
std::set<std::string> IMPL_COMMANDS = {"type", "echo", "exit"};
std::vector<fs::path> PATH_DIRS;

void get_path()
{
    const char *path = std::getenv("PATH");
    std::string str_path = path ? path : "";
    std::stringstream ss(str_path);
    std::string dir;

    char delim;
#if defined(_WIN32)
    delim = ';';
#elif defined(__linux__)
    delim = ':';
#endif

    while (std::getline(ss, dir, delim))
    {
        PATH_DIRS.push_back(dir);
    }
}

fs::path lookup_path_executables(std::string exe_str)
{
    for (fs::path path : PATH_DIRS)
    {
        path = path / exe_str;

        if (!fs::exists(path))
            continue;

        auto perms = fs::status(path).permissions();

        bool exec = (perms & (fs::perms::owner_exec | fs::perms::group_exec |
                              fs::perms::others_exec)) != fs::perms::none;
        if (exec)
            return path;
    }
    return "";
}

void handle_type_input(std::string input)
{
    std::string type_str = input.substr(5, input.length());

    if (IMPL_COMMANDS.contains(type_str))
    {
        std::cout << type_str << " is a shell builtin";
        return;
    }
    else if (!PATH_DIRS.empty())
    {
        fs::path exec_path = lookup_path_executables(type_str);
        if (exec_path != "")
        {
            std::cout << type_str << " is " << exec_path.string();
            return;
        }
    }
    std::cout << type_str << ": not found";
}

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // TODO: Uncomment the code below to pass the first stage

    std::cout << "$ ";
    std::string myStr;
    get_path();
    while (true)
    {

        std::getline(std::cin, myStr);

        if (myStr == "exit")
            break;

        if (myStr.starts_with("echo "))
        {
            std::cout << myStr.substr(5, myStr.length());
        }
        else if (myStr.starts_with("type "))
        {
            handle_type_input(myStr);
        }
        else
        {
            // commands = split(myStr);

            // for (const std::string& command : commands)
            //{
            //     if(command == "echo")

            //}

            std::cout << myStr << ": command not found";
        }
        std::cout << "\n$ ";
    }
}
