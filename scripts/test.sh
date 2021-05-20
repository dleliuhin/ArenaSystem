#!/bin/bash -e

if [ -d "tests/build_test" ];
then
        rm -rf tests/build_test/*
else
        mkdir -p tests/build_test
fi

cd tests/build_test

if [[ -z $1 ]];
then
    cmake .. -DCONNECTED=OFF
else
    cmake .. -D$1
fi

make -j $(($(nproc) - 1))

shopt -s extglob

./test_arena_system --gtest_output=xml

../../scripts/coverage.sh . ../../doc/coverage | tail -n 3

rm -rf !("test_arena_system"|"test_detail.xml")
