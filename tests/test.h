#include <catch.hpp>

#include "../PyLogHook.h"

#include <string>

inline void check_python_error()
{
    CHECK(PyErr_Occurred() == 0);
    if (PyErr_Occurred())
    {

        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        PyObject* pyErrStr = PyObject_Str(ptype);
        FAIL(PyUnicode_AsUTF8(pyErrStr)); 
        Py_DECREF(pyErrStr);
        PyErr_Restore(ptype, pvalue, ptraceback);
    }
}

TEST_CASE(NAME_PRE("Print test"), "[PyLogHook]")
{
    // init Python
    Py_Initialize();
    REQUIRE(Py_IsInitialized() != 0);

    //set hook
    std::string stdoutString;
    tyti::pylog::redirect_stdout([&stdoutString](const char*w)
    {
        stdoutString += w; //stdout
    });
    check_python_error();

    std::string stderrString;
    tyti::pylog::redirect_stderr([&stderrString](const char*w)
    {
        stderrString += w; //stdout
    });
    check_python_error();


    // execute printing operation
    const std::string test_str = "TESTING";
    SECTION("testing stdout")
    {
        std::string code = std::string("print(\"") + test_str + std::string("\")");

        PyRun_SimpleString(code.c_str());
        check_python_error();
        // check
        REQUIRE(stdoutString == test_str + "\n");
        
    }
    SECTION("testing stderr")
    {
        std::string code = std::string("import sys\nsys.stderr.write(\"") + test_str + std::string("\")");

        PyRun_SimpleString(code.c_str());
        check_python_error();
        // check
        REQUIRE(stderrString == test_str);
    }


    Py_Finalize();
}