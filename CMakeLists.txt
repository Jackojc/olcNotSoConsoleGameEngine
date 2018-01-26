cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME olcNotSoConsoleGameEngine)
project(${PROJECT_NAME})


# SOURCE FILES
set(MAIN main.cpp)


# EXECUTABLE
add_executable(${PROJECT_NAME} ${MAIN})


# LINK
#target_link_libraries(${PROJECT_NAME})


# GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lSDL2 -Ofast -flto -m64")


# PLATFORMS
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif (WIN32)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
endif (WIN32)



# PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
