# 指定 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和使用的 C++ 标准
project(ProcessMonitor VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 源文件
set(SOURCES
    ./tests/psmonitor.cpp
    ./src/psmonitor.cc
)

# 包含目录 (即头文件所在的目录)
include_directories(${CMAKE_SOURCE_DIR}/include)

# 生成可执行文件
add_executable(psmonitor ${SOURCES})

# 如果需要链接库，可以在这里添加(这里暂时不需要)
# target_link_libraries(process_monitor pthread mysqlcppconn)  # 示例：如果需要链接 pthread 或 MySQL++

