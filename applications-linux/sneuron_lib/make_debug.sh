rm debug/lib*.so -rf &&
mkdir build_dbg -p &&
mkdir debug -p &&
cd build_dbg &&
cmake .. -DCMAKE_BUILD_TYPE=Debug &&
make -j2 &&
mv libsneuron* ../debug/ &&
cd ..
