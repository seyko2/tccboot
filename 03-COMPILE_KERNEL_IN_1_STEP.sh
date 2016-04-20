#!/bin/bash

. ./03-head.inc

if [ -n "$(echo $CC | grep tcc)" ]; then
    CC="$CC -bench"
fi

echo CC=$CC

echo | tee LOG
echo "step 1: compile & link" | tee -a LOG

$CC \
-o $KERNEL \
-nostdlib -static -Wl,-Ttext,0xc0100000 -Wl,--oformat,binary  \
-nostdinc -iwithprefix include -Ilinux/include \
-D__KERNEL__ -D__OPTIMIZE__ \
$FILE_LIST_1 \
$FILE_LIST_2 \
$FILE_LIST_3 \
$FILE_LIST_4 \
$FILE_LIST_5 \
$CCLIB 2>&1 | tee LOG

. ./03-tail.inc
