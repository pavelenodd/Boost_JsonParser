#include "file_manager.h"

FileManager::FileManager(std::string&& L_file_adress,
                         ManagerState L_manager_state)
    : file_adress_(L_file_adress),  //
      manager_state_(L_manager_state) {
  OpenPath();
}

FileManager::FileManager(std::string&& L_file_adress,  //
                         std::vector<std::string>&& L_key_array,
                         ManagerState L_manager_state)
    : file_adress_(L_file_adress),
      key_array_(L_key_array),
      manager_state_(L_manager_state) {
  OpenPath();
}

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
        cash_json_.push_back(a);
      }

    } catch (const std::exception& e) {
      std::cout << e.what() << '\n';
    }
  }
}

vector_pairs FileManager::Get_Result() const {
  return cash_json_;
}

void FileManager::PrintResult() const {
  for (const auto& kv : cash_json_) {
    std::cout << "Key: " << kv.first << ", Value: ";
    std::visit([](const auto& value) { PrintValue(value); }, kv.second);
  }
}

void FileManager::PrintValue(const auto& value) {
  if constexpr (std::is_same_v<std::decay_t<decltype(value)>, std::nullptr_t>) {
    std::cout << "null";
  } else if constexpr (std::is_same_v<std::decay_t<decltype(value)>,
                                      std::vector<ValueVariant>>) {
    std::cout << "[";
    for (const auto& elem : value) {
      std::visit([](const auto& v) { PrintValue(v); }, elem);
      std::cout << ", ";
    }
    std::cout << "]";
  } else if constexpr (std::is_same_v<
                           std::decay_t<decltype(value)>,
                           std::unordered_map<std::string, ValueVariant>>) {
    std::cout << "{";
    for (const auto& elem : value) {
      std::cout << "\"" << elem.first << "\": ";
      std::visit([](const auto& v) { PrintValue(v); }, elem.second);
      std::cout << ", ";
    }
    std::cout << "}";
  } else {
    std::cout << value;
  }
  std::cout << std::endl;
}
