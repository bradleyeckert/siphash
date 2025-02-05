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


/** Calculate HMAC with SipHash 2.4
 * @param src Input byte array
 * @param src_sz Input length
 * @param out Hash result
 * @param big Hash length: 0=8, 1=16
 * @param key 16-byte key
 */
void siphash24(const uint8_t *src, uint32_t src_sz, uint8_t *out, int big, const uint8_t key[16]);

///**
// * \brief       HMAC initialization
// * \param ctx   HMAC context
// * \param key   Key, 32 bytes
// */
//void x_hmac_setkey(hmac_context *ctx, const uint8_t *key);
//
///**
// * \brief       HMAC append byte
// * \param ctx   HMAC context
// * \param c     Byte to add to HMAC
// */
//void x_hmac_put(hmac_context *ctx, uint8_t c);
//
///**
// * \brief       HMAC append byte
// * \param ctx   HMAC context
// * \param c     Byte to add to HMAC
// * \return      Hash length in bytes
// */
//int x_hmac_final(hmac_context *ctx);

#endif // _SIPHASH_TINY_H_
