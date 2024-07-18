cmake_minimum_required(VERSION 3.30)
project(Harmony2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_image include dirs: ${SDL2_image_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

# Gather all source files
file(GLOB ENGINE_SOURCES "src/Engine/*.cpp" "src/Engine/*.h")
file(GLOB GAME_SOURCES "src/Game/*.cpp" "src/Game/*.h")
file(GLOB MAIN_SOURCE "src/*.cpp" "src/*.h")

# Add executable
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${GAME_SOURCES} ${MAIN_SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
target_link_libraries(Harmony2D PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
  )    