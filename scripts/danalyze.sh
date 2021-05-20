#!/bin/bash

if [ -d "build_danalyze" ]; 
then
	rm -rf build_danalyze/*
else
    mkdir -p build_danalyze
fi

cd build_danalyze
cmake -DGUI=OFF ..
make -j $(($(nproc) - 1))

echo -e '<<<<<<<<<<<<<<<<<<<<< MEMCHECK ANALYZE >>>>>>>>>>>>>>>>>>>>>>>>>>>\n'
timeout 5 valgrind --tool=memcheck --leak-check=full --leak-resolution=low --undef-value-errors=yes --xml=yes --xml-file=memcheck.xml ./camera_lucid -c ../cfg/camera_lucid.cfg -p /tmp/camera_lucid.pid

echo
echo -e '<<<<<<<<<<<<<<<<<<<<< CACHEGRIND ANALYZE >>>>>>>>>>>>>>>>>>>>>>>>>\n'
timeout 5 valgrind --tool=cachegrind ./camera_lucid -c ../cfg/camera_lucid.cfg -p /tmp/camera_lucid.pid

echo
echo -e '<<<<<<<<<<<<<<<<<<<<< MASSIF ANALYZE >>>>>>>>>>>>>>>>>>>>>>>>>\n'
timeout 5 valgrind --tool=massif ./camera_lucid -c ../cfg/camera_lucid.cfg -p /tmp/camera_lucid.pid
