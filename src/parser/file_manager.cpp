#include "file_manager.h"

FileManager::FileManager(std::string&& L_file_adress)
    : file_adress_(L_file_adress) {
  OpenPath();
}
FileManager::FileManager(std::string&& L_file_adress,  //
                         std::vector<std::string>&& L_key_array)
    : file_adress_(L_file_adress), key_array_(L_key_array) {
  OpenPath();
}
FileManager::~FileManager() {}

void FileManager::OpenPath() {
  const b_fs::path L_path = file_adress_;
  if (b_fs::exists(L_path)) {  // проверка на валидность пути
    if (b_fs::is_directory(L_path)) {  // проверка является ли путь директорией
      OpenDirectopy(L_path);
    } else {
      OpenFile();
    }
    std::cout << "Cash_json_ size: " << cash_json_.size() << std::endl;
    // TODO: удалить сделано для визуализации работы
  } else {
    std::cout << "Path does not exist or is not a directory!" << std::endl;
  }
}
void FileManager::OpenFile() {
  const b_fs::path L_file_path = file_adress_;
  const std::string extension = L_file_path.extension().string();
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

void FileManager::OpenDirectopy(b_fs::path L_path) {
  for (const auto& entry : b_fs::directory_iterator(L_path)) {
    std::string file_content = ReadFileContent(entry.path().string());
    cash_json_.insert({entry.path().string(), file_content});
    std::cout << "File: " << entry.path().string() << "\n";
    std::cout << "Content:\n" << file_content << "\n";
  }
}

std::string FileManager::ReadFileContent(const std::string& file_path) {
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