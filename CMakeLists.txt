cmake_minimum_required (VERSION 3.1)
project (rbxx)


set(CMAKE_CXX_FLAGS "--std=c++11")

include_directories("/usr/include/ruby-2.5.0")
include_directories("/usr/include/x86_64-linux-gnu/ruby-2.5.0")
include_directories("./include/rbxx")

aux_source_directory("./src/argparse" ARGPARSE_SRC)
aux_source_directory("./src/rect" RECT_SRC)
aux_source_directory("./src/vector_int" VINT_SRC)
aux_source_directory("./src/string" STR_SRC)
aux_source_directory("./src/file" FILE_SRC)
aux_source_directory("./src/map" MAP_SRC)
aux_source_directory("./src/rbxx" RBXX_SRC)

aux_source_directory("./tests/argparse" T_ARGPARSE_SRC)
aux_source_directory("./tests/rect" T_RECT_SRC)
aux_source_directory("./tests/vector_int" T_VINT_SRC)
aux_source_directory("./tests/string" T_STR_SRC)
aux_source_directory("./tests/file" T_FILE_SRC)
aux_source_directory("./tests/map" T_MAP_SRC)

add_executable(argparse_test ${T_ARGPARSE_SRC} ${ARGPARSE_SRC})
add_executable(rect_test ${T_RECT_SRC} ${RECT_SRC})
add_executable(vint_test ${T_VINT_SRC} ${VINT_SRC})
add_executable(str_test ${T_STR_SRC} ${STR_SRC})
add_executable(file_test ${T_FILE_SRC} ${FILE_SRC})
add_executable(map_test ${T_MAP_SRC} ${MAP_SRC} ${RBXX_SRC})

target_include_directories(argparse_test PUBLIC "./include/argparse")
target_include_directories(rect_test PUBLIC "./include/rect")
target_include_directories(vint_test PUBLIC "./include/vector_int")
target_include_directories(str_test PUBLIC "./include/string")
target_include_directories(file_test PUBLIC "./include/file")
target_include_directories(map_test PUBLIC "./include/map")

target_link_libraries(argparse_test ruby-2.5)
target_link_libraries(rect_test ruby-2.5)
target_link_libraries(vint_test ruby-2.5)
target_link_libraries(str_test ruby-2.5)
target_link_libraries(file_test ruby-2.5 boost_filesystem boost_system)
target_link_libraries(map_test ruby-2.5)

# set_property(argparse_test CXX_STANDARD 14)