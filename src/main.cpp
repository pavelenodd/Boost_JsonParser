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

  FileManager fm("test/test.json", {"age"});
  std::cout << fm.Get_Result()[0] << std::endl;

  return 0;
}