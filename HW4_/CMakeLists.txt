# CMakeLists
cmake_minimum_required(VERSION 3.0)
project(HW4)
file(
      GLOB_RECURSE MAKE_LIST
      ${PROJECT_SOURCE_DIR}/src/*.cpp
)
foreach(mainfile IN LISTS MAKE_LIST)
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile} diary.cpp)
endforeach()

