#include "file_manager.h"

FileManager::FileManager(std::string&& L_file_adress)
    : file_adress_(L_file_adress) {
  if (!b_fs::exists(b_fs::path(L_file_adress))) {
    std::cerr << "Path does not exist or is not a directory!" << std::endl;
  }
}

void FileManager::OpenPath() {
  const b_fs::path L_path = file_adress_;
  if (b_fs::is_directory(L_path)) {  // проверка является ли путь директорией
    OpenDirectopy(L_path);
  } else {
    OpenFile(L_path);
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

      switch (state_) {
        case ManagerState::READ: {
          for (auto a : parser.ParseJson(L_file_path.string(), key_array_)) {
            cash_json_.push_back(a);
          }
          break;
        }
        case ManagerState::WRITE: {
          /* code */
          break;
        }
      }

    } catch (const std::exception& e) {
      std::cout << e.what() << '\n';
    }
  }
}

void FileManager::Read(const std::vector<std::string>& L_key_array) {
  state_ = ManagerState::READ;
  key_array_ = L_key_array;
  OpenPath();
}

void FileManager::Write(const vector_pairs& L_key_array) {
  state_ = ManagerState::WRITE;
  key_array_.clear();
  for (const pairs& a : L_key_array) {
    key_array_.push_back(a.first);
    value_array_.push_back(a.second);
  }
  OpenPath();
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
