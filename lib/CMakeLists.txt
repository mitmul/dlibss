cmake_minimum_required(VERSION 2.6)
project(dlibss)
set(CMAKE_CXX_FLAGS "-O3")

set(inc_dirs
    /usr/local/include
    /usr/local/include/opencv
    /usr/local/include/opencv2
    $ENV{HOME}/anaconda/include
    $ENV{HOME}/Libraries/Boost.Numpy/build/include
    $ENV{HOME}/anaconda/include/python2.7
    $ENV{HOME}/Libraries/dlib
)

set(lib_dirs
    /usr/local/lib
    $ENV{HOME}/anaconda/lib
    $ENV{HOME}/Libraries/Boost.Numpy/build/lib
    $ENV{HOME}/Libraries/dlib/build
)

set(libs
    opencv_core
    opencv_highgui
    opencv_imgproc
    boost_python
    boost_numpy
    python2.7
    dlib
)

include_directories(
    ${inc_dirs}
)

link_directories(
    ${lib_dirs}
)

add_library(dlibss SHARED
    src/dlibss.cpp
)

target_link_libraries(dlibss
    ${libs}
)

set_target_properties(dlibss PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)
