#!/bin/bash

if [ -d "build_codestyle" ]; 
then
	rm -rf build_codestyle/*
else
        mkdir -p build_codestyle
fi

files=$( find "$PWD/src" -path -o -name '*.cpp' -o -name '*.h' )

cd build_codestyle
cmake -DGUI=OFF .. &>/dev/null

# include_args="$(cat ./compile_commands.json | grep command | sed "s/-I/\n-I/g" | grep -v command | awk '{print $1}' | sed "s/-I/-I /g")"

checks=$(cat ../cfg/codestyle.cfg)

clang-tidy-10 -config="$checks" $files -p=.
