#!/bin/bash

if [ -d "build_sanalyze" ]; 
then
	rm -rf build_sanalyze/*
else
    mkdir -p build_sanalyze
fi

files=$( find "$PWD/src" -path -o -name '*.cpp' -o -name '*.h' )

cd build_sanalyze
cmake -DGUI=OFF .. &>/dev/null

# include_args="$(cat ./compile_commands.json | grep command | sed "s/-I/\n-I/g" | grep -v command | awk '{print $1}' | sed "s/-I/-I /g")"

checks=$(cat ../cfg/sanalyzer.cfg)

clang-tidy-10 -config="$checks" $files -p=.
