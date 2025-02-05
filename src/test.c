/* SipHash 2.4 tests
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "siphash.h"

uint64_t sip_vectors0[65] = {
    0x726fdb47dd0e0e31LLU, 0x74f839c593dc67fdLLU, 0x0d6c8009d9a94f5aLLU, 0x85676696d7fb7e2dLLU,
    0xcf2794e0277187b7LLU, 0x18765564cd99a68dLLU, 0xcbc9466e58fee3ceLLU, 0xab0200f58b01d137LLU,
    0x93f5f5799a932462LLU, 0x9e0082df0ba9e4b0LLU, 0x7a5dbbc594ddb9f3LLU, 0xf4b32f46226bada7LLU,
    0x751e8fbc860ee5fbLLU, 0x14ea5627c0843d90LLU, 0xf723ca908e7af2eeLLU, 0xa129ca6149be45e5LLU,
    0x3f2acc7f57c29bdbLLU, 0x699ae9f52cbe4794LLU, 0x4bc1b3f0968dd39cLLU, 0xbb6dc91da77961bdLLU,
    0xbed65cf21aa2ee98LLU, 0xd0f2cbb02e3b67c7LLU, 0x93536795e3a33e88LLU, 0xa80c038ccd5ccec8LLU,
    0xb8ad50c6f649af94LLU, 0xbce192de8a85b8eaLLU, 0x17d835b85bbb15f3LLU, 0x2f2e6163076bcfadLLU,
    0xde4daaaca71dc9a5LLU, 0xa6a2506687956571LLU, 0xad87a3535c49ef28LLU, 0x32d892fad841c342LLU,
    0x7127512f72f27cceLLU, 0xa7f32346f95978e3LLU, 0x12e0b01abb051238LLU, 0x15e034d40fa197aeLLU,
    0x314dffbe0815a3b4LLU, 0x027990f029623981LLU, 0xcadcd4e59ef40c4dLLU, 0x9abfd8766a33735cLLU,
    0x0e3ea96b5304a7d0LLU, 0xad0c42d6fc585992LLU, 0x187306c89bc215a9LLU, 0xd4a60abcf3792b95LLU,
    0xf935451de4f21df2LLU, 0xa9538f0419755787LLU, 0xdb9acddff56ca510LLU, 0xd06c98cd5c0975ebLLU,
    0xe612a3cb9ecba951LLU, 0xc766e62cfcadaf96LLU, 0xee64435a9752fe72LLU, 0xa192d576b245165aLLU,
    0x0a8787bf8ecb74b2LLU, 0x81b3e73d20b49b6fLLU, 0x7fa8220ba3b2eceaLLU, 0x245731c13ca42499LLU,
    0xb78dbfaf3a8d83bdLLU, 0xea1ad565322a1a0bLLU, 0x60e61c23a3795013LLU, 0x6606d7e446282b93LLU,
    0x6ca4ecb15c5f91e1LLU, 0x9f626da15c9625f3LLU, 0xe51b38608ef25f57LLU, 0x958a324ceb064572LLU, 0};

uint64_t sip_vectors1[129] = {
    0x18bb780602b82a2fLLU, 0xbb31a211c53d0a11LLU, 0x052e9dc94e72bffcLLU, 0x84e5c39a147f9ac4LLU,
    0xd2d8b24240e7c453LLU, 0xf9d88d0a98810181LLU, 0x16cbbdfba1498f6eLLU, 0xc0c84389a53208d9LLU,
    0xd654b4d866982f7aLLU, 0xf7ecb436a6ff6be6LLU, 0x32e2e9be789aea25LLU, 0x05f9f4e1dc5de6d6LLU,
    0x4a94b8e3d6b94432LLU, 0x408bd60e7a5a0a5dLLU, 0x5da81fce63487f29LLU, 0x4f2424170459bcacLLU,
    0x067d28cb3b2fb2afLLU, 0xa40fa5264600e4b8LLU, 0x77e4d56be8a3c93eLLU, 0xf6822f4fe0ae25f1LLU,
    0x88a883236361df7cLLU, 0xd113689018810133LLU, 0xb46e471cea3670dfLLU, 0xe13ed6b4144f8422LLU,
    0x9f00ed1ffb0736d7LLU, 0x2ad68189b0d23530LLU, 0xf3d49713bfe05ea8LLU, 0x5b220ed8175c0453LLU,
    0x461767246870a4bcLLU, 0x6d83ca5701c80274LLU, 0x22ceafcef0ac0cd3LLU, 0x91ee698526e09921LLU,
    0x3e32753edb674681LLU, 0x3f8eaf17d47fd63fLLU, 0x1bd3809acc2b6ce7LLU, 0xe542628ef0924d0aLLU,
    0x70269a9eb9fac765LLU, 0x756d5affc0caf06bLLU, 0xfaacc899963532bbLLU, 0x54680393aff3f76dLLU,
    0x73b3af301d487c66LLU, 0xce2c5546e556d710LLU, 0x4c3290782e71357bLLU, 0xe62aef16a944048dLLU,
    0xc8ac94084edb87a8LLU, 0x08d1b42fc7ce6533LLU, 0x83db3a11a29ead34LLU, 0xc9ef2f7b2b98c7eaLLU,
    0xbb6c077a9f52d955LLU, 0xd25cdcbb95c738c9LLU, 0x2f5596ec9b9ff33eLLU, 0x8617216b7372c1a4LLU,
    0xa35609d8c8796289LLU, 0x5373f740163d43b7LLU, 0xe4cb699ba27d8661LLU, 0xabb077c20369fda4LLU,
    0x51ad35faf37ecf08LLU, 0x35542bb4def4d3e8LLU, 0x2938b5dc2320bbeeLLU, 0x2f0d56eff355be66LLU,
    0x71e6ffc8d538020dLLU, 0x7491686530c8a9d9LLU, 0x140c07bc7e354e35LLU, 0x2b16a96434be6f80LLU,
    0x599ce032a90d5d8dLLU, 0x5016f7fbab239546LLU, 0xc8608b73bda86f09LLU, 0xda5a7b81aa2985e2LLU,
    0x1554f41422e36bc8LLU, 0x582321048eeebe93LLU, 0xa7bd82fc75bd77a9LLU, 0xed8a03ab5b3797cbLLU,
    0xfa51b74f1a334002LLU, 0x183185a5f98d5c1fLLU, 0x2a0f6013af5a6a69LLU, 0xe6291d40fa95ddecLLU,
    0x20f829d48fe0ececLLU, 0xf269f4386801c83dLLU, 0x00b270fcc8519b7fLLU, 0x09deecbb4cdf4aecLLU,
    0xc90562ae20624b24LLU, 0x21ab7975e75d8f15LLU, 0xb055b46cf4ced6b2LLU, 0xa1578c0d4c085d24LLU,
    0x1326577ae5d9eb62LLU, 0x47eaa66b580a9a21LLU, 0xe11f074905543e1cLLU, 0x4b7186fdbde2f96aLLU,
    0x45423c982489f6dcLLU, 0x917ae11892e3a8bfLLU, 0x4a0a1f115942f3baLLU, 0x204442768b9d8864LLU,
    0x5dd4934800ebd2d6LLU, 0x6543dbd6329d1fdeLLU, 0x1f53d08c84a530b5LLU, 0x8ff9de158378765fLLU,
    0x30bd2cba0ec441f1LLU, 0x6563e80220f13233LLU, 0x8173c53a0527a72bLLU, 0x34a3140ff7cadba3LLU,
    0xd2f5a4f0f2d08610LLU, 0x08cee59c078e13c7LLU, 0x5ce0e2a10a907f2fLLU, 0x785a64a25f87f91dLLU,
    0x229d60e0efc9535fLLU, 0x9cc43ecac3a11477LLU, 0x8ab19f6cd6522e51LLU, 0x9f3e53f15326a440LLU,
    0x74b6059e1dfcb30fLLU, 0x3ae5f2dc25496335LLU, 0x7e7a08ca4139f07eLLU, 0xe6779a67e4e921bbLLU,
    0x11f26767c5cc63b0LLU, 0x049f543186d1882dLLU, 0xdacc7e65e2346e13LLU, 0xf8168f3613f11361LLU,
    0x91d2b501ca1e072aLLU, 0xa56d34964af41349LLU, 0x70d7734b61ed25edLLU, 0x5621c6295167fd58LLU,
    0xc4b9d15b328536b2LLU, 0x9c10c3cf041a0c6bLLU, 0x5b01dcb740b2933bLLU, 0x42d3eb529448f46aLLU,
    0x8cf1918b7035cdc7LLU, 0x8f816563e12cbf49LLU, 0x5119e73727e35fecLLU, 0xc7261ac8d91f1b6bLLU, 0};

uint8_t key[16] = {0,1,2,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd,0xe,0xf};
uint8_t plaintext[64];

void siphash24(const uint8_t *src, uint32_t src_sz,
               uint8_t *out, int hsize, const uint8_t key[16]) {
    siphash_ctx ctx;
    sip_hmac_setkey(&ctx, key, hsize);
    while(src_sz--) sip_hmac_put(&ctx, *src++);
    int n = sip_hmac_final(&ctx, out);
    if (n != hsize) printf("Size error\n");
}

void makeTestVectors(int sets) { // it's a little like cheating, but...
	int i;
	for (i=0; i<64; i++) plaintext[i] = i;
	for (int set=0; set<sets; set++) {
        printf("uint64_t sip_vectors%d[%d] = {", set, set*64+65);
        for (int i=0; i<64; i++) {
            if ((i % (4 / (set+1))) == 0) {
                printf("\n    ");
            }
            uint8_t t[64]; memset(t, 0, 64);
            siphash24(plaintext, i, t, set*8+8, key);
            printf("0x");       // first 64-bit word of hash
            for (int k=7; k>=0; k--) printf("%02x", t[k]);
            printf("LLU, ");
            if (set) {
                printf("0x");   // second word if "big"
                for (int k=15; k>=8; k--) printf("%02x", t[k]);
                printf("LLU, ");
            }
        }
        printf("0};\n\n");
	}
}

int check_sip0(void) {
	int i;
	for (i=0; i<64; i++) plaintext[i] = i;
    uint64_t t[1];

    // hash the same plaintext with 0 to 63 lengths
    for (i=0; i<64; i++) {
        siphash24(plaintext, i, (uint8_t *)&t[0], 8, key);
        if (t[0] != sip_vectors0[i]) return 1;
    }
	return 0;
}

int check_sip1(void) {
	int i;
	for (i=0; i<64; i++) plaintext[i] = i;
    uint64_t t[2];
    // hash the same plaintext with 0 to 63 lengths
    for (i=0; i<64; i++) {
        siphash24(plaintext, i, (uint8_t *)&t[0], 16, key);
        if (t[0] != sip_vectors1[i*2]) return 2;
        if (t[1] != sip_vectors1[i*2+1]) return 4;
    }
	return 0;
}

int main(void){
//  makeTestVectors(2);
    int r = check_sip0() | check_sip1();
    if(r == 0){
        printf("Cryptographic tests passed\n");
    } else {
        printf("Cryptographic tests failed!\n");
    }

    return r;
}
