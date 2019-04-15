cmake_minimum_required (VERSION 3.1)
project (rbxx)

set(CMAKE_CXX_FLAGS "--std=c++17")

include_directories("/usr/include/ruby-2.3.0")
include_directories("/usr/include/x86_64-linux-gnu/ruby-2.3.0")
include_directories("./include/rbxx")

aux_source_directory("./src/argparse" ARGPARSE_SRC)
aux_source_directory("./src/rect" RECT_SRC)
aux_source_directory("./src/vector" VEC_SRC)
aux_source_directory("./src/string" STR_SRC)
aux_source_directory("./src/file" FILE_SRC)
aux_source_directory("./src/map" MAP_SRC)
aux_source_directory("./src/rbxx" RBXX_SRC)

aux_source_directory("./tests/argparse" T_ARGPARSE_SRC)
aux_source_directory("./tests/rect" T_RECT_SRC)
aux_source_directory("./tests/vector" T_VEC_SRC)
aux_source_directory("./tests/string" T_STR_SRC)
aux_source_directory("./tests/file" T_FILE_SRC)
aux_source_directory("./tests/map" T_MAP_SRC)

aux_source_directory("./lib_src/map" LIB_MAP_SRC)
aux_source_directory("./lib_src/vector" LIB_VEC_SRC)

add_executable(argparse_test ${T_ARGPARSE_SRC} ${ARGPARSE_SRC})
add_executable(rect_test ${T_RECT_SRC} ${RECT_SRC})
# add_executable(vec_test ${T_VEC_SRC} ${VEC_SRC} ${RBXX_SRC})
add_executable(str_test ${T_STR_SRC} ${STR_SRC})
add_executable(file_test ${T_FILE_SRC} ${FILE_SRC})
add_executable(map_test ${T_MAP_SRC} ${MAP_SRC} ${RBXX_SRC})

add_library(map SHARED ${LIB_MAP_SRC} ${MAP_SRC} ${RBXX_SRC} )
add_library(vector SHARED ${LIB_VEC_SRC} ${VEC_SRC} ${RBXX_SRC})

target_include_directories(argparse_test PUBLIC "./include/argparse")
target_include_directories(rect_test PUBLIC "./include/rect")
# target_include_directories(vec_test PUBLIC "./include/vector")
target_include_directories(str_test PUBLIC "./include/string")
target_include_directories(file_test PUBLIC "./include/file")
target_include_directories(map_test PUBLIC "./include/map")

target_include_directories(map PUBLIC "./include/map")
target_include_directories(vector PUBLIC "./include/vector")

target_link_libraries(argparse_test ruby-2.3)
target_link_libraries(rect_test ruby-2.3)
# target_link_libraries(vec_test ruby-2.3)
target_link_libraries(str_test ruby-2.3)
target_link_libraries(file_test ruby-2.3 boost_filesystem boost_system)
target_link_libraries(map_test ruby-2.3)

# set_property(argparse_test CXX_STANDARD 14)
set_target_properties(map PROPERTIES PREFIX "")
set_target_properties(vector PROPERTIES PREFIX "")