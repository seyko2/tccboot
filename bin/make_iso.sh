#!/bin/bash
# ---------------------------------------------------
# Script to create bootable ISO in Linux
# usage: make_iso.sh [ /tmp/fantoo.iso ]
# author: Tomas M. <http://www.linux-live.org>
# ---------------------------------------------------
# Fantoo modifications:
#  * use grub as boot loader insteed of isolinux
#  * allow long file names (iso-level 4)
#  * no Joilet
#  * no images, changes,... to iso

if [ "$1" = "--help" -o "$1" = "-h" ]; then
  echo "This script will create bootable ISO from files in curent directory."
  echo "Current directory must be writable."
  echo "example: $0 /mnt/hda5/fantoo.iso"
  exit
fi

MKISOFS=`which mkisofs`
if [ -z "$MKISOFS" ]; then
    echo "WARNING: mkisofs not found, image not created"
    exit
fi

CDLABEL="TCCBOOT"
ISONAME=./tccboot.iso

echo
echo "ISO file name:	$ISONAME"
echo

[ -f "boot/grub/stage2_eltorito.boot" ] && {
    rm boot/grub/stage2_eltorito.boot
}

[ -f "$ISONAME" ] && {
    rm $ISONAME
}

mkisofs \
-o "$ISONAME" \
   -V "$CDLABEL" \
-iso-level 4 \
-R -D \
   -no-emul-boot -boot-info-table -boot-load-size 4 \
   -b boot/grub/stage2_eltorito -c boot/grub/stage2_eltorito.boot \
-graft-points \
    boot=boot \
    make_iso.sh=make_iso.sh \
    READNE=README \
    bzImage=bzImage \
    initrd.ext2.gz=initrd.ext2.gz

#  -o filename                 
# 
#  is the name of the file to which the iso9660 filesystem image should be written.
#  If not specified, stdout is used.

#  -V volid
#
#   Specifies  the  volume  ID  (volume name or label) to be written into the master block.  There is
#   space on the disc for 32 characters of information. Note that if you assign a volume ID, this is
#   the name that will be used as the mount point used by the Solaris volume management system.

# -iso-level 4
#
#   Level 4 officially does not exists but mkisofs maps it to
#   ISO-9660:1999 which is ISO-9660 version 2.
#
#   With level 4, an enhanced volume descriptor with version number and file structure version number
#   set to 2 is emitted.  There may be more than 8 levels of directory nesting, there is no need  for
#   a  file  to contain a dot and the dot has no more special meaning, file names do not have version
#   numbers, the maximum length for files and directory is raised to 207.  If Rock Ridge is used, the
#   maximum ISO-9660 name length is reduced to 197.

#  -R Generate SUSP and RR records using the Rock Ridge protocol to further         
#     describe the files on the iso9660 filesystem.
#
#  SUSP (System Use Sharing Protocol records) specified by the Rock Ridge
#  Interchange Protocol are used to further describe the files in the iso9660
#  filesystem to a unix host, and provides information such as longer filenames,
#  uid/gid, posix permissions, symbolic links, block and character devices.

#  -D Do not use deep directory relocation, and instead just pack them in the
#     way we see them. If ISO9660:1999 has not been selected,this violates
#     the ISO9660 standard, but it happens to work on many systems.

# If  the  option -graft-points has been specified, it is possible to graft the
# paths at points other than the root directory, and it is possible to graft files
# or directories onto the  cdrom  image  with  names different  than what they
# have in the source filesystem.  This is easiest to illustrate with a couple of
# examples.   Let's start by assuming that a local file ../old.lis exists, and you
# wish to include  it  in the cdrom image.
# 
#       foo/bar/=../old.lis
# 
#  will include the file old.lis in the cdrom image at /foo/bar/old.lis, while
# 
#       foo/bar/xxx=../old.lis
# 
# will  include  the file old.lis in the cdrom image at /foo/bar/xxx.  The same
# sort of syntax can be used with directories as well.  mkisofs will create any
# directories required such that the graft points exist on  the cdrom image - the
# directories do not need to appear in one of the paths.  By default, any direc-
# tories that are created on the fly like this will have permissions 0555 and
# appear to be  owned  by  the person  running  mkisofs.   If you wish other
# permissions or owners of the intermediate directories, see
# -uid, -gid, -dir-mode, -file-mode and -new-dir-mode.
