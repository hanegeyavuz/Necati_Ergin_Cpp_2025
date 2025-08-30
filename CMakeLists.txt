cmake_minimum_required(VERSION 3.16)
project(CppCourse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common libs
include_directories(libs/Inc)
file(GLOB LIB_SRC "libs/Src/*.cpp")

# Add lessons
file(GLOB LESSONS "lessons/*/main.cpp")
foreach(lesson ${LESSONS})
    # lesson full path => lessons/Lesson01/main.cpp
    get_filename_component(lesson_dir ${lesson} DIRECTORY)
    get_filename_component(lesson_name ${lesson_dir} NAME)  # Lesson01 etc..
    add_executable(${lesson_name} ${lesson} ${LIB_SRC})
endforeach()


# Add Homeworks
file(GLOB HOMEWORKS "homeworks/*.cpp")
foreach(hw ${HOMEWORKS})
    get_filename_component(hw_name ${hw} NAME_WE)
    add_executable(${hw_name} ${hw} ${LIB_SRC})
endforeach()
