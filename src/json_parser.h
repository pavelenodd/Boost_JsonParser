#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace parser {
namespace b_pt = boost::property_tree;

class JsonParser {
 private:
  b_pt::ptree tree_;

  void ReadJson(const std::string& L_file_name) {
    try {
      b_pt::read_json(L_file_name, tree_);
    } catch (const b_pt::json_parser::json_parser_error& e) {
      std::cout << e.what() << '\n';
    }
  }

 public:
  /**
   * @brief Парсинг JSON-файла
   * @param file_name - имя JSON-файла
   * @param key_array - массив ключей для парсинга
   * @result unordered_map<std::string, std::string>
   */
  std::unordered_map<std::string, std::string> ParseJson(
      const std::string& file_name, const std::vector<std::string>& key_array) {
    ReadJson(file_name);

    std::unordered_map<std::string, std::string> result;
    for (const auto& key : key_array) {
      std::string param = tree_.get<std::string>(key);
      result[key] = param;
    }
    return result;
  }
};

}  // namespace parser