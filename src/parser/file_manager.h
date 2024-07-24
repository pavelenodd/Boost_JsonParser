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
using unordered_map_str_str = std::unordered_multimap<std::string, std::string>;

/**
 * @brief Режим работы менеджера
 * @param READ  режим чтения файла =0
 * @param WRITE режим записи в файл =1
 */
enum ManagerState { READ = 0, WRITE = 1 };

class FileManager {
 private:
  unordered_map_str_str cash_json_;  // unordered_map для хранения парсинга
  std::vector<std::string> key_array_;  // Массив ключей для парсинга
  std::string file_adress_;             // адрес файла
  ManagerState manager_state_ = ManagerState::READ;  // режим работы менеджера
 public:
 private:
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
  void OpenFile(b_fs::path L_path);

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
              std::vector<std::string>&& L_key_array,
              ManagerState L_manager_state);

  /**
   * @brief Конструктор для парсинга TXT-файла
   * @param L_file_adress - путь к файлу
   */
  FileManager(std::string&& L_file_adress,  //
              ManagerState L_manager_state);
  ~FileManager();

  /**
   *Получает результат функции.
   *
   *@tparam T тип ключа в неупорядоченной карте
   *@tparam U тип значения в неупорядоченной карте
   *
   *@return неупорядоченная карта, содержащая результат
   */

  unordered_map_str_str Get_Result() const;
};
