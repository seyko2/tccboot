#!/bin/bash

. ./03-head.inc
CC="$CC -bench"
echo CC=$CC

echo | tee LOG
echo "step 1: compile & link" | tee -a LOG

$CC \
-o $KERNEL \
-nostdlib -static -Wl,-Ttext,c0100000 -Wl,--oformat,binary  \
-nostdinc -iwithprefix include -Ilinux/include \
-D__KERNEL__ -D__OPTIMIZE__ \
$FILE_LIST_1 \
$FILE_LIST_2 \
$FILE_LIST_3 \
$FILE_LIST_4 \
$FILE_LIST_5 \
$CCLIB 2>&1 | tee LOG

. ./03-tail.inc
