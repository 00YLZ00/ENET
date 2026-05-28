# cmake_minimum_required(VERSION 3.10)

# project(EdoyunNet)

# set(CMAKE_CXX_STANDARD 11)

# include_directories(${PROJECT_SOURCE_DIR}/EdoyunNet)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# aux_source_directory(${PROJECT_SOURCE_DIR}/EdoyunNet SRC_LIST)

# add_executable(
#     EdoyunNet
#     ${SRC_LIST}
# )

# # 添加线程库
# find_package(Threads REQUIRED)
# target_link_libraries(EdoyunNet PRIVATE Threads::Threads)


cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#静态库的输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
#动态库的输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
#可执行文件的输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


add_subdirectory(${PROJECT_SOURCE_DIR}/EdoyunNet)
add_subdirectory(${PROJECT_SOURCE_DIR}/RtmpServer)
