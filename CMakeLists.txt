cmake_minimum_required(VERSION 3.27)

project(${PROJECT_NAME} Parser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

# Укажите, какие компоненты Boost вы хотите использовать
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(${PROJECT_NAME} src/parser.cpp)

# Подключите библиотеки Boost
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::filesystem Boost::system)
