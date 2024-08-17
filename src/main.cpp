#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <locale.h>
#endif
#include <filesystem>
#include <string>
#include "parser/file_manager.h"

int main(int argc, char* argv[]) {
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif
#ifdef __linux__
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
  const std::string programm_path =
      (std::filesystem::current_path()).string() + '/';

  {
    // простой набор значений
    std::vector<std::string> simple_array = {
        "string", "number", "boolean", "double", "null", "empty", "char"};

    // пример json массива
    std::pair<std::string, value_variant> json_array;

    // пример json объекта

    std::string file_path = programm_path + "test/test.json";
    FileManager fm(file_path);
    fm.Read(simple_array);

    fm.PrintResult();
  }
  {}
#ifdef _WIN32
  system("pause");
#endif
  return 0;
}
// TODO сделать поддержку object
// TODO сделать поддержку array
// TODO сделать запись в простые переменные
// TODO сделать запись в массив