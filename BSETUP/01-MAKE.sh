#!/bin/bash

echo "bsetup"

CC=i386-tcc
#CC=gcc-2.95
#CC=gcc
echo " CC=$CC"

#AS=tcc         # bsetup.s:112: error: constant expected
AS="as --32"
echo " AS=$AS"

#LD=gcc
LD=i386-tcc
#LD=ld
echo " LD=$LD"

$CC  -E -P -I../linux/include setup.S -D__ASSEMBLY__ -D__KERNEL__ -D__BIG_KERNEL__ -o bsetup.s
$AS bsetup.s -o bsetup.o

if [ "$LD" = "ld" ]; then
    ld -Ttext=0 --oformat=binary -e begtext -o bsetup bsetup.o
else
    $LD  \
    -nostdlib -nostdinc \
    -static -Wl,-Ttext,0 -Wl,--oformat,binary  \
    -fno-common \
    -D__KERNEL__ -D__OPTIMIZE__ \
    -D__GNUC__=2 -D__GNUC_MINOR__=95 \
    -o bsetup.tcc bsetup.o
    
    dd if=bsetup.tcc of=bsetup bs=1 count=2531 2> /dev/null
    chmod a+x bsetup
    chmod a-x bsetup.tcc
fi

cp bsetup ..
