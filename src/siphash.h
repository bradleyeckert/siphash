/*
 * Header file for tiny SipHash
 */
#include <stdint.h>

#ifndef _SIPHASH_H_
#define _SIPHASH_H_

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

// Use this API to handle big messages without big buffers:

/** HMAC initialization
 * @param ctx   HMAC context
 * @param key   Key, 32 bytes
 * @param hsize Expected hash length in bytes, 8 and 16 are valid
 * @param ctr   Counter to prevent repeating keys
 * @return      Actual hash length in bytes (0 if bogus)
 */
int sip_hmac_init(siphash_ctx *ctx, const uint8_t *key, int hsize, uint64_t ctr);
int sip_hmac_init_g(size_t *ctx, const uint8_t *key, int hsize, uint64_t ctr);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param c     Byte to add to HMAC
 */
void sip_hmac_putc(siphash_ctx *ctx, uint8_t c);
void sip_hmac_putc_g(size_t *ctx, uint8_t c);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param out   Output hash
 * @return      Hash length in bytes
 */
int sip_hmac_final(siphash_ctx *ctx, uint8_t *out);
int sip_hmac_final_g(size_t *ctx, uint8_t *out);


#endif // _SIPHASH_H_
