project(EdoyunNet)

include_directories(&{CMAKE_SOURCE_DIR}/EdoyunNet)

aux_source_directory(. NET_SRC)

add_executable(
    EdoyunNet
    ${NET_SRC}
)

# 添加线程库
find_package(Threads REQUIRED)
target_link_libraries(EdoyunNet PRIVATE Threads::Threads)