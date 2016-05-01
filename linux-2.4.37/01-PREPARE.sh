#!/bin/bash

if [ "_$1" = "_" ]; then
    echo "Usage: $0 CC_COMPILER"; 
    exit
fi
CC=$1

if [ "$CC" = "tcc" ]; then
    CC="i386-tcc"
fi

cp config.tccboot .config

echo CC=$CC HOSTCC=$CC
sleep 2
make oldconfig 2>&1 | tee LOG

echo >> LOG
echo "======================================================" >> LOG
echo >> LOG

echo CC="$CC" HOSTCC="$CC" >> LOG

make dep CC="$CC" HOSTCC="$CC" 2>&1 | tee -a LOG
echo CC="$CC" > COMPILER.inc
