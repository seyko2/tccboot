#!/bin/bash

echo "build"

CC=tcc
#CC=gcc-2.95
#CC=gcc
echo " CC=$CC"

$CC build.c -o build

cp build ..
