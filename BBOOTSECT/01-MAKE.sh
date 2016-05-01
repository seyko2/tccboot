#!/bin/bash

echo "bbootsect"

CC=i386-tcc
#CC=gcc-2.95
#CC=gcc
echo " CC=$CC"

#AS=i386-tcc         # bsetup.s:112: error: constant expected
AS="as --32"
echo " AS=$AS"

#LD=gcc
LD=i386-tcc
#LD=ld
echo " LD=$LD"

$CC -E -P bootsect.S -D__BIG_KERNEL__ -o bootsect.s

$AS bootsect.s -o bootsect.o

if [ "$LD" = "ld" ]; then
    $LD -Ttext=0 --oformat=binary -o bbootsect bootsect.o
else
    $CC  \
    -nostdlib -nostdinc \
    -static -Wl,-Ttext,0 -Wl,--oformat,binary \
    -fno-common \
    -D__KERNEL__ -D__OPTIMIZE__ \
    -D__GNUC__=2 -D__GNUC_MINOR__=95 \
    -o bootsect.tcc bootsect.o

    dd if=bootsect.tcc of=bbootsect bs=1 count=512 2> /dev/null
    chmod a+x bbootsect
    chmod a-x bootsect.tcc
fi

cp bbootsect ..
