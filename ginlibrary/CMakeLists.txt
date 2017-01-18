# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.c 
             src/main/cpp/md5.c
             src/main/cpp/md5.h
             )
find_library( 
              log-lib
              log )
target_link_libraries( 
                       native-lib
                       ${log-lib} )