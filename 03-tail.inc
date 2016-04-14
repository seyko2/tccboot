# bash

[ -f "$KERNEL" ] && {
    echo | tee -a LOG
    echo "step B: build" | tee -a LOG
    ./build -b ./bbootsect ./bsetup \
              $KERNEL CURRENT > $KERNEL_BOOT
    rm "$KERNEL"
    cd bin
    ./make_iso.sh
    exit 0
}

echo "error: compilation failed" | tee -a LOG
exit 1
