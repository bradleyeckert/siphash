# Tiny Version of SipHash 2.4

Various versions of SipHash take one long byte array.
They are macro-based to trade code size for speed.
This version goes for minimum code size at the expense of speed.
Heavy factoring and a little-endian dependency made it small.

The best part, besides the small size, is the API's stream orientation.
It's much better for RAM-constrained systems that deal with long messages.
The API maps nicely to other HMACs (HMAC-SHA256, etc.) to facilitate drop-in compatibility.

## References

- [Wikipedia SipHash](https://en.wikipedia.org/wiki/SipHash)
- [SipHash: a fast short-input PRF](https://www.aumasson.jp/siphash/siphash.pdf)
- [Cryptoanalysis of SipHash](https://eprint.iacr.org/2014/722.pdf)

