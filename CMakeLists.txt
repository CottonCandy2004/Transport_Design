cmake_minimum_required(VERSION 3.10)

# 设置编译器为MinGW
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE "Debug")

# 设置项目名称
project(Transport_Design)

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/lib)

# 添加源文件
add_executable(${PROJECT_NAME}
    src/struct.c
    src/vector.c
    src/fileio.c
    src/station.c
    src/train.c
    src/ui_terminal.c
    src/ui.c
    src/lookup.c
    src/main.c
    # test/test_train.c
)

# 设置C标准
set(CMAKE_C_STANDARD 11)
