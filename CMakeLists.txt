cmake_minimum_required(VERSION 3.14)

project(game)
project(server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


file(GLOB_RECURSE SERV_VARIABLE net/server/*.c net/general/*.c physick/*.c)
file(GLOB_RECURSE VARIABLE *.c)
set(filtered_files "")
foreach(file ${VARIABLE})
   if(NOT file MATCHES "build/*" AND NOT file MATCHES "net/server/*")
        list(APPEND filtered_files ${file})
    endif()
endforeach()
#compilation
set(ARGS -Wall -g -lm -Werror)
add_executable(game main.c ${filtered_files} )
add_executable(server ${SERV_VARIABLE})
target_link_libraries(game m ncurses)
target_compile_options(game PRIVATE ${ARGS})
target_link_libraries(server m ncurses)
target_compile_options(server PRIVATE ${ARGS})
