cmake_minimum_required (VERSION 2.6)
project (RbRectXX)

include_directories("/usr/include/ruby-2.5.0")
include_directories("/usr/include/x86_64-linux-gnu/ruby-2.5.0")

aux_source_directory("./src/rect" RECT_SRC)
aux_source_directory("./src/vector_int" VINT_SRC)
aux_source_directory("./src/string" STR_SRC)

aux_source_directory("./tests/rect" T_RECT_SRC)
aux_source_directory("./tests/vector_int" T_VINT_SRC)
aux_source_directory("./tests/string" T_STR_SRC)

add_executable(rect_test ${T_RECT_SRC} ${RECT_SRC})
add_executable(vint_test ${T_VINT_SRC} ${VINT_SRC})
add_executable(str_test ${T_STR_SRC} ${STR_SRC})

target_include_directories(rect_test PUBLIC "./include/rect")
target_include_directories(vint_test PUBLIC "./include/vector_int")
target_include_directories(str_test PUBLIC "./include/string")

target_link_libraries(rect_test ruby-2.5)
target_link_libraries(vint_test ruby-2.5)
target_link_libraries(str_test ruby-2.5)