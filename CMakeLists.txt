cmake_minimum_required(VERSION 3.16)

project(202691sdl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# 加入 SDL3
add_subdirectory(3rd_party/SDL EXCLUDE_FROM_ALL)
set(LUAJIT_DIR
    "${CMAKE_SOURCE_DIR}/3rd_party/LuaJIT"
)

add_library(
    LuaJIT::LuaJIT
    SHARED
    IMPORTED
)

set_target_properties(
    LuaJIT::LuaJIT
    PROPERTIES

    IMPORTED_IMPLIB
        "${LUAJIT_DIR}/src/lua51.lib"

    IMPORTED_LOCATION
        "${LUAJIT_DIR}/src/lua51.dll"

    INTERFACE_INCLUDE_DIRECTORIES
        "${LUAJIT_DIR}/src"
)


# 创建程序
add_executable(202691sdl
    src/main.cpp
 "src/core/modules/Window/Window.h" "src/core/modules/Window/Window.cpp" "src/core/runtime/SDL_Runtime.h" "src/core/runtime/SDL_Runtime/SDL_Runtime.cpp" "src/core/runtime/Frame_Runtime/Frame_Runtime.h")
#[[

add_executable(202691sdl WIN32
    src/main.cpp
)

]]

# 让程序链接 SDL3
target_link_libraries(202691sdl
    PRIVATE
    SDL3::SDL3
    LuaJIT::LuaJIT
)

add_custom_command(
    TARGET 202691sdl
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LUAJIT_DIR}/src/lua51.dll"
        "$<TARGET_FILE_DIR:202691sdl>"
)