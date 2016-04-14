/* small TinyCC runtime for the Linux kernel */

#define DUMMY(x) const char x = 0xcc;

typedef int Wtype;
typedef unsigned int UWtype;
typedef unsigned int USItype;
typedef long long DWtype;
typedef unsigned long long UDWtype;

struct DWstruct {
    Wtype low, high;
};

typedef union
{
  struct DWstruct s;
  DWtype ll;
} DWunion;

int abs(int a)
{
    if (a < 0)
        return -a;
    else
        return a;
}

/* XXX: fix tcc's code generator to do this instead */
#ifdef __TINYC__
long long __sardi3(long long a, int b)
{
    DWunion u;
    u.ll = a;
    if (b >= 32) {
        u.s.low = u.s.high >> (b - 32);
        u.s.high = u.s.high >> 31;
    } else if (b != 0) {
        u.s.low = ((unsigned)u.s.low >> b) | (u.s.high << (32 - b));
        u.s.high = u.s.high >> b;
    }
    return u.ll;
}
//    return a >> b;
#endif

/* XXX: fix tcc's code generator to do this instead */
#ifdef __TINYC__
long long __shldi3(long long a, int b)
{
    DWunion u;
    u.ll = a;
    if (b >= 32) {
        u.s.high = (unsigned)u.s.low << (b - 32);
        u.s.low = 0;
    } else if (b != 0) {
        u.s.high = ((unsigned)u.s.high << b) | (u.s.low >> (32 - b));
        u.s.low = (unsigned)u.s.low << b;
    }
    return u.ll;
}
//    return a << b;
#endif

/* XXX: fix tcc's code generator to do this instead */
#ifdef __TINYC__
long long __ashrdi3(long long a, int b)
{
    DWunion u;
    u.ll = a;
    if (b >= 32) {
        u.s.low = u.s.high >> (b - 32);
        u.s.high = u.s.high >> 31;
    } else if (b != 0) {
        u.s.low = ((unsigned)u.s.low >> b) | (u.s.high << (32 - b));
        u.s.high = u.s.high >> b;
    }
    return u.ll;
}
//    return a >> b;
#endif

#ifdef __TINYC__
/* XXX: fix tcc's code generator to do this instead */
long long __ashldi3(long long a, int b)
{
    DWunion u;
    u.ll = a;
    if (b >= 32) {
        u.s.high = (unsigned)u.s.low << (b - 32);
        u.s.low = 0;
    } else if (b != 0) {
        u.s.high = ((unsigned)u.s.high << b) | ((unsigned)u.s.low >> (32 - b));
        u.s.low = (unsigned)u.s.low << b;
    }
    return u.ll;
}
//    return a << b;
#endif

#ifdef __TINYC__
void *__builtin_return_address(int a)
{
    return 0;
}
#endif

/* these symbols are needed because TCC is not smart enough to
   suppress unused code */

#ifdef __TINYC__
DUMMY(__skb_cb_too_small_for_tcp)
DUMMY(cookie_v4_init_sequence)
DUMMY(save_i387_soft)
DUMMY(restore_i387_soft)
DUMMY(__this_fixmap_does_not_exist)
DUMMY(__bad_udelay)
DUMMY(__bad_ndelay)
DUMMY(__get_user_bad)
DUMMY(__put_user_bad)
DUMMY(__buggy_fxsr_alignment)
DUMMY(__get_user_X)
DUMMY(__struct_cpy_bug)
DUMMY(netlink_skb_parms_too_large)
#endif
