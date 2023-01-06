# 1 "interpreter.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "interpreter.c"
# 1 "interpreter.h" 1
       

# 1 "parser.h" 1
       

# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdbool.h" 1 3 4
# 4 "parser.h" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 461 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 452 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 453 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 454 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 462 "/usr/include/features.h" 2 3 4
# 485 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 486 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 26 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 209 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4

# 209 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 321 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef int wchar_t;
# 32 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 1 3 4
# 52 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4
typedef enum
{
  P_ALL,
  P_PID,
  P_PGID
} idtype_t;
# 40 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 55 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 1 3 4
# 120 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 2 3 4
# 121 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 2 3 4
# 56 "/usr/include/stdlib.h" 2 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 97 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 176 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 385 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/x86_64-linux-gnu/sys/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 142 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time64.h" 1 3 4
# 143 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 30 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 97 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/x86_64-linux-gnu/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 127 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 129 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/time_t.h" 1 3 4






typedef __time_t time_t;
# 130 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 131 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
# 144 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 145 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;




# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4


typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 24 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/endian.h" 1 3 4
# 35 "/usr/include/x86_64-linux-gnu/bits/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/endianness.h" 1 3 4
# 36 "/usr/include/x86_64-linux-gnu/bits/endian.h" 2 3 4
# 25 "/usr/include/endian.h" 2 3 4
# 35 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/x86_64-linux-gnu/bits/uintn-identity.h" 3 4
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/sys/select.h" 1 3 4
# 30 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/select.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/select.h" 2 3 4
# 31 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/sigset_t.h" 1 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/x86_64-linux-gnu/bits/types/sigset_t.h" 2 3 4


typedef __sigset_t sigset_t;
# 34 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h" 1 3 4







struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 38 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h" 3 4
struct timespec
{
  __time_t tv_sec;



  __syscall_slong_t tv_nsec;
# 26 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h" 3 4
};
# 40 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4



typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

# 101 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 113 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 126 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

# 180 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 227 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 1 3 4
# 44 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 2 3 4
# 45 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 74 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/struct_mutex.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/struct_mutex.h" 3 4
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 53 "/usr/include/x86_64-linux-gnu/bits/struct_mutex.h" 3 4
};
# 75 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 2 3 4
# 87 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/struct_rwlock.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/struct_rwlock.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 55 "/usr/include/x86_64-linux-gnu/bits/struct_rwlock.h" 3 4
};
# 88 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 2 3 4




struct __pthread_cond_s
{
  __extension__ union
  {
    __extension__ unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union
  {
    __extension__ unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
# 24 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



# 395 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)));



extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));


# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 569 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 647 "/usr/include/stdlib.h" 3 4
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 675 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 688 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 710 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 731 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 784 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;
# 800 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 820 "/usr/include/stdlib.h" 3 4
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 840 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;






extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 872 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));







extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 957 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 1003 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1013 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 1 3 4
# 1014 "/usr/include/stdlib.h" 2 3 4
# 1023 "/usr/include/stdlib.h" 3 4

# 5 "parser.h" 2

# 1 "generated.h" 1





# 5 "generated.h"
typedef enum {
    ExprTag_Unary = 0,
    ExprTag_Binary = 1,
    ExprTag_Call = 2,
    ExprTag_Super = 3,
    ExprTag_Grouping = 4,
    ExprTag_Primary = 5,
} ExprTag;

char* ExprTagToString(ExprTag theEnum);

typedef enum {
    StmtTag_Expr = 0,
    StmtTag_Global = 1,
    StmtTag_For = 2,
    StmtTag_While = 3,
    StmtTag_Do = 4,
    StmtTag_If = 5,
    StmtTag_Switch = 6,
    StmtTag_Array = 7,
} StmtTag;

char* StmtTagToString(StmtTag theEnum);

typedef enum {
    DeclTag_Stmt = 0,
    DeclTag_Fun = 1,
    DeclTag_Proc = 2,
    DeclTag_Class = 3,
} DeclTag;

char* DeclTagToString(DeclTag theEnum);

typedef enum {
    ObjType_Ref = 0,
    ObjType_Class = 1,
    ObjType_Func = 2,
    ObjType_Proc = 3,
    ObjType_NativeFunc = 4,
    ObjType_NativeProc = 5,
    ObjType_Nil = 6,
    ObjType_Bool = 7,
    ObjType_Int = 8,
    ObjType_String = 9,
    ObjType_Float = 10,
    ObjType_Array = 11,
    ObjType_Instance = 12,
} ObjType;

char* ObjTypeToString(ObjType theEnum);
# 7 "parser.h" 2

# 1 "lexer.h" 1
       

# 1 "vector.h" 1


       


# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 43 "/usr/include/string.h" 3 4

# 43 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 91 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 122 "/usr/include/string.h" 3 4
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



# 1 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 154 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 226 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 253 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 273 "/usr/include/string.h" 3 4
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 303 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 330 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 385 "/usr/include/string.h" 3 4
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 410 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)));
# 428 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 433 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 499 "/usr/include/string.h" 3 4

# 7 "vector.h" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 34 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 37 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 44 "/usr/include/stdio.h" 2 3 4
# 52 "/usr/include/stdio.h" 3 4
typedef __gnuc_va_list va_list;
# 84 "/usr/include/stdio.h" 3 4
typedef __fpos_t fpos_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4



extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 173 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void) ;
# 187 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
# 204 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;







extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);
# 227 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 246 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 279 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
# 292 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;





extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
# 379 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));






extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 432 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));




extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 485 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 510 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 521 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 537 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
# 603 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
# 673 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 707 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 731 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 757 "/usr/include/stdio.h" 3 4
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);





# 1 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 782 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 800 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 840 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 858 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 873 "/usr/include/stdio.h" 3 4

# 8 "vector.h" 2
# 52 "vector.h"

