/* https://github.com/bradleyeckert/siphash
 *
 * A highly refactored version of https://github.com/majek/csiphash
 */

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

int sip_hmac_setkey(siphash_ctx *ctx, const uint8_t *key, int hsize) {
    const uint64_t *_key = (uint64_t *)key;
	uint64_t k0 = (uint64_t)(_key[0]);
	uint64_t k1 = (uint64_t)(_key[1]);
	int r = 0;
	memset(ctx, 0, sizeof(siphash_ctx));
	ctx->v[0] = k0 ^ 0x736f6d6570736575ULL;
	ctx->v[1] = k1 ^ 0x646f72616e646f6dULL;
	ctx->v[2] = k0 ^ 0x6c7967656e657261ULL;
	ctx->v[3] = k1 ^ 0x7465646279746573ULL;
    if (hsize == 16) {
        ctx->v[1] += 0xEE;  r = 16;
    } else if (hsize == 8)  r = 8;
    ctx->hsize = r;
    return r;
}

void sip_hmac_put(siphash_ctx *ctx, uint8_t c) {
	uint8_t *s = (uint8_t *)&ctx->m;
	uint8_t i = ctx->mp;
	s[i++] = c;
	if (i & 8) {
        i = 0;
		ctx->v[3] ^= ctx->m;
		doubleround(ctx->v);
		ctx->v[0] ^= ctx->m;
		ctx->m = 0;
	}
	ctx->mp = i;
	ctx->length++;
}

int sip_hmac_final(siphash_ctx *ctx, uint8_t *out) {
	uint64_t b = (uint64_t)ctx->length << 56;
	uint64_t t = 0;
	uint8_t *pt = (uint8_t *)&t;
	uint8_t *m = (uint8_t *)&ctx->m;
	switch (ctx->mp) {
	case 7: pt[6] = m[6];
	case 6: pt[5] = m[5];
	case 5: pt[4] = m[4];
	case 4: *((uint32_t*)&pt[0]) = *((uint32_t*)&m[0]); break;
	case 3: pt[2] = m[2];
	case 2: pt[1] = m[1];
	case 1: pt[0] = m[0];
	}
	b |= (uint64_t)(t);

	ctx->v[3] ^= b;
	doubleround(ctx->v);
	ctx->v[0] ^= b;
	int hashlength = ctx->hsize;
    if (hashlength == 16) ctx->v[2] ^= 0xEE;
    else     ctx->v[2] ^= 0xFF;
	doubleround(ctx->v);
	vout(ctx->v, out);
    if (hashlength == 16) {
        ctx->v[1] ^= 0xDD;
        vout(ctx->v, &out[8]);
    }
    return hashlength;
}

// The original function tested by test.c

void siphash24(siphash_ctx *ctx, const uint8_t *src, uint32_t src_sz,
               uint8_t *out, int hsize, const uint8_t key[16]) {
    sip_hmac_setkey(ctx, key, hsize);
    while(src_sz--) sip_hmac_put(ctx, *src++);
    sip_hmac_final(ctx, out);
}
