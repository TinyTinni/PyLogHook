#define BOOST_PYTHON_STATIC_LIB
#define TYTI_PYLOGHOOK_USE_BOOST

#define STR(x) #x
#define NAME_PRE(x) STR(boost.python ## x) 


#include "test.h"