# 52 "vector.h"
static void _append(void** vec, void* item, size_t size, int* currentLength, int* currentCapacity) {
    if (*currentLength == *currentCapacity) {
        *vec = realloc(*vec, *currentCapacity * size * 2);
        *currentCapacity *= 2;
    }
    memcpy(&((*(char**)vec)[(*currentLength) * size]), item, size);
    *currentLength += 1;
}
# 4 "lexer.h" 2

typedef enum {

    Tok_Equal, Tok_EqualEqual, Tok_BangEqual, Tok_Less, Tok_LessEqual, Tok_Greater, Tok_GreaterEqual,
    Tok_Plus, Tok_Minus, Tok_Star, Tok_Slash, Tok_Exp,
    Tok_PlusEqual, Tok_MinusEqual, Tok_StarEqual, Tok_SlashEqual, Tok_ExpEqual,
    Tok_Colon, Tok_Dot, Tok_Comma, Tok_LParen, Tok_RParen, Tok_LSquare, Tok_RSquare,


    Tok_Global, Tok_For, Tok_To, Tok_Next, Tok_While, Tok_EndWhile, Tok_Do, Tok_Until, Tok_If, Tok_Then, Tok_ElseIf, Tok_Else, Tok_EndIf,
    Tok_Switch, Tok_Case, Tok_Default, Tok_EndSwitch,
    Tok_And, Tok_Or, Tok_Not, Tok_Mod, Tok_Div,
    Tok_Function, Tok_Return, Tok_EndFunction, Tok_Procedure, Tok_EndProcedure, Tok_ByVal, Tok_ByRef,
    Tok_Class, Tok_EndClass, Tok_Inherits, Tok_Public, Tok_Private, Tok_Super, Tok_Self, Tok_New,
    Tok_Array,


    Tok_True, Tok_False, Tok_StringLit, Tok_IntLit, Tok_FloatLit, Tok_Nil, Tok_Identifier,


    Tok_EOF
} TokType;

typedef struct {
    TokType type;
    char* start;
    int length;
    int line, col;
} Token;

typedef struct TokList { Token* root; int len, cap; Token* elemTempStorage; } TokList; typedef Token _Vec_TokList_Entry;
typedef TokList LexOutput;




char* tokText(Token tok);

void destroyLexOutput(LexOutput lo);
LexOutput lex(char* source);
# 9 "parser.h" 2

# 1 "common.h" 1
       
# 11 "parser.h" 2

typedef struct {
    Token tok;
    char* msg;
} ParseError;

typedef struct ParseErrList { ParseError* root; int len, cap; ParseError* elemTempStorage; } ParseErrList; typedef ParseError _Vec_ParseErrList_Entry;

typedef struct Expression Expression;
typedef struct Declaration Declaration;
typedef struct DeclList DeclList;

typedef struct ExprList { Expression* root; int len, cap; Expression* elemTempStorage; } ExprList; typedef Expression _Vec_ExprList_Entry;

typedef struct {
    Token operator;
    Expression* operand;
} UnaryExpr;

typedef struct {
    Token operator;
    Expression* a, * b;
} BinaryExpr;

typedef struct {
    Expression* callee;
    enum { Call_Call, Call_Array, Call_GetMember} tag;
    union {
        ExprList arguments;
        Token memberName;
    };
} CallExpr;

typedef struct {
    Token memberName;
} SuperExpr;

typedef Expression* GroupingExpr;
typedef Token PrimaryExpr;

struct Expression {
    ExprTag tag;
    union {
        UnaryExpr unary;
        BinaryExpr binary;
        CallExpr call;
        SuperExpr super;
        GroupingExpr grouping;
        PrimaryExpr primary;
    };
};

typedef Expression ExprStmt;

typedef struct {
    Token name;
    Expression initializer;
} GlobalStmt;

typedef struct {
    Token iterator;
    Expression min;
    Expression max;
    DeclList* block;
} ForStmt;

typedef struct {
    Expression condition;
    DeclList* block;
} ConditionalBlock;

typedef ConditionalBlock WhileStmt;
typedef ConditionalBlock DoStmt;

typedef struct ElseIfList { ConditionalBlock* root; int len, cap; ConditionalBlock* elemTempStorage; } ElseIfList; typedef ConditionalBlock _Vec_ElseIfList_Entry;

typedef struct {
    ConditionalBlock primary;
    ElseIfList secondary;
    
# 90 "parser.h" 3 4
   _Bool 
# 90 "parser.h"
        hasElse;
    ConditionalBlock else_;
} IfStmt;

typedef struct SwitchCaseList { ConditionalBlock* root; int len, cap; ConditionalBlock* elemTempStorage; } SwitchCaseList; typedef ConditionalBlock _Vec_SwitchCaseList_Entry;

typedef struct {
    Expression expr;
    SwitchCaseList cases;
    
# 99 "parser.h" 3 4
   _Bool 
# 99 "parser.h"
        hasDefault;
    DeclList* default_;
} SwitchStmt;

typedef struct ArrayDimensions { Expression* root; int len, cap; Expression* elemTempStorage; } ArrayDimensions; typedef Expression _Vec_ArrayDimensions_Entry;

typedef struct {
    Token name;
    ArrayDimensions dimensions;
} ArrayStmt;

typedef struct {
    StmtTag tag;
    union {
        ExprStmt expr;
        GlobalStmt global;
        ForStmt for_;
        WhileStmt while_;
        DoStmt do_;
        IfStmt if_;
        SwitchStmt switch_;
        ArrayStmt array;
    };
} Statement;

typedef enum {
    Param_byRef, Param_byVal
} ParamPassMode;

typedef struct {
    Token name;
    ParamPassMode passMode;
} Parameter;

typedef struct ParamList { Parameter* root; int len, cap; Parameter* elemTempStorage; } ParamList; typedef Parameter _Vec_ParamList_Entry;


typedef struct {
    enum { DOR_decl, DOR_return } tag;
    union {
        Declaration* declaration;
        Expression return_;
    };
} DeclOrReturn;

typedef struct FuncDeclList { DeclOrReturn* root; int len, cap; DeclOrReturn* elemTempStorage; } FuncDeclList; typedef DeclOrReturn _Vec_FuncDeclList_Entry;

