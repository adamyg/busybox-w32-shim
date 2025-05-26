@echo off
perl buildinfo.pl
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release %* ..

