rm -r build
mkdir build
cd build
cmake -GNinja ../
ninja
./udp_server
