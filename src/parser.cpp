#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <locale.h>
#endif

#include <boost/filesystem.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "json_parser.h"

namespace b_fs = boost::filesystem;

class FileManager : private parser::JsonParser {
 private:
  std::unordered_map<std::string, std::string> cash_json_;
  std::vector<std::string> key_array_;
  const std::string file_adress_;

 public:
 private:
  std::string ReadFileContent(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
      std::cout << "Unable to open file: " << file_path << std::endl;
      return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
  }
  void OpenDirectopy(b_fs::path L_path) {
    for (const auto& entry : b_fs::directory_iterator(L_path)) {
      std::string file_content = ReadFileContent(entry.path().string());
      cash_json_.insert(
          {entry.path().string(), file_content});  // Заполнение unordered_map
      std::cout << "File: " << entry.path().string() << "\nContent:\n"
                << file_content << "\n"
                << std::endl;
    }
  }
  void OpenFile() {
    // Получение расширения файла

    b_fs::path file_path(file_adress_);
    std::string extension = file_path.extension().string();
    if (extension == ".txt") {
      std::cout << "File extension is .txt" << std::endl;
    } else if (extension == ".json") {
      try {
        cash_json_ = ParseJson(file_adress_, key_array_);

        // TODO: удалить сделано для визуализации работы
        for (const auto& [key, value] : cash_json_) {
          std::cout << key << ": " << value << std::endl;
        }
        //

      } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
      }
    }
  }

  /**
   * @brief Открытие пути файла или папки
   */
  void OpenPath() {
    b_fs::path path(file_adress_);
    if (b_fs::exists(path)) {  // проверка на валидность пути
      if (b_fs::is_directory(path)) {  // проверка является ли путь директорией
        OpenDirectopy(path);
      } else {
        OpenFile();
      }
      std::cout << "Cash_json_ size: " << cash_json_.size() << std::endl;
    } else {
      std::cout << "Path does not exist or is not a directory!" << std::endl;
    }
  }

 public:
  FileManager() = delete;
  FileManager(const FileManager&) = delete;
  FileManager& operator=(const FileManager&) = delete;
  FileManager(FileManager&&) = delete;
  // ^удаление сандартного коструктора,копирования,перемещения,присваивания

  /**
   * @brief Конструктор для парсинга JSON-файла
   * @param file_adress - путь к файлу
   * @param key_array - массив ключей
   */
  FileManager(std::string&& file_adress,  //
              std::vector<std::string>&& key_array)
      : file_adress_(file_adress), key_array_(key_array) {
    OpenPath();
  }

  /**
   * @brief Конструктор для парсинга TXT-файла
   * @param file_adress - путь к файлу
   */
  FileManager(std::string&& file_adress) : file_adress_(file_adress) {
    OpenPath();
  }
  ~FileManager() {}
};

int main(int argc, char* argv[]) {
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif
#ifdef __linux__
  setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

  FileManager fm("E:/Projects/Pets/Boost_JsonParser/src/test/test.json",
                 {"name", "age"});

  return 0;
}
