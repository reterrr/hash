#include "library.h"
#include "md4.h"

__uint128_t md4(const unsigned char *in, const unsigned long len) {
    return __md4(in, len);
}
