cls
mkdir build
cd build
"C:\Program Files\CMake\bin\cmake.EXE" --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug "-DCMAKE_C_COMPILER:FILEPATH=C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe" "-DCMAKE_CXX_COMPILER:FILEPATH=C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe" -Hd:/game/EternalGarden -Bd:/game/EternalGarden/build -G "MinGW Makefiles"
cmake --build .
cd ..