Compile
-------

mkdir build
cd build
cmake .. # -DDISABLE_TESTS=TRUE
         # -DCMAKE_BUILD_TYPE=Release
         # -DCMAKE_BUILD_TYPE=Debug
make


Compile & Run tests/TEST_NAME test
-------------------------------

make && ./test__TEST_NAME
