#!/bin/bash

pushd linux 1> /dev/null 

./01-PREPARE.sh > /dev/null 2>&1
make include/linux/compile.h > /dev/null 2>&1
tar xzf ../addon.tgz

popd 1> /dev/null
