cmake_minimum_required (VERSION 3.14)
project (PyLogHook)

option(USE_BOOST "test with boost instead of pybind11" ON)

find_package(Python 3 REQUIRED COMPONENTS Development)

if (USE_BOOST)
    find_package(Boost REQUIRED COMPONENTS python)
    set(SRC "tests/boost_test.cpp")
else()
    find_package(pybind11 REQUIRED)
    set(SRC "tests/pybind11_test.cpp")
endif()

include(CTest)
enable_testing()

add_executable(tests tests/main.cpp ${SRC})
if (USE_BOOST)
    target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS} )
    target_link_libraries(tests PRIVATE ${Boost_LIBRARIES} Python::Python)
else()
    target_link_libraries(tests PRIVATE pybind11::pybind11 Python::Python)
endif()
add_test(NAME tests COMMAND tests)