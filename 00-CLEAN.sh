#!/bin/bash

rm bbootsect bsetup build LOG ./bin/bzImage ./bin/tccboot.iso 2> /dev/null
cd ./BBOOTSECT; ./02-CLEAN.sh; cd ..
cd ./BSETUP; ./02-CLEAN.sh; cd ..
cd ./BUILD; .//02-CLEAN.sh; cd ..
[ -d temp ] && rm -r temp
rm *.log 2> /dev/null
git checkout -- bin/boot/grub/stage2_eltorito

pushd linux 1> /dev/null 
./00-CLEAN.sh > /dev/null 2>&1
popd 1> /dev/null
