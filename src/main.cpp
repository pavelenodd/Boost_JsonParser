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

  FileManager fm("test",  //
                 {
                     "string", "number", "boolean",  //
                     "double", "null", "empty",      //
                     "char"                          //
                 },
                 ManagerState::READ);

  fm.PrintResult();
  return 0;
}
// TODO сделать поддержку object
// TODO сделать поддержку array
// TODO сделать запись в простые переменные
// TODO сделать запись в массив