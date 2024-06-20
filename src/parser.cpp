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

namespace b_fs = boost::filesystem;

class FileManager {
 private:
  std::unordered_map<std::string, std::string> cash_json_;
  const std::string file_adress_;

 private:
  std::string ReadFileContent(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
      std::cerr << "Unable to open file: " << file_path << std::endl;
      return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
  }
  void OpenPah() {}
  void OpenFile() {}

  /**
   * @brief Открытие пути файла или папки
   */
  void OpenPah() {
    b_fs::path p(file_adress_);
    if (b_fs::exists(p)) {  // проверка на валидность пути
      if (b_fs::is_directory(p)) {  // проверка является ли путь директорией
        for (const auto& entry : b_fs::directory_iterator(p)) {
          std::string file_content = ReadFileContent(entry.path().string());
          cash_json_.insert({entry.path().string(),
                             file_content});  // Заполнение unordered_map
          std::cout << "File: " << entry.path().string() << "\nContent:\n"
                    << file_content << "\n"
                    << std::endl;
        }
      } else {
        std::string file_content = ReadFileContent(file_adress_);
        cash_json_[file_adress_] = file_content;
        std::cout << "File: " << file_adress_ << "\nContent:\n"
                  << file_content << "\n"
                  << std::endl;
      }
      std::cout << "Cash_json_ size: " << cash_json_.size() << std::endl;
    } else {
      std::cerr << "Path does not exist or is not a directory!" << std::endl;
    }
  }

 public:
  FileManager() = delete;
  FileManager(const FileManager&) = delete;
  FileManager& operator=(const FileManager&) = delete;
  FileManager(FileManager&&) = delete;
  // удаление сандартного коструктора,копирования,перемещения,присваивания
  FileManager(std::string file_adress) : file_adress_(file_adress) {}
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
  try {
    FileManager fm("E:/Projects/Pets/Boost_JsonParser/src/test");
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
