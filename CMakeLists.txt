cmake_minimum_required(VERSION 3.10)

project(EdoyunNet)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/EdoyunNet)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(${PROJECT_SOURCE_DIR}/EdoyunNet SRC_LIST)

add_executable(
    EdoyunNet
    ${SRC_LIST}
)

# 添加线程库
find_package(Threads REQUIRED)
target_link_libraries(EdoyunNet PRIVATE Threads::Threads)
