# dlibss
Python wrapper of selective search like algorithm in dlib

## Requirements
- OpenCV (http://opencv.org/downloads.html)
- Boost.Numpy (https://github.com/ndarray/Boost.NumPy)
- dlib (https://github.com/davisking/dlib)

## Build dlibss

    $ cd lib
    $ mkdir build
    $ cmake ../
    $ make

## Test dlibss

    $ python scripts/test_dlibss.py

will create `tmp` dir and `result.jpg`