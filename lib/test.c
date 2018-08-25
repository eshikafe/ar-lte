#include <stdio.h>
#include <stdint.h>

void liblte_value_2_bits(uint32_t   value,
                         uint8_t  **bits,
                         uint32_t   N_bits)
{
    uint32_t i;

    for(i=0; i<N_bits; i++)
    {
        (*bits)[i] = (value >> (N_bits-i-1)) & 0x1;
    }
    *bits += N_bits;
}

int main()
{
	uint8_t *b;
	
	liblte_value_2_bits(5, &b, 2);

	printf("bits: %x", b[1]);

	return 0;


}