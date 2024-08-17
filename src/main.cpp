#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <locale.h>
#endif
#include <filesystem>
#include <string>
#include "parser/data.h"
#include "parser/file_manager.h"

int main() {
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif
#ifdef __linux__
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

  std::string file_path = programm_path + "test/test.json";
  FileManager fm(file_path);
  {
    // простой набор значений
    std::vector<std::string> simple_array = {
        "string", "number", "boolean", "double", "null", "empty", "char"};

    fm.Read(simple_array);
    std::cout << "current result \n";
    fm.PrintResult();
  }
  {
    std::vector<pairs> simple_array = {{"string", "new_string"},
                                       {"number", 123},
                                       {"boolean", false},
                                       {"double", 123.456},
                                       {"null", 2},
                                       {" empty ", " qweqwe "},
                                       {"char", 'x'}};

    fm.Write(simple_array);
    std::cout << "new recult \n";
    fm.PrintResult();
  }

#ifdef _WIN32
  system("pause");
#endif
  return 0;
}
// TODO сделать поддержку object
// TODO сделать поддержку array
// TODO сделать запись в простые переменные
// TODO сделать запись в массив