typedef struct {
    Token name;
    ParamList params;
    FuncDeclList block;
} FunDecl;

typedef struct {
    Token name;
    ParamList params;
    DeclList* block;
} ProcDecl;

typedef struct {

} ClassDecl;

struct Declaration {
    DeclTag tag;
    union {
        Statement stmt;
        FunDecl fun;
        ProcDecl proc;
        ClassDecl class;
    };
};

struct DeclList { Declaration* root; int len, cap; Declaration* elemTempStorage; }; typedef Declaration _Vec_DeclList_Entry;






typedef struct {
    DeclList ast;
    ParseErrList errors;
} ParseOutput;

ParseOutput parse(LexOutput lo);
void destroyParseOutput(ParseOutput po);




static inline Expression* copyExpr(Expression expr) {
    Expression* new = malloc(sizeof(Expression));
    memcpy(new, &expr, sizeof(Expression));
    return new;
}
# 4 "interpreter.h" 2

# 1 "map.h" 1


       
# 6 "interpreter.h" 2


typedef struct InterpreterObj InterpreterObj;
typedef struct ObjList { InterpreterObj* root; int len, cap; InterpreterObj* elemTempStorage; } ObjList; typedef InterpreterObj _Vec_ObjList_Entry;;

typedef struct { char* key; FunDecl value; } _Map_FuncNS_Entry; typedef struct FuncNS { _Map_FuncNS_Entry* root; int len, cap; _Map_FuncNS_Entry* elemTempStorage; } FuncNS; typedef _Map_FuncNS_Entry _Vec_FuncNS_Entry; static inline FuncNS NewFuncNS() { FuncNS out; do { (out).root = malloc(sizeof(*(out).root)); (out).cap = 1; (out).len = 0; (out).elemTempStorage = malloc(sizeof(*(out).root)); } while(0); return out; } static inline void DestroyFuncNS(FuncNS* map) { do { free((*map).root); free((*map).elemTempStorage); } while(0); } static inline FunDecl* FuncNSFind(FuncNS* map, char* key) { for (_Vec_FuncNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) return &entry->value; } return 
# 11 "interpreter.h" 3 4
((void *)0)
# 11 "interpreter.h"
; } static inline FunDecl* FuncNSSet(FuncNS* map, char* key, FunDecl value) { for (_Vec_FuncNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) { entry->value = value; return; } } do { *(*map).elemTempStorage = (((_Map_FuncNS_Entry) {.key = key, .value = value})); _append((void**)&((*map).root), (*map).elemTempStorage, sizeof(*(*map).elemTempStorage), &(*map).len, &(*map).cap); } while(0); return *(map).root[*(map).len - 1]; } static inline void FuncNSRemove(FuncNS* map, char* key) { for (int i = 0; i < map->len; i++) { if (strcmp(map->root[i].key, key) == 0) { do { memcpy(&(*map).root[i], &(*map).root[i + 1], sizeof(*(*map).root) * ((*map).len - i - 1)); (*map).len--; } while(0); return; } } }
typedef struct { char* key; ProcDecl value; } _Map_ProcNS_Entry; typedef struct ProcNS { _Map_ProcNS_Entry* root; int len, cap; _Map_ProcNS_Entry* elemTempStorage; } ProcNS; typedef _Map_ProcNS_Entry _Vec_ProcNS_Entry; static inline ProcNS NewProcNS() { ProcNS out; do { (out).root = malloc(sizeof(*(out).root)); (out).cap = 1; (out).len = 0; (out).elemTempStorage = malloc(sizeof(*(out).root)); } while(0); return out; } static inline void DestroyProcNS(ProcNS* map) { do { free((*map).root); free((*map).elemTempStorage); } while(0); } static inline ProcDecl* ProcNSFind(ProcNS* map, char* key) { for (_Vec_ProcNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) return &entry->value; } return 
# 12 "interpreter.h" 3 4
((void *)0)
# 12 "interpreter.h"
; } static inline ProcDecl* ProcNSSet(ProcNS* map, char* key, ProcDecl value) { for (_Vec_ProcNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) { entry->value = value; return; } } do { *(*map).elemTempStorage = (((_Map_ProcNS_Entry) {.key = key, .value = value})); _append((void**)&((*map).root), (*map).elemTempStorage, sizeof(*(*map).elemTempStorage), &(*map).len, &(*map).cap); } while(0); return *(map).root[*(map).len - 1]; } static inline void ProcNSRemove(ProcNS* map, char* key) { for (int i = 0; i < map->len; i++) { if (strcmp(map->root[i].key, key) == 0) { do { memcpy(&(*map).root[i], &(*map).root[i + 1], sizeof(*(*map).root) * ((*map).len - i - 1)); (*map).len--; } while(0); return; } } }

typedef void (*NativeProc)(ObjList);
typedef InterpreterObj (*NativeFunc)(ObjList);

typedef struct {
    FuncNS funcs;
    ProcNS procs;
} ClassObj;

typedef struct {
    ClassObj class;
} InstanceObj;

struct InterpreterObj {
    ObjType tag;
    union {
        char* string;
        
# 30 "interpreter.h" 3 4
       _Bool 
# 30 "interpreter.h"
            bool_;
        int int_;
        float float_;
        FunDecl func;
        ProcDecl proc;
        NativeFunc nativeFunc;
        NativeProc nativeProc;
        ClassObj class;
        ObjList array;
        InstanceObj instance;
        InterpreterObj* reference;
    };
};

InterpreterObj interpretExpr(Expression expr);

# 45 "interpreter.h" 3 4
_Bool 
# 45 "interpreter.h"
    isTruthy(InterpreterObj obj);
void interpret(ParseOutput po);
# 2 "interpreter.c" 2


# 1 "/usr/include/math.h" 1 3 4
# 27 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/math.h" 2 3 4












# 1 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 2 3 4
# 41 "/usr/include/math.h" 2 3 4
# 138 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/flt-eval-method.h" 1 3 4
# 139 "/usr/include/math.h" 2 3 4
# 149 "/usr/include/math.h" 3 4

