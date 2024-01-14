#!/bin/sh

TARGET="days/$1"

g++ -Wall -std=c++20 -o $TARGET/$2-bin $TARGET/$2.cpp