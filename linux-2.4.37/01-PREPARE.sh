#!/bin/bash

if [ -z "$CC" ]; then
    CC="gcc"
    #CC="gcc-2.95"
    #CC="tcc"
fi

cp config.tccboot .config
make oldconfig 2>&1 | tee LOG

echo >> LOG
echo "======================================================" >> LOG
echo >> LOG

echo CC=$CC | tee -a LOG
sleep 3

make dep CC=$CC 2>&1 | tee -a LOG