# 149 "/usr/include/math.h" 3 4
typedef float float_t;
typedef double double_t;
# 190 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/fp-logb.h" 1 3 4
# 191 "/usr/include/math.h" 2 3 4
# 233 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/fp-fast.h" 1 3 4
# 234 "/usr/include/math.h" 2 3 4
# 289 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __iseqsig (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignaling (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 290 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));




extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 211 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));





extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));




extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));





extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));







extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 272 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));
# 290 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));
# 400 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
# 291 "/usr/include/math.h" 2 3 4
# 306 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __iseqsigf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 307 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));





 extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));






 extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));




extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 211 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));





extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));




extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));





extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));







extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 272 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));
# 290 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));
# 400 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));
# 308 "/usr/include/math.h" 2 3 4
# 349 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __iseqsigl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 350 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 211 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));




extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));







extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 272 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
# 290 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));
# 400 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
# 351 "/usr/include/math.h" 2 3 4
# 420 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitef128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __isnanf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __iseqsigf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 421 "/usr/include/math.h" 2 3 4
# 773 "/usr/include/math.h" 3 4
extern int signgam;
# 853 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN =

      0,
    FP_INFINITE =

      1,
    FP_ZERO =

      2,
    FP_SUBNORMAL =

      3,
    FP_NORMAL =

      4
  };
# 1338 "/usr/include/math.h" 3 4

# 5 "interpreter.c" 2


# 1 "panic.h" 1
       

# 1 "/usr/include/setjmp.h" 1 3 4
# 27 "/usr/include/setjmp.h" 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 2 3 4




typedef long int __jmp_buf[8];
# 30 "/usr/include/setjmp.h" 2 3 4



struct __jmp_buf_tag
  {




    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };


typedef struct __jmp_buf_tag jmp_buf[1];



extern int setjmp (jmp_buf __env) __attribute__ ((__nothrow__));




extern int __sigsetjmp (struct __jmp_buf_tag __env[1], int __savemask) __attribute__ ((__nothrow__));



extern int _setjmp (struct __jmp_buf_tag __env[1]) __attribute__ ((__nothrow__));
# 67 "/usr/include/setjmp.h" 3 4
extern void longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));





extern void _longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));







typedef struct __jmp_buf_tag sigjmp_buf[1];
# 93 "/usr/include/setjmp.h" 3 4
extern void siglongjmp (sigjmp_buf __env, int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
# 103 "/usr/include/setjmp.h" 3 4

# 4 "panic.h" 2
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4







# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdint.h" 2 3 4
# 5 "panic.h" 2
# 15 "panic.h"

# 15 "panic.h"
typedef enum {
    Panic_Main = 1,
    Panic_Parser = 2,
    Panic_Interpreter = 3,
    Panic_Stdlib = 4,
    Panic_Test = 5
} PanicCode;


typedef enum {
    PCC_InterpreterUnknownVar,
    PCC_Test
} PanicCatchableCode;







extern jmp_buf _panicJump;
# 57 "panic.h"
void _catchPanic();
void _releasePanic();
void _panicFailure(uint16_t code);

void panic(uint16_t code, char* msg, ...);
# 8 "interpreter.c" 2
# 1 "ocrpi_stdlib.h" 1
       



void stl_print(ObjList args);
InterpreterObj stl_typeof(ObjList args);

InterpreterObj stl_bool(ObjList args);
InterpreterObj stl_string(ObjList args);
InterpreterObj stl_float(ObjList args);
InterpreterObj stl_int(ObjList args);
# 9 "interpreter.c" 2

typedef struct { char* key; InterpreterObj value; } _Map_ObjNS_Entry; typedef struct ObjNS { _Map_ObjNS_Entry* root; int len, cap; _Map_ObjNS_Entry* elemTempStorage; } ObjNS; typedef _Map_ObjNS_Entry _Vec_ObjNS_Entry; static inline ObjNS NewObjNS() { ObjNS out; do { (out).root = malloc(sizeof(*(out).root)); (out).cap = 1; (out).len = 0; (out).elemTempStorage = malloc(sizeof(*(out).root)); } while(0); return out; } static inline void DestroyObjNS(ObjNS* map) { do { free((*map).root); free((*map).elemTempStorage); } while(0); } static inline InterpreterObj* ObjNSFind(ObjNS* map, char* key) { for (_Vec_ObjNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) return &entry->value; } return 
# 10 "interpreter.c" 3 4
((void *)0)
# 10 "interpreter.c"
; } static inline InterpreterObj* ObjNSSet(ObjNS* map, char* key, InterpreterObj value) { for (_Vec_ObjNS_Entry* entry = (*map).root; entry - (*map).root < (*map).len; entry++) { if (strcmp(entry->key, key) == 0) { entry->value = value; return; } } do { *(*map).elemTempStorage = (((_Map_ObjNS_Entry) {.key = key, .value = value})); _append((void**)&((*map).root), (*map).elemTempStorage, sizeof(*(*map).elemTempStorage), &(*map).len, &(*map).cap); } while(0); return *(map).root[*(map).len - 1]; } static inline void ObjNSRemove(ObjNS* map, char* key) { for (int i = 0; i < map->len; i++) { if (strcmp(map->root[i].key, key) == 0) { do { memcpy(&(*map).root[i], &(*map).root[i + 1], sizeof(*(*map).root) * ((*map).len - i - 1)); (*map).len--; } while(0); return; } } };

typedef struct Scope Scope;

struct Scope {
    ObjNS objects;
    Scope* parent;
};

static Scope* currentScope = 
# 19 "interpreter.c" 3 4
                            ((void *)0)
# 19 "interpreter.c"
                                ;
static Scope* globalScope = 
# 20 "interpreter.c" 3 4
                           ((void *)0)
# 20 "interpreter.c"
                               ;

static Scope* newScope() {
    Scope* out = malloc(sizeof(Scope));
    out->objects = NewObjNS();
    return out;
}

static void destroyScope(Scope* scope) {
    do { free((scope->objects).root); free((scope->objects).elemTempStorage); } while(0);
    free(scope);
}

