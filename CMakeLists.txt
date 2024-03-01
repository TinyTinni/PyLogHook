cmake_minimum_required (VERSION 3.6)
project (PyLogHook)

option(USE_BOOST "test with boost instead of pybind11" ON)

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
add_test(NAME tests COMMAND tests)