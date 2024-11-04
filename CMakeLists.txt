cmake_minimum_required(VERSION 3.30)

project(${PROJECT_NAME} Parser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

find_package(Boost COMPONENTS system filesystem REQUIRED)

find_package(nlohmann_json REQUIRED)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/file_manager.cpp
    src/file_manager.h
    
    )


target_link_libraries(${PROJECT_NAME} 
    Boost::boost Boost::filesystem Boost::system
    nlohmann_json::nlohmann_json
    )
