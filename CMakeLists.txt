cmake_minimum_required(VERSION 3.22)
project(Number_Recognition)

set(CMAKE_CXX_STANDARD 23)

include_directories(headers)
set(SOURCE_FILES src/main.cpp src/App.cpp headers/App.h src/Button.cpp headers/Button.h)

add_executable(Number_Recognition ${SOURCE_FILES})

set(SFML_DIR Libraries/SFML-2.5.1/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(Libraries/SFML-2.5.1/include)
target_link_libraries(Number_Recognition sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

file(COPY ${CMAKE_SOURCE_DIR}/fonts/Roboto-Light.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts/Roboto-Light.ttf)