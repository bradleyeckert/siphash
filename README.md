# Tiny Version of SipHash 2.4

Various versions of SipHash take one long byte array.
They are macro-based to trade code size for speed.
This version goes for minimum code size at the expense of speed.
Heavy factoring and a little-endian dependency made it small.
