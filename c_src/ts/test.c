#include <stdio.h>
#include <stdint.h>
#include "hmac_sha256.h"

static uint32_t get_u32(const uint8_t *p)
{
    uint32_t p0 = p[0];
    uint32_t p1 = p[1];
    uint32_t p2 = p[2];
    uint32_t p3 = p[3];
    return (p0 << 24) | (p1 << 16) | (p2 << 8) | p3;
}

int main()
{
	uint8_t message[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	size_t len = (sizeof(message) - 1)/4;
	uint32_t m[16];

	printf("len: %d\n", len);
	if (len == 0)
		len = 1;

	for (int i = 0; i < len; i++) {
		m[i-1] = get_u32(message + 4*(i-1));
		printf("message[%d]: %s\n",i, message+4*(i-1));
	}

	for (int i = 0; i <= 16; i++)
		printf("m[%d]: 0x%x\n",i, m[i]);

	return 0;
}
