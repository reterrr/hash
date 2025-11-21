//
// Created by yhwach on 11/21/25.
//

#ifndef SHA256_MYENDIAN_H
#define SHA256_MYENDIAN_H

#define le32(ptr) \
    ((uint32_t)(ptr)[0]       | \
    ((uint32_t)(ptr)[1] << 8) | \
    ((uint32_t)(ptr)[2] << 16)| \
    ((uint32_t)(ptr)[3] << 24))

#endif //SHA256_MYENDIAN_H