static void pushScope() {
    Scope* oldScope = currentScope;
    currentScope = newScope();
    currentScope->parent = oldScope;
    if (oldScope == 
# 37 "interpreter.c" 3 4
                   ((void *)0)
# 37 "interpreter.c"
                       ) globalScope = currentScope;
}

static void popScope() {
    if (currentScope == 
# 41 "interpreter.c" 3 4
                       ((void *)0)
# 41 "interpreter.c"
                           ) panic(Panic_Interpreter, "Can't exit the root scope!");
    Scope* parentScope = currentScope->parent;
    destroyScope(currentScope);
    currentScope = parentScope;
}


InterpreterObj interpretExpr(Expression expr);
static inline InterpreterObj IOAbs(InterpreterObj obj);

# 50 "interpreter.c" 3 4
_Bool 
# 50 "interpreter.c"
    isTruthy(InterpreterObj obj);
static void interpretDecl(Declaration decl);
static void interpretBlock(DeclList block);

static inline InterpreterObj* findObj(char* name) {
    Scope* searchScope = currentScope;
    InterpreterObj* obj = 
# 56 "interpreter.c" 3 4
                         ((void *)0)
# 56 "interpreter.c"
                             ;
    while (searchScope != 
# 57 "interpreter.c" 3 4
                         ((void *)0)
# 57 "interpreter.c"
                             ) {
        obj = ObjNSFind(&searchScope->objects, name);
        if (obj != 
# 59 "interpreter.c" 3 4
                  ((void *)0)
# 59 "interpreter.c"
                      ) break;
        searchScope = searchScope->parent;
    }
    return obj;
}

static inline InterpreterObj* setVar(char* name, InterpreterObj value) {
    InterpreterObj* obj = findObj(name);
    if (obj != 
# 67 "interpreter.c" 3 4
              ((void *)0)
# 67 "interpreter.c"
                  ) {
        *obj = value;
        return obj;
    }

    else return ObjNSSet(&currentScope->objects, name, value);
}


static ObjList parseArgsForNative(CallExpr call) {
    ObjList out;
    do { (out).root = malloc(sizeof(*(out).root)); (out).cap = 1; (out).len = 0; (out).elemTempStorage = malloc(sizeof(*(out).root)); } while(0);
    for (_Vec_ExprList_Entry* current = (call.arguments).root; current - (call.arguments).root < (call.arguments).len; current++) {
        do { *(out).elemTempStorage = (interpretExpr(*current)); _append((void**)&((out).root), (out).elemTempStorage, sizeof(*(out).elemTempStorage), &(out).len, &(out).cap); } while(0);
    }
    return out;
}

static 
# 85 "interpreter.c" 3 4
      _Bool 
# 85 "interpreter.c"
           isExprTruthy(Expression expr) {
    return isTruthy(interpretExpr(expr));
}

static inline InterpreterObj assign(Expression a, InterpreterObj b) {
    InterpreterObj* ref;


    { _catchPanic(); 
# 93 "interpreter.c" 3 4
   _Bool 
# 93 "interpreter.c"
   _panicCaught = 
# 93 "interpreter.c" 3 4
   0
# 93 "interpreter.c"
   ; uint16_t _panicRet = 
# 93 "interpreter.c" 3 4
   _setjmp (
# 93 "interpreter.c"
   _panicJump
# 93 "interpreter.c" 3 4
   )
# 93 "interpreter.c"
   ; ; if (!_panicRet) { {

        InterpreterObj target = interpretExpr(a);
        if (target.tag != ObjType_Ref) panic(Panic_Interpreter, "Can't assign - not an lvalue! (%s)", ExprTagToString(a->tag));
        *target.reference = b;
        ref = target.reference;
    } } else if ((_panicRet & (0b1111111 << 8)) == (PCC_InterpreterUnknownVar << 8)) { _releasePanic(); _panicCaught = 
# 99 "interpreter.c" 3 4
     1
# 99 "interpreter.c"
     ; {




        if (a.tag != ExprTag_Primary) {
            panic(Panic_Interpreter, "This type of value can only be assigned to!");
        }

        setVar(tokText(a.primary), b);
    } } if (!_panicCaught) _panicFailure(_panicRet); }

    return (InterpreterObj)
}

static 
# 114 "interpreter.c" 3 4
      _Bool 
# 114 "interpreter.c"
           equal(InterpreterObj a, InterpreterObj b) {
    if (a.tag != b.tag) return 
# 115 "interpreter.c" 3 4
                              0
# 115 "interpreter.c"
                                   ;
    switch (a.tag) {
        case ObjType_Class:
        case ObjType_Func:
        case ObjType_Proc:
        case ObjType_NativeFunc:
        case ObjType_NativeProc:
        case ObjType_Instance: panic(Panic_Interpreter, "Can't check %s for equality yet!", ObjTypeToString(a.tag));

        case ObjType_Nil: return 
# 124 "interpreter.c" 3 4
                                1
# 124 "interpreter.c"
                                    ;
        case ObjType_Bool: return a.bool_ == b.bool_;
        case ObjType_Int: return a.int_ == b.int_;
        case ObjType_String: return strcmp(a.string, b.string) == 0;
        case ObjType_Float: return a.float_ == b.float_;
        case ObjType_Array: {
            if (a.array.len != b.array.len) return 
# 130 "interpreter.c" 3 4
                                                  0
# 130 "interpreter.c"
                                                       ;
            for (int i = 0; i < a.array.len; i++) {
                if (!equal(a.array.root[i], b.array.root[i])) return 
# 132 "interpreter.c" 3 4
                                                                    0
# 132 "interpreter.c"
                                                                         ;
            }
            return 
# 134 "interpreter.c" 3 4
                  1
# 134 "interpreter.c"
                      ;
        }
    }
}

static 
# 139 "interpreter.c" 3 4
      _Bool 
