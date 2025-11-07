//
// Created by yhwach on 11/6/25.
//

#ifndef MD4_H
#define MD4_H

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

#define MD4_MIN_EXTRA_BYTES 9
#define MD4_LEN_BYTES 8

#define PADDED_LEN(len) \
((size_t)(((len) + MD4_MIN_EXTRA_BYTES + 63) / 64) * 64)

#define le32(ptr) \
((uint32_t)(ptr)[0]       | \
((uint32_t)(ptr)[1] << 8) | \
((uint32_t)(ptr)[2] << 16)| \
((uint32_t)(ptr)[3] << 24))

#define f(x,y,z) (((x) & (y)) | (~(x) & (z)))
#define g(x,y,z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define h(x,y,z) ((x) ^ (y) ^ (z))

#define ROL32(x, s) ( (uint32_t)(((x) << (s)) | ((x) >> (32 - (s)))) )

#define round1(a,b,c,d,X,i,s) (a = ROL32((a) + f((b),(c),(d)) + (X)[(i)], (s)))
#define round2(a,b,c,d,X,i,s) (a = ROL32((a) + g((b),(c),(d)) + (X)[(i)] + 0x5A827999u, (s)))
#define round3(a,b,c,d,X,i,s) (a = ROL32((a) + h((b),(c),(d)) + (X)[(i)] + 0x6ED9EBA1u, (s)))

__uint128_t __md4(const unsigned char *in, unsigned long len);

#endif //MD4_H
