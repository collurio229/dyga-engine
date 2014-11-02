cmake_minimum_required(VERSION 2.8)

project (dyga-engine)

add_subdirectory(gtest-1.7.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS filesystem system date_time python3 REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )

find_package(SDL2 REQUIRED sdl2)
message("Include dirs of SDL: " ${SDL2_INCLUDE_DIR} )
message("Libs of SDL: " ${SDL2_LIBRARY} )
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/compositor/
	${PROJECT_SOURCE_DIR}/compositor/python
	${PROJECT_SOURCE_DIR}/compositor/common
	${PROJECT_SOURCE_DIR}/painter
	${gtest_SOURCE_DIR}/include
)

set(test_sources
	test/main_test.cpp
	test/compositor_common_test.cpp
)

add_library(painter STATIC painter/Painter.cpp)

target_link_libraries(painter
	${SDL2_LIBRARY}
)

add_executable(dyga compositor/main.cpp)

target_link_libraries(dyga
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
	${SDL2_LIBRARIES}
	painter
)

add_executable(test_all ${test_sources})

target_link_libraries(test_all gtest_main)
