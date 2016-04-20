# bash

[ ! -f bbootsect ] && {
    echo "error: no bbootsect"
    exit 1
}
[ ! -f bsetup ] && {
    echo "error: no bsetup"
    exit 1
}

if [ -z "$CC" ]; then
    CC=tcc
fi

if [ "$CC" = "tcc" ]; then
    CC="i386-tcc -D__GNUC__=2 -D__GNUC_MINOR__=95 -fold-struct-init-code"
    CCLIB="/usr/local/lib/tcc/i386/libtcc1.a"
fi

if [ "$CC" = "gcc" ]; then
    # gcc-3.4.6 or gcc-4.1.2
    CC="gcc -e startup_32 -O2 -fno-strict-aliasing -fno-common -fomit-frame-pointer \
        -pipe -mpreferred-stack-boundary=2 -march=i486 -Tstandalone/vmlinux.lds"
    CCLIB=""
fi

KERNEL=vmlinux
KERNEL_BOOT=bin/bzImage
[ -f "$KERNEL" ] && rm "$KERNEL"
[ -f "$KERNEL_BOOT" ] && rm "$KERNEL_BOOT"

FILE_LIST_1="
standalone/kstart.S
linux/arch/i386/kernel/head.S"

FILE_LIST_2="
linux/arch/i386/kernel/init_task.c
linux/init/main.c
linux/init/version.c
linux/init/do_mounts.c
linux/fs/proc/inode.c
linux/fs/proc/root.c
linux/fs/proc/base.c
linux/fs/proc/generic.c
linux/fs/proc/array.c
linux/fs/proc/kmsg.c
linux/fs/proc/proc_tty.c
linux/fs/proc/proc_misc.c
linux/fs/proc/kcore.c
linux/fs/isofs/namei.c
linux/fs/isofs/inode.c
linux/fs/isofs/dir.c
linux/fs/isofs/util.c
linux/fs/isofs/rock.c
linux/fs/ext2/balloc.c
linux/fs/ext2/bitmap.c
linux/fs/ext2/dir.c
linux/fs/ext2/file.c
linux/fs/ext2/fsync.c
linux/fs/ext2/ialloc.c
linux/fs/ext2/inode.c
linux/fs/ext2/ioctl.c
linux/fs/ext2/namei.c
linux/fs/ext2/super.c
linux/fs/ext2/symlink.c
linux/fs/devpts/root.c 
linux/fs/devpts/inode.c
linux/fs/partitions/check.c
linux/fs/partitions/msdos.c
linux/fs/ramfs/inode.c
linux/fs/romfs/inode.c
linux/fs/open.c
linux/fs/read_write.c
linux/fs/devices.c
linux/fs/file_table.c
linux/fs/buffer.c
linux/fs/super.c
linux/fs/block_dev.c
linux/fs/char_dev.c
linux/fs/stat.c
linux/fs/exec.c
linux/fs/pipe.c
linux/fs/namei.c
linux/fs/fcntl.c
linux/fs/ioctl.c
linux/fs/readdir.c
linux/fs/select.c
linux/fs/fifo.c
linux/fs/locks.c
linux/fs/dcache.c
linux/fs/inode.c
linux/fs/attr.c
linux/fs/bad_inode.c
linux/fs/file.c
linux/fs/iobuf.c
linux/fs/dnotify.c
linux/fs/filesystems.c
linux/fs/namespace.c
linux/fs/seq_file.c
linux/fs/xattr.c
linux/fs/quota.c
linux/fs/binfmt_script.c
linux/fs/binfmt_elf.c
linux/kernel/sched.c
linux/kernel/dma.c
linux/kernel/fork.c
linux/kernel/exec_domain.c
linux/kernel/panic.c
linux/kernel/printk.c
linux/kernel/module.c
linux/kernel/exit.c
linux/kernel/itimer.c
linux/kernel/info.c
linux/kernel/time.c
linux/kernel/softirq.c
linux/kernel/resource.c
linux/kernel/sysctl.c
linux/kernel/acct.c
linux/kernel/capability.c
linux/kernel/ptrace.c
linux/kernel/timer.c
linux/kernel/user.c
linux/kernel/signal.c
linux/kernel/sys.c
linux/kernel/kmod.c
linux/kernel/context.c
linux/kernel/uid16.c
linux/lib/errno.c
linux/lib/ctype.c
linux/lib/string.c
linux/lib/vsprintf.c
linux/lib/brlock.c
linux/lib/cmdline.c
linux/lib/rbtree.c
linux/lib/rwsem.c
linux/lib/dec_and_lock.c
linux/lib/crc32.c
linux/mm/memory.c
linux/mm/mmap.c
linux/mm/filemap.c
linux/mm/mprotect.c
linux/mm/mlock.c
linux/mm/mremap.c
linux/mm/vmalloc.c
linux/mm/slab.c
linux/mm/bootmem.c
linux/mm/swap.c
linux/mm/vmscan.c
linux/mm/page_io.c
linux/mm/page_alloc.c
linux/mm/swap_state.c
linux/mm/swapfile.c
linux/mm/numa.c
linux/mm/oom_kill.c
linux/mm/shmem.c
linux/net/unix/af_unix.c
linux/net/unix/garbage.c
linux/net/unix/sysctl_net_unix.c
linux/net/802/p8023.c
linux/net/802/sysctl_net_802.c
linux/net/core/sock.c
linux/net/core/skbuff.c
linux/net/core/iovec.c
linux/net/core/datagram.c
linux/net/core/scm.c
linux/net/core/sysctl_net_core.c
linux/net/core/dev.c
linux/net/core/ethtool.c
linux/net/core/dev_mcast.c
linux/net/core/dst.c
linux/net/core/neighbour.c
linux/net/core/rtnetlink.c
linux/net/core/utils.c
linux/net/ethernet/eth.c
linux/net/ethernet/sysctl_net_ether.c
linux/net/ipv4/utils.c
linux/net/ipv4/route.c
linux/net/ipv4/inetpeer.c
linux/net/ipv4/proc.c
linux/net/ipv4/protocol.c
linux/net/ipv4/ip_input.c
linux/net/ipv4/ip_fragment.c
linux/net/ipv4/ip_forward.c
linux/net/ipv4/ip_options.c
linux/net/ipv4/ip_output.c
linux/net/ipv4/ip_sockglue.c
linux/net/ipv4/tcp.c
linux/net/ipv4/tcp_input.c
linux/net/ipv4/tcp_output.c
linux/net/ipv4/tcp_timer.c
linux/net/ipv4/tcp_ipv4.c
linux/net/ipv4/tcp_minisocks.c
linux/net/ipv4/tcp_diag.c
linux/net/ipv4/raw.c
linux/net/ipv4/udp.c
linux/net/ipv4/arp.c
linux/net/ipv4/icmp.c
linux/net/ipv4/devinet.c
linux/net/ipv4/af_inet.c
linux/net/ipv4/igmp.c
linux/net/ipv4/sysctl_net_ipv4.c
linux/net/ipv4/fib_frontend.c
linux/net/ipv4/fib_semantics.c
linux/net/ipv4/fib_hash.c
linux/net/netlink/af_netlink.c
linux/net/packet/af_packet.c
linux/net/sched/sch_generic.c
linux/net/socket.c
linux/net/sysctl_net.c
linux/ipc/util.c
linux/ipc/msg.c
linux/ipc/sem.c
linux/ipc/shm.c
linux/drivers/block/ll_rw_blk.c
linux/drivers/block/blkpg.c
linux/drivers/block/genhd.c
linux/drivers/block/elevator.c
linux/drivers/block/floppy.c
linux/drivers/block/rd.c
linux/drivers/block/loop.c
linux/drivers/char/mem.c
linux/drivers/char/tty_io.c
linux/drivers/char/n_tty.c
linux/drivers/char/tty_ioctl.c
linux/drivers/char/raw.c
linux/drivers/char/pty.c
linux/drivers/char/misc.c
linux/drivers/char/random.c
linux/drivers/char/vt.c
linux/drivers/char/vc_screen.c
linux/drivers/char/consolemap.c
linux/drivers/char/consolemap_deftbl.c
linux/drivers/char/console.c
linux/drivers/char/selection.c
linux/drivers/char/serial.c
linux/drivers/char/keyboard.c
linux/drivers/char/defkeymap.c
linux/drivers/char/pc_keyb.c
linux/drivers/cdrom/cdrom.c
linux/drivers/ide/ide-iops.c
linux/drivers/ide/ide-taskfile.c
linux/drivers/ide/ide.c
linux/drivers/ide/ide-lib.c
linux/drivers/ide/ide-io.c
linux/drivers/ide/ide-default.c
linux/drivers/ide/ide-probe.c
linux/drivers/ide/ide-geometry.c
linux/drivers/ide/ide-proc.c
linux/drivers/ide/ide-disk.c
linux/drivers/ide/ide-cd.c
linux/drivers/ide/ide-probe-mini.c
linux/drivers/net/Space.c
linux/drivers/net/setup.c
linux/drivers/net/net_init.c
linux/drivers/net/loopback.c
linux/drivers/net/dummy.c
linux/drivers/net/auto_irq.c
linux/drivers/video/vgacon.c
linux/arch/i386/mm/init.c
linux/arch/i386/mm/fault.c
linux/arch/i386/mm/ioremap.c
linux/arch/i386/mm/extable.c
linux/arch/i386/mm/pageattr.c
linux/arch/i386/lib/old-checksum.c
linux/arch/i386/lib/delay.c
linux/arch/i386/lib/usercopy.c
linux/arch/i386/lib/memcpy.c
linux/arch/i386/lib/strstr.c
linux/arch/i386/kernel/process.c
linux/arch/i386/kernel/semaphore.c
linux/arch/i386/kernel/signal.c
linux/arch/i386/kernel/traps.c
linux/arch/i386/kernel/irq.c
linux/arch/i386/kernel/vm86.c
linux/arch/i386/kernel/ptrace.c
linux/arch/i386/kernel/i8259.c
linux/arch/i386/kernel/ioport.c
linux/arch/i386/kernel/ldt.c
linux/arch/i386/kernel/setup.c
linux/arch/i386/kernel/time.c
linux/arch/i386/kernel/sys_i386.c
linux/arch/i386/kernel/pci-dma.c
linux/arch/i386/kernel/i386_ksyms.c
linux/arch/i386/kernel/i387.c
linux/arch/i386/kernel/bluesmoke.c
linux/arch/i386/kernel/dmi_scan.c"

FILE_LIST_3="
linux/arch/i386/kernel/entry.S
linux/arch/i386/lib/getuser.S
linux/arch/i386/lib/checksum.S"

if [ -n "$CCLIB" ]; then
 FILE_LIST_4="
 standalone/dummy_syms.c"
fi

FILE_LIST_5="
standalone/kend.S"

FILE_LIST_o=
for i in \
    $FILE_LIST_1  \
    $FILE_LIST_2  \
    $FILE_LIST_3  \
    $FILE_LIST_4  \
    $FILE_LIST_5; \
do
    FILE_LIST_o="$FILE_LIST_o temp/$i.o"
done

make CC="$CC" -C linux include/linux/compile.h > /dev/null 2>&1
