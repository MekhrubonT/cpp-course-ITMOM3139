cmake_minimum_required(VERSION 3.0)

if (POLICY CMP0063) #  Honor visibility properties for all target types (introduced in 3.3)
    cmake_policy(SET CMP0063 NEW)
endif ()

project(mpl_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_executable(mpl_demo
    is_nil.h
    main.cpp
    node.h
    print.h
    push_back.h
)