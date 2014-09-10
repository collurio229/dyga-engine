project (dyga-engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("${PROJECT_SOURCE_DIR}/compositor/common")
add_executable(dyga compositor/main.cpp)