# 139 "interpreter.c"
           exprEqual(Expression* a, Expression* b) {
    return equal(interpretExpr(*a), interpretExpr(*b));
}
# 166 "interpreter.c"
static InterpreterObj iExponent(InterpreterObj a, InterpreterObj b) { if (a.tag == ObjType_Float) { float aNum = a.float_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Float, .float_ = pow(aNum, bNum)}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Float, .float_ = pow(aNum, bNum)}; } } else if (a.tag == ObjType_Int) { float aNum = a.int_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Int, .int_ = pow(aNum, bNum)}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Int, .int_ = pow(aNum, bNum)}; } } panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); }
static InterpreterObj multiply(InterpreterObj a, InterpreterObj b) { if (a.tag == ObjType_Float) { float aNum = a.float_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum * bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum * bNum}; } } else if (a.tag == ObjType_Int) { float aNum = a.int_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum * bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum * bNum}; } } panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); }
static InterpreterObj divide(InterpreterObj a, InterpreterObj b) { if (a.tag == ObjType_Float) { float aNum = a.float_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum / bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum / bNum}; } } else if (a.tag == ObjType_Int) { float aNum = a.int_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum / bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum / bNum}; } } panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); }
static InterpreterObj subtract(InterpreterObj a, InterpreterObj b) { if (a.tag == ObjType_Float) { float aNum = a.float_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum - bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum - bNum}; } } else if (a.tag == ObjType_Int) { float aNum = a.int_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum - bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum - bNum}; } } panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); }
static InterpreterObj _addNum(InterpreterObj a, InterpreterObj b) { if (a.tag == ObjType_Float) { float aNum = a.float_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum + bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Float, .float_ = aNum + bNum}; } } else if (a.tag == ObjType_Int) { float aNum = a.int_; if (b.tag == ObjType_Float) { float bNum = b.float_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum + bNum}; } else if (b.tag == ObjType_Int) { int bNum = b.int_; return (InterpreterObj){.tag = ObjType_Int, .int_ = aNum + bNum}; } } panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); }

static InterpreterObj add(InterpreterObj a, InterpreterObj b) {
    if (a.tag == ObjType_String && b.tag == ObjType_String) {
        char* out = malloc(strlen(a.string) + strlen(b.string) + 1);
        memcpy(out, a.string, strlen(a.string) + 1);
        strcat(out, b.string);
        return (InterpreterObj){
            .tag = ObjType_String,
            .string = out
        };
    } else if (a.tag == ObjType_Array && b.tag == ObjType_Array) {
        ObjList out;
        do { (out).root = malloc(sizeof(*(out).root)); (out).cap = 1; (out).len = 0; (out).elemTempStorage = malloc(sizeof(*(out).root)); } while(0);
        for (_Vec_ObjList_Entry* obj = (a.array).root; obj - (a.array).root < (a.array).len; obj++) {
            do { *(out).elemTempStorage = (*obj); _append((void**)&((out).root), (out).elemTempStorage, sizeof(*(out).elemTempStorage), &(out).len, &(out).cap); } while(0);
        }
        for (_Vec_ObjList_Entry* obj = (b.array).root; obj - (b.array).root < (b.array).len; obj++) {
            do { *(out).elemTempStorage = (*obj); _append((void**)&((out).root), (out).elemTempStorage, sizeof(*(out).elemTempStorage), &(out).len, &(out).cap); } while(0);
        }
        return (InterpreterObj){
            .tag = ObjType_Array,
            .array = out
        };
    }
    return _addNum(a, b);
}

static 
# 198 "interpreter.c" 3 4
      _Bool 
# 198 "interpreter.c"
           less(InterpreterObj a, InterpreterObj b) {
    if (a.tag == ObjType_Float) {
        if (b.tag == ObjType_Float) return a.float_ < b.float_;
        else if (b.tag == ObjType_Int) return a.float_ < b.int_;
    } else if (a.tag == ObjType_Int) {
        if (b.tag == ObjType_Float) return a.int_ < b.float_;
        else if (b.tag == ObjType_Int) return a.int_ < b.int_;
    }
    panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag));
}

static inline 
# 209 "interpreter.c" 3 4
             _Bool 
# 209 "interpreter.c"
                  greaterEqual(InterpreterObj a, InterpreterObj b) {
    return !less(a, b);
}

static inline 
# 213 "interpreter.c" 3 4
             _Bool 
# 213 "interpreter.c"
                  lessEqual(InterpreterObj a, InterpreterObj b) {
    return less(a, b) || equal(a, b);
}

static inline 
# 217 "interpreter.c" 3 4
             _Bool 
# 217 "interpreter.c"
                  greater(InterpreterObj a, InterpreterObj b) {
    return !lessEqual(a, b);
}



InterpreterObj binaryExpr(TokType operator, Expression a, Expression b) {


    InterpreterObj aRes = interpretExpr(a);
    if (operator != Tok_Equal) aRes = IOAbs(aRes);
    InterpreterObj bRes = IOAbs(interpretExpr(b));

    switch (operator) {
        case Tok_Equal: {
            assign(a, interpretExpr(b));
            break;
        }
        case Tok_ExpEqual: {
            assign(a, binaryExpr(Tok_Exp, a, b));
            break;
        }
        case Tok_StarEqual: {
            assign(a, binaryExpr(Tok_Star, a, b));
            break;
        }
        case Tok_SlashEqual: {
            assign(a, binaryExpr(Tok_Slash, a, b));
            break;
        }
        case Tok_PlusEqual: {
            assign(a, binaryExpr(Tok_Plus, a, b));
            break;
        }
        case Tok_MinusEqual: {
            assign(a, binaryExpr(Tok_Minus, a, b));
            break;
        }

        case Tok_Or: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = isExprTruthy(a) || isExprTruthy(b)};
        case Tok_And: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = isExprTruthy(a) && isExprTruthy(b)};

        case Tok_EqualEqual: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = equal(aRes, bRes)};
        case Tok_BangEqual: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = !equal(aRes, bRes)};

        case Tok_Less: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = less(aRes, bRes)};
        case Tok_LessEqual: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = lessEqual(aRes, bRes)};
        case Tok_Greater: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = greater(aRes, bRes)};
        case Tok_GreaterEqual: return (InterpreterObj){.tag = ObjType_Bool, .bool_ = greaterEqual(aRes, bRes)};

        case Tok_Exp: return iExponent(aRes, bRes);
        case Tok_Star: return multiply(aRes, bRes);
        case Tok_Slash: return divide(aRes, bRes);
        case Tok_Plus: return add(aRes, bRes);
        case Tok_Minus: return subtract(aRes, bRes);
    }




}




