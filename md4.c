#include "md4.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

int pad_message(const uint8_t *in, const size_t len, uint8_t *out, size_t *out_len) {
    if (!in || !out || !out_len) return -1;

    *out_len = PADDED_LEN(len);

    memcpy(out, in, len);
    out[len] = 0x80;

    const size_t zero_bytes = *out_len - len - 1 - MD4_LEN_BYTES;
    memset(out + len + 1, 0, zero_bytes);

    const uint64_t bitlen = len * 8;

    for (size_t i = 0; i < 8; ++i) {
        out[*out_len - 8 + i] = (uint8_t) (bitlen >> (8 * i));
    }

    return 0;
}

__uint128_t __md4(const unsigned char *in, const unsigned long len) {
    unsigned long padded_len;
    unsigned char temp[PADDED_LEN(len)];
    if (pad_message(in, len, temp, &padded_len) != 0) return 0;

    uint32_t a = A, b = B, c = C, d = D;

    for (size_t off = 0; off < padded_len; off += 64) {
        uint32_t X[16];
        for (size_t j = 0; j < 16; ++j)
            X[j] = le32(&temp[off + 4 * j]);

        uint32_t aa = a, bb = b, cc = c, dd = d;


        round1(aa, bb, cc, dd, X, 0, 3);
        round1(dd, aa, bb, cc, X, 1, 7);
        round1(cc, dd, aa, bb, X, 2, 11);
        round1(bb, cc, dd, aa, X, 3, 19);
        round1(aa, bb, cc, dd, X, 4, 3);
        round1(dd, aa, bb, cc, X, 5, 7);
        round1(cc, dd, aa, bb, X, 6, 11);
        round1(bb, cc, dd, aa, X, 7, 19);
        round1(aa, bb, cc, dd, X, 8, 3);
        round1(dd, aa, bb, cc, X, 9, 7);
        round1(cc, dd, aa, bb, X, 10, 11);
        round1(bb, cc, dd, aa, X, 11, 19);
        round1(aa, bb, cc, dd, X, 12, 3);
        round1(dd, aa, bb, cc, X, 13, 7);
        round1(cc, dd, aa, bb, X, 14, 11);
        round1(bb, cc, dd, aa, X, 15, 19);


        round2(aa, bb, cc, dd, X, 0, 3);
        round2(dd, aa, bb, cc, X, 4, 5);
        round2(cc, dd, aa, bb, X, 8, 9);
        round2(bb, cc, dd, aa, X, 12, 13);
        round2(aa, bb, cc, dd, X, 1, 3);
        round2(dd, aa, bb, cc, X, 5, 5);
        round2(cc, dd, aa, bb, X, 9, 9);
        round2(bb, cc, dd, aa, X, 13, 13);
        round2(aa, bb, cc, dd, X, 2, 3);
        round2(dd, aa, bb, cc, X, 6, 5);
        round2(cc, dd, aa, bb, X, 10, 9);
        round2(bb, cc, dd, aa, X, 14, 13);
        round2(aa, bb, cc, dd, X, 3, 3);
        round2(dd, aa, bb, cc, X, 7, 5);
        round2(cc, dd, aa, bb, X, 11, 9);
        round2(bb, cc, dd, aa, X, 15, 13);


        round3(aa, bb, cc, dd, X, 0, 3);
        round3(dd, aa, bb, cc, X, 8, 9);
        round3(cc, dd, aa, bb, X, 4, 11);
        round3(bb, cc, dd, aa, X, 12, 15);
        round3(aa, bb, cc, dd, X, 2, 3);
        round3(dd, aa, bb, cc, X, 10, 9);
        round3(cc, dd, aa, bb, X, 6, 11);
        round3(bb, cc, dd, aa, X, 14, 15);
        round3(aa, bb, cc, dd, X, 1, 3);
        round3(dd, aa, bb, cc, X, 9, 9);
        round3(cc, dd, aa, bb, X, 5, 11);
        round3(bb, cc, dd, aa, X, 13, 15);
        round3(aa, bb, cc, dd, X, 3, 3);
        round3(dd, aa, bb, cc, X, 11, 9);
        round3(cc, dd, aa, bb, X, 7, 11);
        round3(bb, cc, dd, aa, X, 15, 15);

        a += aa;
        b += bb;
        c += cc;
        d += dd;
    }

    return ((__uint128_t) a) |
           (((__uint128_t) b) << 32) |
           (((__uint128_t) c) << 64) |
           (((__uint128_t) d) << 96);
}
