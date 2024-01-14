#!/bin/sh

TARGET="days/$1/$2"

g++ -Wall -std=c++20 -o $TARGET/main $TARGET/main.cpp