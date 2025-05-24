cmake_minimum_required (VERSION 3.12)

project("busybox-shim")

include_directories(shim)

file(GLOB SOURCE_FILES ./apps/*.c)

foreach(SOURCE_PATH ${SOURCE_FILES})

        get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
        add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH} ./shim/shim.c ./shim/shim.rc)

endforeach(SOURCE_PATH ${SOURCE_FILES})
