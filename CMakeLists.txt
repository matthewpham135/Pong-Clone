cmake_minimum_required(VERSION 3.5)
project(Pong)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(Pong PRIVATE SDL2::SDL2)
target_link_libraries(Pong PRIVATE SDL2_image::SDL2_image)
target_link_libraries(Pong PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(Pong PRIVATE SDL2_mixer::SDL2_mixer)
file(GLOB RESOURCE_FILES *.bmp *.wav) 
set(RESOURCE_FILE_NAMES)
set(RESOURCE_FILES_BINDIR)
foreach(resource_file IN LISTS RESOURCE_FILES)
    get_filename_component(res_file_name ${resource_file} NAME)
    list(APPEND RESOURCE_FILE_NAMES "${res_file_name}")
    set(resource_file_bindir "${CMAKE_CURRENT_BINARY_DIR}/${res_file_name}")
    add_custom_command(OUTPUT "${resource_file_bindir}"
        COMMAND "${CMAKE_COMMAND}" -E copy "${resource_file}" "${resource_file_bindir}"
        DEPENDS "${resource_file}"
    )
    list(APPEND RESOURCE_FILES_BINDIR "${resource_file_bindir}")
endforeach()
add_custom_target(copy-resources DEPENDS "${RESOURCE_FILES_BINDIR}")
add_dependencies(Pong copy-resources)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
  )
  target_link_options(Pong
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

