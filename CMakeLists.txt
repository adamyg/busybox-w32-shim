#
# CMake Application Build Manifest
#
# Copyright (c) 2024 - 2025, Adam Young.
#
# https://github.com/adamyg/busybox-w32-shim
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required (VERSION 3.12)

project("busybox-shim")

include_directories(shim)

file(GLOB SOURCE_FILES ./apps/*.c)

foreach(SOURCE_PATH ${SOURCE_FILES})

	get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)

	add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH} ./shim/shim.c ./shim/shim.rc)
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

endforeach(SOURCE_PATH ${SOURCE_FILES})

#end
