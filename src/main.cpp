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
  std::vector<std::string> array = {"string", "number", "boolean", "double",
                                    "null",   "empty",  "char"};
  {
    FileManager fm("test/test.json");
    fm.Read(array);

    fm.PrintResult();

    // fm.Write("test2.json");
  }
  {
    // FileManager fm("test.json");

    // fm.PrintResult();
  }
  return 0;
}
// TODO сделать поддержку object
// TODO сделать поддержку array
// TODO сделать запись в простые переменные
// TODO сделать запись в массив