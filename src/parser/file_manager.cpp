#include "file_manager.h"

/**
 *Создает объект FileManager с заданным адресом файла и состоянием менеджера.
 *
 *@param L_file_adress Адрес файла, который будет использоваться FileManager.
 *@param L_manager_state Состояние менеджера, которое будет использоваться
 *
 *@throws Нет
 */
FileManager::FileManager(std::string&& L_file_adress,
                         ManagerState L_manager_state)
    : file_adress_(L_file_adress),  //
      manager_state_(L_manager_state) {
  OpenPath();
}
/**
 *Создает новый экземпляр класса FileManager.
 *
 *@param L_file_adress Адрес файла.
 *@param L_key_array Массив ключей.
 *@param L_manager_state Состояние менеджера.
 *
 *@throws Нет.
 */
FileManager::FileManager(std::string&& L_file_adress,  //
                         std::vector<std::string>&& L_key_array,
                         ManagerState L_manager_state)
    : file_adress_(L_file_adress),
      key_array_(L_key_array),
      manager_state_(L_manager_state) {
  OpenPath();
}
FileManager::~FileManager() {}

void FileManager::OpenPath() {
  const b_fs::path L_path = file_adress_;
  if (b_fs::exists(L_path)) {  // проверка на валидность пути
    if (b_fs::is_directory(L_path)) {  // проверка является ли путь директорией
      OpenDirectopy(L_path);
    } else {
      OpenFile(L_path);
    }

  } else {
    std::cout << "Path does not exist or is not a directory!" << std::endl;
  }
}
void FileManager::OpenDirectopy(b_fs::path L_path) {
  for (const auto& entry : b_fs::directory_iterator(L_path)) {
    OpenFile(entry);
  }
}

void FileManager::OpenFile(b_fs::path L_file_path) {
  const std::string extension = L_file_path.extension().string();
  if (extension == ".txt") {
    std::cout << "File extension is .txt" << std::endl;
  } else if (extension == ".json") {
    try {
      parser::JsonParser parser;
      for (auto a : parser.ParseJson(L_file_path.string(), key_array_)) {
        cash_json_.insert(a);
      }

    } catch (const std::exception& e) {
      std::cout << e.what() << '\n';
    }
  }
}

unordered_map_str_str FileManager::Get_Result() const { return cash_json_; }