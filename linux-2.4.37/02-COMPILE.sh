#!/bin/bash

. ./COMPILER.inc

if [ "$CC" = "i386-tcc" ]; then
  HOSTCC="tcc"
  CC="$CC -U__GNUC__ -D__GNUC__=2 -U__GNUC_MINOR__ -D__GNUC_MINOR__=95 -D__OPTIMIZE__ "
  CC="$CC -fold-struct-init-code"
  #CC="$CC -fnocode-if-false"
  CCLIBS=/usr/local/lib/tcc/i386/libtcc1.a
fi

echo CC=$CC HOSTCC="$HOSTCC" | tee LOG
#echo | tee -a LOG
sleep 2

make bzImage CC="$CC" HOSTCC="$HOSTCC" CCLIBS="$CCLIBS" 2>&1 | tee -a LOG
[ -f arch/i386/boot/bzImage ] && {
    mv arch/i386/boot/bzImage ../bin/bzImage
    cd ../bin
    ./make_iso.sh
    exit 0
}

echo "error: compilation failed"
exit 1
