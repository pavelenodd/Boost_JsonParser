#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

namespace parser {
namespace b_pt = boost::property_tree;
using ValueVariant =
    std::variant<bool, int, double, char, std::string, std::nullptr_t>;
using vector_pairs = std::vector<std::pair<std::string, ValueVariant>>;

class JsonParser {
 private:
  b_pt::ptree tree_;  // JSON-дерево

  /**
   * Считывает содержимое файла JSON и сохраняет его в дереве свойств.
   * @param file_name Путь к файлу JSON для чтения.
   * @throws b_pt::json_parser::json_parser_error Если файл JSON не может быть
   * проанализирован
   */
  void ReadJson(const std::string& file_name) {
    try {
      b_pt::read_json(file_name, tree_);
    } catch (const b_pt::json_parser::json_parser_error& e) {
      std::cout << e.what() << '\n';
    }
  }

 public:
  /**
   * @brief Парсинг JSON-файла
   * @param file_name Имя JSON-файла
   * @param key_array Массив ключей для парсинга
   * @return vector_pairs Вектор пар ключ-значение
   */
  vector_pairs ParseJson(const std::string& file_name,
                         const std::vector<std::string>& key_array) {
    ReadJson(file_name);

    vector_pairs result;
    for (const auto& key : key_array) {
      ValueVariant param;

      auto child_optional = tree_.get_child_optional(key);
      if (!child_optional) {
        std::cerr << "Key: " << key << " not found" << std::endl;
        continue;
      }
      const b_pt::ptree& child = child_optional.get();
      if (child.empty()) {
        // Если узел пустой, то это может быть string, int, double, char или
        // null
        try {  // Попытка извлечь значение как bool
          param = tree_.get<bool>(key);
        } catch (const b_pt::ptree_bad_data&) {
          try {  // Попытка извлечь значение как int
            param = tree_.get<int>(key);
          } catch (const b_pt::ptree_bad_data&) {
            try {  // Попытка извлечь значение как double
              param = tree_.get<double>(key);
            } catch (const b_pt::ptree_bad_data&) {
              try {  // Попытка извлечь значение как char
                param = tree_.get<char>(key);
              } catch (const b_pt::ptree_bad_data&) {
                try {  // Попытка извлечь значение как string
                  std::string value = tree_.get<std::string>(key);
                  if (value.empty()) {
                    param = nullptr;  // Пустая строка
                  } else {
                    param = value;  // Непустая строка
                  }
                } catch (const b_pt::ptree_bad_data&) {
                  param = nullptr;  // null значение
                }
              }
            }
          }
        }
      } else {
        // Если узел не пустой, то это объект или массив
        if (tree_.front().first.empty()) {
          // Если первый элемент имеет пустой ключ, то это массив
        } else {
          // В противном случае это объект
        }
      }

      result.emplace_back(key, param);
    }

    return result;
  }
};

}  // namespace parser
