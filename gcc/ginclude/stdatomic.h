/* Copyright (C) 2013-2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* ISO C11 Standard:  7.17  Atomics <stdatomic.h>.  */

#ifndef _STDATOMIC_H
#define _STDATOMIC_H

/* Macro to test version of GCC.  Returns 0 for non-GCC or too old GCC. */
#ifndef __GNUC_PREREQ
# if defined __GNUC__ && defined __GNUC_MINOR__
#  define __GNUC_PREREQ(maj, min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
# else
#  define __GNUC_PREREQ(maj, min) 0
# endif
#endif /* __GNUC_PREREQ */

#if (__has_extension(c_atomic) || __has_extension(cxx_atomic)) &&              \
    defined(__clang__)
#define __CLANG_ATOMICS
#elif __GNUC_PREREQ(4, 7)
#define __GNUC_ATOMICS
#elif defined(__GNUC__)
#error "stdatomic.h does not support your compiler"
#endif

typedef enum {
  memory_order_relaxed = __ATOMIC_RELAXED,
  memory_order_consume = __ATOMIC_CONSUME,
  memory_order_acquire = __ATOMIC_ACQUIRE,
  memory_order_release = __ATOMIC_RELEASE,
  memory_order_acq_rel = __ATOMIC_ACQ_REL,
  memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

typedef _Atomic _Bool atomic_bool;
typedef _Atomic char atomic_char;
typedef _Atomic signed char atomic_schar;
typedef _Atomic unsigned char atomic_uchar;
typedef _Atomic short atomic_short;
typedef _Atomic unsigned short atomic_ushort;
typedef _Atomic int atomic_int;
typedef _Atomic unsigned int atomic_uint;
typedef _Atomic long atomic_long;
typedef _Atomic unsigned long atomic_ulong;
typedef _Atomic long long atomic_llong;
typedef _Atomic unsigned long long atomic_ullong;
#ifdef __CHAR8_TYPE__
typedef _Atomic __CHAR8_TYPE__ atomic_char8_t;
#endif
typedef _Atomic __CHAR16_TYPE__ atomic_char16_t;
typedef _Atomic __CHAR32_TYPE__ atomic_char32_t;
typedef _Atomic __WCHAR_TYPE__ atomic_wchar_t;
typedef _Atomic __INT_LEAST8_TYPE__ atomic_int_least8_t;
typedef _Atomic __UINT_LEAST8_TYPE__ atomic_uint_least8_t;
typedef _Atomic __INT_LEAST16_TYPE__ atomic_int_least16_t;
typedef _Atomic __UINT_LEAST16_TYPE__ atomic_uint_least16_t;
typedef _Atomic __INT_LEAST32_TYPE__ atomic_int_least32_t;
typedef _Atomic __UINT_LEAST32_TYPE__ atomic_uint_least32_t;
typedef _Atomic __INT_LEAST64_TYPE__ atomic_int_least64_t;
typedef _Atomic __UINT_LEAST64_TYPE__ atomic_uint_least64_t;
typedef _Atomic __INT_FAST8_TYPE__ atomic_int_fast8_t;
typedef _Atomic __UINT_FAST8_TYPE__ atomic_uint_fast8_t;
typedef _Atomic __INT_FAST16_TYPE__ atomic_int_fast16_t;
typedef _Atomic __UINT_FAST16_TYPE__ atomic_uint_fast16_t;
typedef _Atomic __INT_FAST32_TYPE__ atomic_int_fast32_t;
typedef _Atomic __UINT_FAST32_TYPE__ atomic_uint_fast32_t;
typedef _Atomic __INT_FAST64_TYPE__ atomic_int_fast64_t;
typedef _Atomic __UINT_FAST64_TYPE__ atomic_uint_fast64_t;
typedef _Atomic __INTPTR_TYPE__ atomic_intptr_t;
typedef _Atomic __UINTPTR_TYPE__ atomic_uintptr_t;
typedef _Atomic __SIZE_TYPE__ atomic_size_t;
typedef _Atomic __PTRDIFF_TYPE__ atomic_ptrdiff_t;
typedef _Atomic __INTMAX_TYPE__ atomic_intmax_t;
typedef _Atomic __UINTMAX_TYPE__ atomic_uintmax_t;

#if !(defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L)
#define ATOMIC_VAR_INIT(VALUE) (VALUE)
#endif

/* Initialize an atomic object pointed to by PTR with VAL.  */
#define atomic_init(PTR, VAL) atomic_store_explicit(PTR, VAL, __ATOMIC_RELAXED)

#define kill_dependency(Y)                                                     \
  __extension__({                                                              \
    __auto_type __kill_dependency_tmp = (Y);                                   \
    __kill_dependency_tmp;                                                     \
  })

extern void atomic_thread_fence(memory_order);
extern void atomic_signal_fence(memory_order);
#if defined(__CLANG_ATOMICS)
#define atomic_thread_fence(MO) __c11_atomic_thread_fence(MO)
#define atomic_signal_fence(MO) __c11_atomic_signal_fence(MO)
#else
#define atomic_thread_fence(MO) __atomic_thread_fence(MO)
#define atomic_signal_fence(MO) __atomic_signal_fence(MO)
#endif
#define atomic_is_lock_free(OBJ) __atomic_is_lock_free(sizeof(*(OBJ)), (OBJ))

#define ATOMIC_BOOL_LOCK_FREE __GCC_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE __GCC_ATOMIC_CHAR_LOCK_FREE
#ifdef __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#define ATOMIC_CHAR8_T_LOCK_FREE __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#endif
#define ATOMIC_CHAR16_T_LOCK_FREE __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE __GCC_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE __GCC_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE __GCC_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE __GCC_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE __GCC_ATOMIC_POINTER_LOCK_FREE

/* Note that these macros require __auto_type to remove
   _Atomic qualifiers (and const qualifiers, if those are valid on
   macro operands).

   Also note that the header file uses the generic form of __atomic
   builtins, which requires the address to be taken of the value
   parameter, and then we pass that value on.  This allows the macros
   to work for any type, and the compiler is smart enough to convert
   these to lock-free _N variants if possible, and throw away the
   temps.  */

#if defined(__CLANG_ATOMICS)
#define atomic_store_explicit(PTR, VAL, MO) __c11_atomic_store(PTR, VAL, MO)
#define atomic_load_explicit(PTR, MO) __c11_atomic_load(PTR, MO)
#define atomic_exchange_explicit(PTR, VAL, MO)                                 \
  __c11_atomic_exchange(PTR, VAL, MO)
#define atomic_compare_exchange_strong_explicit(PTR, VAL, DES, SUC, FAIL)      \
  __c11_atomic_compare_exchange_strong(PTR, VAL, DES, SUC, FAIL)
#define atomic_compare_exchange_weak_explicit(PTR, VAL, DES, SUC, FAIL)        \
  __c11_atomic_compare_exchange_weak(PTR, VAL, DES, SUC, FAIL)
#define atomic_fetch_add(PTR, VAL)                                             \
  __c11_atomic_fetch_add(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(PTR, VAL, MO)                                \
  __c11_atomic_fetch_add(PTR, VAL, MO)
#define atomic_fetch_sub(PTR, VAL)                                             \
  __c11_atomic_fetch_sub(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(PTR, VAL, MO)                                \
  __c11_atomic_fetch_sub(PTR, VAL, MO)
#define atomic_fetch_or(PTR, VAL)                                              \
  __c11_atomic_fetch_or(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(PTR, VAL, MO)                                 \
  __c11_atomic_fetch_or(PTR, VAL, MO)
#define atomic_fetch_xor(PTR, VAL)                                             \
  __c11_atomic_fetch_xor(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(PTR, VAL, MO)                                \
  __c11_atomic_fetch_xor(PTR, VAL, MO)
#define atomic_fetch_and(PTR, VAL)                                             \
  __c11_atomic_fetch_and(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(PTR, VAL, MO)                                \
  __c11_atomic_fetch_and(PTR, VAL, MO)

#else /* defined(__CLANG_ATOMICS) */

#define atomic_store_explicit(PTR, VAL, MO) __atomic_store_n(PTR, VAL, MO)
#define atomic_load_explicit(PTR, MO) __atomic_load_n(PTR, MO)
#define atomic_exchange_explicit(PTR, VAL, MO) __atomic_exchange_n(PTR, VAL, MO)
#define atomic_compare_exchange_strong_explicit(PTR, VAL, DES, SUC, FAIL)      \
  __atomic_compare_exchange_n(PTR, VAL, DES, 0, SUC, FAIL)
#define atomic_compare_exchange_weak_explicit(PTR, VAL, DES, SUC, FAIL)        \
  __atomic_compare_exchange_n(PTR, VAL, DES, 1, SUC, FAIL)
#define atomic_fetch_add(PTR, VAL)                                             \
  __atomic_fetch_add(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(PTR, VAL, MO) __atomic_fetch_add(PTR, VAL, MO)
#define atomic_fetch_sub(PTR, VAL)                                             \
  __atomic_fetch_sub(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(PTR, VAL, MO) __atomic_fetch_sub(PTR, VAL, MO)
#define atomic_fetch_or(PTR, VAL) __atomic_fetch_or(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(PTR, VAL, MO) __atomic_fetch_or(PTR, VAL, MO)
#define atomic_fetch_xor(PTR, VAL)                                             \
  __atomic_fetch_xor(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(PTR, VAL, MO) __atomic_fetch_xor(PTR, VAL, MO)
#define atomic_fetch_and(PTR, VAL)                                             \
  __atomic_fetch_and(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(PTR, VAL, MO) __atomic_fetch_and(PTR, VAL, MO)

#endif /* defined(__CLANG_ATOMICS) */

#define atomic_store(PTR, VAL) atomic_store_explicit(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_load(PTR) atomic_load_explicit(PTR, __ATOMIC_SEQ_CST)
#define atomic_exchange(PTR, VAL)                                              \
  atomic_exchange_explicit(PTR, VAL, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_strong(PTR, VAL, DES)                          \
  atomic_compare_exchange_strong_explicit(PTR, VAL, DES, __ATOMIC_SEQ_CST,     \
                                          __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak(PTR, VAL, DES)                            \
  atomic_compare_exchange_weak_explicit(PTR, VAL, DES, __ATOMIC_SEQ_CST,       \
                                        __ATOMIC_SEQ_CST)

typedef _Atomic struct {
  atomic_bool __flag;
} atomic_flag;

#define ATOMIC_FLAG_INIT {0}

#if defined(__CLANG_ATOMICS)
static __inline _Bool
atomic_flag_test_and_set_explicit(volatile atomic_flag *__object,
                                  memory_order __order) {
  return atomic_exchange_explicit(&__object->__flag, 1, __order);
}

static __inline void atomic_flag_clear_explicit(volatile atomic_flag *__object,
                                                memory_order __order) {

  atomic_store_explicit(&__object->__flag, 0, __order);
}

#ifndef _KERNEL
static __inline _Bool atomic_flag_test_and_set(volatile atomic_flag *__object) {

  return (atomic_flag_test_and_set_explicit(__object, memory_order_seq_cst));
}

static __inline void atomic_flag_clear(volatile atomic_flag *__object) {

  atomic_flag_clear_explicit(__object, memory_order_seq_cst);
}
#endif /* !_KERNEL */

#else /* __CLANG_ATOMICS */

extern _Bool atomic_flag_test_and_set (volatile atomic_flag *);
#define atomic_flag_test_and_set(PTR)                                   \
                        __atomic_test_and_set ((PTR), __ATOMIC_SEQ_CST)
extern _Bool atomic_flag_test_and_set_explicit (volatile atomic_flag *,
                                                memory_order);
#define atomic_flag_test_and_set_explicit(PTR, MO)                      \
                        __atomic_test_and_set ((PTR), (MO))

extern void atomic_flag_clear (volatile atomic_flag *);
#define atomic_flag_clear(PTR)  __atomic_clear ((PTR), __ATOMIC_SEQ_CST)
extern void atomic_flag_clear_explicit (volatile atomic_flag *, memory_order);
#define atomic_flag_clear_explicit(PTR, MO)   __atomic_clear ((PTR), (MO))

#endif /* __CLANG_ATOMICS */

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
#define __STDC_VERSION_STDATOMIC_H__ 202311L
#endif

#endif /* _STDATOMIC_H */
