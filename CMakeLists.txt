cmake_minimum_required(VERSION 3.0)
project(state C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(state "${SOURCE}" src/other.c src/texture_functions.c src/mouse.c src/potion.c src/attack.c src/handle_events.c src/save_load_scoreboard.c src/map.c src/main-map.c src/first_menu.c src/select_map.c src/text_input.c src/user_name.c)

include_directories("/usr/include/SDL2")
include_directories("/usr/include")

target_link_libraries(state m SDL2 SDL2_gfx SDL2_ttf SDL2_image SDL2_mixer)  
