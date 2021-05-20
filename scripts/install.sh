#!/bin/bash

sudo apt-get install build-essential gcc-8 g++-8 cmake make lcov gcovr clang-tools-10 clang-tidy-10 clang-format-10 ninja-build valgrind libx264-dev libx265-dev
sudo apt install libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib
