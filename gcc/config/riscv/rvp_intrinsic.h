/* Builtin definitions for P extension
   Copyright (C) 2021 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef _RISCV_RVP_INTRINSIC_H
#define _RISCV_RVP_INTRINSIC_H

#if !defined (__riscv_zpn) && !defined (__riscv_zbpbo)
#error "Packed SIMD intrinsics require either zbpbo or zpn extensions."
#endif

#include <stdint.h>

typedef signed char int8x4_t __attribute ((vector_size(4)));
typedef signed char int8x8_t __attribute ((vector_size(8)));
typedef short int16x2_t __attribute ((vector_size(4)));
typedef short int16x4_t __attribute__((vector_size (8)));
typedef int int32x2_t __attribute__((vector_size(8)));
typedef unsigned char uint8x4_t __attribute__ ((vector_size (4)));
typedef unsigned char uint8x8_t __attribute__ ((vector_size (8)));
typedef unsigned short uint16x2_t __attribute__ ((vector_size (4)));
typedef unsigned short uint16x4_t __attribute__((vector_size (8)));
typedef unsigned int uint32x2_t __attribute__((vector_size(8)));

#if __riscv_xlen == 32
typedef int32_t intXLEN_t;
typedef uint32_t uintXLEN_t;
typedef int32_t int32xN_t;
typedef uint32_t uint32xN_t;
typedef uint16x2_t uint16xN_t;
typedef int16x2_t int16xN_t;
typedef uint8x4_t uint8xN_t;
typedef int8x4_t int8xN_t;
#else
typedef int64_t intXLEN_t;
typedef uint64_t uintXLEN_t;
typedef int32x2_t int32xN_t;
typedef uint32x2_t uint32xN_t;
typedef uint16x4_t uint16xN_t;
typedef int16x4_t int16xN_t;
typedef uint8x8_t uint8xN_t;
typedef int8x8_t int8xN_t;
#endif

#define CREATE_RVP_INTRINSIC_1(ret_type, name, type1) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_##name(type1 a) {\
        return __builtin_riscv_##name(a); \
    }

#define CREATE_RVP_INTRINSIC_2(ret_type, name, type1, type2) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_##name(type1 a, type2 b) {\
        return __builtin_riscv_##name(a, b); \
    }

#define CREATE_RVP_INTRINSIC_3(ret_type, name, type1, type2, type3) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_##name(type1 a, type2 b, type3 c) {\
        return __builtin_riscv_##name(a, b, c); \
    }

#if __riscv_xlen == 32

#define CREATE_RVP_INTRINSIC_VECTOR_1(ret_type, v_name, type1, name, type2) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a) { \
        return (ret_type)__builtin_riscv_v_##v_name(a); \
    }

#define CREATE_RVP_INTRINSIC_VECTOR_2(ret_type, v_name, type1, type2, name, type3, type4) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a, type2 b) { \
        return (ret_type)__builtin_riscv_v_##v_name(a, b); \
    }

#define CREATE_RVP_INTRINSIC_VECTOR_3(ret_type, v_name, type1, type2, type3, name, type4, type5, type6) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a, type2 b, type3 c) { \
        return (ret_type)__builtin_riscv_v_##v_name(a, b, c); \
    }

#else // rv64

#define CREATE_RVP_INTRINSIC_VECTOR_1(ret_type, v_name, type1, name, type2) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a) { \
        return (ret_type)__builtin_riscv_v64_##v_name(a); \
    }

#define CREATE_RVP_INTRINSIC_VECTOR_2(ret_type, v_name, type1, type2, name, type3, type4) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a, type2 b) { \
        return (ret_type)__builtin_riscv_v64_##v_name(a, b); \
    }

#define CREATE_RVP_INTRINSIC_VECTOR_3(ret_type, v_name, type1, type2, type3, name, type4, type5, type6) \
    __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__)) \
    ret_type __rv_v_##v_name(type1 a, type2 b, type3 c) { \
        return (ret_type)__builtin_riscv_v64_##v_name(a, b, c); \
    }
#endif // __riscv_xlen == 32

#if defined(__riscv_zbpbo)
CREATE_RVP_INTRINSIC_1(uint32_t, clz, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pack, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, packu, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(uint32_t, fsr, uint32_t, uint32_t, uint32_t)
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC_3(uint32_t, fsrw, uint32_t, uint32_t, uint32_t)
#endif
CREATE_RVP_INTRINSIC_2(intXLEN_t, max, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, min, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, rev8h, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(uintXLEN_t, cmix, uintXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, rev, uintXLEN_t)
#if !defined(__clang__)
CREATE_RVP_INTRINSIC_VECTOR_1(uint8x4_t,  rev8h,  uint8x4_t,  rev8h,  uintXLEN_t)
#endif
#endif

#if defined(__riscv_zpn)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clrs8, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clrs16, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clrs32, intXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clz8, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clz16, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, clz32, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, kabs8, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, kabs16, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(int32_t, kabsw, int32_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, sunpkd810, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, sunpkd820, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, sunpkd830, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, sunpkd831, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, sunpkd832, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, zunpkd810, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, zunpkd820, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, zunpkd830, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, zunpkd831, uintXLEN_t)
CREATE_RVP_INTRINSIC_1(uintXLEN_t, zunpkd832, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, add8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, add16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, ave, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, bitrev, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, cmpeq8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, cmpeq16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, cras16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, crsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kadd8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kadd16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, kaddh, int16_t, int16_t)
CREATE_RVP_INTRINSIC_2(int32_t, kaddw, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kcras16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kcrsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, kdmbb, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(int32_t, kdmbt, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(int32_t, kdmtt, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, khm8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, khmx8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, khm16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, khmx16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, khmbb, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(int32_t, khmbt, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(int32_t, khmtt, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmda, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmxda, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmmwb2, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmmwb2_u, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmmwt2, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kmmwt2_u, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, ksllw, int32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ksll8, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ksll16, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kslra8, uintXLEN_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kslra8_u, uintXLEN_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kslra16, uintXLEN_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kslra16_u, uintXLEN_t, int32_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kslraw, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kslraw_u, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kstas16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, kstsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ksub8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ksub16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, ksubh, int16_t, int16_t)
CREATE_RVP_INTRINSIC_2(int32_t, ksubw, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kwmmul, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, kwmmul_u, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pbsad, uintXLEN_t, uintXLEN_t)
#if __riscv_xlen == 64 || !defined(__riscv_zbpbo)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pkbb16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pktt16, uintXLEN_t, uintXLEN_t)
#endif
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pkbt16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, pktb16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, radd8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, radd16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, raddw, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rcras16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rcrsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rstas16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rstsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rsub8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, rsub16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(int32_t, rsubw, int32_t, int32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, scmple8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, scmple16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, scmplt8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, scmplt16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sll8, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sll16, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, smax8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, smax16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smbb16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smbt16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smtt16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smds, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smdrs, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smxds, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, smin8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, smin16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmul, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmul_u, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmwb, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmwb_u, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmwt, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, smmwt_u, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, sra_u, intXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sra8, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sra8_u, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sra16, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sra16_u, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, srl8, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, srl8_u, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, srl16, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, srl16_u, uintXLEN_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, stas16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, stsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sub8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sub16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ucmple8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ucmple16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ucmplt8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ucmplt16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukadd8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukadd16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uint32_t, ukaddh, uint16_t, uint16_t)
CREATE_RVP_INTRINSIC_2(uint32_t, ukaddw, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukcras16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukcrsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukstas16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ukstsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uksub8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uksub16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uint32_t, uksubh, uint16_t, uint16_t)
CREATE_RVP_INTRINSIC_2(uint32_t, uksubw, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, umax8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, umax16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, umin8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, umin16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uradd8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uradd16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uint32_t, uraddw, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, urcras16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, urcrsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, urstas16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, urstsa16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ursub8, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, ursub16, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_2(uint32_t, ursubw, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_3(int32_t, kdmabb, int32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_3(int32_t, kdmabt, int32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_3(int32_t, kdmatt, int32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmabb, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmabt, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmatt, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmada, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmaxda, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmads, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmadrs, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmaxds, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmac, intXLEN_t, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmac_u, intXLEN_t, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawb, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawb_u, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawb2, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawb2_u, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawt, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawt_u, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawt2, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmawt2_u, intXLEN_t, intXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmsb, intXLEN_t, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmmsb_u, intXLEN_t, intXLEN_t, intXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmsda, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, kmsxda, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(int32_t, maddr32, int32_t, int32_t, int32_t)
CREATE_RVP_INTRINSIC_3(int32_t, msubr32, int32_t, int32_t, int32_t)
CREATE_RVP_INTRINSIC_3(uintXLEN_t, pbsada, uintXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, smaqa, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(intXLEN_t, smaqa_su, intXLEN_t, uintXLEN_t, uintXLEN_t)
CREATE_RVP_INTRINSIC_3(uintXLEN_t, umaqa, uintXLEN_t, uintXLEN_t, uintXLEN_t)
#if defined(__clang__)
#define __rv_insb __builtin_riscv_insb
#define __rv_sclip8 __builtin_riscv_sclip8
#define __rv_sclip16 __builtin_riscv_sclip16
#define __rv_sclip32 __builtin_riscv_sclip32
#define __rv_uclip8 __builtin_riscv_uclip8
#define __rv_uclip16 __builtin_riscv_uclip16
#define __rv_uclip32 __builtin_riscv_uclip32
#else
CREATE_RVP_INTRINSIC_3(uintXLEN_t, insb, uintXLEN_t, uintXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sclip8, uintXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, sclip16, uintXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(intXLEN_t, sclip32, intXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uclip8, uintXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uclip16, uintXLEN_t, const uint32_t)
CREATE_RVP_INTRINSIC_2(uintXLEN_t, uclip32, intXLEN_t, const uint32_t)
#endif
// Vector is only supported in GCC
#if !defined(__clang__)
CREATE_RVP_INTRINSIC_VECTOR_1(uint8x4_t,  clrs8,  int8x4_t,  clrs8,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  clrs16,  int16x2_t,  clrs16,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint8x4_t,  clz8,  uint8x4_t,  clz8,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  clz16,  uint16x2_t,  clz16,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int8x4_t,  kabs8,  int8x4_t,  kabs8,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  kabs16,  int16x2_t,  kabs16,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  sunpkd810,  int8x4_t,  sunpkd810,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  sunpkd820,  int8x4_t,  sunpkd820,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  sunpkd830,  int8x4_t,  sunpkd830,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  sunpkd831,  int8x4_t,  sunpkd831,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(int16x2_t,  sunpkd832,  int8x4_t,  sunpkd832,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  zunpkd810,  uint8x4_t,  zunpkd810,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  zunpkd820,  uint8x4_t,  zunpkd820,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  zunpkd830,  uint8x4_t,  zunpkd830,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  zunpkd831,  uint8x4_t,  zunpkd831,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_1(uint16x2_t,  zunpkd832,  uint8x4_t,  zunpkd832,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  kadd8,  int8x4_t,  int8x4_t,  kadd8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kadd16,  int16x2_t,  int16x2_t,  kadd16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kcras16,  int16x2_t,  int16x2_t,  kcras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kcrsa16,  int16x2_t,  int16x2_t,  kcrsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kdmbb,  int16x2_t,  int16x2_t,  kdmbb,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kdmbt,  int16x2_t,  int16x2_t,  kdmbt,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kdmtt,  int16x2_t,  int16x2_t,  kdmtt,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  khm8,  int8x4_t,  int8x4_t,  khm8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  khmx8,  int8x4_t,  int8x4_t,  khmx8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  khm16,  int16x2_t,  int16x2_t,  khm16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  khmx16,  int16x2_t,  int16x2_t,  khmx16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  khmbb,  int16x2_t,  int16x2_t,  khmbb,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  khmbt,  int16x2_t,  int16x2_t,  khmbt,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  khmtt,  int16x2_t,  int16x2_t,  khmtt,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmda,  int16x2_t,  int16x2_t,  kmda,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmxda,  int16x2_t,  int16x2_t,  kmxda,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmmwb2,  int32_t,  int16x2_t,  kmmwb2,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmmwb2_u,  int32_t,  int16x2_t,  kmmwb2_u,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmmwt2,  int32_t,  int16x2_t,  kmmwt2,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  kmmwt2_u,  int32_t,  int16x2_t,  kmmwt2_u,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  ksll8,  int8x4_t,  uint32_t,  ksll8,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  ksll16,  int16x2_t,  uint32_t,  ksll16,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  kslra8,  int8x4_t,  int32_t,  kslra8,  uintXLEN_t,  int32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  kslra8_u,  int8x4_t,  int32_t,  kslra8_u,  uintXLEN_t,  int32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kslra16,  int16x2_t,  int32_t,  kslra16,  uintXLEN_t,  int32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kslra16_u,  int16x2_t,  int32_t,  kslra16_u,  uintXLEN_t,  int32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kstas16,  int16x2_t,  int16x2_t,  kstas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  kstsa16,  int16x2_t,  int16x2_t,  kstsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  ksub8,  int8x4_t,  int8x4_t,  ksub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  ksub16,  int16x2_t,  int16x2_t,  ksub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint32_t,  pbsad,  uint8x4_t,  uint8x4_t,  pbsad,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  pkbb16,  uint16x2_t,  uint16x2_t,  pkbb16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  pktt16,  uint16x2_t,  uint16x2_t,  pktt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  pkbt16,  uint16x2_t,  uint16x2_t,  pkbt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  pktb16,  uint16x2_t,  uint16x2_t,  pktb16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  radd8,  int8x4_t,  int8x4_t,  radd8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  radd16,  int16x2_t,  int16x2_t,  radd16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  rcras16,  int16x2_t,  int16x2_t,  rcras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  rcrsa16,  int16x2_t,  int16x2_t,  rcrsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  rstas16,  int16x2_t,  int16x2_t,  rstas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  rstsa16,  int16x2_t,  int16x2_t,  rstsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  rsub8,  int8x4_t,  int8x4_t,  rsub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  rsub16,  int16x2_t,  int16x2_t,  rsub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  sclip8,  int8x4_t,  const uint32_t,  sclip8,  uintXLEN_t,  const uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sclip16,  int16x2_t,  const uint32_t,  sclip16,  uintXLEN_t,  const uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  scmple8,  int8x4_t,  int8x4_t,  scmple8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  scmple16,  int16x2_t,  int16x2_t,  scmple16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  scmplt8,  int8x4_t,  int8x4_t,  scmplt8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  scmplt16,  int16x2_t,  int16x2_t,  scmplt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  sll8,  uint8x4_t,  uint32_t,  sll8,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  sll16,  uint16x2_t,  uint32_t,  sll16,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  smax8,  int8x4_t,  int8x4_t,  smax8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  smax16,  int16x2_t,  int16x2_t,  smax16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smbb16,  int16x2_t,  int16x2_t,  smbb16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smbt16,  int16x2_t,  int16x2_t,  smbt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smtt16,  int16x2_t,  int16x2_t,  smtt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smds,  int16x2_t,  int16x2_t,  smds,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smdrs,  int16x2_t,  int16x2_t,  smdrs,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smxds,  int16x2_t,  int16x2_t,  smxds,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  smin8,  int8x4_t,  int8x4_t,  smin8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  smin16,  int16x2_t,  int16x2_t,  smin16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smmwb,  int32_t,  int16x2_t,  smmwb,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smmwb_u,  int32_t,  int16x2_t,  smmwb_u,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smmwt,  int32_t,  int16x2_t,  smmwt,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int32_t,  smmwt_u,  int32_t,  int16x2_t,  smmwt_u,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  sra8,  int8x4_t,  uint32_t,  sra8,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  sra8_u,  int8x4_t,  uint32_t,  sra8_u,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sra16,  int16x2_t,  uint32_t,  sra16,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sra16_u,  int16x2_t,  uint32_t,  sra16_u,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  srl8,  uint8x4_t,  uint32_t,  srl8,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  srl8_u,  uint8x4_t,  uint32_t,  srl8_u,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  srl16,  uint16x2_t,  uint32_t,  srl16,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  srl16_u,  uint16x2_t,  uint32_t,  srl16_u,  uintXLEN_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  uclip8,  int8x4_t,  const uint32_t,  uclip8,  uintXLEN_t,  const uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  uclip16,  int16x2_t,  const uint32_t,  uclip16,  uintXLEN_t,  const uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  ucmple8,  uint8x4_t,  uint8x4_t,  ucmple8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ucmple16,  uint16x2_t,  uint16x2_t,  ucmple16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  ucmplt8,  uint8x4_t,  uint8x4_t,  ucmplt8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ucmplt16,  uint16x2_t,  uint16x2_t,  ucmplt16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  ukadd8,  uint8x4_t,  uint8x4_t,  ukadd8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ukadd16,  uint16x2_t,  uint16x2_t,  ukadd16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ukcras16,  uint16x2_t,  uint16x2_t,  ukcras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ukcrsa16,  uint16x2_t,  uint16x2_t,  ukcrsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ukstas16,  uint16x2_t,  uint16x2_t,  ukstas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ukstsa16,  uint16x2_t,  uint16x2_t,  ukstsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  uksub8,  uint8x4_t,  uint8x4_t,  uksub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  uksub16,  uint16x2_t,  uint16x2_t,  uksub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  umax8,  uint8x4_t,  uint8x4_t,  umax8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  umax16,  uint16x2_t,  uint16x2_t,  umax16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  umin8,  uint8x4_t,  uint8x4_t,  umin8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  umin16,  uint16x2_t,  uint16x2_t,  umin16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  uradd8,  uint8x4_t,  uint8x4_t,  uradd8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  uradd16,  uint16x2_t,  uint16x2_t,  uradd16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  urcras16,  uint16x2_t,  uint16x2_t,  urcras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  urcrsa16,  uint16x2_t,  uint16x2_t,  urcrsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  urstas16,  uint16x2_t,  uint16x2_t,  urstas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  urstsa16,  uint16x2_t,  uint16x2_t,  urstsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  ursub8,  uint8x4_t,  uint8x4_t,  ursub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ursub16,  uint16x2_t,  uint16x2_t,  ursub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  uadd8,  uint8x4_t,  uint8x4_t,  add8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  sadd8,  int8x4_t,  int8x4_t,  add8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  uadd16,  uint16x2_t,  uint16x2_t,  add16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sadd16,  int16x2_t,  int16x2_t,  add16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  scmpeq8,  int8x4_t,  int8x4_t,  cmpeq8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  ucmpeq8,  uint8x4_t,  uint8x4_t,  cmpeq8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  scmpeq16,  int16x2_t,  int16x2_t,  cmpeq16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ucmpeq16,  uint16x2_t,  uint16x2_t,  cmpeq16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ucras16,  uint16x2_t,  uint16x2_t,  cras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  scras16,  int16x2_t,  int16x2_t,  cras16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ucrsa16,  uint16x2_t,  uint16x2_t,  crsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  scrsa16,  int16x2_t,  int16x2_t,  crsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ustas16,  uint16x2_t,  uint16x2_t,  stas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sstas16,  int16x2_t,  int16x2_t,  stas16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  ustsa16,  uint16x2_t,  uint16x2_t,  stsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  sstsa16,  int16x2_t,  int16x2_t,  stsa16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint8x4_t,  usub8,  uint8x4_t,  uint8x4_t,  sub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int8x4_t,  ssub8,  int8x4_t,  int8x4_t,  sub8,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(uint16x2_t,  usub16,  uint16x2_t,  uint16x2_t,  sub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_2(int16x2_t,  ssub16,  int16x2_t,  int16x2_t,  sub16,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kdmabb,  int32_t,  int16x2_t,  int16x2_t,  kdmabb,  int32_t,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kdmabt,  int32_t,  int16x2_t,  int16x2_t,  kdmabt,  int32_t,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kdmatt,  int32_t,  int16x2_t,  int16x2_t,  kdmatt,  int32_t,  uint32_t,  uint32_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmabb,  int32_t,  int16x2_t,  int16x2_t,  kmabb,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmabt,  int32_t,  int16x2_t,  int16x2_t,  kmabt,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmatt,  int32_t,  int16x2_t,  int16x2_t,  kmatt,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmada,  int32_t,  int16x2_t,  int16x2_t,  kmada,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmaxda,  int32_t,  int16x2_t,  int16x2_t,  kmaxda,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmads,  int32_t,  int16x2_t,  int16x2_t,  kmads,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmadrs,  int32_t,  int16x2_t,  int16x2_t,  kmadrs,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmaxds,  int32_t,  int16x2_t,  int16x2_t,  kmaxds,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawb,  int32_t,  int32_t,  int16x2_t,  kmmawb,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawb_u,  int32_t,  int32_t,  int16x2_t,  kmmawb_u,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawb2,  int32_t,  int32_t,  int16x2_t,  kmmawb2,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawb2_u,  int32_t,  int32_t,  int16x2_t,  kmmawb2_u,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawt,  int32_t,  int32_t,  int16x2_t,  kmmawt,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawt_u,  int32_t,  int32_t,  int16x2_t,  kmmawt_u,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawt2,  int32_t,  int32_t,  int16x2_t,  kmmawt2,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmmawt2_u,  int32_t,  int32_t,  int16x2_t,  kmmawt2_u,  intXLEN_t,  intXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmsda,  int32_t,  int16x2_t,  int16x2_t,  kmsda,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  kmsxda,  int32_t,  int16x2_t,  int16x2_t,  kmsxda,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(uint32_t,  pbsada,  uint32_t,  uint8x4_t,  uint8x4_t,  pbsada,  uintXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  smaqa,  int32_t,  int8x4_t,  int8x4_t,  smaqa,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(int32_t,  smaqa_su,  int32_t,  int8x4_t,  uint8x4_t,  smaqa_su,  intXLEN_t,  uintXLEN_t,  uintXLEN_t)
CREATE_RVP_INTRINSIC_VECTOR_3(uint32_t,  umaqa,  uint32_t,  uint8x4_t,  uint8x4_t,  umaqa,  uintXLEN_t,  uintXLEN_t,  uintXLEN_t)
#endif // !defined(__clang__)

#if defined(__riscv_zbpbo)
// swap8 -> rev8.h
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uintXLEN_t __rv_swap8(uintXLEN_t a) {
    return __rv_rev8h(a);
}

#if !defined(__clang__)
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uint8x4_t __rv_v_swap8(uint8x4_t a) {
    return __rv_v_rev8h(a);
}
#endif // !defined(__clang__)

#if __riscv_xlen == 32
// pkbb16 -> pack
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uintXLEN_t __rv_pkbb16(uintXLEN_t a, uintXLEN_t b) {
    return __rv_pack(b, a);
}

// pktt16 -> packu
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uintXLEN_t __rv_pktt16(uintXLEN_t a, uintXLEN_t b) {
    return __rv_packu(b, a);
}

#endif // __riscv_xlen == 32

#endif // defined(__riscv_zbpbo)

// swap16 -> pkbt16
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uintXLEN_t __rv_swap16(uintXLEN_t a) {
    return __rv_pkbt16(a, a);
}

#if !defined(__clang__)
__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uint16x2_t __rv_v_swap16(uint16x2_t a) {
    return __rv_v_pkbt16(a, a);
}
#endif // !defined(__clang__)

#endif // defined(__riscv_zpn)

__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
void __rv_clrov (void) {
    __asm volatile("csrci vxsat, 1");
}

__extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))
uintXLEN_t __rv_rdov (void) {
    uintXLEN_t __val;
    __asm volatile("csrrs %0, vxsat, x0" : "=r"(__val));
    return __val;
}

#endif // END OF _RISCV_RVP_INTRINSIC_H
