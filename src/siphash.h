/*
 * Header file for tiny SipHash
 */
#include <stdint.h>

#ifndef _SIPHASH_TINY_H_
#define _SIPHASH_TINY_H_

#define ROTL64(x, b) (uint64_t)( ((x) << (b)) | ( (x) >> (64 - (b))) )

#define HALF_ROUND(a,b,c,d,s,t)     \
    a += b; c += d;                 \
    b = ROTL64(b, s) ^ a;           \
    d = ROTL64(d, t) ^ c;           \
    a = ROTL64(a, 32);

#define DOUBLE_ROUND(v0,v1,v2,v3)   \
    HALF_ROUND(v0,v1,v2,v3,13,16);  \
    HALF_ROUND(v2,v1,v0,v3,17,21);  \
    HALF_ROUND(v0,v1,v2,v3,13,16);  \
    HALF_ROUND(v2,v1,v0,v3,17,21);

typedef struct
{   uint64_t v[4];
    uint64_t m;
    uint32_t length;
    uint8_t mp;
    uint8_t hsize;
} siphash_ctx;

// There's nothing like an old classic...

/** Calculate HMAC with SipHash 2.4
 * @param src    Input byte array
 * @param src_sz Input length
 * @param out    Hash result
 * @param hsize  Hash length, must be 8 or 16
 * @param key    16-byte key
 */
void siphash24(siphash_ctx *ctx, const uint8_t *src, uint32_t src_sz,
			   uint8_t *out, int hsize, const uint8_t key[16]);

// ... but use this abstraction to handle big messages without big buffers:

/** HMAC initialization
 * @param ctx   HMAC context
 * @param key   Key, 32 bytes
 * @param hsize Expected hash length in bytes
 * @return      Actual hash length in bytes (0 if bogus)
 */
int sip_hmac_setkey(siphash_ctx *ctx, const uint8_t *key, int hsize);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param c     Byte to add to HMAC
 */
void sip_hmac_put(siphash_ctx *ctx, uint8_t c);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param out   Output hash
 * @return      Hash length in bytes
 */
int sip_hmac_final(siphash_ctx *ctx, uint8_t *out);


#endif // _SIPHASH_TINY_H_
