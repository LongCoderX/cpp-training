
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(cpp-demo)

cmake_minimum_required(VERSION 3.10)
project(SmartPtrProject)

add_subdirectory(smart_ptr)
add_subdirectory(tests)

# 安装 smart_ptr 库的头文件到 include/smart_ptr 目录
install(DIRECTORY smart_ptr/
        DESTINATION include/smart_ptr
        FILES_MATCHING PATTERN "*.h")
