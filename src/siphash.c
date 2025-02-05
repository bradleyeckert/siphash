/* https://github.com/bradleyeckert/siphash
 *
 * A highly refactored version of https://github.com/majek/csiphash
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "siphash.h"

static void doubleround(uint64_t *v) {
	DOUBLE_ROUND(v[0],v[1],v[2],v[3]);
}

static void vout(uint64_t *v, uint8_t *out) {
	doubleround(v);
    uint64_t b = (v[0] ^ v[1]) ^ (v[2] ^ v[3]);
	memcpy(out, &b, sizeof(uint64_t));
}

void siphash24(const uint8_t *src, uint32_t src_sz,
               uint8_t *out, int big, const uint8_t key[16]) {
	const uint64_t *_key = (uint64_t *)key;
	uint64_t k0 = (uint64_t)(_key[0]);
	uint64_t k1 = (uint64_t)(_key[1]);
	uint64_t b = (uint64_t)src_sz << 56;
	uint64_t v[4];

	v[0] = k0 ^ 0x736f6d6570736575ULL;
	v[1] = k1 ^ 0x646f72616e646f6dULL;
	v[2] = k0 ^ 0x6c7967656e657261ULL;
	v[3] = k1 ^ 0x7465646279746573ULL;
    if (big) v[1] += 0xEE;

	uint64_t mi;
	uint8_t *pt = (uint8_t *)&mi;
	while (src_sz) {
		mi = 0;
		for (int i = 0; i < 8; i++) {   // little-endian input stream
            if (i < src_sz)  pt[i] = *src++;
		}
		if (src_sz < 8) break;
		v[3] ^= mi;
		doubleround(v);
		v[0] ^= mi;
		src_sz -= 8;
	}

	uint64_t t = 0;
	pt = (uint8_t *)&t;
	uint8_t *m = (uint8_t *)&mi;
	switch (src_sz) {
	case 7: pt[6] = m[6];
	case 6: pt[5] = m[5];
	case 5: pt[4] = m[4];
	case 4: *((uint32_t*)&pt[0]) = *((uint32_t*)&m[0]); break;
	case 3: pt[2] = m[2];
	case 2: pt[1] = m[1];
	case 1: pt[0] = m[0];
	}
	b |= (uint64_t)(t);

	v[3] ^= b;
	doubleround(v);
	v[0] ^= b;
    if (big) v[2] ^= 0xEE;
    else v[2] ^= 0xFF;
	doubleround(v);
	vout(v, out);
    if (big) {
        v[1] ^= 0xDD;
        vout(v, &out[8]);
    }
}
