cmake_minimum_required(VERSION 3.30)

project(${PROJECT_NAME} Parser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

# Укажите, какие компоненты Boost вы хотите использовать
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/parser/file_manager.cpp
    src/parser/file_manager.h
    
    )


# Подключите библиотеки Boost
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::filesystem Boost::system)
