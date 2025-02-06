# Tiny Version of SipHash 2.4

Various versions of SipHash take one long byte array.
They are macro-based to trade code size for speed.
This version goes for minimum code size at the expense of speed.
Heavy factoring and a little-endian dependency made it small.

The best part, besides the small size, is the API's stream orientation.
It's much better for RAM-constrained systems that deal with long messages.

## References

- [Wikipedia SipHash](https://en.wikipedia.org/wiki/SipHash)
- [SipHash: a fast short-input PRF](https://www.aumasson.jp/siphash/siphash.pdf)
- [Cryptoanalysis of SipHash](https://eprint.iacr.org/2014/722.pdf)

## API

```C
/** HMAC initialization
 * @param ctx   HMAC context
 * @param key   Key, 32 bytes
 * @param hsize Expected hash length in bytes
 * @return      Actual hash length in bytes (0 if bogus)
 */
int sip_hmac_init(siphash_ctx *ctx, const uint8_t *key, int hsize);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param c     Byte to add to HMAC
 */
void sip_hmac_putc(siphash_ctx *ctx, uint8_t c);

/** HMAC append 16-byte blocks
 * @param ctx   HMAC context
 * @param src   Source to add to HMAC
 * @param blocks Number of 16-byte blocks
 */
void sip_hmac_bloc(siphash_ctx *ctx, const uint8_t *src, unsigned int blocks);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param out   Output hash
 * @return      Hash length in bytes
 */
int sip_hmac_final(siphash_ctx *ctx, uint8_t *out);
```

The rationale is that data is encrypted in 16-byte chunks but the extra data of AEAD can be any length.
`ip_hmac_bloc` matches the encryption call. The API may be implemented with a block hash like AES.

Function pointers would use the following typedefs:

```C
typedef void (*hmac_initFn)((void *)ctx, const uint8_t *key);
typedef void (*hmac_putcFn)((void *)ctx, uint8_t c);
typedef void (*hmac_blocFn)((void *)ctx, const uint8_t *src, unsigned int blocks);
typedef int (*hmac_finalFn)((void *)ctx, uint8_t *out);
```