InterpreterObj interpretExpr(Expression expr) {
    InterpreterObj out;


    switch (expr.tag) {
        case ExprTag_Unary: {
            break;
        }
        case ExprTag_Binary: {
            out = binaryExpr(expr.binary.operator.type, expr.binary.a, expr.binary.b);
            break;
        }
        case ExprTag_Call: {
            switch (expr.call.tag) {
                case Call_Call: {
                    InterpreterObj calleeObj = IOAbs(interpretExpr(*expr.call.callee));

                    if (!(
                        calleeObj.tag == ObjType_Func ||
                        calleeObj.tag == ObjType_Proc ||
                        calleeObj.tag == ObjType_NativeFunc ||
                        calleeObj.tag == ObjType_NativeProc
                    ))
                        panic(Panic_Interpreter, "Can't call this object!");

                    switch (calleeObj.tag) {
                        case ObjType_Func: {

                            Scope* executionScope = newScope();

                            executionScope->parent = globalScope;

                            if (expr.call.arguments.len != calleeObj.func.params.len)
                                panic(Panic_Interpreter, "Called function %s with %i args instead of %i", tokText(calleeObj.func.name), expr.call.arguments.len, calleeObj.func.params.len);


                            ObjList referenceArgs;
                            do { (referenceArgs).root = malloc(sizeof(*(referenceArgs).root)); (referenceArgs).cap = 1; (referenceArgs).len = 0; (referenceArgs).elemTempStorage = malloc(sizeof(*(referenceArgs).root)); } while(0);


                            for (int i = 0; i < expr.call.arguments.len; i++) {
                                InterpreterObj arg = interpretExpr(expr.call.arguments.root[i]);
                                if (calleeObj.func.params.root[i].passMode == Param_byRef) {
                                    if (!arg.tag == ObjType_Ref) panic(Panic_Interpreter, "Can't pass a %s by reference!", ExprTagToString(expr.call.arguments.root[i].tag));
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj.func.params.root[i].name), (InterpreterObj){
                                        .tag = ObjType_Ref,
                                        .reference = &arg
                                    });
                                } else {
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj.func.params.root[i].name), arg);
                                }
                            }



                            Scope* outerScope = currentScope;
                            currentScope = executionScope;

                            for (_Vec_FuncDeclList_Entry* currentDOR = (calleeObj.func.block).root; currentDOR - (calleeObj.func.block).root < (calleeObj.func.block).len; currentDOR++) {
                                if (currentDOR->tag == DOR_return) {
                                    out = interpretExpr(currentDOR->return_);
                                    destroyScope(executionScope);
                                    currentScope = outerScope;


                                    goto returned;
                                }
                                interpretDecl(*currentDOR->declaration);
                            }


                            panic(Panic_Interpreter, "Function %s must return a value!", tokText(calleeObj.func.name));

                            returned: break;
                        }
                        case ObjType_Proc: {
                            break;
                        }
                        case ObjType_NativeFunc: {
                            ObjList args = parseArgsForNative(expr.call);
                            out = calleeObj.nativeFunc(args);
                            do { free((args).root); free((args).elemTempStorage); } while(0);
                            break;
                        }
                        case ObjType_NativeProc: {
                            ObjList args = parseArgsForNative(expr.call);
                            calleeObj.nativeProc(args);
                            do { free((args).root); free((args).elemTempStorage); } while(0);
                            out = (InterpreterObj){.tag = ObjType_Nil};
                            break;
                        }
                    }
                    break;
                }
                case Call_GetMember: {
                    break;
                }
                case Call_Array: {
                    break;
                }
            }
            break;
        }
        case ExprTag_Super: {
            break;
        }
        case ExprTag_Grouping: {
            interpretExpr(*expr.grouping);
            break;
        }
        case ExprTag_Primary: {
            char* text = tokText(expr.primary);
            switch (expr.primary.type) {

                case Tok_Nil: {
                    out = (InterpreterObj){.tag = ObjType_Nil};
                    break;
                }
                case Tok_True:
                case Tok_False: {
                    out = (InterpreterObj){.tag = ObjType_Bool, .bool_ = expr.primary.type == Tok_True};
                    break;
                }
                case Tok_StringLit: {

                    char* stringContents = malloc(strlen(text) - 1);
                    memcpy(stringContents, text + 1, strlen(text) - 2);
                    stringContents[strlen(text) - 2] = 0;
                    out = (InterpreterObj){.tag = ObjType_String, .string = stringContents};
                    break;
                }
                case Tok_IntLit: {
                    out = (InterpreterObj){.tag = ObjType_Int, .int_ = atoi(text)};
                    break;
                }
                case Tok_FloatLit: {
                    out = (InterpreterObj){.tag = ObjType_Float, .float_ = strtof(text, 
# 418 "interpreter.c" 3 4
                   ((void *)0)
# 418 "interpreter.c"
                   )};
                    break;
                }
                case Tok_Identifier: {
                    InterpreterObj* obj = findObj(text);
                    if (obj == 
# 423 "interpreter.c" 3 4
                              ((void *)0)
# 423 "interpreter.c"
                                  ) panic((1 << 15) | (PCC_InterpreterUnknownVar << 8) | Panic_Interpreter, "Unknown variable %s!", text);
                    out = (InterpreterObj){.tag = ObjType_Ref, .reference = obj};
                    break;
                }
            }
            free(text);
            break;
        }
    }
    return out;


}

static inline InterpreterObj IOAbs(InterpreterObj obj) {
    while (obj.tag == ObjType_Ref) obj = *obj.reference;
    return obj;
}


