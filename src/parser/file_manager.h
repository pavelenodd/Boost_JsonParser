#pragma once

#include <boost/filesystem.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "json_parser.h"

namespace b_fs = boost::filesystem;
using unordered_map_str_str = std::unordered_map<std::string, std::string>;

class FileManager : private parser::JsonParser {
 private:
  unordered_map_str_str cash_json_;  // unordered_map для хранения парсинга
  std::vector<std::string> key_array_;  // Массив ключей для парсинга
  const std::string file_adress_;  // адрес файла

 public:
 private:
  /**
   * Reads the content of a file.
   *
   * @param file_path The path to the file to be read.
   *
   * @return The content of the file as a string. If the file cannot be opened,
   * an empty string is returned.
   *
   * @throws None
   */
  std::string ReadFileContent(const std::string& file_path);

  /**
   * Получение расширения файла
   *
   * @return описание возвращаемого значения
   *
   * @throws ErrorType описание ошибки
   */
  void OpenDirectopy(b_fs::path L_path);

  /**
   * Получение расширения файла
   *
   * @return описание возвращаемого значения
   * @throws ErrorType описание ошибки
   */
  void OpenFile();

  /**
   * @brief Открытие пути файла или папки
   */
  void OpenPath();

 public:
  FileManager() = delete;
  FileManager(const FileManager&) = delete;
  FileManager& operator=(const FileManager&) = delete;
  FileManager(FileManager&&) = delete;
  // ^удаление сандартного коструктора,копирования,перемещения,присваивания

  /**
   * @brief Конструктор для парсинга JSON-файла
   * @param L_file_adress - путь к файлу
   * @param L_key_array - массив ключей
   */
  FileManager(std::string&& L_file_adress,  //
              std::vector<std::string>&& L_key_array);

  /**
   * @brief Конструктор для парсинга TXT-файла
   * @param L_file_adress - путь к файлу
   */
  FileManager(std::string&& L_file_adress);
  ~FileManager();
};
