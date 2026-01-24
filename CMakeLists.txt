cmake_minimum_required(VERSION 3.10)

project(VSCmakeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# [优化 1]：设置可执行文件的输出目录为项目根目录下的 bin 文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# [优化 2]：自动包含 src 目录，这样你在代码里 #include "header.h" 就能找到 src 下的头文件
include_directories(src)

# [优化 3]：自动发现 src 目录下的所有源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(main ${SOURCES})

# 如果你在 Windows 上使用 MSVC，设置编码为 UTF-8 以避免乱码
if(MSVC)
    add_compile_options("/utf-8")
endif()
