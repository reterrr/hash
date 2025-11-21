//
// Created by yhwach on 11/7/25.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "library.h"

typedef __uint128_t (*hash_fn)(const unsigned char* in, unsigned long len);

typedef struct
{
    const char* name;
    hash_fn fn;
} hash_entry;

static const hash_entry hash_algorithms[] = {
    {"md4", md4},
    {"md5", md5},
};

static void print_hex128(const __uint128_t v)
{
    unsigned char b[16];

    for (int i = 0; i < 16; ++i)
        b[i] = (unsigned char)(v >> (8 * i));

    for (int i = 0; i < 16; ++i)
        printf("%02x", b[i]);
}

static const hash_entry* find_algorithm(const char* name)
{
    const size_t n = sizeof(hash_algorithms) / sizeof(hash_algorithms[0]);

    for (size_t i = 0; i < n; ++i)
    {
        if (strcmp(name, hash_algorithms[i].name) == 0)
            return &hash_algorithms[i];
    }
    return NULL;
}

int main(const int argc, const char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s [md4|md5] <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* algo_name = argv[1];
    const char* msg_str = argv[2];

    const hash_entry* algo = find_algorithm(algo_name);
    if (!algo)
    {
        fprintf(stderr, "Unknown algorithm '%s'. Supported: md4, md5\n", algo_name);
        return EXIT_FAILURE;
    }

    const unsigned char* msg = (const unsigned char*)msg_str;
    const unsigned long len = strlen(msg_str);

    const __uint128_t digest = algo->fn(msg, len);

    print_hex128(digest);
    putchar('\n');

    return EXIT_SUCCESS;
}
