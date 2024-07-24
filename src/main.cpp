#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <locale.h>
#endif

#include "parser/file_manager.h"

int main(int argc, char* argv[]) {
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif
#ifdef __linux__
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

  FileManager fm("test", {"age"}, ManagerState::READ);
  for (auto a : fm.Get_Result()) {
    std::cout << a.first << " " << a.second << std::endl;
  }

  return 0;
} /*Please provide the details of the code changes you made*/