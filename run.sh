#/bin/sh
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
if [ -d ./build ]; then
  echo "Build dir doesn't exist"
  exit 1
cd build
cmake --build .
ctest --output-on-failure
