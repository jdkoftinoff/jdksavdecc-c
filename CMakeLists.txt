cmake_minimum_required (VERSION 2.8)

if(BIICODE)
    ADD_BIICODE_TARGETS()
else(NOT BIICODE)
    set(PROJECT jdksavdecc-c)
    project(${PROJECT} C CXX)

    set(CXX11 "OFF")

    include(common.cmake)
endif(BIICODE)

