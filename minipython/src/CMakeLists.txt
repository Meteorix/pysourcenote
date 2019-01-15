cmake_minimum_required (VERSION 2.6)
project (minipython)

set(CMAKE_CXX_STANDARD 11)


set(
	MODULES
    PyTypeObject
    PyIntObject
    PyStrObject
    PyDictObject
    PythonVM
)

foreach(MODULE ${MODULES})
	set(SOURCES ${SOURCES} ${MODULE}.cpp)
	set(HEADERS ${HEADERS} PyObject.h ${MODULE}.h)
endforeach()

add_executable(
    minipython.exe
	python.cpp
	${SOURCES}
)
