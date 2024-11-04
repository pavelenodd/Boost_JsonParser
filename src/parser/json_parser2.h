#pragma once
#include <cassert>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "data.h"

using json = nlohmann::json;

namespace parser {

/**
 * \brief Считывает содержимое файла JSON и сохраняет его в дереве свойств.
 */
class JsonParser {
 private:
  json json_tree_;                // JSON-дерево.
  complex_value complex_values_;  // Комплексные значения
  std::string file_name_;         // Имя JSON-файла
  std::string file_directory_;    // Адрес папки с JSON-файлом

 public:
 private:
  /**
   * \brief Считывает содержимое файла JSON и сохраняет его в списке значений
   * \param L_file_name Путь к файлу JSON для чтения.
   */
  complex_value ParseJsonToComplexValue(const std::string& L_file_name) {
    if (L_file_name.empty()) {
      std::cout << "File name is empty!" << std::endl;
    } else {
      std::ifstream json_file(L_file_name);

      if (json_file.is_open()) {
        json_file >> json_tree_;

        json_file.close();
      }
    }
  }

 public:
  JsonParser() {};
  ~JsonParser() {};
};
}  // namespace parser
