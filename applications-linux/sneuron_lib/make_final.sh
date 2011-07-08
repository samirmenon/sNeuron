rm release/lib*.so -rf &&
mkdir build_rel -p &&
mkdir release -p &&
cd build_rel &&
cmake .. -DCMAKE_BUILD_TYPE=Release &&
make -j2 &&
mv libsneuron* ../release/ &&
cd ..
