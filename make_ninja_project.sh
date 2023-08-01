rm -r build
mkdir build
cd build
cmake -GNinja ../
ninja
./com_upd_transfer /dev/pts/6 1234
