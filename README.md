# Tiny Version of SipHash 2.4

Various versions of SipHash take one long byte array.
They are macro-based to trade code size for speed.
This version goes for minimum code size at the expense of speed.
Heavy factoring and a little-endian dependency made it small.

The API uses stream orientation so that RAM-constrained systems can handle long messages.

## References

- [Wikipedia SipHash](https://en.wikipedia.org/wiki/SipHash)
- [SipHash: a fast short-input PRF](https://www.aumasson.jp/siphash/siphash.pdf)
- [Cryptoanalysis of SipHash](https://eprint.iacr.org/2014/722.pdf)

## API

```C
/** HMAC initialization
 * @param ctx   HMAC context
 * @param key   Key, 32 bytes
 * @param hsize Expected hash length in bytes, 8 and 16 are valid
 * @return      Actual hash length in bytes (0 if bogus)
 */
int sip_hmac_init(siphash_ctx *ctx, const uint8_t *key, int hsize);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param c     Byte to add to HMAC
 */
void sip_hmac_putc(siphash_ctx *ctx, uint8_t c);

/** HMAC append byte
 * @param ctx   HMAC context
 * @param out   Output hash
 * @return      Hash length in bytes
 */
int sip_hmac_final(siphash_ctx *ctx, uint8_t *out);
```
