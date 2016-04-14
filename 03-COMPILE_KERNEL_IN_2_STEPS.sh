#!/bin/bash

. ./03-head.inc
echo CC=$CC

[ -d temp ] && rm -r temp
mkdir temp

echo | tee LOG
echo "step 1: compile" | tee -a LOG
sleep 1
for i in \
    $FILE_LIST_1  \
    $FILE_LIST_2  \
    $FILE_LIST_3  \
    $FILE_LIST_4  \
    $FILE_LIST_5; \
do
    echo $i
    dir=$(dirname $i)
    [ ! -d temp/$dir ] && mkdir -p temp/$dir

    $CC -c \
    -o temp/$i.o \
    -nostdinc -iwithprefix include -Ilinux/include \
    -D__KERNEL__ -D__OPTIMIZE__ $i 2>&1 | tee -a LOG
done

echo | tee -a LOG
echo "step 2: link" | tee -a LOG
sleep 1
$CC \
-o $KERNEL \
-nostdlib -static -Wl,-Ttext,c0100000 -Wl,--oformat,binary  \
$FILE_LIST_o \
$CCLIB 2>&1 | tee -a LOG

. ./03-tail.inc
