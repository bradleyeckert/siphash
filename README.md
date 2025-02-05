# Tiny Version of SipHash 2.4

Various versions of SipHash take one long byte array.
They are macro-based to trade code size for speed.
This version goes for minimum code size at the expense of speed.
Heavy factoring and a little-endian dependency made it small.

## References

- [Wikipedia SipHash](https://en.wikipedia.org/wiki/SipHash)
- [SipHash: a fast short-input PRF](https://www.aumasson.jp/siphash/siphash.pdf)
- [Cryptanalysis of SipHash](https://eprint.iacr.org/2014/722.pdf)