# 442 "interpreter.c" 3 4
_Bool 
# 442 "interpreter.c"
    isTruthy(InterpreterObj obj) {
    switch (obj.tag) {
        case ObjType_Ref: return isTruthy(*obj.reference);

        case ObjType_Class:
        case ObjType_Func:
        case ObjType_Proc:
        case ObjType_NativeFunc:
        case ObjType_NativeProc:
        case ObjType_Instance: panic(Panic_Interpreter, "Can't (yet) use a %s as a boolean!", ObjTypeToString(obj.tag));

        case ObjType_Nil: return 
# 453 "interpreter.c" 3 4
                                0
# 453 "interpreter.c"
                                     ;
        case ObjType_Bool: return obj.bool_;
        case ObjType_Int: return obj.int_ > 0;
        case ObjType_String: return obj.string[0] != 0;
        case ObjType_Float: return obj.float_ > 0;
        case ObjType_Array: return obj.array.len > 0;
    }
}

static void interpretStmt(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Expr: {
            interpretExpr(stmt.expr);
            break;
        }
        case StmtTag_Global: {
            ObjNSSet(&globalScope->objects, tokText(stmt.global.name), interpretExpr(stmt.global.initializer));
            break;
        }
        case StmtTag_For: {
            pushScope();
            setVar(tokText(stmt.for_.iterator), interpretExpr(stmt.for_.min));
            Expression iterator = (Expression){
                .tag = ExprTag_Primary,
                .primary = stmt.for_.iterator,
            };
            Expression cond = (Expression){
                .tag = ExprTag_Binary,
                .binary = (BinaryExpr){
                    .a = &iterator,
                    .b = &stmt.for_.max,
                    .operator = (Token){
                        .line = 0,
                        .col = 0,
                        .start = "<",
                        .length = 1,
                        .type = Tok_Less
                    }
                }
            };
            Expression incr = (Expression){
                .tag = ExprTag_Binary,
                .binary = (BinaryExpr){
                    .a = &iterator,
                    .b = copyExpr((Expression){
                        .tag = ExprTag_Primary,
                        .primary = (Token){
                            .line = 0,
                            .col = 0,
                            .start = "1",
                            .length = 1,
                            .type = Tok_IntLit
                        }
                    }),
                    .operator = (Token){
                        .line = 0,
                        .col = 0,
                        .start = "+=",
                        .length = 2,
                        .type = Tok_PlusEqual
                    }
                }
            };
            while (isExprTruthy(cond)) {
                interpretBlock(*stmt.for_.block);
                interpretExpr(incr);
            }
            free(incr.binary.b);
            popScope();
            break;
        }
        case StmtTag_While: {
            while (isExprTruthy(stmt.while_.condition)) {
                interpretBlock(*stmt.while_.block);
            }
            break;
        }
        case StmtTag_Do: {

            while (!isExprTruthy(stmt.do_.condition)) {
                interpretBlock(*stmt.do_.block);
            }
            break;
        }
        case StmtTag_If: {
            if (isExprTruthy(stmt.if_.primary.condition)) {
                interpretBlock(*stmt.if_.primary.block);
            } else {
                for (_Vec_ElseIfList_Entry* currentBranch = (stmt.if_.secondary).root; currentBranch - (stmt.if_.secondary).root < (stmt.if_.secondary).len; currentBranch++) {
                    if (isExprTruthy(currentBranch->condition)) {
                        interpretBlock(*currentBranch->block);
                        break;
                    }
                }
                if (stmt.if_.hasElse && isExprTruthy(stmt.if_.else_.condition)) {
                    interpretBlock(*stmt.if_.else_.block);
                }
            }
            break;
        }
        case StmtTag_Switch: {
            break;
        }
        case StmtTag_Array: {
            break;
        }
    }
}

static void interpretProc(ProcDecl proc) {
    setVar(tokText(proc.name), (InterpreterObj){
        .tag = ObjType_Proc,
        .proc = proc
    });
}

static void interpretFun(FunDecl func) {
    setVar(tokText(func.name), (InterpreterObj){
        .tag = ObjType_Func,
        .func = func
    });
}

static void interpretClass(ClassDecl class) {

}

static void interpretDecl(Declaration decl) {
    switch (decl.tag) {
        case DeclTag_Class: {
            interpretClass(decl.class);
            break;
        }
        case DeclTag_Fun: {
            interpretFun(decl.fun);
            break;
        }
        case DeclTag_Proc: {
            interpretProc(decl.proc);
            break;
        }
        case DeclTag_Stmt: {
            interpretStmt(decl.stmt);
            break;
        }
    }
}

static void interpretBlock(DeclList block) {
    for (int i = 0; i < block.len; i++) {
        interpretDecl(block.root[i]);
    }
}

typedef struct {
    char* name;
    NativeFunc func;
} STLFuncDef;

typedef struct {
    char* name;
    NativeProc proc;
} STLProcDef;

static STLFuncDef stl_funcs[] = {
    {"typeof", stl_typeof},
    {"bool", stl_bool},
    {"string", stl_string},
    {"float", stl_float},
    {"int", stl_int},
    {"", 
# 623 "interpreter.c" 3 4
        ((void *)0)
# 623 "interpreter.c"
            }
};

static STLProcDef stl_procs[] = {
    {"print", stl_print},
    {"", 
# 628 "interpreter.c" 3 4
        ((void *)0)
# 628 "interpreter.c"
            }
};

static void setupSTL() {
    for (int i = 0; stl_funcs[i].name[0] != '\0'; i++) {
        setVar(stl_funcs[i].name, (InterpreterObj){
            .tag = ObjType_NativeFunc,
            .nativeFunc = stl_funcs[i].func
        });
    }

    for (int i = 0; stl_procs[i].name[0] != '\0'; i++) {
        setVar(stl_procs[i].name, (InterpreterObj){
            .tag = ObjType_NativeProc,
            .nativeProc = stl_procs[i].proc
        });
    }
}

void interpret(ParseOutput po) {
    pushScope();
    setupSTL();
    interpretBlock(po.ast);
    popScope();
}
