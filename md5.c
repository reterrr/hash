//
// Created by yhwach on 11/21/25.
//

#include "md5.h"

#include <stdint.h>
#include <string.h>
#include <endian.h>

#include "myendian.h"

#if defined(_MSC_VER)
#define FORCE_INLINE  __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#   define FORCE_INLINE inline
#endif


FORCE_INLINE static void
md5_pad_message(const unsigned char* __restrict begin,
                const unsigned char* __restrict end,
                const unsigned long orig_len)
{
    unsigned char* ptr = (unsigned char*)(begin + orig_len);

    *ptr++ = 0x80;
    const size_t zero_bytes = end - begin - orig_len - 1 - MD5_LEN_BYTES;
    memset(ptr, 0x00, zero_bytes);
    ptr += zero_bytes;

    uint64_t bitlen = (uint64_t)orig_len << 3;

#if defined(__BYTE_ORDER) && (__BYTE_ORDER == __ORDER_BIG_ENDIAN__)
    bitlen = __builtin_bswap64(bitlen);
#endif

    memcpy(ptr, &bitlen, MD5_LEN_BYTES);
}

__uint128_t __md5(const unsigned char* in, const unsigned long len)
{
    const long padded_len = md5_pad_length(len);
    unsigned char buff[padded_len];
    memcpy(buff, in, len);

    md5_pad_message(buff, buff + padded_len, len);

    uint32_t a = A_MD5, b = B_MD5, c = C_MD5, d = D_MD5;

    for (size_t i = 0; i < padded_len; i += 64)
    {
        uint32_t X[16];
        for (size_t j = 0; j < 16; ++j)
            X[j] = le32(&buff[i + j * 4]);

        const uint32_t aa = a, bb = b, cc = c, dd = d;

        round1_MD5(a, b, c, d, X, 0, 7, 0);
        round1_MD5(d, a, b, c, X, 1, 12, 1);
        round1_MD5(c, d, a, b, X, 2, 17, 2);
        round1_MD5(b, c, d, a, X, 3, 22, 3);

        round1_MD5(a, b, c, d, X, 4, 7, 4);
        round1_MD5(d, a, b, c, X, 5, 12, 5);
        round1_MD5(c, d, a, b, X, 6, 17, 6);
        round1_MD5(b, c, d, a, X, 7, 22, 7);

        round1_MD5(a, b, c, d, X, 8, 7, 8);
        round1_MD5(d, a, b, c, X, 9, 12, 9);
        round1_MD5(c, d, a, b, X, 10, 17, 10);
        round1_MD5(b, c, d, a, X, 11, 22, 11);

        round1_MD5(a, b, c, d, X, 12, 7, 12);
        round1_MD5(d, a, b, c, X, 13, 12, 13);
        round1_MD5(c, d, a, b, X, 14, 17, 14);
        round1_MD5(b, c, d, a, X, 15, 22, 15);

        /* Round 2 */
        round2_MD5(a, b, c, d, X, 1, 5, 16);
        round2_MD5(d, a, b, c, X, 6, 9, 17);
        round2_MD5(c, d, a, b, X, 11, 14, 18);
        round2_MD5(b, c, d, a, X, 0, 20, 19);

        round2_MD5(a, b, c, d, X, 5, 5, 20);
        round2_MD5(d, a, b, c, X, 10, 9, 21);
        round2_MD5(c, d, a, b, X, 15, 14, 22);
        round2_MD5(b, c, d, a, X, 4, 20, 23);

        round2_MD5(a, b, c, d, X, 9, 5, 24);
        round2_MD5(d, a, b, c, X, 14, 9, 25);
        round2_MD5(c, d, a, b, X, 3, 14, 26);
        round2_MD5(b, c, d, a, X, 8, 20, 27);

        round2_MD5(a, b, c, d, X, 13, 5, 28);
        round2_MD5(d, a, b, c, X, 2, 9, 29);
        round2_MD5(c, d, a, b, X, 7, 14, 30);
        round2_MD5(b, c, d, a, X, 12, 20, 31);

        /* Round 3 */
        round3_MD5(a, b, c, d, X, 5, 4, 32);
        round3_MD5(d, a, b, c, X, 8, 11, 33);
        round3_MD5(c, d, a, b, X, 11, 16, 34);
        round3_MD5(b, c, d, a, X, 14, 23, 35);

        round3_MD5(a, b, c, d, X, 1, 4, 36);
        round3_MD5(d, a, b, c, X, 4, 11, 37);
        round3_MD5(c, d, a, b, X, 7, 16, 38);
        round3_MD5(b, c, d, a, X, 10, 23, 39);

        round3_MD5(a, b, c, d, X, 13, 4, 40);
        round3_MD5(d, a, b, c, X, 0, 11, 41);
        round3_MD5(c, d, a, b, X, 3, 16, 42);
        round3_MD5(b, c, d, a, X, 6, 23, 43);

        round3_MD5(a, b, c, d, X, 9, 4, 44);
        round3_MD5(d, a, b, c, X, 12, 11, 45);
        round3_MD5(c, d, a, b, X, 15, 16, 46);
        round3_MD5(b, c, d, a, X, 2, 23, 47);

        /* Round 4 */
        round4_MD5(a, b, c, d, X, 0, 6, 48);
        round4_MD5(d, a, b, c, X, 7, 10, 49);
        round4_MD5(c, d, a, b, X, 14, 15, 50);
        round4_MD5(b, c, d, a, X, 5, 21, 51);

        round4_MD5(a, b, c, d, X, 12, 6, 52);
        round4_MD5(d, a, b, c, X, 3, 10, 53);
        round4_MD5(c, d, a, b, X, 10, 15, 54);
        round4_MD5(b, c, d, a, X, 1, 21, 55);

        round4_MD5(a, b, c, d, X, 8, 6, 56);
        round4_MD5(d, a, b, c, X, 15, 10, 57);
        round4_MD5(c, d, a, b, X, 6, 15, 58);
        round4_MD5(b, c, d, a, X, 13, 21, 59);

        round4_MD5(a, b, c, d, X, 4, 6, 60);
        round4_MD5(d, a, b, c, X, 11, 10, 61);
        round4_MD5(c, d, a, b, X, 2, 15, 62);
        round4_MD5(b, c, d, a, X, 9, 21, 63);

        a += aa;
        b += bb;
        c += cc;
        d += dd;
    }

    return
        (__uint128_t)a |
        (__uint128_t)b << 32 |
        (__uint128_t)c << 64 |
        (__uint128_t)d << 96;
}
