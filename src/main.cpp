#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::set<std::string> IMPL_COMMANDS = {"type", "echo", "exit"};

std::vector<std::string> get_path() {
  const char *path = std::getenv("path");
  std::string str_path = path ? path : "";
  std::vector<std::string> dirs;
  std::stringstream ss(str_path);
  std::string dir;

  char delim;
#if defined(_WIN32)
  delim = ';';
#elif defined(__linux__)
  delim = ':';
#endif

  while (std::getline(ss, dir, delim)) {
    dirs.push_back(dir);
  }

  return dirs;
}

void handle_type_input(std::string input) {
  std::string type_str = input.substr(5, input.length());

  if (IMPL_COMMANDS.contains(type_str)) {
    std::cout << type_str << " is a shell builtin";
  } else {
    std::cout << type_str << ": not found";
  }
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage

  std::cout << "$ ";
  std::string myStr;
  std::vector<std::string> paths = get_path();

  while (true) {

    std::getline(std::cin, myStr); // "noah is" stored correctly

    if (myStr == "exit")
      break;

    if (myStr.starts_with("echo ")) {
      std::cout << myStr.substr(5, myStr.length());
    } else if (myStr.starts_with("type ")) {
      handle_type_input(myStr);

    } else {
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
