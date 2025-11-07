//
// Created by yhwach on 11/7/25.
//

#include <stdio.h>
#include <string.h>

#include "library.h"

static void print_md4_hex128(const __uint128_t v) {
    unsigned char b[16];
    for (int i = 0; i < 16; ++i)
        b[i] = (unsigned char) (v >> (8 * i));
    for (int i = 0; i < 16; ++i)
        printf("%02x", b[i]);
    printf("\n");
}

int main(int argc, const char *argv[]) {
    print_md4_hex128(md4((const unsigned char *) argv[1], strlen(argv[1])));

    return 0;
}
