#!/bin/bash

if [ -z "$CC" ]; then
    #CC="gcc-3.4.6"
    CC="i386-tcc"
fi

if [ "$CC" = "tcc" ]; then
    CC="i386-tcc"
fi

if [ "$CC" = "i386-tcc" ]; then
  CC="$CC -U__GNUC__ -D__GNUC__=2 -U__GNUC_MINOR__ -D__GNUC_MINOR__=95 -D__OPTIMIZE__ -fold-struct-init-code"
  CCLIBS=/usr/local/lib/tcc/i386/libtcc1.a
fi

echo CC=$CC | tee LOG
#echo | tee -a LOG
sleep 1

make bzImage CC="$CC" CCLIBS="$CCLIBS" 2>&1 | tee -a LOG
[ -f arch/i386/boot/bzImage ] && {
    mv arch/i386/boot/bzImage ../bin/bzImage
    cd ../bin
    ./make_iso.sh
    exit 0
}

echo "error: compilation failed"
exit 1
