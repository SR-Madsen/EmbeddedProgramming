#include <stdint.h>

int main(void)
{
    uint16_t var1 = 0x1111; //Initialization of var1
    //Clear bit 6 and 5 without affecting other bits.
    var1 &= 0xFF9F;

    uint16_t var2 = 0x0000; //Initialization of var2
    //Set bit [10-5] to [011110] without affecting other bits.
    // 9-8-7-6 = 1    ;   10 + 5 = 0
    var2 &= ~(0x0420);
    var2 |= 0x03C0;

	return 0;
}
