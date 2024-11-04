#pragma once
#include <filesystem>
#include <string>
#include <variant>
#include <vector>
using value_variant = std::variant<bool,
                                   int,  //
                                   double,
                                   char,
                                   std::string,
                                   std::nullptr_t>;
// массив значений
using value_array = std::vector<value_variant>;
// пара ключ-значение
using pairs = std::pair<std::string, value_variant>;
// массив пар ключ-значение
using vector_pairs = std::vector<std::pair<std::string,  
                                           value_variant>>;
// комплексное значение(значение/массив/пара/массив пар)
using complex_value = std::variant<value_variant,  //
                                   value_array,
                                   pairs,
                                   vector_pairs>;

/*========================константные значения======================*/

const static std::string programm_path =
    (std::filesystem::current_path()).string() + '/';
